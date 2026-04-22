/**
 * @file main.rs
 * @brief Atividade Integradora 33: Auditoria Forense em Relacionamentos N:N.
 * 
 * Aprendizados: Tratamento de Nulls (Option), Chaves Estrangeiras, Auditoria.
 * 
 * @author SENAI - Arquiteto de Sistemas
 * @date 21/04/2026
 */

use rusqlite::{params, Connection, Result};
use std::io::{self, Write};

// -----------------------------------------------------------------------------
// UI UTILITIES
// -----------------------------------------------------------------------------

fn pedir_input(label: &str) -> String {
    print!("{}", label);
    io::stdout().flush().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Falha ao ler");
    input.trim().to_string()
}

fn inicializar_sistema_completo(conn: &Connection) -> Result<()> {
    // ATIVAÇÃO DE CHAVES ESTRANGEIRAS: Crucial para evitar IDs inválidos
    conn.execute("PRAGMA foreign_keys = ON;", [])?;

    conn.execute_batch("
        CREATE TABLE IF NOT EXISTS pilotos (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nome TEXT NOT NULL
        );
        CREATE TABLE IF NOT EXISTS drones (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            modelo TEXT NOT NULL UNIQUE
        );
        CREATE TABLE IF NOT EXISTS habilitacoes (
            piloto_id INTEGER,
            drone_id INTEGER,
            PRIMARY KEY (piloto_id, drone_id),
            FOREIGN KEY (piloto_id) REFERENCES pilotos(id) ON DELETE CASCADE,
            FOREIGN KEY (drone_id) REFERENCES drones(id) ON DELETE CASCADE
        );
        CREATE TABLE IF NOT EXISTS historico_certificacoes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            piloto_nome TEXT,
            drone_modelo TEXT,
            data_certificacao TEXT DEFAULT CURRENT_TIMESTAMP
        );
    ")?;

    // Criando o Gatilho de Auditoria
    conn.execute("
        CREATE TRIGGER IF NOT EXISTS trg_audit_habilitacao
        AFTER INSERT ON habilitacoes
        BEGIN
            INSERT INTO historico_certificacoes (piloto_nome, drone_modelo)
            SELECT 
                (SELECT nome FROM pilotos WHERE id = NEW.piloto_id),
                (SELECT modelo FROM drones WHERE id = NEW.drone_id);
        END;
    ", [])?;

    // Populando dados iniciais
    conn.execute("INSERT OR IGNORE INTO drones (modelo) VALUES ('X-10'), ('B-22')", [])?;
    
    let count: i32 = conn.query_row("SELECT COUNT(*) FROM pilotos", [], |r| r.get(0))?;
    if count == 0 {
        conn.execute("INSERT INTO pilotos (nome) VALUES ('Piloto Alpha')", [])?;
    }

    println!("\x1b[32m[SISTEMA]:\x1b[0m Infraestrutura e Auditoria prontas para uso.");
    Ok(())
}

// -----------------------------------------------------------------------------
// OPERAÇÕES
// -----------------------------------------------------------------------------

fn vincular_e_auditar(conn: &Connection) -> Result<()> {
    println!("\n--- NOVO VÍNCULO DE HABILITAÇÃO ---");
    let piloto_id = pedir_input("ID do Piloto: ");
    let drone_id = pedir_input("ID do Drone: ");

    // O uso de Chaves Estrangeiras agora vai barrar IDs inexistentes automaticamente
    match conn.execute(
        "INSERT INTO habilitacoes (piloto_id, drone_id) VALUES (?, ?)",
        params![piloto_id, drone_id],
    ) {
        Ok(_) => println!("\x1b[32m[SUCESSO]: Vínculo criado e auditado.\x1b[0m"),
        Err(e) => println!("\x1b[31m[ERRO DE INTEGRIDADE]: ID inválido ou já existente. ({})\x1b[0m", e),
    }
    Ok(())
}

fn ver_timeline(conn: &Connection) -> Result<()> {
    let mut stmt = conn.prepare("SELECT id, piloto_nome, drone_modelo, data_certificacao FROM historico_certificacoes ORDER BY data_certificacao DESC")?;
    
    // MUDANÇA SENIOR: Usamos Option<String> para lidar com possíveis NULLs sem crashar o programa
    let logs = stmt.query_map([], |row| {
        let id: i32 = row.get(0)?;
        let p_nome: Option<String> = row.get(1)?;
        let d_modelo: Option<String> = row.get(2)?;
        let data: String = row.get(3)?;

        let nome = p_nome.unwrap_or_else(|| "DESCONHECIDO".to_string());
        let modelo = d_modelo.unwrap_or_else(|| "NÃO ENCONTRADO".to_string());

        Ok(format!("[ID:{}] {} habilitado para o drone {} em: {}", id, nome, modelo, data))
    })?;

    println!("\n\x1b[33m--- TIMELINE DE CERTIFICAÇÕES (AUDITORIA) ---\x1b[0m");
    for log in logs { println!("{}", log?); }
    Ok(())
}

fn main() -> Result<()> {
    let conn = Connection::open("integracao-rust-sql/32-relacionamento-muitos-para-muitos/certificacoes.db")?;
    inicializar_sistema_completo(&conn)?;

    loop {
        println!("\n\x1b[34m=== GESTOR DE CERTIFICAÇÃO PRO (v2.1) ===\x1b[0m");
        println!("1. Listar Timeline de Auditoria");
        println!("2. Vincular Piloto a Drone");
        println!("0. Sair");
        
        let opcao = pedir_input("Escolha: ");

        match opcao.as_str() {
            "1" => ver_timeline(&conn)?,
            "2" => vincular_e_auditar(&conn)?,
            "0" => break,
            _ => println!("Opção inválida."),
        }
    }

    Ok(())
}

/**
 * @file main.rs
 * @brief Atividade Integradora 32: Relacionamentos Muitos-para-Muitos.
 * 
 * Aprendizados: Join Tables, Mapeamento N:N, SQL Relacional Avançado.
 * 
 * @author SENAI - Arquiteto de Sistemas
 * @date 21/04/2026
 */

use rusqlite::{params, Connection, Result};
use std::io::{self, Write};

/// Modelo de um Piloto.
#[derive(Debug)]
struct Piloto {
    id: i32,
    nome: String,
    habilitacoes: Vec<String>, // Lista de modelos de drones que ele voa
}

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

fn inicializar_banco(conn: &Connection) -> Result<()> {
    conn.execute_batch("
        -- 1. Tabela de Pilotos
        CREATE TABLE IF NOT EXISTS pilotos (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nome TEXT NOT NULL
        );
        -- 2. Tabela de Drones
        CREATE TABLE IF NOT EXISTS drones (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            modelo TEXT NOT NULL UNIQUE
        );
        -- 3. Tabela de Ligação (Muitos-para-Muitos)
        CREATE TABLE IF NOT EXISTS habilitacoes (
            piloto_id INTEGER,
            drone_id INTEGER,
            PRIMARY KEY (piloto_id, drone_id),
            FOREIGN KEY (piloto_id) REFERENCES pilotos(id) ON DELETE CASCADE,
            FOREIGN KEY (drone_id) REFERENCES drones(id) ON DELETE CASCADE
        );
    ")?;

    // Inserindo alguns drones base se não existirem
    conn.execute("INSERT OR IGNORE INTO drones (modelo) VALUES ('X-10'), ('B-22'), ('AGRO-01')", [])?;
    Ok(())
}

// -----------------------------------------------------------------------------
// OPERAÇÕES
// -----------------------------------------------------------------------------

fn cadastrar_piloto(conn: &Connection) -> Result<()> {
    let nome = pedir_input("Nome do Piloto: ");
    conn.execute("INSERT INTO pilotos (nome) VALUES (?)", params![nome])?;
    println!("\x1b[32m[OK]: Piloto cadastrado.\x1b[0m");
    Ok(())
}

fn vincular_habilitacao(conn: &Connection) -> Result<()> {
    println!("\n--- VINCULAR HABILITAÇÃO ---");
    let piloto_id = pedir_input("ID do Piloto: ");
    
    // Lista drones disponíveis
    let mut stmt = conn.prepare("SELECT id, modelo FROM drones")?;
    let drone_rows = stmt.query_map([], |row| Ok((row.get::<_, i32>(0)?, row.get::<_, String>(1)?)))?;
    println!("Drones Disponíveis:");
    for d in drone_rows { let (id, modl) = d?; println!("  [{}] {}", id, modl); }

    let drone_id = pedir_input("ID do Drone a habilitar: ");

    match conn.execute(
        "INSERT INTO habilitacoes (piloto_id, drone_id) VALUES (?, ?)",
        params![piloto_id, drone_id],
    ) {
        Ok(_) => println!("\x1b[32m[SUCESSO]: Piloto habilitado para este modelo.\x1b[0m"),
        Err(e) => println!("\x1b[31m[ERRO]: Já habilitado ou ID inválido. ({})\x1b[0m", e),
    }
    Ok(())
}

fn listar_equipe_completa(conn: &Connection) -> Result<()> {
    // 1. Buscamos todos os pilotos
    let mut stmt_pilotos = conn.prepare("SELECT id, nome FROM pilotos")?;
    let pilotos_iter = stmt_pilotos.query_map([], |row| {
        let id: i32 = row.get(0)?;
        let nome: String = row.get(1)?;
        
        // 2. Para cada piloto, buscamos suas habilitações em outra query (JOIN)
        let mut stmt_hab = conn.prepare("
            SELECT d.modelo 
            FROM drones d
            JOIN habilitacoes h ON d.id = h.drone_id
            WHERE h.piloto_id = ?
        ")?;
        
        let hab_iter = stmt_hab.query_map(params![id], |r| r.get::<_, String>(0))?;
        let mut lista_hab = Vec::new();
        for h in hab_iter { lista_hab.push(h?); }

        Ok(Piloto { id, nome, habilitacoes: lista_hab })
    })?;

    println!("\n\x1b[36m--- QUADRO DE PILOTOS E HABILITAÇÕES ---\x1b[0m");
    for p in pilotos_iter {
        let p = p?;
        let habs = if p.habilitacoes.is_empty() { 
            "Nenhuma".to_string() 
        } else { 
            p.habilitacoes.join(", ") 
        };
        println!("[#{}] {:<15} | Aptidão: {}", p.id, p.nome, habs);
    }
    println!("--------------------------------------------------");
    Ok(())
}

fn main() -> Result<()> {
    let conn = Connection::open("certificacoes.db")?;
    inicializar_banco(&conn)?;

    loop {
        println!("\n\x1b[34m=== SISTEMA DE CERTIFICAÇÃO SKYCARGO ===\x1b[0m");
        println!("1. Listar Pilotos e Habilitações (N:N)");
        println!("2. Cadastrar Novo Piloto");
        println!("3. Habilitar Piloto para Drone");
        println!("0. Sair");
        
        let opcao = pedir_input("Escolha: ");

        match opcao.as_str() {
            "1" => listar_equipe_completa(&conn)?,
            "2" => cadastrar_piloto(&conn)?,
            "3" => vincular_habilitacao(&conn)?,
            "0" => break,
            _ => println!("Opção inválida."),
        }
    }

    Ok(())
}

/* 
    ===============================================================
    RESUMO TEÓRICO: RELACIONAMENTOS N:N NO BACKEND
    ===============================================================

    1. A TABELA DE LIGAÇÃO (JOIN TABLE):
       - É a única forma de representar que "Muitos" se ligam a 
         "Muitos". Ela armazena apenas as chaves primárias dos dois 
         lados.

    2. MAPEAMENTO DE LISTAS:
       - No Rust, representamos isso com um 'Vec<T>' dentro da struct. 
       - Isso exige uma "Nested Query" (uma consulta dentro do mapeamento 
         da outra), demonstrando como consolidar dados relacionais em 
         objetos de memória.

    3. INTEGRIDADE EM CASCATA:
       - Usamos 'ON DELETE CASCADE' na tabela de ligação. Se um piloto 
         for demitido (deletado), suas habilitações somem sozinhas, 
         evitando lixo no banco.

    VANTAGEM DIDÁTICA: 
    O aluno domina o cenário mais complexo do SQL e aprende a orquestrar 
    múltiplas consultas para montar um objeto de negócio completo.
    ===============================================================
*/

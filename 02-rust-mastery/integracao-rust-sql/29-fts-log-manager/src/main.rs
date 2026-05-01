const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Atividade Integradora 29: CRUD com Motor de Busca FTS5.
 *
 * Aprendizados: Busca textual de alta performance, CRUD em tabelas virtuais.
 *
 * @author SENAI - Master Orchestrator
 * @date 21/04/2026
 */
use rusqlite::{Connection, Result, params};
use std::io::{self, Write};

#[derive(Debug)]
struct Incidente {
    rowid: i64, // FTS5 usa rowid como identificador único padrão
    drone_id: String,
    descricao: String,
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
    // Criamos a tabela virtual FTS5. Note que ela suporta rowid automaticamente.
    conn.execute(
        "CREATE VIRTUAL TABLE IF NOT EXISTS logs_incidentes USING fts5(
            drone_id,
            descricao
        )",
        [],
    )?;
    Ok(())
}

// -----------------------------------------------------------------------------
// CRUD OPERATIONS
// -----------------------------------------------------------------------------

/// CREATE: Registrar novo incidente
fn registrar_incidente(conn: &Connection) -> Result<()> {
    println!("\n\x1b[33m[NOVO INCIDENTE]:\x1b[0m");
    let drone = pedir_input("ID do Drone: ");
    let desc = pedir_input("Relatório do Piloto (Texto Livre): ");

    conn.execute(
        "INSERT INTO logs_incidentes (drone_id, descricao) VALUES (?, ?)",
        params![drone, desc],
    )?;

    println!("\x1b[32m[SUCESSO]: Relatório indexado pelo motor de busca.\x1b[0m");
    Ok(())
}

/// READ (SEARCH): Buscar usando o poder do FTS5
fn buscar_incidentes(conn: &Connection) -> Result<()> {
    println!("\n\x1b[35m[BUSCA INTELIGENTE]:\x1b[0m");
    let termo = pedir_input("Palavra-chave (ex: motor, bateria): ");

    // O operador MATCH é o segredo da velocidade aqui.
    let mut stmt = conn.prepare(
        "
        SELECT rowid, drone_id, descricao 
        FROM logs_incidentes 
        WHERE logs_incidentes MATCH ?
        ORDER BY rank
    ",
    )?;

    let incidentes_iter = stmt.query_map(params![termo], |row| {
        Ok(Incidente {
            rowid: row.get(0)?,
            drone_id: row.get(1)?,
            descricao: row.get(2)?,
        })
    })?;

    println!("\nResultados para '{}':", termo);
    println!("---------------------------------------------------------------");
    for item in incidentes_iter {
        let i = item?;
        println!(
            "ID: {:<4} | Drone: {:<10} | Relato: {}",
            i.rowid, i.drone_id, i.descricao
        );
    }
    println!("---------------------------------------------------------------");
    Ok(())
}

/// READ (ALL): Listar tudo
fn listar_todos(conn: &Connection) -> Result<()> {
    let mut stmt = conn.prepare("SELECT rowid, drone_id, descricao FROM logs_incidentes")?;
    let logs = stmt.query_map([], |row| {
        Ok(Incidente {
            rowid: row.get(0)?,
            drone_id: row.get(1)?,
            descricao: row.get(2)?,
        })
    })?;

    println!("\n\x1b[36m--- BASE DE DADOS COMPLETA ---\x1b[0m");
    for log in logs {
        let l = log?;
        println!("[#{}] Drone {}: {}", l.rowid, l.drone_id, l.descricao);
    }
    Ok(())
}

/// UPDATE: Editar um relatório existente
fn editar_incidente(conn: &Connection) -> Result<()> {
    let id = pedir_input("ID do registro a editar: ");
    let nova_desc = pedir_input("Novo texto do relatório: ");

    let rows = conn.execute(
        "UPDATE logs_incidentes SET descricao = ? WHERE rowid = ?",
        params![nova_desc, id],
    )?;

    if rows > 0 {
        println!("\x1b[32m[SUCESSO]: Registro atualizado no índice.\x1b[0m");
    } else {
        println!("\x1b[31m[ERRO]: ID não encontrado.\x1b[0m");
    }
    Ok(())
}

/// DELETE: Remover um registro
fn excluir_incidente(conn: &Connection) -> Result<()> {
    let id = pedir_input("ID do registro a EXCLUIR: ");
    let rows = conn.execute("DELETE FROM logs_incidentes WHERE rowid = ?", params![id])?;

    if rows > 0 {
        println!("\x1b[32m[SUCESSO]: Registro removido permanentemente.\x1b[0m");
    } else {
        println!("\x1b[31m[ERRO]: ID não encontrado.\x1b[0m");
    }
    Ok(())
}

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------

fn main() -> Result<()> {
    let conn = Connection::open("incidentes_pro.db")?;
    inicializar_banco(&conn)?;

    loop {
        println!("\n\x1b[34m=== GESTOR DE INCIDENTES (CRUD + FTS5) ===\x1b[0m");
        println!("1. Registrar Incidente (CREATE)");
        println!("2. Buscar por Palavra-Chave (READ/SEARCH)");
        println!("3. Listar Tudo (READ)");
        println!("4. Editar Relatório (UPDATE)");
        println!("5. Remover Relatório (DELETE)");
        println!("0. Sair");

        let opcao = pedir_input("Escolha: ");

        match opcao.as_str() {
            "1" => registrar_incidente(&conn)?,
            "2" => buscar_incidentes(&conn)?,
            "3" => listar_todos(&conn)?,
            "4" => editar_incidente(&conn)?,
            "5" => excluir_incidente(&conn)?,
            "0" => break,
            _ => println!("Opção inválida."),
        }
    }

    Ok(())
}

/* @section MemoryMap
 * Stack: Tipos fixos.
 * Heap: Alocações dinâmicas (Box, Vec).
 */
/*
 * RESUMO TEÓRICO
 * Implementação em Rust seguindo as diretrizes de segurança e performance.
 */

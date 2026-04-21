/**
 * @file main.rs
 * @brief Atividade Integradora 28: CRUD Completo Rust-SQL.
 *
 * Operações: CREATE, READ, UPDATE, DELETE.
 *
 * @author SENAI - Rust/SQL Master
 * @date 21/04/2026
 */
use rusqlite::{Connection, Result, params};
use std::io::{self, Write};

#[derive(Debug)]
struct Drone {
    id: i32,
    serial: String,
    modelo: String,
    status: String,
}

// -----------------------------------------------------------------------------
// FUNÇÕES DE APOIO (UI)
// -----------------------------------------------------------------------------

fn pedir_input(label: &str) -> String {
    print!("{}", label);
    io::stdout().flush().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Falha ao ler");
    input.trim().to_string()
}

fn inicializar_banco(conn: &Connection) -> Result<()> {
    conn.execute(
        "CREATE TABLE IF NOT EXISTS drones (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            serial TEXT UNIQUE NOT NULL,
            modelo TEXT NOT NULL,
            status TEXT NOT NULL
        )",
        [],
    )?;
    Ok(())
}

// -----------------------------------------------------------------------------
// OPERAÇÕES CRUD
// -----------------------------------------------------------------------------

/// READ: Listar todos os drones
fn listar_drones(conn: &Connection) -> Result<()> {
    let mut stmt = conn.prepare("SELECT id, serial, modelo, status FROM drones")?;
    let drones_iter = stmt.query_map([], |row| {
        Ok(Drone {
            id: row.get(0)?,
            serial: row.get(1)?,
            modelo: row.get(2)?,
            status: row.get(3)?,
        })
    })?;

    println!("\n\x1b[36m--- LISTAGEM DE FROTA ---\x1b[0m");
    println!(
        "{:<5} | {:<15} | {:<15} | {:<10}",
        "ID", "SERIAL", "MODELO", "STATUS"
    );
    println!("---------------------------------------------------------------");

    let mut cont = 0;
    for drone in drones_iter {
        let d = drone?;
        println!(
            "{:<5} | {:<15} | {:<15} | {:<10}",
            d.id, d.serial, d.modelo, d.status
        );
        cont += 1;
    }

    if cont == 0 {
        println!("(Nenhum drone cadastrado)");
    }
    println!("---------------------------------------------------------------");
    Ok(())
}

/// CREATE: Cadastrar novo drone
fn cadastrar_drone(conn: &Connection) -> Result<()> {
    println!("\n\x1b[33m[CADASTRO]:\x1b[0m");
    let serial = pedir_input("Número de Serial: ");
    let modelo = pedir_input("Modelo do Drone: ");
    let status = String::from("PRONTO");

    match conn.execute(
        "INSERT INTO drones (serial, modelo, status) VALUES (?, ?, ?)",
        params![serial, modelo, status],
    ) {
        Ok(_) => println!("\x1b[32m[SUCESSO]: Drone registrado!\x1b[0m"),
        Err(e) => println!(
            "\x1b[31m[ERRO]: Falha ao registrar (Serial possivelmente duplicado). Detalhe: {}\x1b[0m",
            e
        ),
    }
    Ok(())
}

/// UPDATE: Atualizar status do drone
fn atualizar_status(conn: &Connection) -> Result<()> {
    let id = pedir_input("ID do drone a atualizar: ");
    let novo_status = pedir_input("Novo status (ex: MANUTENÇÃO, VOO, PRONTO): ");

    let rows = conn.execute(
        "UPDATE drones SET status = ? WHERE id = ?",
        params![novo_status, id],
    )?;

    if rows > 0 {
        println!("\x1b[32m[SUCESSO]: Status atualizado.\x1b[0m");
    } else {
        println!("\x1b[31m[AVISO]: ID não encontrado.\x1b[0m");
    }
    Ok(())
}

/// DELETE: Remover drone da frota
fn remover_drone(conn: &Connection) -> Result<()> {
    let id = pedir_input("ID do drone a REMOVER: ");
    println!(
        "\x1b[31mATENÇÃO: Deseja realmente remover o drone ID {}? (s/n)\x1b[0m",
        id
    );
    let confirma = pedir_input(">> ");

    if confirma.to_lowercase() == "s" {
        let rows = conn.execute("DELETE FROM drones WHERE id = ?", params![id])?;
        if rows > 0 {
            println!("\x1b[32m[SUCESSO]: Drone removido da base.\x1b[0m");
        } else {
            println!("\x1b[31m[ERRO]: ID não encontrado.\x1b[0m");
        }
    }
    Ok(())
}

fn main() -> Result<()> {
    let conn = Connection::open("frota_pro.db")?;
    inicializar_banco(&conn)?;

    loop {
        println!("\n\x1b[34m=== GESTOR DE FROTA SKYCARGO (CRUD) ===\x1b[0m");
        println!("1. Listar Frota (READ)");
        println!("2. Cadastrar Drone (CREATE)");
        println!("3. Atualizar Status (UPDATE)");
        println!("4. Remover Drone (DELETE)");
        println!("0. Sair");

        let opcao = pedir_input("Escolha: ");

        match opcao.as_str() {
            "1" => listar_drones(&conn)?,
            "2" => cadastrar_drone(&conn)?,
            "3" => atualizar_status(&conn)?,
            "4" => remover_drone(&conn)?,
            "0" => break,
            _ => println!("Opção inválida."),
        }
    }

    println!("Sistema encerrado.");
    Ok(())
}

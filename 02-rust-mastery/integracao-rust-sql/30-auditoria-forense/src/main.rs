const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Atividade Integradora 30: Auditoria Forense com Triggers.
 * 
 * Aprendizados: Shadow Tables, Auditoria Automática, Integração Rust-Trigger.
 * 
 * @author SENAI - Master Orchestrator
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

fn inicializar_banco(conn: &Connection) -> Result<()> {
    // 1. Criando Tabelas
    conn.execute_batch("
        CREATE TABLE IF NOT EXISTS drone_configs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            serial TEXT UNIQUE NOT NULL,
            firmware TEXT NOT NULL
        );
        CREATE TABLE IF NOT EXISTS caixa_preta_logs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            drone_id INTEGER,
            campo TEXT,
            valor_antigo TEXT,
            valor_novo TEXT,
            data_hora TEXT DEFAULT CURRENT_TIMESTAMP
        );
    ")?;

    // 2. Criando o Gatilho de Auditoria (O Segredo da Fortress)
    conn.execute("
        CREATE TRIGGER IF NOT EXISTS trg_audit_drone
        AFTER UPDATE OF firmware ON drone_configs
        BEGIN
            INSERT INTO caixa_preta_logs (drone_id, campo, valor_antigo, valor_novo)
            VALUES (OLD.id, 'firmware', OLD.firmware, NEW.firmware);
        END;
    ", [])?;

    // Populando drone inicial se não existir
    conn.execute("INSERT OR IGNORE INTO drone_configs (serial, firmware) VALUES ('ALPHA-X', 'v1.0.0')", [])?;
    
    Ok(())
}

// -----------------------------------------------------------------------------
// OPERAÇÕES
// -----------------------------------------------------------------------------

fn mostrar_configuracao(conn: &Connection) -> Result<()> {
    let mut stmt = conn.prepare("SELECT id, serial, firmware FROM drone_configs")?;
    let rows = stmt.query_map([], |row| {
        Ok(format!("ID: {} | Serial: {} | Firmware: {}", 
            row.get::<_, i32>(0)?, row.get::<_, String>(1)?, row.get::<_, String>(2)?))
    })?;

    println!("\n\x1b[36m--- CONFIGURAÇÃO ATUAL ---\x1b[0m");
    for r in rows { println!("{}", r?); }
    Ok(())
}

fn atualizar_firmware(conn: &Connection) -> Result<()> {
    let serial = pedir_input("Digite o Serial do Drone: ");
    let nova_versao = pedir_input("Nova versão do Firmware: ");

    // O Rust apenas faz o UPDATE. O log de auditoria acontece "sozinho" no SQL.
    let rows = conn.execute(
        "UPDATE drone_configs SET firmware = ? WHERE serial = ?",
        params![nova_versao, serial],
    )?;

    if rows > 0 {
        println!("\x1b[32m[SUCESSO]: Firmware atualizado. Auditoria registrada no banco.\x1b[0m");
    } else {
        println!("\x1b[31m[ERRO]: Drone não encontrado.\x1b[0m");
    }
    Ok(())
}

fn ver_caixa_preta(conn: &Connection) -> Result<()> {
    let mut stmt = conn.prepare("
        SELECT l.id, d.serial, l.valor_antigo, l.valor_novo, l.data_hora 
        FROM caixa_preta_logs l
        JOIN drone_configs d ON l.drone_id = d.id
        ORDER BY l.data_hora DESC
    ")?;

    let logs = stmt.query_map([], |row| {
        Ok(format!("[LOG #{}] Drone: {} | Mudou de: {} | Para: {} | Em: {}", 
            row.get::<_, i32>(0)?, row.get::<_, String>(1)?, row.get::<_, String>(2)?, 
            row.get::<_, String>(3)?, row.get::<_, String>(4)?))
    })?;

    println!("\n\x1b[33m--- CAIXA PRETA: REGISTROS DE AUDITORIA ---\x1b[0m");
    for log in logs { println!("{}", log?); }
    Ok(())
}

fn main() -> Result<()> {
    let conn = Connection::open("seguranca_forense.db")?;
    inicializar_banco(&conn)?;

    loop {
        println!("\n\x1b[34m=== GESTOR DE SEGURANÇA SKYCARGO ===\x1b[0m");
        println!("1. Ver Configuração Atual (READ)");
        println!("2. Atualizar Firmware (UPDATE + AUDIT)");
        println!("3. Ver Caixa Preta (AUDIT LOGS)");
        println!("0. Sair");
        
        let opcao = pedir_input("Escolha: ");

        match opcao.as_str() {
            "1" => mostrar_configuracao(&conn)?,
            "2" => atualizar_firmware(&conn)?,
            "3" => ver_caixa_preta(&conn)?,
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

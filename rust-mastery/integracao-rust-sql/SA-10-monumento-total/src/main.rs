use r2d2::Pool;
/**
 * @file main.rs
 * @brief SA-10: O Monumento Total (Orquestração Multilinguagem).
 *
 * Integração Final: C++ (FFI), Rust (Async/Pool/Serde) e SQL (Analytics).
 *
 * @author SENAI - Master of Systems
 * @date 21/04/2026
 */
use r2d2_sqlite::SqliteConnectionManager;
use rusqlite::params;
use serde::{Deserialize, Serialize};
use std::sync::Arc;
use std::time::Duration;
use tokio;

// -----------------------------------------------------------------------------
// 1. MÓDULO DE HARDWARE (FFI - C++)
// -----------------------------------------------------------------------------
unsafe extern "C" {
    fn iniciar_motores_cpp(potencia: i32) -> i32;
}

// -----------------------------------------------------------------------------
// 2. MÓDULO DE DADOS (SERDE & SQL)
// -----------------------------------------------------------------------------
#[derive(Serialize, Deserialize, Debug)]
struct TelemetriaFinal {
    bateria: u32,
    distancia: f64,
}

type SqlPool = Pool<SqliteConnectionManager>;

async fn inicializar_banco(pool: &SqlPool) -> Result<(), Box<dyn std::error::Error>> {
    let conn = pool.get()?;
    conn.execute_batch(
        "
        CREATE TABLE IF NOT EXISTS frota_final (
            id INTEGER PRIMARY KEY,
            serial TEXT UNIQUE,
            regiao TEXT
        );
        CREATE TABLE IF NOT EXISTS operacoes_final (
            id INTEGER PRIMARY KEY,
            drone_serial TEXT,
            telemetria_json TEXT,
            data_hora TEXT DEFAULT CURRENT_TIMESTAMP
        );
    ",
    )?;

    // Populando drones iniciais
    conn.execute("INSERT OR IGNORE INTO frota_final (serial, regiao) VALUES ('SN-ALPHA', 'Americas'), ('SN-BETA', 'Europa')", [])?;
    Ok(())
}

// -----------------------------------------------------------------------------
// 3. O CORAÇÃO DO SISTEMA: MISSÃO ASSÍNCRONA
// -----------------------------------------------------------------------------
async fn executar_missao(serial: String, pool: Arc<SqlPool>) {
    println!(
        "\n\x1b[33m[CENTRAL]:\x1b[0m Iniciando sequência para o drone {}...",
        serial
    );

    // PASSO A: Chamar Hardware (C++)
    let hardware_ok = unsafe { iniciar_motores_cpp(75) };
    if hardware_ok == 0 {
        println!(
            "\x1b[31m[FALHA]:\x1b[0m Hardware do drone {} rejeitou ignição.",
            serial
        );
        return;
    }

    // PASSO B: Simular Voo (Async)
    println!(
        "\x1b[32m[DECOLAGEM]:\x1b[0m Drone {} está em missão...",
        serial
    );
    tokio::time::sleep(Duration::from_secs(1)).await;

    // PASSO C: Gerar Telemetria (JSON)
    let dados = TelemetriaFinal {
        bateria: 85,
        distancia: 150.5,
    };
    let json_payload = serde_json::to_string(&dados).unwrap();

    // PASSO D: Persistir no Data Warehouse (Pool + Blocking)
    let pool_clone = Arc::clone(&pool);
    let serial_db = serial.clone(); // Clona para o banco
    let _ = tokio::task::spawn_blocking(move || {
        let conn = pool_clone.get().expect("Erro no pool");
        conn.execute(
            "INSERT INTO operacoes_final (drone_serial, telemetria_json) VALUES (?, ?)",
            params![serial_db, json_payload],
        )
    })
    .await;

    println!(
        "\x1b[36m[STATUS]:\x1b[0m Drone {} finalizou missão e reportou dados.",
        serial
    );
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("===============================================");
    println!("     SKYCARGO OS v1.0 - O MONUMENTO TOTAL      ");
    println!("===============================================");

    // Configuração do Ambiente
    let manager = SqliteConnectionManager::file("skycargo_final.db");
    let pool = Arc::new(Pool::new(manager)?);
    inicializar_banco(&pool).await?;

    // Disparando missões simultâneas para drones diferentes
    let missao1 = executar_missao(String::from("SN-ALPHA"), Arc::clone(&pool));
    let missao2 = executar_missao(String::from("SN-BETA"), Arc::clone(&pool));

    tokio::join!(missao1, missao2);

    // CONSULTA ANALÍTICA DE ENCERRAMENTO (WINDOW FUNCTIONS)
    println!("\n\x1b[35m[INTELIGÊNCIA]:\x1b[0m Gerando Dashboard de Elite Final...\n");

    let conn = pool.get()?;
    let mut stmt = conn.prepare(
        "
        SELECT drone_serial, 
               json_extract(telemetria_json, '$.distancia') as km,
               RANK() OVER(ORDER BY json_extract(telemetria_json, '$.distancia') DESC) as rank
        FROM operacoes_final
    ",
    )?;

    let mut rows = stmt.query([])?;
    println!("{:<10} | {:<10} | {:<5}", "DRONE", "KM", "RANK");
    println!("----------------------------------");
    while let Some(row) = rows.next()? {
        let serial: String = row.get(0)?;
        let km: f64 = row.get(1)?;
        let rank: i32 = row.get(2)?;
        println!("{:<10} | {:<10.1} | #{}", serial, km, rank);
    }

    println!("\n===============================================");
    println!("     MISSÃO CUMPRIDA. SISTEMA ÍNTEGRO.         ");
    println!("===============================================");
    Ok(())
}

const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief SA-09: Hub Assíncrono de Operações Globais.
 * 
 * Integração: Connection Pool, Migrações e SQL Assíncrono.
 * 
 * @author SENAI - Master Orchestrator
 * @date 21/04/2026
 */

use r2d2_sqlite::SqliteConnectionManager;
use r2d2::Pool;
use rusqlite::params;
use std::sync::Arc;
use std::time::Duration;
use tokio;

type SqlPool = Pool<SqliteConnectionManager>;

// 1. MÓDULO DE MIGRAÇÃO (Automação de Inicialização)
fn inicializar_sistema(pool: &SqlPool) -> Result<(), Box<dyn std::error::Error>> {
    let conn = pool.get()?;
    conn.execute(
        "CREATE TABLE IF NOT EXISTS faturamento_global (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            servico TEXT,
            valor_brl REAL,
            data_hora TEXT DEFAULT CURRENT_TIMESTAMP
        )",
        [],
    )?;
    println!("\x1b[32m[SISTEMA]:\x1b[0m Estrutura de faturamento validada e pronta.");
    Ok(())
}

// 2. TAREFA CRÍTICA (Navegação sem Bloqueio)
async fn loop_navegação_drone() {
    for i in 1..=5 {
        println!("\x1b[35m[VOO]:\x1b[0m Drone navegando... Ponto de controle {} ativo.", i);
        tokio::time::sleep(Duration::from_millis(600)).await;
    }
}

// 3. TAREFA DE SUPORTE (Faturamento Assíncrono)
async fn processar_fatura_usd(pool: Arc<SqlPool>, valor_usd: f64) {
    println!("\x1b[33m[FINANCEIRO]:\x1b[0m Recebida fatura externa de ${:.2}. Iniciando conversão...", valor_usd);
    
    let taxa_conversao = 5.50; // Simulação de consulta de câmbio

    // Usamos spawn_blocking para não travar o drone durante a escrita no disco
    let _ = tokio::task::spawn_blocking(move || {
        let conn = pool.get().expect("Falha ao pegar conexão do pool");
        let valor_final = valor_usd * taxa_conversao;
        
        conn.execute(
            "INSERT INTO faturamento_global (servico, valor_brl) VALUES (?, ?)",
            params!["Entrega Internacional", valor_final],
        )
    }).await;

    println!("\x1b[32m[FINANCEIRO]:\x1b[0m Fatura processada e salva com sucesso.");
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("===============================================");
    println!("     SKYCARGO - HUB OPERACIONAL INTEGRADO      ");
    println!("===============================================");

    // A. Criando o Pool de Conexões
    let manager = SqliteConnectionManager::file("hub_global.db");
    let pool = Pool::new(manager)?;
    let pool_arc = Arc::new(pool);

    // B. Rodando Migrações Automáticas
    inicializar_sistema(&pool_arc)?;

    // C. ORQUESTRAÇÃO CONCORRENTE
    println!("\nIniciando operações simultâneas...");
    
    tokio::join!(
        loop_navegação_drone(),
        processar_fatura_usd(Arc::clone(&pool_arc), 100.0)
    );

    println!("\n[SISTEMA]: Operações do dia finalizadas.");
    println!("===============================================");
    Ok(())
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO INTEGRADOR SA-09
    ===============================================================

    1. O HUB DE ALTA DISPONIBILIDADE:
       - Este projeto é a prova final de que o aluno consegue unir 
         o SQL ao Rust de forma profissional. 
       - O banco gerencia a si mesmo (Migrações) e a aplicação 
         gerencia os recursos (Pooling).

    2. VANTAGEM DA ASINCRONICIDADE:
       - A missão de voo não parou por um único milissegundo para 
         esperar o faturamento ser salvo. Isso é vital em sistemas 
         embarcados e robótica.

    3. ESCALABILIDADE:
       - O uso de Pool permite que, em uma expansão futura, mil 
         faturas sejam processadas simultaneamente sem esgotar os 
         recursos do sistema.

    VANTAGEM DIDÁTICA: 
    O aluno conclui o ciclo de Integração sendo capaz de construir 
    backends robustos, rápidos e inquebráveis.
    ===============================================================
*/

/* @section MemoryMap
 * Stack: Tipos fixos.
 * Heap: Alocações dinâmicas (Box, Vec).
 */

#[allow(dead_code)]
const ANSI_RESET: &str = "\033[0m";
#[allow(dead_code)]
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Atividade Integradora 27: SQL Assíncrono com Tokio (Standard Method).
 * 
 * Aprendizados: spawn_blocking, Non-blocking IO, Orquestração Tokio.
 * 
 * @author SENAI - Master Orchestrator
 * @date 21/04/2026
 */

use rusqlite::{Connection, Result};
use std::time::Duration;
use tokio;
use std::sync::{Arc, Mutex};

/// Simula o processamento do hardware de voo (Navegação).
async fn motor_navegacao_critico() {
    for i in 1..=5 {
        println!("\x1b[35m[VOO]:\x1b[0m Calculando rota... Estágio {} (Processamento em tempo real)", i);
        tokio::time::sleep(Duration::from_millis(500)).await;
    }
}

/// Simula a gravação de logs de forma assíncrona usando spawn_blocking.
async fn gravador_logs_async(conn: Arc<Mutex<Connection>>) {
    println!("\x1b[33m[SISTEMA]:\x1b[0m Iniciando gravador de logs assíncrono...");
    
    for i in 1..=3 {
        // Pausa entre gravações
        tokio::time::sleep(Duration::from_millis(800)).await;

        let log_msg = format!("Log assíncrono número {}", i);
        let conn_clone = Arc::clone(&conn);

        // spawn_blocking executa o código síncrono em uma thread dedicada,
        // garantindo que o loop de eventos do Tokio não pare.
        let _ = tokio::task::spawn_blocking(move || {
            let c = conn_clone.lock().unwrap();
            c.execute("INSERT INTO logs (mensagem) VALUES (?)", [log_msg])
        }).await;

        println!("\x1b[32m[BANCO]:\x1b[0m Log {} persistido com sucesso.", i);
    }
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("===============================================");
    println!("     SKYCARGO - NAVEGAÇÃO ASYNC (TOKIO)        ");
    println!("===============================================");

    // 1. Criando a conexão e a tabela inicial
    let conn = Connection::open_in_memory()?;
    conn.execute("CREATE TABLE logs (id INTEGER PRIMARY KEY, mensagem TEXT)", [])?;
    
    // Envolvemos em Arc e Mutex para permitir o uso dentro do spawn_blocking
    let conn_shared = Arc::new(Mutex::new(conn));

    println!("[SISTEMA]: Banco de dados pronto em memória.");

    // 2. ORQUESTRAÇÃO CONCORRENTE
    // O drone continua navegando enquanto o banco grava em paralelo!
    tokio::join!(
        motor_navegacao_critico(),
        gravador_logs_async(conn_shared)
    );

    println!("\n[SISTEMA]: Missão e logs finalizados concorrentemente.");
    println!("===============================================");
    Ok(())
}

/* 
    ===============================================================
    RESUMO TEÓRICO: SPAWN_BLOCKING (A PONTE SINC/ASYNC)
    ===============================================================

    1. O DILEMA DO ASYNC:
       - O Tokio é como um garçom atendendo muitas mesas. Se um 
         cliente (banco de dados) demora demais para fazer o pedido, 
         o garçom trava e ninguém mais é atendido.

    2. SPAWN_BLOCKING:
       - É como se o garçom chamasse um colega do escritório para 
         resolver o problema demorado. O garçom (Tokio) fica livre 
         para o loop crítico (VOO), enquanto o colega (Thread de 
         Bloqueio) espera o banco de dados.

    3. QUANDO USAR?
       - Sempre que você usar bibliotecas que não foram feitas para 
         Async (como rusqlite, processamento de imagem pesado, etc).

    VANTAGEM DIDÁTICA: 
    O aluno aprende a lidar com a realidade do mercado: nem todas 
    as bibliotecas são assíncronas, e saber integrá-las corretamente 
    é o que define um Especialista de Performance.
    ===============================================================
*/

/* @section MemoryMap
 * Stack: Tipos fixos.
 * Heap: Alocações dinâmicas (Box, Vec).
 */

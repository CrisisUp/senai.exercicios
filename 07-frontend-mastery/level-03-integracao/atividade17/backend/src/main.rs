const ANSI_RESET: &str = "\033[0m";
//! @date 2026
/**
 * @file main.rs
 * @brief Servidor Industrial de Telemetria (Axum + CORS).
 * @author Engenheiro de Elite
 */

use axum::{
    routing::get,
    Json,
    Router,
    http::{Method, HeaderValue},
};
use serde::{Serialize, Deserialize};
use tower_http::cors::CorsLayer;
use chrono::{DateTime, Utc};
use std::net::SocketAddr;

#[derive(Serialize, Deserialize, Debug)]
struct Telemetria {
    id: String,
    modelo: String,
    status: String,
    altitude: f64,
    timestamp: DateTime<Utc>,
}

#[tokio::main]
async fn main() {
    println!("\x1b[1;36m=== NEXUS API: SERVIDOR DE TELEMETRIA v2.0 ===\x1b[0m");

    // 1. Configuração do Middleware de CORS (A Ponte de Segurança)
    // Permite apenas o nosso frontend (localhost:5173)
    let cors = CorsLayer::new()
        .allow_origin("http://localhost:5173".parse::<HeaderValue>().unwrap())
        .allow_methods([Method::GET, Method::POST]);

    // 2. Definição das Rotas
    let app = Router::new()
        .route("/api/telemetria", get(obter_telemetria))
        .layer(cors);

    // 3. Inicialização do Servidor
    let addr = SocketAddr::from(([127, 0, 0, 1], 8080));
    println!("\x1b[1;32m[SYSTEM]\x1b[0m Escutando em: http://{}", addr);
    
    let listener = tokio::net::TcpListener::bind(addr).await.unwrap();
    axum::serve(listener, app).await.unwrap();
}

async fn obter_telemetria() -> Json<Vec<Telemetria>> {
    println!("\x1b[1;34m[API]\x1b[0m Requisição de telemetria recebida.");

    let dados = vec![
        Telemetria {
            id: "ALPHA-707".to_string(),
            modelo: "Interceptor v3".to_string(),
            status: "OPERACIONAL".to_string(),
            altitude: 150.5,
            timestamp: Utc::now(),
        },
        Telemetria {
            id: "BETA-404".to_string(),
            modelo: "Cargo Lifter".to_string(),
            status: "ALERTA".to_string(),
            altitude: 12.0,
            timestamp: Utc::now(),
        }
    ];

    Json(dados)
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

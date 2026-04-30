/**
 * @file main.rs
 * @brief Servidor de Telemetria Industrial via WebSocket.
 * @author Engenheiro de Elite
 */

use futures_util::{StreamExt, SinkExt};
use serde::{Serialize, Deserialize};
use std::net::SocketAddr;
use std::time::Duration;
use tokio::net::{TcpListener, TcpStream};
use tokio_tungstenite::accept_async;
use tokio_tungstenite::tungstenite::Message;

#[derive(Serialize, Deserialize, Debug)]
struct Coordenada {
    id: String,
    x: f64,
    y: f64,
    bateria: u8,
}

#[tokio::main]
async fn main() {
    let addr = "127.0.0.1:9001";
    let listener = TcpListener::bind(addr).await.expect("Falha ao abrir porta 9001");
    println!("\x1b[1;36m=== NEXUS WS SERVER: LIVE TELEMETRY v2.0 ===\x1b[0m");
    println!("\x1b[1;32m[SYSTEM]\x1b[0m Escutando em ws://{}", addr);

    while let Ok((stream, addr)) = listener.accept().await {
        tokio::spawn(handle_connection(stream, addr));
    }
}

async fn handle_connection(stream: TcpStream, addr: SocketAddr) {
    println!("\x1b[1;34m[WS]\x1b[0m Nova conexão estabelecida: {}", addr);
    
    let ws_stream = accept_async(stream).await.expect("Erro no handshake WS");
    let (mut ws_sender, _) = ws_stream.split();

    let mut count = 0;
    loop {
        count += 1;
        
        // 1. Geração de Telemetria Fictícia (Simulando sinal C++)
        let telemetria = Coordenada {
            id: "ALPHA-707".to_string(),
            x: 100.0 + (count as f64 * 1.5) % 400.0,
            y: 200.0 + (count as f64 * 0.8) % 300.0,
            bateria: 100 - (count % 100) as u8,
        };

        let json = serde_json::to_string(&telemetria).unwrap();

        // 2. Envio do pacote para o Frontend
        if let Err(e) = ws_sender.send(Message::Text(json)).await {
            println!("\x1b[1;31m[WS]\x1b[0m Conexão encerrada com {}: {}", addr, e);
            break;
        }

        tokio::time::sleep(Duration::from_secs(1)).await;
    }
}

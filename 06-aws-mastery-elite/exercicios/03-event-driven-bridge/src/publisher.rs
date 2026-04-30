/**
 * @file publisher.rs
 * @brief Publicador de Eventos para AWS EventBridge (Contrato de Elite).
 */
use serde::{Deserialize, Serialize};
use std::time::{SystemTime, UNIX_EPOCH};

/**
 * @struct EventBridgeEntry
 * @brief O envelope exigido pela AWS para enviar eventos.
 */
#[derive(Serialize)]
struct EventBridgeEntry {
    source: String,
    detail_type: String,
    detail: String, // O conteúdo real vai aqui como JSON string
    event_bus_name: String,
}

/**
 * @struct TelemetriaEvent
 * @brief O contrato do dado (Schema).
 */
#[derive(Serialize, Deserialize)]
struct TelemetriaEvent {
    drone_id: String,
    velocidade: f64,
    timestamp: u64,
}

fn main() {
    println!("\x1b[1;36m=== NEXUS EVENT PUBLISHER: ARQUITETURA DESACOPLADA ===\x1b[0m\n");

    // 1. Criamos o dado da missão
    let agora = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_secs();
    let evento_real = TelemetriaEvent {
        drone_id: "ALPHA-707".to_string(),
        velocidade: 125.5, // EXCESSO DETECTADO! (Regra do Terraform irá capturar)
        timestamp: agora,
    };

    // 2. Serializamos o conteúdo
    let detail_json = serde_json::to_string(&evento_real).unwrap();

    // 3. Montamos o envelope do EventBridge
    let entry = EventBridgeEntry {
        source: "nexus.telemetria".to_string(),
        detail_type: "TelemetriaProcessada".to_string(),
        detail: detail_json,
        event_bus_name: "Nexus-Global-Events".to_string(),
    };

    println!("\x1b[1;32m[PUBLISH]\x1b[0m Enviando evento para o Barramento...");
    println!(
        "Payload Final:\n{}",
        serde_json::to_string_pretty(&entry).unwrap()
    );

    println!("\n\x1b[1;33m[ANÁLISE DE ELITE]\x1b[0m");
    println!("Diferente de uma fila SQS, onde o produtor envia para UM destino,");
    println!("o EventBridge permite que N alvos escutem este mesmo evento.");
    println!("Se no futuro precisarmos de um Notificador Slack, basta adicionar");
    println!("uma regra no Terraform, sem recompilar este código Rust.");
}

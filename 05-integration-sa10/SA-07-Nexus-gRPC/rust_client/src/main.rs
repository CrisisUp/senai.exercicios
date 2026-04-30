/**
 * @file main.rs
 * @brief Orquestrador Rust consumindo telemetria via gRPC.
 * @author Engenheiro de Elite
 */

pub mod logispeed {
    // Inclui o código gerado pelo build.rs
    tonic::include_proto!("logispeed");
}

use logispeed::telemetria_service_client::TelemetriaServiceClient;
use logispeed::DroneRequest;

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("\x1b[1;36m=== NEXUS ORCHESTRATOR: gRPC CLIENT v3.0 ===\x1b[0m\n");

    // 1. Estabelece conexão com o servidor C++
    let mut client = TelemetriaServiceClient::connect("http://[::1]:50051").await?;

    println!("\x1b[1;34m[RUST]\x1b[0m Solicitando status via canal binário...");

    // 2. Monta a requisição tipada
    let request = tonic::Request::new(DroneRequest {
        drone_id: "ALPHA-707".into(),
    });

    // 3. Executa a RPC (Remote Procedure Call)
    let response = client.obter_status(request).await?;

    // 4. Exibe o resultado binário traduzido
    println!("\x1b[1;32m[SUCESSO]\x1b[0m Resposta do Motor C++: {}", response.into_inner().msg);

    println!("\n\x1b[1;33m[ANÁLISE DE ELITE]\x1b[0m");
    println!("A comunicação foi realizada em formato binário comprimido.");
    println!("Diferente do REST/JSON, não houve overhead de texto ou chaves repetidas.");
    println!("O gRPC garantiu que o Rust e o C++ usassem exatamente o mesmo contrato.");

    Ok(())
}

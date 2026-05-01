const ANSI_RESET: &str = "\033[0m";
//! @author Cristiano
//! @date 2026
/**
 * @file build.rs
 * @brief Gerador de código gRPC para o cliente Rust.
 */

fn main() -> Result<(), Box<dyn std::error::Error>> {
    tonic_build::compile_protos("../proto/telemetria.proto")?;
    Ok(())
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

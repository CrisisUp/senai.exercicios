/**
 * @file build.rs
 * @brief Gerador de código gRPC para o cliente Rust.
 */

fn main() -> Result<(), Box<dyn std::error::Error>> {
    tonic_build::compile_protos("../proto/telemetria.proto")?;
    Ok(())
}

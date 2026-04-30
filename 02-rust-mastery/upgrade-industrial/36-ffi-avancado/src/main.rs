/**
 * @file main.rs
 * @brief Orquestrador Rust com integração segura C++ via cxx.rs.
 * @author Engenheiro de Elite
 */

#[cxx::bridge(namespace = "logispeed")]
mod ffi {
    // Tipos e assinaturas C++ que o Rust pode ver
    unsafe extern "C++" {
        include!("ffi-avancado/include/motor_rota.h");

        type MotorRota;

        fn novo_motor(config: String) -> UniquePtr<MotorRota>;
        fn calcular_melhor_rota(self: &MotorRota, origem: String, destino: String) -> String;
        fn obter_distancia(self: &MotorRota) -> f64;
    }
}

fn main() {
    println!("\x1b[1;36m=== LOGISPEED 8.0: PONTE SEGURA RUST <-> C++ ===\x1b[0m\n");

    // 1. Criamos o motor C++ de dentro do Rust
    // O cxx gerencia a alocação na Heap e devolve um UniquePtr (RAII)
    let motor = ffi::novo_motor("ALGORITMO-V3-ALPHA".to_string());

    println!("\x1b[1;34m[RUST]\x1b[0m Solicitando cálculo de rota ao motor C++...");

    // 2. Chamada de método complexo (Strings cruzando a fronteira com segurança)
    let rota = motor.calcular_melhor_rota(
        "CD-MATRIZ".to_string(), 
        "FILIAL-SUL".to_string()
    );

    let distancia = motor.obter_distancia();

    // 3. Resultado
    println!("\x1b[1;32m[RESULTADO]\x1b[0m {}", rota);
    println!("\x1b[1;32m[DISTÂNCIA]\x1b[0m {} km", distancia);

    println!("\n\x1b[1;33m[ANÁLISE DE ELITE]\x1b[0m");
    println!("Nenhum bloco 'unsafe' foi necessário no main.rs.");
    println!("A classe C++ foi encapsulada em um UniquePtr do Rust.");
    println!("Strings foram convertidas sem risco de vazamento ou corrompimento.");
}

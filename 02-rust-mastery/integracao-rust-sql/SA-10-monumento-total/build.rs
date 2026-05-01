const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
//! @file build.rs
//! @brief Implementação de build.rs
//! @author Cristiano
//! @date 2026

fn main() {
    // Compila o Driver em C++ e linka com o Rust
    cc::Build::new()
        .cpp(true) // Habilita modo C++
        .file("src/driver_hardware.cpp")
        .compile("dronehardware");
}

/* @section MemoryMap
 * Stack: Tipos fixos.
 * Heap: Alocações dinâmicas (Box, Vec).
 */
/*
 * RESUMO TEÓRICO
 * Implementação em Rust seguindo as diretrizes de segurança e performance.
 */

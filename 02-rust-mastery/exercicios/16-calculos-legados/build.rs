const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
//! @file build.rs
//! @brief Implementação de build.rs
//! @author Cristiano
//! @date 2026

fn main() {
    // Compila o arquivo C e linka com o binário Rust
    cc::Build::new()
        .file("src/math_motor.c")
        .compile("mathmotor");
}

/* @section MemoryMap
 * Stack: Tipos fixos.
 * Heap: Alocações dinâmicas (Box, Vec).
 */
/*
 * RESUMO TEÓRICO
 * Implementação em Rust seguindo as diretrizes de segurança e performance.
 */

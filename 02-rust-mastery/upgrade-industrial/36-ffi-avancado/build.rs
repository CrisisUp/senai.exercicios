#[allow(dead_code)]
const ANSI_RESET: &str = "\033[0m";
#[allow(dead_code)]
const ANSI_GREEN: &str = "\033[32m";

/**
 * @file build.rs
 * @brief Script de build para integrar C++ e Rust.
 * @author Cristiano
 * @date 2026
 */

fn main() {
    cxx_build::bridge("src/main.rs")
        .file("src/motor_rota.cpp")
        .include(".") // Permite encontrar ffi-avancado/include/...
        .flag_if_supported("-std=c++14")
        .compile("ffi-avancado");

    println!("cargo:rerun-if-changed=src/main.rs");
    println!("cargo:rerun-if-changed=src/motor_rota.cpp");
    println!("cargo:rerun-if-changed=include/motor_rota.h");
}

/* @section MemoryMap
 * Stack: Tipos fixos.
 * Heap: Alocações dinâmicas (Box, Vec).
 */
/*
 * RESUMO TEÓRICO
 * Implementação em Rust seguindo as diretrizes de segurança e performance.
 */

/**
 * @file build.rs
 * @brief Script de build para integrar C++ e Rust.
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

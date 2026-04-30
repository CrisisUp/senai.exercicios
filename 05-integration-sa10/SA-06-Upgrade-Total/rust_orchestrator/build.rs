/**
 * @file build.rs
 * @brief Script de build para a integração final SA-06 (Caminhos de Elite).
 */

fn main() {
    cxx_build::bridge("src/main.rs")
        .file("../cpp_core/src/nexus_core.cpp")
        .include("../cpp_core/include")
        // O diretório abaixo contém o header gerado pelo cxxbridge
        .include("src") 
        .flag_if_supported("-std=c++14")
        .compile("nexus-core");

    println!("cargo:rerun-if-changed=src/main.rs");
    println!("cargo:rerun-if-changed=../cpp_core/src/nexus_core.cpp");
    println!("cargo:rerun-if-changed=../cpp_core/include/nexus_core.h");
}

/**
 * @file main.rs
 * @brief Atividade 16: Cálculos Legados (Unsafe e FFI).
 *
 * Aprendizados: FFI (Interação C-Rust), blocos unsafe, build.rs.
 *
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */
use std::io::{self, Write};

/*
 * DECLARAÇÃO DE INTERFACE EXTERNA:
 * Aqui avisamos ao Rust que existe uma função no mundo exterior (C).
 */
unsafe extern "C" {
    fn calcular_torque_c(aceleracao: f64) -> f64;
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - INTEGRAÇÃO C-RUST (FFI)        ");
    println!("===============================================");

    // 1. Interação com o usuário
    print!("Digite a aceleração desejada (m/s²): ");
    io::stdout().flush().unwrap();

    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Falha ao ler entrada");

    let aceleracao: f64 = input.trim().parse().unwrap_or(0.0);

    /**
     * BLOCO UNSAFE:
     * O Rust não pode olhar dentro do código C para saber se ele é seguro.
     * Ao entrar no bloco unsafe, o programador assume a responsabilidade
     * por possíveis bugs de memória ou erros da biblioteca externa.
     */
    unsafe {
        println!("\x1b[33m[SISTEMA]: Chamando motor físico em C...\x1b[0m");

        let torque = calcular_torque_c(aceleracao);

        println!("\n\x1b[32m[RESULTADO]:\x1b[0m");
        println!("Aceleração Inserida: {:.2} m/s²", aceleracao);
        println!("Torque Calculado (C): {:.2} Nm", torque);
    }

    println!("===============================================");
}

/*
    ===============================================================
    RESUMO TEÓRICO: UNSAFE RUST E FFI
    ===============================================================

    1. O QUE É UNSAFE?
       - Não significa "código ruim". Significa que o compilador
         não consegue provar a segurança.
       - O unsafe permite: desreferenciar ponteiros crus, chamar
         funções externas e acessar variáveis globais mutáveis.

    2. FFI (Foreign Function Interface):
       - É o mecanismo que permite que linguagens diferentes se
         comuniquem.
       - Rust é excelente nisso, sendo frequentemente usado para
         substituir partes críticas de sistemas em C/C++.

    3. BUILD.RS:
       - Um script que roda ANTES da compilação do Rust. No nosso
         caso, ele invoca o compilador de C para gerar a biblioteca
         estática que o Rust vai usar.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende que o Rust não é uma "bolha". Ele pode
         aproveitar 40 anos de bibliotecas escritas em C, trazendo
         performance sem abrir mão da segurança no resto do sistema.
    ===============================================================
*/

/**
 * @file main.rs
 * @brief Atividade 16: Cálculos Legados (Unsafe e FFI).
 *
 * @section MemoryMap Mapeamento de Memória (Mestre)
 * - **Stack:** Argumentos (`f64`) são passados via Stack seguindo a ABI do C (System V ou Windows x64).
 * - **Unsafe Boundary:** O bloco `unsafe` sinaliza que o Rust abre mão das garantias de memória
 *   ao cruzar a fronteira para o código C.
 * - **Foreign Memory:** Se o C alocasse memória, ela estaria em um Heap externo ao controle do Rust.
 *
 * @section FantasmaCPU Fantasma do CPU: Eficiência de Referências
 * Chamadas FFI têm um overhead mínimo (apenas alguns ciclos de CPU para ajuste de registradores).
 * É a forma mais eficiente de reutilizar lógica de baixo nível sem reescrever tudo em Rust.
 *
 * @author SENAI - Rust Master (Refatoração de Elite Fase 2)
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
    RESUMO TEÓRICO: UNSAFE RUST E FFI (ELITE)
    ===============================================================

    1. O QUE É UNSAFE?
       - Permite: desreferenciar ponteiros crus, chamar funções FFI,
         acessar estáticos mutáveis e implementar traits unsafe.

    2. FFI (Foreign Function Interface):
       - Usa a ABI (Application Binary Interface) do C como padrão de ouro
         para interoperabilidade entre linguagens.

    3. BUILD.RS E LINKAGEM:
       - O script de build instrui o linker do Rust sobre onde encontrar
         os símbolos externos compitados (bibliotecas estáticas ou dinâmicas).

    ASSUNTOS CORRELATOS:
    - Bindgen (geração automática de bindings).
    - C-style Enums e Structs em Rust (#[repr(C)]).
    - Manipulação de Strings entre C e Rust (CString, CStr).
    - Pânico através da fronteira FFI (comportamento indefinido).
    ===============================================================
*/

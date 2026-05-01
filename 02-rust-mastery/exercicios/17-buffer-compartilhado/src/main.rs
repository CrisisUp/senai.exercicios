#[allow(dead_code)]
const ANSI_RESET: &str = "\033[0m";
#[allow(dead_code)]
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Atividade 17: Buffer Compartilhado (Ponteiros Crus e FFI).
 *
 * @section MemoryMap Mapeamento de Memória (Mestre)
 * - **Stack:** O descritor do `Vec` (ponteiro, capacidade, tamanho) reside na Stack.
 * - **Heap:** O buffer real de dados `[i32; tamanho]` reside no Heap.
 * - **Pointer Arithmetic:** `ptr_buffer.add(i)` calcula o endereço exato no Heap sem verificações de limites (bounds checking).
 *
 * @section FantasmaCPU Fantasma do CPU: Eficiência de Referências
 * O uso de ponteiros crus elimina o overhead do "Bounds Checking" do Rust em cada acesso,
 * permitindo que a CPU execute loops de processamento de vetores com máxima performance (SIMD-friendly),
 * ao custo da segurança garantida pelo compilador.
 *
 * @author SENAI - Rust Master (Refatoração de Elite Fase 2)
 * @date 20/04/2026
 */
use std::io::{self, Write};

/*
 * INTERFACE EXTERNA:
 * Importando a função C que opera sobre ponteiros crus.
 */
unsafe extern "C" {
    fn processar_buffer_c(buffer: *mut i32, tamanho: i32);
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - GESTÃO DE MEMÓRIA BRUTA        ");
    println!("===============================================");

    // 1. Interação: Definir tamanho do processamento
    print!("Digite o tamanho do buffer de sensores (ex: 5): ");
    io::stdout().flush().unwrap();

    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Falha ao ler");
    let tamanho: usize = input.trim().parse().unwrap_or(0);

    if tamanho == 0 {
        println!("\x1b[31m[ERRO]: Tamanho inválido.\x1b[0m");
        return;
    }

    // 2. Alocação no Rust (Segura)
    // Criamos um vetor com o tamanho solicitado preenchido com zeros.
    let mut buffer_sensores: Vec<i32> = vec![0; tamanho];

    // 3. Conversão para Ponteiro Cru (Unsafe)
    // as_mut_ptr() nos dá o endereço de memória inicial do vetor.
    let ptr_buffer = buffer_sensores.as_mut_ptr();

    println!(
        "\x1b[33m[SISTEMA]: Memória alocada em: {:p}\x1b[0m",
        ptr_buffer
    );

    // 4. Chamada FFI (Unsafe)
    unsafe {
        println!("[SISTEMA]: Transferindo controle para o código C...");
        processar_buffer_c(ptr_buffer, tamanho as i32);
    }

    // 5. Verificação do Resultado (Voltando ao Rust Seguro)
    println!("\n\x1b[32m[SUCESSO]:\x1b[0m Dados processados e retornados ao Rust:");

    for (i, valor) in buffer_sensores.iter().enumerate() {
        /*
         * Demonstração de Aritmética de Ponteiros (Apenas didático):
         * Poderíamos acessar o valor via ponteiro cru manualmente:
         * let val_via_ptr = unsafe { *ptr_buffer.add(i) };
         */
        println!("  - Sensor [{:02}] -> Valor Final: {}", i, valor);
    }

    println!("===============================================");
}

/*
    ===============================================================
    RESUMO TEÓRICO: PONTEIROS CRUS EM RUST
    ===============================================================

    1. O QUE SÃO PONTEIROS CRUS?
       - '*const T' (Imutável) e '*mut T' (Mutável).
       - Diferente das referências (&), eles ignoram as regras de
         empréstimo (Borrow Rules) e tempos de vida (Lifetimes).

    2. POR QUE USAR?
       - Para interagir com código escrito em C ou C++.
       - Para implementar estruturas de dados de baixíssimo nível
         onde o Borrow Checker é restritivo demais.

    3. PERIGOS:
       - Podem ser nulos (Null Pointer).
       - Podem apontar para memória já liberada (Dangling Pointer).
       - Podem causar Race Conditions (múltiplas threads escrevendo).
       - Por isso, toda desreferenciação deve estar em bloco 'unsafe'.

    4. VANTAGEM DIDÁTICA:
       - O aluno percebe que o Rust dá liberdade total de hardware
         quando necessário, mas exige que você "assine" o risco
         usando a palavra-chave 'unsafe'.
    ===============================================================
*/

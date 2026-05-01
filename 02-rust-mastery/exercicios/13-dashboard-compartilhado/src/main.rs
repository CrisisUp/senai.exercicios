const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
use std::io::{self, Write};
/**
 * @file main.rs
 * @brief Atividade 13: Dashboard Compartilhado (Rc e Interatividade).
 * 
 * @section MemoryMap
 * - Heap: O Rc<T> aloca o valor T e dois contadores (strong e weak) na Heap.
 * - Layout: O ponteiro Rc na Stack aponta para a "Inner Struct" na Heap.
 * - Ownership: O Rc gerencia o tempo de vida; o dado só é destruído quando o strong_count atinge zero.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */
use std::rc::Rc; // Smart pointer para contagem de referências // Módulo de I/O para interação

#[derive(Debug)]
struct Telemetria {
    drone_id: String,
    altitude: f64,
}

impl Drop for Telemetria {
    fn drop(&mut self) {
        println!(
            "\n\x1b[31m[MEMÓRIA]: Destruindo Telemetria de {}. Memória liberada.\x1b[0m",
            self.drone_id
        );
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - DASHBOARD INTERATIVO           ");
    println!("===============================================");

    // 1. Interação: Pedindo o ID do Drone
    print!("Digite o ID do Drone para inicializar: ");
    io::stdout().flush().unwrap(); // Garante que o texto apareça antes da entrada

    let mut drone_input = String::new();
    io::stdin()
        .read_line(&mut drone_input)
        .expect("Falha ao ler entrada");
    let drone_id = drone_input.trim().to_string();

    // 2. Criando o dado central envolto em um Rc
    // O Ownership original é do Rc.
    let telemetria_original = Rc::new(Telemetria {
        drone_id: drone_id.clone(),
        altitude: 120.5,
    });

    println!("\n[SISTEMA]: Telemetria criada para {}.", drone_id);
    println!(
        "Contador de donos atual: {}",
        Rc::strong_count(&telemetria_original)
    );

    // 3. Interação: Quantos observadores?
    print!("\nQuantos sistemas deseja conectar ao dashboard? ");
    io::stdout().flush().unwrap();

    let mut num_input = String::new();
    io::stdin()
        .read_line(&mut num_input)
        .expect("Falha ao ler entrada");

    // Converte String para número (u32)
    let total_sistemas: u32 = num_input.trim().parse().unwrap_or(0);

    // 4. Simulando a conexão de múltiplos sistemas (Propriedade Compartilhada)
    let mut observadores = Vec::new();

    for i in 1..=total_sistemas {
        println!(">> Conectando Sistema #{}...", i);
        // .clone() em um Rc NÃO copia o objeto, apenas aumenta o contador!
        let nova_referencia = Rc::clone(&telemetria_original);
        observadores.push(nova_referencia);
    }

    println!("\n\x1b[32m[STATUS]: DASHBOARD ATIVO!\x1b[0m");
    println!(
        "Total de sistemas lendo os dados: {}",
        Rc::strong_count(&telemetria_original)
    );

    // 5. Demonstrando o desligamento progressivo
    println!("\nIniciando desligamento de emergência...");
    while !observadores.is_empty() {
        observadores.pop(); // Remove um dono da lista
        println!(
            "Um sistema foi desconectado. Donos restantes: {}",
            Rc::strong_count(&telemetria_original)
        );
    }

    println!(
        "\nApenas o sistema original restou: {}",
        Rc::strong_count(&telemetria_original)
    );

    println!("\nEncerrando programa principal...");
    // O telemetria_original sairá de escopo aqui e o contador chegará a zero.
}

/*
    ===============================================================
    RESUMO TEÓRICO: RC (REFERENCE COUNTING) - Fase 2
    ===============================================================

    1. PROPRIEDADE MÚLTIPLA:
       - O Rc permite que um dado tenha múltiplos donos no mesmo thread, 
         rastreando a validade do dado via contagem de referências.

    2. FANTASMA DO CPU (RC::CLONE):
       - Rc::clone(&ptr) incrementa apenas o contador (operação barata). 
       - Não deve ser confundido com .clone() de tipos que duplicam dados.

    3. GESTÃO DE MEMÓRIA:
       - O Drop de cada Rc decrementa o contador. Quando zera, a memória na 
         Heap é desalocada automaticamente, prevenindo leaks básicos.
    ===============================================================

    ASSUNTOS CORRELATOS:
    - Ciclos de Referência e o tipo Weak<T>.
    - Arc<T> (Atomic Reference Counting) para multi-threading.
    - Cow (Copy-on-Write) para otimização de referências e clones.
    - Interior Mutability com RefCell<T>.
*/


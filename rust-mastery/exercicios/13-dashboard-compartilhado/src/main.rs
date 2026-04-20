use std::io::{self, Write};
/**
 * @file main.rs
 * @brief Atividade 13: Dashboard Compartilhado (Rc e Interatividade).
 *
 * Aprendizados: Rc<T>, Entrada de Usuário (stdin), Parsing de tipos.
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
    RESUMO TEÓRICO: RC (REFERENCE COUNTING)
    ===============================================================

    1. PROPRIEDADE MÚLTIPLA:
       - No Rust normal, você não pode ter dois donos para o mesmo
         dado. O Rc quebra essa regra de forma segura.
       - Ele é ideal para "Leitura Compartilhada".

    2. CUSTO ZERO?
       - Quase. O Rc tem um custo mínimo de performance para manter
         o contador atualizado, mas é muito mais barato que clonar
         objetos gigantes na memória.

    3. TRATAMENTO DE ENTRADA:
       - 'read_line' sempre inclui o caractere de nova linha (\n).
         O '.trim()' é obrigatório para limpar a string.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende que o Rust é flexível. Quando a regra de um
         único dono atrapalha a arquitetura, a biblioteca padrão
         fornece ferramentas como o Rc para resolver o problema.
    ===============================================================
*/

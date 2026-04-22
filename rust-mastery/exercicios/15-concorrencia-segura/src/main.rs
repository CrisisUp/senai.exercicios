/**
 * @file main.rs
 * @brief Atividade 15: Concorrência Segura (Threads, Arc e Mutex).
 *
 * @section MemoryMap Mapeamento de Memória (Mestre)
 * - **Stack:** Cada thread possui sua própria stack para variáveis locais.
 * - **Heap:** O `Arc<Mutex<f64>>` reside no Heap, permitindo que o contador de referências
 *   e o Mutex sejam acessíveis por todas as threads de forma atômica.
 * - **MutexGuard:** É um ponteiro inteligente na Stack que libera o lock ao sair de escopo.
 *
 * @section FantasmaCPU Fantasma do CPU: Eficiência de Referências
 * O uso de `Arc::clone` apenas incrementa um contador atômico, sem duplicar o dado real.
 * O `Mutex` garante que não existam conflitos de cache (cache coherency) entre núcleos de CPU
 * ao forçar a sincronização de memória.
 *
 * @author SENAI - Rust Master (Refatoração de Elite Fase 2)
 * @date 20/04/2026
 */
use std::sync::{Arc, Mutex}; // Para compartilhamento seguro entre threads
use std::thread; // Para criação de threads
use std::time::Duration;
use std::io::{self, Write};

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - PROCESSAMENTO PARALELO         ");
    println!("===============================================");

    // 1. Criando o Recurso Compartilhado (Arc + Mutex)
    // Arc permite múltiplos donos em diferentes threads.
    // Mutex garante exclusividade de escrita.
    let quilometragem_global = Arc::new(Mutex::new(0.0));

    // 2. Interação: Quantos drones processar?
    print!("Quantos drones estão enviando dados agora? ");
    io::stdout().flush().unwrap();

    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Falha ao ler");
    let num_drones: u32 = input.trim().parse().unwrap_or(1);

    // Vetor para armazenar as 'handles' das threads (para podermos dar join depois)
    let mut handles = vec![];

    println!(
        "\n[SISTEMA]: Iniciando {} threads de processamento...",
        num_drones
    );

    for i in 1..=num_drones {
        // Clonamos o Arc para cada thread.
        // Isso NÃO copia o dado, apenas cria uma nova referência atômica.
        let quilometragem = Arc::clone(&quilometragem_global);

        let handle = thread::spawn(move || {
            // Simula um processamento pesado
            println!("   >> Drone #{}: Processando logs de voo...", i);
            thread::sleep(Duration::from_millis(500 * (i as u64 % 3 + 1)));

            let km_viagem = 12.5 * (i as f64);

            // 3. BLOQUEIO (Lock): Solicitando acesso ao dado global
            // O lock() retorna um MutexGuard que libera o dado automaticamente
            // ao fim deste escopo.
            {
                let mut dado = quilometragem.lock().unwrap();
                *dado += km_viagem;
                println!(
                    "\x1b[32m   [OK] Drone #{}:\x1b[0m Adicionou {:.1} km ao global.",
                    i, km_viagem
                );
            }
        });

        handles.push(handle);
    }

    // 4. SINCRONIZAÇÃO (Join): Esperando o fim de todos os processos
    println!("\n[CENTRAL]: Aguardando sincronização final...");
    for handle in handles {
        handle.join().unwrap();
    }

    // 5. Resultado Final
    let resultado_final = quilometragem_global.lock().unwrap();
    println!("\n===============================================");
    println!("RELATÓRIO CONSOLIDADO DE FROTA:");
    println!(
        "Total de Quilometragem Processada: \x1b[33m{:.2} km\x1b[0m",
        *resultado_final
    );
    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_concorrencia_soma() {
        let counter = Arc::new(Mutex::new(0.0));
        let mut handles = vec![];

        for _ in 0..10 {
            let c = Arc::clone(&counter);
            let h = thread::spawn(move || {
                let mut num = c.lock().unwrap();
                *num += 1.0;
            });
            handles.push(h);
        }

        for h in handles {
            h.join().unwrap();
        }

        assert_eq!(*counter.lock().unwrap(), 10.0);
    }
}

/*
    ===============================================================
    RESUMO TEÓRICO: CONCORRÊNCIA DESTEMIDA (ELITE)
    ===============================================================

    1. ARC VS RC:
       - Rc (Reference Counted) não é seguro para threads. Arc (Atomic)
         garante que o contador seja atualizado via instruções de CPU.

    2. MUTEX E POISONING:
       - Se uma thread entrar em pânico enquanto segura um Mutex, o
         Rust marca o Mutex como "envenenado". O unwrap() no lock()
         propaga esse pânico para outras threads para evitar dados inconsistentes.

    3. DATA RACES VS RACE CONDITIONS:
       - O Rust elimina Data Races (acessos simultâneos sem sincronia).
       - Race Conditions lógicas ainda são possíveis, mas muito mais fáceis de diagnosticar.

    ASSUNTOS CORRELATOS:
    - Atomics (std::sync::atomic).
    - RwLock (Read-Write Lock) para múltiplos leitores.
    - Channels (mpsc) para comunicação entre threads.
    - Send and Sync traits.
    ===============================================================
*/

/**
 * @file main.rs
 * @brief SA-05: Sistema de Controle de Tráfego Aéreo (Refatoração de Elite).
 *
 * Implementação de alta confiabilidade para gerenciamento de aeronaves em tempo real utilizando concorrência segura.
 *
 * @author SENAI - Rust Master
 * @date 20/04/2026
 * 
 * @section MemoryMap Árvore de Ownership e Gerenciamento de Memória:
 * - frota (Arc<Mutex<Vec<DroneAereo>>>): [STACK] Ponteiro atômico p/ [HEAP] Mutex que protege [HEAP] Vetor.
 * - frota_simulacao: Clone do Arc (incrementa o contador de referências no HEAP), compartilha o mesmo Mutex.
 * - DroneAereo: [HEAP] Alocado dentro do vetor, contém sua própria string de ID.
 * 
 * @section FantasmadoCPU Fantasma do CPU (Performance e Segurança):
 * - Zero-copy: O uso de iteradores (.iter()) no vetor bloqueado pelo Mutex evita a cópia dos drones.
 * - Referências: 'drones.iter()' e 'drones.iter_mut()' trabalham diretamente na memória protegida pelo lock.
 * - Lifetimes: O tempo de vida do 'lock' (MutexGuard) garante que a memória não seja acessada após o desbloqueio.
 */
use std::io::{self, Write};
use std::sync::{Arc, Mutex};
use std::thread;
use std::time::Duration;

/// Representa uma aeronave individual no sistema.
#[derive(Debug, Clone)]
struct DroneAereo {
    id: String,
    altitude: f64,
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - TORRE DE CONTROLE (SA-05)      ");
    println!("===============================================");

    // 1. Estado Compartilhado: Lista Global de Drones
    // Arc permite que a Torre e os Drones tenham posse da lista.
    // Mutex garante que apenas uma thread altere a lista por vez.
    let frota = Arc::new(Mutex::new(Vec::<DroneAereo>::new()));

    // 2. Thread de Simulação de Voo
    // Esta thread "invisível" atualiza a altitude dos drones autonomamente.
    let frota_simulacao = Arc::clone(&frota);
    thread::spawn(move || {
        loop {
            thread::sleep(Duration::from_secs(2));
            let mut drones = frota_simulacao.lock().unwrap();
            for drone in drones.iter_mut() {
                // Simula oscilação de altitude (+/- 1m)
                drone.altitude += 1.0;
            }
        }
    });

    // 3. Loop Principal de Interação (Menu do Usuário)
    loop {
        println!("\n\x1b[36m--- MENU DE COMANDO ---\x1b[0m");
        println!("1. Adicionar Drone ao Espaço Aéreo");
        println!("2. Listar Monitoramento (Tempo Real)");
        println!("3. Aplicar Calibração de Emergência (Todos)");
        println!("0. Encerrar Sistema");
        print!("Opção: ");
        io::stdout().flush().unwrap();

        let mut opcao = String::new();
        io::stdin().read_line(&mut opcao).unwrap();

        match opcao.trim() {
            "1" => {
                print!("Digite o ID do Drone: ");
                io::stdout().flush().unwrap();
                let mut id = String::new();
                io::stdin().read_line(&mut id).unwrap();

                let novo_drone = DroneAereo {
                    id: id.trim().to_string(),
                    altitude: 100.0,
                };

                let mut drones = frota.lock().unwrap();
                drones.push(novo_drone);
                println!("\x1b[32m[OK]: Drone registrado e em voo.\x1b[0m");
            }
            "2" => {
                let drones = frota.lock().unwrap();
                println!("\n\x1b[33m--- STATUS DO TRÁFEGO AÉREO ---\x1b[0m");
                if drones.is_empty() {
                    println!("Céu limpo. Nenhum drone detectado.");
                } else {
                    for d in drones.iter() {
                        println!(">> [{}] Altitude: {:.1}m", d.id, d.altitude);
                    }
                }
            }
            "3" => {
                print!("Digite o ajuste de altitude (ex: -10 para descer): ");
                io::stdout().flush().unwrap();
                let mut ajuste_str = String::new();
                io::stdin().read_line(&mut ajuste_str).unwrap();
                let ajuste: f64 = ajuste_str.trim().parse().unwrap_or(0.0);

                let mut drones = frota.lock().unwrap();
                for d in drones.iter_mut() {
                    d.altitude += ajuste;
                }
                println!("\x1b[35m[COMANDO]: Calibração enviada para toda a frota.\x1b[0m");
            }
            "0" => {
                println!("Desativando torre de controle... Até logo!");
                break;
            }
            _ => println!("Opção inválida."),
        }
    }

    println!("===============================================");
}

/*
    ===============================================================
    RESUMO TEÓRICO: DESAFIO INTEGRADOR SA-05 (REFATORAÇÃO DE ELITE)
    ===============================================================

    1. O PODER DA CONCORRÊNCIA SEGURA:
       - No C++, compartilhar um 'std::vector' entre threads sem
         cuidado causaria um crash. No Rust, o Mutex garante que
         a leitura e escrita sejam atômicas.

    2. ARC + MUTEX (O Padrão Ouro):
       - Arc gerencia QUEM tem acesso ao dado (várias threads).
       - Mutex gerencia COMO o dado é acessado (exclusividade).

    3. INTERATIVIDADE EM TEMPO REAL:
       - Enquanto o usuário navega no menu, uma thread de background
         está alterando os dados (simulando os drones voando).
       - O usuário vê os valores mudarem toda vez que pede a listagem.

    4. EVOLUÇÃO DO MESTRE DE SISTEMAS:
       - Este projeto encerra o ciclo de gerenciamento de recursos,
         provando que o aluno consegue arquitetar aplicações multi-cpu
         completas e seguras.

    ASSUNTOS CORRELATOS PARA PESQUISA:
    - Deadlocks (Como evitar o travamento mútuo entre Mutexes).
    - Send e Sync (Traits que garantem a segurança entre threads).
    - RwLock (Como permitir múltiplas leituras simultâneas, mas escrita única).
    ===============================================================
*/

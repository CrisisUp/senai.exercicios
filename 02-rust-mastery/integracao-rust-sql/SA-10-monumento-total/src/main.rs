const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
//! @author Cristiano
//! @date 2026

/**
 * @file main.rs
 * @brief SA-10: SkyCargo OS (v2.2 - Interface de Comando Interativa).
 */
mod db;
mod hardware;

use anyhow::Result;
use db::SkyRepo;
use std::io::{self, Write};
use std::sync::Arc;
use std::time::Duration;
use tokio;

/// Helper para ler entrada do terminal de forma limpa.
fn prompt(mensagem: &str) -> String {
    print!("{}", mensagem);
    io::stdout().flush().unwrap();
    let mut entrada = String::new();
    io::stdin()
        .read_line(&mut entrada)
        .expect("Falha ao ler entrada");
    entrada.trim().to_string()
}

/// Loop principal de interação com o usuário.
async fn menu_principal(repo: Arc<SkyRepo>) -> Result<()> {
    loop {
        println!("\n\x1b[35m--- MENU DE COMANDO SKYCARGO ---\x1b[0m");
        println!("[1] Listar Frota");
        println!("[2] Cadastrar Novo Drone");
        println!("[3] Atualizar Região");
        println!("[4] Remover Drone");
        println!("[5] INICIAR MISSÕES (Simultâneo)");
        println!("[6] Ver Dashboard de Performance");
        println!("[0] Sair do Sistema");

        let opcao = prompt("\nEscolha uma opção: ");

        match opcao.as_str() {
            "1" => {
                if let Ok(frota) = repo.listar_frota() {
                    println!("\n\x1b[32m--- FROTA ATUAL ---\x1b[0m");
                    if frota.is_empty() {
                        println!("A frota está vazia.");
                    } else {
                        for d in frota {
                            println!(
                                "ID: {:<3} | Serial: {:<10} | Região: {}",
                                d.id.unwrap(),
                                d.serial,
                                d.regiao
                            );
                        }
                    }
                }
            }
            "2" => {
                let serial = prompt("Serial do Drone: ");
                let regiao = prompt("Região de Operação: ");
                if let Err(e) = repo.cadastrar_drone(&serial, &regiao) {
                    eprintln!("\n\x1b[41m[ERRO DE CADASTRO]:\x1b[0m {}", e);
                } else {
                    println!("\x1b[32m[OK]: Drone cadastrado com sucesso.\x1b[0m");
                }
            }
            "3" => {
                let serial = prompt("Serial do Drone para mover: ");
                let nova_regiao = prompt("Nova Região: ");
                if let Err(e) = repo.atualizar_regiao(&serial, &nova_regiao) {
                    eprintln!("\n\x1b[41m[ERRO]:\x1b[0m {}", e);
                } else {
                    println!("\x1b[32m[OK]: Região atualizada.\x1b[0m");
                }
            }
            "4" => {
                let serial = prompt("Serial do Drone para remover: ");
                if let Err(e) = repo.remover_drone(&serial) {
                    eprintln!("\n\x1b[41m[ERRO]:\x1b[0m {}", e);
                } else {
                    println!("\x1b[31m[AVISO]: Drone removido do sistema.\x1b[0m");
                }
            }
            "5" => {
                println!("\x1b[33m[SISTEMA]: Preparando decolagem simultânea...\x1b[0m");
                if let Ok(frota) = repo.listar_frota() {
                    if frota.is_empty() {
                        println!("\x1b[31mErro: NENHUM drone cadastrado!\x1b[0m");
                    } else {
                        let mut handles = vec![];
                        for drone in frota {
                            let r = Arc::clone(&repo);
                            let s = drone.serial.clone();
                            handles.push(tokio::spawn(executar_missao(s, r)));
                        }
                        for h in handles {
                            let _ = h.await; // Aguarda sem encerrar o menu em caso de erro individual
                        }
                    }
                }
            }
            "6" => {
                if let Err(e) = exibir_dashboard(&repo) {
                    eprintln!("\x1b[41m[ERRO ANALÍTICO]:\x1b[0m {}", e);
                }
            }
            "0" => {
                println!("Encerrando sistemas...");
                break;
            }
            _ => println!("\x1b[31mOpção inválida!\x1b[0m"),
        }
    }
    Ok(())
}

/// Orquestração de uma missão individual.
async fn executar_missao(serial: String, repo: Arc<SkyRepo>) -> Result<()> {
    println!("\x1b[33m[MISSÃO]:\x1b[0m Iniciando drone {}...", serial);

    // Hardware Check (FFI C++)
    hardware::iniciar_ignicao(75).map_err(|e| anyhow::anyhow!(e))?;

    // Simulação de tempo de voo
    tokio::time::sleep(Duration::from_secs(2)).await;

    let telemetria = db::Telemetria {
        bateria: rand::random::<u32>() % 100,
        distancia: 50.0 + (rand::random::<f64>() * 100.0),
    };

    let repo_clone = Arc::clone(&repo);
    let s = serial.clone();
    tokio::task::spawn_blocking(move || repo_clone.registrar_missao(&s, telemetria)).await??;

    println!(
        "\x1b[36m[FINALIZADO]:\x1b[0m Drone {} reportou dados com sucesso.",
        serial
    );
    Ok(())
}

/// Exibição de relatórios analíticos.
fn exibir_dashboard(repo: &SkyRepo) -> Result<()> {
    println!("\n\x1b[35m[INTELIGÊNCIA]:\x1b[0m Dashboard de Performance Global\n");
    let dados = repo.gerar_dashboard()?;
    if dados.is_empty() {
        println!("Nenhum dado de missão disponível.");
    } else {
        println!("{:<10} | {:<10} | {:<5}", "DRONE", "KM TOTAL", "RANK");
        println!("-----------------------------------------");
        for (serial, km, rank) in dados {
            println!("{:<10} | {:<10.1} | #{}", serial, km, rank);
        }
    }
    Ok(())
}

#[tokio::main]
async fn main() -> Result<()> {
    println!("===============================================");
    println!("     SKYCARGO OS v2.2 - TERMINAL INTERATIVO    ");
    println!("===============================================");

    let repo = Arc::new(SkyRepo::new("skycargo_final.db")?);
    repo.inicializar()?;

    // Inicia o Loop do Menu
    menu_principal(repo).await?;

    println!("\nSistemas desligados com segurança.");
    Ok(())
}

/* @section MemoryMap
 * Stack: Tipos fixos.
 * Heap: Alocações dinâmicas (Box, Vec).
 */
/*
 * RESUMO TEÓRICO
 * Implementação em Rust seguindo as diretrizes de segurança e performance.
 */

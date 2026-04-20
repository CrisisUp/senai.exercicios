/**
 * @file main.rs
 * @brief SA-06: Simulador de Fábrica Automata.
 *
 * Integração: Type States, Listas Ligadas, Sobrecarga de Operadores e FFI.
 *
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */
use std::io::{self, Write};
use std::marker::PhantomData;
use std::mem;
use std::ops::Add;

// -----------------------------------------------------------------------------
// FFI: INTEGRAÇÃO COM MÓDULO C
// -----------------------------------------------------------------------------
unsafe extern "C" {
    fn realizar_stress_test_c(carga: f64) -> i32;
}

// -----------------------------------------------------------------------------
// ESTRUTURA DE DADOS: PEÇA (Sobrecarga de Operadores)
// -----------------------------------------------------------------------------
#[derive(Debug, Clone, Copy)]
struct Peca {
    massa_kg: f64,
}

impl Add for Peca {
    type Output = Self;
    fn add(self, other: Self) -> Self {
        Self {
            massa_kg: self.massa_kg + other.massa_kg,
        }
    }
}

// -----------------------------------------------------------------------------
// ESTRUTURA DE DADOS: LISTA LIGADA (Manual)
// -----------------------------------------------------------------------------
enum LinhaProducao {
    Vazia,
    No(Peca, Box<LinhaProducao>),
}

impl LinhaProducao {
    fn new() -> Self {
        LinhaProducao::Vazia
    }

    fn empilhar(&mut self, p: Peca) {
        let antiga = mem::take(self);
        *self = LinhaProducao::No(p, Box::new(antiga));
    }

    fn calcular_massa_total(&self) -> f64 {
        let mut total = 0.0;
        let mut atual = self;
        while let LinhaProducao::No(p, prox) = atual {
            total += p.massa_kg;
            atual = prox;
        }
        total
    }
}

impl Default for LinhaProducao {
    fn default() -> Self {
        LinhaProducao::Vazia
    }
}

// -----------------------------------------------------------------------------
// ARQUITETURA: TYPE STATES (Robô Montador)
// -----------------------------------------------------------------------------
struct Ocioso;
struct Carregado {
    peca: Peca,
}
struct Montando;

struct Robo<S> {
    id: String,
    estado: S,
}

impl Robo<Ocioso> {
    fn new(id: &str) -> Self {
        Self {
            id: id.to_string(),
            estado: Ocioso,
        }
    }

    fn capturar_peca(self, p: Peca) -> Robo<Carregado> {
        println!(
            "\x1b[32m[ROBÔ]:\x1b[0m Peça de {:.2}kg capturada.",
            p.massa_kg
        );
        Robo {
            id: self.id,
            estado: Carregado { peca: p },
        }
    }
}

impl Robo<Carregado> {
    fn iniciar_montagem(self) -> (Robo<Montando>, Peca) {
        println!("\x1b[33m[ROBÔ]:\x1b[0m Iniciando processo de soldagem e montagem...");
        let p = self.estado.peca;
        (
            Robo {
                id: self.id,
                estado: Montando,
            },
            p,
        )
    }
}

impl Robo<Montando> {
    fn finalizar(self) -> Robo<Ocioso> {
        println!("\x1b[32m[ROBÔ]:\x1b[0m Montagem concluída. Retornando ao estado ocioso.");
        Robo {
            id: self.id,
            estado: Ocioso,
        }
    }
}

// -----------------------------------------------------------------------------
// PROGRAMA PRINCIPAL
// -----------------------------------------------------------------------------
fn main() {
    println!("===============================================");
    println!("     SKYCARGO - FÁBRICA AUTOMATA (SA-06)       ");
    println!("===============================================");

    let mut estoque_saida = LinhaProducao::new();
    let mut robo = Robo::new("MONTADOR-01");

    // Como o robô muda de tipo nas transições, não podemos guardá-lo em uma
    // variável mutável simples se quisermos mudar o estado.
    // Vamos usar um pattern de shadowing ou Option para a demo.

    loop {
        println!("\nMENU DE FÁBRICA:");
        println!("1. Comandar Robô: Capturar Peça (5kg)");
        println!("2. Comandar Robô: Realizar Montagem");
        println!("3. Ver Massa Total Produzida");
        println!("0. Sair");
        print!("Escolha: ");
        io::stdout().flush().unwrap();

        let mut escolha = String::new();
        io::stdin().read_line(&mut escolha).unwrap();

        match escolha.trim() {
            "1" => {
                // Simulação: Pegar peça e testar via FFI
                let peca_nova = Peca { massa_kg: 5.0 };
                unsafe {
                    if realizar_stress_test_c(peca_nova.massa_kg) == 1 {
                        // Transição: Ocioso -> Carregado
                        // Nota: Nesta versão simplificada, assumimos que o robo SEMPRE está ocioso aqui.
                        // Em uma versão real, usaríamos um Enum ou Wrapper para gerenciar o tipo dinâmico.
                        let robo_carregado = robo.capturar_peca(peca_nova);

                        // Executa montagem imediatamente para simplificar a demo
                        let (robo_m, p) = robo_carregado.iniciar_montagem();
                        estoque_saida.empilhar(p);
                        robo = robo_m.finalizar();
                    }
                }
            }
            "2" => {
                println!("[INFO]: No modo simplificado, a montagem é feita junto com a captura.")
            }
            "3" => {
                let total = estoque_saida.calcular_massa_total();
                println!("\x1b[36m[ESTOQUE]:\x1b[0m Massa Total: {:.2} kg", total);
            }
            "0" => break,
            _ => println!("Opção inválida."),
        }
    }

    println!("Fábrica encerrada com sucesso.");
}

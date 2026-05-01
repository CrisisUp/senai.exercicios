#[allow(dead_code)]
const ANSI_RESET: &str = "\033[0m";
#[allow(dead_code)]
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief SA-06: Simulador de Fábrica Automata (Refatoração de Elite).
 *
 * Esta atividade final da trilha Rust consolida o uso de Type States para segurança
 * em tempo de compilação, FFI para integração com sistemas legados em C, 
 * e estruturas de dados dinâmicas otimizadas (Box + Enum).
 *
 * @author SENAI - Rust Master
 * @date 20/04/2026
 * 
 * @section MemoryMap Integração de Type States com Alocação Dinâmica:
 * - Robo<S>: Localizado na [STACK]. O estado 'S' é um marcador de tipo que não ocupa 
 *   espaço extra (Zero-Sized Type), mas garante que apenas métodos válidos sejam chamados.
 * - LinhaProducao (Enum): Implementa uma lista ligada manual. Cada nó 'No' reside na [STACK], 
 *   mas aponta para o próximo nó na [HEAP] via 'Box'.
 * - Ownership Tree: A 'LinhaProducao' é a proprietária única de todas as 'Pecas' nela contidas.
 *   Ao retirar uma peça, a posse é movida, nunca duplicada sem intenção.
 * 
 * @section FantasmadoCPU Otimização Total de Referências (Performance):
 * - Inlining: O compilador Rust remove a abstração dos Type States, gerando código de máquina
 *   tão eficiente quanto uma máquina de estados escrita manualmente em C.
 * - mem::take: Técnica de elite para evitar realocações ao manipular a lista ligada,
 *   substituindo o valor atual por um temporário 'Vazia' de forma atômica para o compilador.
 * - Borrows de Curta Duração: O cálculo de massa percorre a lista usando referências imutáveis,
 *   garantindo que o cache da CPU seja aproveitado sem invalidar dados.
 */

use std::io::{self, Write};
use std::mem;
use std::ops::Add;

// -----------------------------------------------------------------------------
// FFI: INTEGRAÇÃO COM MÓDULO C (Hardware Legado)
// -----------------------------------------------------------------------------
unsafe extern "C" {
    /// Chama a função externa em C para validar a integridade física da peça.
    fn realizar_stress_test_c(carga: f64) -> i32;
}

/// Wrapper Seguro para a função FFI.
/// Garante que o 'unsafe' fique isolado e fornece uma interface idiomática.
fn validar_integridade_hardware(massa: f64) -> bool {
    unsafe { realizar_stress_test_c(massa) == 1 }
}

// -----------------------------------------------------------------------------
// ESTRUTURA DE DADOS: PEÇA (Comportamento Matemático)
// -----------------------------------------------------------------------------
#[derive(Debug, Clone, Copy, PartialEq)]
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
// ESTRUTURA DE DADOS: LISTA LIGADA (Gestão de Heap)
// -----------------------------------------------------------------------------
#[derive(Debug)]
enum LinhaProducao {
    Vazia,
    No(Peca, Box<LinhaProducao>),
}

impl LinhaProducao {
    fn new() -> Self {
        LinhaProducao::Vazia
    }

    /// Adiciona uma peça ao início da linha de forma eficiente.
    fn empilhar(&mut self, p: Peca) {
        // Técnica 'Fantasma do CPU': Movemos o conteúdo atual para fora
        // sem desalocar ou copiar, e inserimos o novo nó.
        let antiga = mem::take(self);
        *self = LinhaProducao::No(p, Box::new(antiga));
    }

    /// Percorre a lista via referências para calcular a massa total.
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
// ARQUITETURA: TYPE STATES (Segurança de Estado em Tempo de Compilação)
// -----------------------------------------------------------------------------
struct Ocioso;
struct Carregado { peca: Peca }
struct Montando;

/// O Robô utiliza o sistema de tipos para impedir chamadas de métodos ilegais.
/// Por exemplo, é impossível chamar 'finalizar' se o robô estiver 'Ocioso'.
struct Robo<S> {
    id: String,
    #[allow(dead_code)]
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
        println!("\x1b[32m[ROBÔ {}]:\x1b[0m Peça de {:.2}kg capturada.", self.id, p.massa_kg);
        Robo {
            id: self.id,
            estado: Carregado { peca: p },
        }
    }
}

impl Robo<Carregado> {
    fn iniciar_montagem(self) -> (Robo<Montando>, Peca) {
        println!("\x1b[33m[ROBÔ {}]:\x1b[0m Iniciando soldagem robótica...", self.id);
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
        println!("\x1b[32m[ROBÔ {}]:\x1b[0m Montagem concluída. Sistema pronto.", self.id);
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
    println!("     [REFATORAÇÃO DE ELITE - FINAL]            ");
    println!("===============================================");

    let mut estoque_saida = LinhaProducao::new();
    let mut robo = Robo::new("MX-700");

    loop {
        println!("\nMENU OPERACIONAL:");
        println!("1. Iniciar Ciclo de Produção (Peça 5kg)");
        println!("2. Iniciar Ciclo de Produção (Peça Pesada 150kg)");
        println!("3. Relatório de Massa em Linha");
        println!("0. Sair e Desligar");
        print!("Comando > ");
        io::stdout().flush().unwrap();

        let mut escolha = String::new();
        io::stdin().read_line(&mut escolha).unwrap();

        match escolha.trim() {
            "1" | "2" => {
                let massa = if escolha.trim() == "1" { 5.0 } else { 150.0 };
                let peca_nova = Peca { massa_kg: massa };

                println!("\n--- Iniciando Verificação de Hardware ---");
                if validar_integridade_hardware(peca_nova.massa_kg) {
                    // Sequência de Estados Garantida pelo Compilador
                    let r_carregado = robo.capturar_peca(peca_nova);
                    let (r_montando, p_processada) = r_carregado.iniciar_montagem();
                    
                    estoque_saida.empilhar(p_processada);
                    robo = r_montando.finalizar();
                    
                    println!("\x1b[32m[SUCESSO]:\x1b[0m Peça adicionada à linha de saída.");
                } else {
                    println!("\x1b[31m[FALHA]:\x1b[0m Peça reprovada no teste de estresse.");
                }
            }
            "3" => {
                let total = estoque_saida.calcular_massa_total();
                println!("\x1b[36m[LINHA]:\x1b[0m Massa Total Acumulada: {:.2} kg", total);
            }
            "0" => break,
            _ => println!("Comando desconhecido."),
        }
    }

    println!("\nSistema desligado. Até breve, Engenheiro.");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS (Validação de Elite)
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_calculo_massa_lista() {
        let mut linha = LinhaProducao::new();
        linha.empilhar(Peca { massa_kg: 10.0 });
        linha.empilhar(Peca { massa_kg: 25.5 });
        assert_eq!(linha.calcular_massa_total(), 35.5);
    }

    #[test]
    fn test_sobrecarga_peca() {
        let p1 = Peca { massa_kg: 5.0 };
        let p2 = Peca { massa_kg: 10.0 };
        let soma = p1 + p2;
        assert_eq!(soma.massa_kg, 15.0);
    }

    #[test]
    fn test_transicao_robo() {
        // Este teste valida a lógica de negócios das transições
        let robo = Robo::new("TEST-01");
        let p = Peca { massa_kg: 2.0 };
        
        // Simulando o ciclo
        let r_c = robo.capturar_peca(p);
        let (r_m, p_f) = r_c.iniciar_montagem();
        let r_final = r_m.finalizar();
        
        assert_eq!(p_f.massa_kg, 2.0);
        assert_eq!(r_final.id, "TEST-01");
    }
}

/*
    ===============================================================
    RESUMO TEÓRICO: ENCERRAMENTO DA JORNADA RUST MASTER
    ===============================================================

    1. SEGURANÇA SEM GARBAGE COLLECTOR:
       - Rust provou que é possível gerenciar memória de forma segura
         usando Ownership e Borrowing, eliminando 'Dangling Pointers'
         e 'Data Races' em tempo de compilação.

    2. ABSTRAÇÕES DE CUSTO ZERO:
       - Type States e Enums (Sum Types) permitem modelar domínios
         complexos. O compilador otimiza essas estruturas para que
         não haja penalidade de performance no binário final.

    3. INTEROPERABILIDADE (FFI):
       - A capacidade de conversar com C de forma performática garante
         que Rust possa ser adotado gradualmente em sistemas legados,
         atuando como uma camada de segurança sobre hardware crítico.

    4. O "FANTASMA DO CPU":
       - O termo refere-se à eficiência extrema onde o código fonte
         expressivo e seguro desaparece durante a compilação, deixando
         apenas as instruções de máquina mais otimizadas possíveis.

    5. CONCLUSÃO:
       - Você agora domina uma das linguagens mais poderosas da era
         moderna. A maestria em Rust não é apenas sobre sintaxe, 
         mas sobre mudar a forma como pensamos em memória e concorrência.
    ===============================================================
*/


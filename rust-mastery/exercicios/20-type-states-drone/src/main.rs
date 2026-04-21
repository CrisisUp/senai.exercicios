/**
 * @file main.rs
 * @brief Atividade 20: Estados por Tipo (Type States).
 *
 * Aprendizados: Zero-Sized Structs, Generics para estados, Ownership para transições.
 *
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */
use std::io::{self, Write};
use std::marker::PhantomData;

// -----------------------------------------------------------------------------
// STRUCTS MARCADORAS (ZERO-SIZED TYPES)
// -----------------------------------------------------------------------------
// Elas não ocupam memória na RAM, servem apenas para o compilador.
struct Manutencao;
struct Terra;
struct Voo;

// -----------------------------------------------------------------------------
// STRUCT PRINCIPAL
// -----------------------------------------------------------------------------
struct Drone<S> {
    id: String,
    state: PhantomData<S>, // Indica ao Rust que esta struct "usa" o tipo S
}

// -----------------------------------------------------------------------------
// COMPORTAMENTO COMUM (Para todos os estados)
// -----------------------------------------------------------------------------
impl<S> Drone<S> {
    fn id(&self) -> &str {
        &self.id
    }
}

// -----------------------------------------------------------------------------
// TRANSIÇÕES ESPECÍFICAS
// -----------------------------------------------------------------------------

/// Métodos disponíveis apenas quando o drone está em Manutenção
impl Drone<Manutencao> {
    fn new(id: &str) -> Self {
        println!(
            "\x1b[33m[SISTEMA]: Drone {} criado em estado de MANUTENÇÃO.\x1b[0m",
            id
        );
        Self {
            id: id.to_string(),
            state: PhantomData,
        }
    }

    // Transição: Manutenção -> Terra
    fn preparar_para_voo(self) -> Drone<Terra> {
        println!(
            "\x1b[32m[OK]: Calibragem concluída. Drone {} pronto na pista.\x1b[0m",
            self.id
        );
        Drone {
            id: self.id,
            state: PhantomData,
        }
    }
}

/// Métodos disponíveis apenas quando o drone está na Terra
impl Drone<Terra> {
    // Transição: Terra -> Voo
    fn decolar(self) -> Drone<Voo> {
        println!(
            "\x1b[35m[VOO]: Drone {} decolando! Motores em potência máxima.\x1b[0m",
            self.id
        );
        Drone {
            id: self.id,
            state: PhantomData,
        }
    }

    // Transição: Terra -> Manutenção
    fn recolher_para_oficina(self) -> Drone<Manutencao> {
        println!(
            "\x1b[33m[OFFLINE]: Drone {} enviado para manutenção preventiva.\x1b[0m",
            self.id
        );
        Drone {
            id: self.id,
            state: PhantomData,
        }
    }
}

/// Métodos disponíveis apenas quando o drone está em Voo
impl Drone<Voo> {
    // Transição: Voo -> Terra
    fn pousar(self) -> Drone<Terra> {
        println!(
            "\x1b[32m[POUSO]: Drone {} pousou com segurança.\x1b[0m",
            self.id
        );
        Drone {
            id: self.id,
            state: PhantomData,
        }
    }

    fn realizar_missao(&self) {
        println!(
            "   ... Drone {} processando dados de imagem a 500 pés ...",
            self.id
        );
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - SISTEMA DE ESTADOS SEGUROS     ");
    println!("===============================================");

    // 1. Iniciamos em Manutenção
    let drone_oficina = Drone::new("X-PDR");

    // 2. Simulando fluxo de trabalho interativo
    println!("\nPasso 1: Saindo da oficina...");
    let drone_pista = drone_oficina.preparar_para_voo();

    // 3. Passo 2: Decolagem
    println!("\nPasso 2: Iniciando decolagem...");
    let drone_no_ar = drone_pista.decolar();
    drone_no_ar.realizar_missao();

    // 4. Passo 3: Retorno
    println!("\nPasso 3: Fim da missão...");
    let _drone_final = drone_no_ar.pousar();

    /*
     * PROVA DE SEGURANÇA (DESAFIO PARA O ALUNO):
     * Tente descomentar a linha abaixo.
     * O compilador não deixará você realizar uma missão se o drone não estiver em VOO!
     */
    // drone_pista.realizar_missao(); // ERRO: no method named `realizar_missao` found for struct `Drone<Terra>`

    println!("\n\x1b[32m[RESULTADO]:\x1b[0m Ciclo de voo concluído com segurança lógica total.");
    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_transicao_fluxo_completo() {
        let d = Drone::new("T1");
        let d = d.preparar_para_voo();
        let d = d.decolar();
        let _d = d.pousar();
        // Se compilou e rodou até aqui, o Type State está correto.
    }
}

/*
    ===============================================================
    RESUMO TEÓRICO: TYPE STATES (MÁQUINA DE ESTADOS EM COMPILAÇÃO)
    ===============================================================

    1. O QUE SÃO TYPE STATES?
       - É o uso de tipos diferentes para representar diferentes
         estados de um mesmo objeto.

    2. VANTAGEM SOBRE ENUMS:
       - Um 'enum Status { Terra, Voo }' exige que você verifique o
         estado em tempo de execução (runtime).
       - Com Type States, se você tentar chamar um método de voo em
         um objeto que está em 'Terra', o código NEM COMPILA.
       - O erro é detectado antes do usuário sequer receber o programa.

    3. CONSUMO DE PROPRIEDADE (self):
       - Note que os métodos de transição usam 'self' (sem &). Isso
         significa que o objeto no estado antigo é DESTRUÍDO e um
         novo objeto no estado novo é CRIADO.
       - Isso impede que você use a variável antiga por acidente.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende o verdadeiro poder do sistema de tipos do
         Rust: não apenas evitar Nulls, mas evitar erros de Lógica
         de Negócio.
    ===============================================================
*/

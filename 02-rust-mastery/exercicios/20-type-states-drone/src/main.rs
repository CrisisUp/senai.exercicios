#[allow(dead_code)]
const ANSI_RESET: &str = "\033[0m";
#[allow(dead_code)]
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Atividade 20: Estados por Tipo (Type States).
 *
 * @section Aprendizado
 * Zero-Sized Structs, Generics para estados, Ownership para transições.
 *
 * @section MemoryMap: Zero-cost Abstractions
 * - As structs marcadoras (Terra, Voo, Manutencao) são Zero-Sized Types (ZST).
 * - Em tempo de execução, elas ocupam 0 bytes na memória RAM.
 * - O `PhantomData<S>` também é removido pelo compilador.
 * - O custo de segurança é pago inteiramente em Tempo de Compilação.
 *
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */
use std::marker::PhantomData;

/// @section Fantasma do CPU: Performance
/// No 'Type States', o código de máquina gerado é exatamente o mesmo que se não usássemos tipos.
/// O 'Fantasma do CPU' não precisa realizar verificações de estado (checks) no processador,
/// pois o Rust garante que o drone estará no estado correto pela estrutura do código.

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
    #[allow(dead_code)]
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
    #[allow(dead_code)]
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
    RESUMO TEÓRICO: TYPE STATES (FASE ELITE - SEGURANÇA TOTAL)
    ===============================================================

    1. O QUE SÃO TYPE STATES?
       - É o uso de tipos diferentes (ZSTs) para representar estados
         distintos de um mesmo objeto em tempo de compilação.

    2. VANTAGEM SOBRE ENUMS:
       - Enums são verificados em Runtime. Type States são
         verificados em Compile-Time.
       - Erros de lógica de negócio (ex: decolar em manutenção) se
         tornam erros de compilação, não bugs em produção.

    3. ZERO COST ABSTRACTION (MemoryMap):
       - Structs vazias e PhantomData não ocupam espaço na RAM.
       - A segurança é "grátis" para o usuário final, com o custo
         sendo pago apenas durante o build.

    4. CONSUMO DE PROPRIEDADE (Ownership):
       - Ao usar 'fn metodo(self)', garantimos a transição atômica
         de estados, prevenindo o uso acidental do estado antigo.

    5. FANTASMA DO CPU:
       - O processador não executa nenhuma instrução extra para
         manter essa segurança; é pura semântica de tipos do Rust.
    ===============================================================
*/


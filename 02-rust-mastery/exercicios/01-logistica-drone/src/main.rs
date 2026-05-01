const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Sistema de Decolagem de Drones (Atividade 01 - Nível 01).
 * 
 * Aprendizados: Imutabilidade, Tipagem f64, Testes Unitários.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Rust Safety Standard)
 * - nome_drone: String Literal (&str) alocada no CODE SEGMENT do binário.
 * - peso_carga (f64): Alocada na STACK (8 bytes).
 * - nivel_bateria (f64): Alocada na STACK (8 bytes).
 * - Ciclo de Vida: Todas as variáveis são destruídas ao fim do escopo da main().
 */

/// Verifica se o drone tem condições técnicas para decolagem.
/// @param peso_kg O peso da carga em quilogramas.
/// @param bateria_percentual O nível da bateria de 0 a 100.
fn pode_decolar(peso_kg: f64, bateria_percentual: f64) -> bool {
    // Rust usa 'expressões': o valor da última linha sem ponto e vírgula é o retorno.
    peso_kg < 5.0 && bateria_percentual > 20.0
}

fn main() {
    // Variáveis imutáveis por padrão (Conceito chave do Rust)
    let nome_drone = "Sky-Walker 01";
    let peso_carga = 3.2;
    let nivel_bateria = 85.0;

    println!("\x1b[36m===============================================\x1b[0m");
    println!("     SKYCARGO - SISTEMA DE DECOLAGEM v2.0      ");
    println!("\x1b[36m===============================================\x1b[0m");
    println!("Drone: \x1b[1m{}\x1b[0m", nome_drone);

    if pode_decolar(peso_carga, nivel_bateria) {
        // Uso de cores ANSI no terminal para feedback UX
        println!("\x1b[32m[STATUS]: DECOLAGEM AUTORIZADA!\x1b[0m");
    } else {
        println!("\x1b[31m[ALERTA]: CONDIÇÕES INSUFICIENTES PARA VOO.\x1b[0m");
    }

    println!("\x1b[36m===============================================\x1b[0m");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS (Obrigatórios em todas as atividades Rust)
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*; // Importa a função do escopo acima

    #[test]
    fn test_decolagem_sucesso() {
        assert_eq!(pode_decolar(3.0, 50.0), true);
    }

    #[test]
    fn test_decolagem_falha_peso() {
        assert_eq!(pode_decolar(6.0, 50.0), false);
    }

    #[test]
    fn test_decolagem_falha_bateria() {
        assert_eq!(pode_decolar(2.0, 10.0), false);
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: SEGURANÇA ATÔMICA DO RUST
    ===============================================================

    1. IMUTABILIDADE ESTÁTICA:
       - No Rust, variáveis são 'Ready-only' por padrão. Isso significa 
         que o compilador garante que 'peso_carga' nunca mudará entre a 
         leitura e a chamada da função, prevenindo 'Side Effects'.

    2. TIPAGEM FORTE:
       - Diferente do C++, o Rust não faz conversões implícitas 
         perigosas (ex: converter int para float sem avisar). Isso 
         elimina classes inteiras de bugs de precisão.

    3. TEST-DRIVEN DEVELOPMENT (TDD):
       - A macro #[cfg(test)] permite que a validação viva no mesmo 
         arquivo do código, facilitando a manutenção e garantindo 
         que mudanças futuras não quebrem a lógica de decolagem.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Shadowing: Redefinindo variáveis no mesmo escopo.
    - Floating Point Standards (IEEE 754).
    - Cargo: O gerenciador de pacotes e build do Rust.
    ===============================================================
*/


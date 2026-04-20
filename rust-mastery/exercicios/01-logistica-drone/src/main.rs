/**
 * @file main.rs
 * @brief Sistema de Decolagem de Drones (Atividade 01 - Nível 01).
 * 
 * Aprendizados: Imutabilidade, Tipagem f64, Testes Unitários.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
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

    println!("===============================================");
    println!("     SKYCARGO - SISTEMA DE DECOLAGEM           ");
    println!("===============================================");
    println!("Drone: {}", nome_drone);

    if pode_decolar(peso_carga, nivel_bateria) {
        // Uso de cores ANSI no terminal
        println!("\x1b[32m[STATUS]: DECOLAGEM AUTORIZADA!\x1b[0m");
    } else {
        println!("\x1b[31m[ALERTA]: CONDIÇÕES INSUFICIENTES.\x1b[0m");
    }

    println!("===============================================");
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
    RESUMO TEÓRICO: O FUNDAMENTO DO RUST
    ===============================================================

    1. IMUTABILIDADE:
       - No C++, variáveis podem mudar a qualquer momento. No Rust,
         você deve pedir permissão ao compilador usando 'mut'.
       - Isso evita que dados mudem por acidente em programas grandes.

    2. FUNÇÕES E EXPRESSÕES:
       - Em Rust, não precisamos sempre da palavra 'return'. 
       - Se a última linha da função não tiver ';' ela é tratada
         como o valor de retorno.

    3. SEGURANÇA NA COMPILAÇÃO:
       - Se você tentar passar um 'int' onde a função pede 'f64',
         o Rust nem sequer gera o executável. Zero surpresas no runtime.
    ===============================================================
*/

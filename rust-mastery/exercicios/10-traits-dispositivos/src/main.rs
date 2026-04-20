/**
 * @file main.rs
 * @brief Atividade 11: Transmissão Genérica (Generics e Traits).
 *
 * Aprendizados: Uso de <T>, Trait Bounds, Monomorfização.
 *
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */
use std::fmt::Display;

/// Função genérica que aceita qualquer tipo T, desde que ele implemente a trait Display.
fn enviar_multiplos<T: Display>(dado1: T, dado2: T) {
    println!(
        "[RÁDIO]: Transmitindo múltiplos dados: {} e {}",
        dado1, dado2
    );
    println!("[OK]: Pacotes enviados com sucesso.");
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - TRANSMISSÃO GENÉRICA          ");
    println!("===============================================");

    // 1. Simulação de transmissão de pacotes (dados específicos)
    println!("[RÁDIO]: Transmitindo pacote...");
    println!(">> Conteúdo: [MSG|PRIO:1]: Carga entregue no ponto B");
    println!("[OK]: Pacote enviado com sucesso.\n");

    println!("[RÁDIO]: Transmitindo pacote...");
    println!(">> Conteúdo: [GPS]: -23.5505, -46.6333");
    println!("[OK]: Pacote enviado com sucesso.\n");

    // 2. Utilizando a função genérica para demonstrar polimorfismo paramétrico
    println!("[INFO]: Utilizando função genérica para múltiplos dados:");

    // Teste com strings
    enviar_multiplos("Sensor_01", "Sensor_02");
    println!();

    // Teste com números (f64)
    enviar_multiplos(10.5, 20.8);
    println!();

    println!("[INFO]: Dados transmitidos e limpos da memória.");
    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_generics_logic() {
        // Apenas para garantir que o compilador resolve os tipos corretamente
        enviar_multiplos(1, 2);
        enviar_multiplos("A", "B");
        assert!(true);
    }
}

/*
    ===============================================================
    RESUMO TEÓRICO: TRAITS (INTERFACES RUST)
    ===============================================================

    1. O QUE SÃO TRAITS?
       - São contratos. Elas definem "o que um tipo pode fazer" sem
         se preocupar com "quem o tipo é".

    2. DYNAMIC DISPATCH (dyn):
       - Quando usamos 'Box<dyn Trait>', estamos usando polimorfismo
         de tempo de execução. O Rust usa uma vtable (similar ao C++)
         para localizar o método correto.

    3. COMPARAÇÃO COM C++:
       - Em C++, usaríamos herança e métodos virtuais. No Rust,
         usamos composição e Traits, o que é considerado mais
         flexível e evita o "problema do diamante" na herança.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende a arquitetar sistemas plugáveis, onde o
         código central não precisa conhecer os detalhes de cada
         peça de hardware, apenas o seu protocolo.
    ===============================================================
*/

/**
 * @file main.rs
 * @brief Atividade 04: Sistema de Telemetria (Borrowing e Referências).
 * 
 * Aprendizados: Referências Imutáveis (&), Referências Mutáveis (&mut), Structs.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/// Dados de voo capturados pelos sensores.
struct Telemetria {
    altitude: f64,
    velocidade: f64,
    bateria: f64,
}

/**
 * Função que toma um EMPRÉSTIMO IMUTÁVEL.
 * Pode apenas ler os dados. O objeto original não é destruído.
 */
fn exibir_painel(t: &Telemetria) {
    println!("\x1b[36m--- PAINEL DE TELEMETRIA ---\x1b[0m");
    println!("ALTITUDE  : {:.1} m", t.altitude);
    println!("VELOCIDADE: {:.1} km/h", t.velocidade);
    println!("BATERIA   : {:.0}%", t.bateria);
}

/**
 * Função que toma um EMPRÉSTIMO MUTÁVEL.
 * Permite alterar o objeto original através da referência.
 */
fn calibrar_altitude(t: &mut Telemetria, nova_alt: f64) {
    println!("\x1b[33m[SISTEMA]: Calibrando altitude para {:.1} m...\x1b[0m", nova_alt);
    t.altitude = nova_alt; // Altera o valor no objeto original
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - SISTEMA DE TELEMETRIA          ");
    println!("===============================================");

    // 1. Criando o objeto (Deve ser 'mut' para permitir empréstimos de escrita futuramente)
    let mut dados_voo = Telemetria {
        altitude: 150.5,
        velocidade: 45.0,
        bateria: 88.0,
    };

    // 2. PRIMEIRO EMPRÉSTIMO (Leitura)
    // Passamos '&dados_voo'. Main continua sendo o dono.
    exibir_painel(&dados_voo);

    // 3. SEGUNDO EMPRÉSTIMO (Escrita)
    // Passamos '&mut dados_voo'. 
    calibrar_altitude(&mut dados_voo, 160.0);

    // 4. TERCEIRO EMPRÉSTIMO (Leitura pós-calibração)
    // Provamos que o objeto original foi alterado e ainda existe!
    exibir_painel(&dados_voo);

    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_calibracao() {
        let mut t = Telemetria { altitude: 0.0, velocidade: 0.0, bateria: 100.0 };
        calibrar_altitude(&mut t, 50.0);
        assert_eq!(t.altitude, 50.0);
    }

    #[test]
    fn test_persistencia_dados() {
        let t = Telemetria { altitude: 10.0, velocidade: 10.0, bateria: 10.0 };
        exibir_painel(&t);
        // Se o Ownership fosse transferido, a linha abaixo não compilaria.
        assert_eq!(t.altitude, 10.0); 
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: BORROWING (EMPRÉSTIMO)
    ===============================================================

    1. POR QUE É MELHOR QUE C++?
       - No C++, você pode ter referências (aliasing) para o mesmo 
         dado e alterá-lo enquanto outra parte do código o lê, 
         causando bugs imprevisíveis.
       - No Rust, o Borrow Checker impede isso em tempo de compilação.

    2. REFERÊNCIAS IMUTÁVEIS (&):
       - "Posso dar uma olhada?" - Sim, e muitos podem olhar ao 
         mesmo tempo.

    3. REFERÊNCIAS MUTÁVEIS (&mut):
       - "Posso mexer?" - Sim, mas enquanto você estiver mexendo, 
         ninguém mais pode nem olhar nem mexer. Isso garante 
         exclusividade e segurança.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende a diferença entre ler e escrever e como 
         o acesso compartilhado aos dados deve ser controlado.
    ===============================================================
*/

/**
 * @file main.rs
 * @brief Sistema de Telemetria de Voo (Atividade 04 - Refatoração de Elite).
 * 
 * @section MemoryMap
 * - Ownership: A struct 'Telemetria' no main é a dona dos dados.
 * - Borrowing: Utilizamos &Telemetria (Leitura) e &mut Telemetria (Escrita).
 * - Stack vs Heap: A struct Telemetria reside no Stack por conter apenas tipos primitivos (f64).
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
 * @section Fantasma do CPU
 * Função que toma um EMPRÉSTIMO IMUTÁVEL (&).
 * Passa apenas o ponteiro (8 bytes), evitando a cópia da struct.
 */
fn exibir_painel(t: &Telemetria) {
    println!("\x1b[36m--- PAINEL DE TELEMETRIA ---\x1b[0m");
    println!("ALTITUDE  : {:.1} m", t.altitude);
    println!("VELOCIDADE: {:.1} km/h", t.velocidade);
    println!("BATERIA   : {:.0}%", t.bateria);
}

/**
 * Função que toma um EMPRÉSTIMO MUTÁVEL (&mut).
 * Permite alteração segura sem invalidação de outros ponteiros.
 */
fn calibrar_altitude(t: &mut Telemetria, nova_alt: f64) {
    println!("\x1b[33m[SISTEMA]: Calibrando altitude para {:.1} m...\x1b[0m", nova_alt);
    t.altitude = nova_alt;
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - SISTEMA DE TELEMETRIA (ELITE)  ");
    println!("===============================================");

    let mut dados_voo = Telemetria {
        altitude: 150.5,
        velocidade: 45.0,
        bateria: 88.0,
    };

    // Leitura via referência
    exibir_painel(&dados_voo);

    // Escrita via referência mutável
    calibrar_altitude(&mut dados_voo, 160.0);

    // Verificação de persistência
    exibir_painel(&dados_voo);

    println!("===============================================");
}

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
    fn test_borrowing_rules() {
        let t = Telemetria { altitude: 10.0, velocidade: 10.0, bateria: 10.0 };
        exibir_painel(&t);
        assert_eq!(t.altitude, 10.0); 
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: BORROWING E SEGURANÇA
    ===============================================================
    1. EXCLUSIVIDADE MUTÁVEL: O Rust impede que você tenha uma 
       referência mutável e qualquer outra referência ao mesmo tempo.
    2. ALIASING PROTECTION: Evita que uma função altere um dado 
       enquanto outra função o lê de forma concorrente.
    3. ZERO OVERHEAD: Referências em Rust compilam para ponteiros 
       simples, sem checagem de runtime (a checagem é estática).

    ASSUNTOS CORRELATOS:
    - Interior Mutability (Cell, RefCell).
    - Concurrency and Send/Sync traits.
    - Pointer aliasing in LLVM.
    ===============================================================
*/

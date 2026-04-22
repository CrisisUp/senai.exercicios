/**
 * @file main.rs
 * @brief SA-02: Hub de Diagnóstico de Frota (Refatoração de Elite).
 * 
 * Integração de Borrowing, Tratamento de Erros e Lifetimes com foco em performance.
 * 
 * @section MemoryMap Árvore de Posse e Empréstimos
 * - `d1`, `d2`: Drone (Posse do main, Stack-based struct).
 * - `alerta_final`: String (Heap-allocated, mutável para acumular diagnósticos).
 * - `&Drone`: Empréstimo imutável passado para funções de análise (Zero Copy).
 * - `&'a str`: Referência com Lifetime vinculada à String de erro (Fantasma do CPU).
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/// Representa o estado básico de um drone para monitoramento.
struct Drone {
    id: String,
    bateria: f64,
    status_sensor: Option<f64>, // Some(leitura) ou None (sensor quebrado)
}

/**
 * Valida a integridade da bateria.
 * Fantasma do CPU: Usa empréstimo imutável (&) para evitar clonagem do Drone.
 */
fn verificar_saude(d: &Drone) -> Result<(), String> {
    // 1. Verifica sensor (Uso de Option)
    if d.status_sensor.is_none() {
        // Alocação em Heap necessária apenas no caminho de erro
        return Err(format!("ERRO_HARDWARE: Sensor offline no drone {}", d.id));
    }

    // 2. Verifica bateria (Uso de Result)
    if d.bateria < 15.0 {
        return Err(format!("ERRO_ENERGIA: Bateria crítica ({:.1}%) no drone {}", d.bateria, d.id));
    }

    Ok(())
}

/**
 * Seleciona o alerta mais detalhado entre dois erros detectados.
 * Fantasma do CPU: Trabalha apenas com referências, zero alocação adicional.
 */
fn selecionar_prioridade<'a>(erro1: &'a str, erro2: &'a str) -> &'a str {
    if erro1.len() >= erro2.len() {
        erro1
    } else {
        erro2
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - HUB DE DIAGNÓSTICO (SA-02)     ");
    println!("     REFATORAÇÃO DE ELITE - FANTASMA DO CPU    ");
    println!("===============================================");

    // Guardião Financeiro: Custo de manutenção preventiva (centavos)
    let custo_diagnostico: u32 = 5000; // R$ 50,00 por drone analisado

    // 1. Instanciando drones (Ownership permanece no main)
    let d1 = Drone { id: String::from("ALPHA-01"), bateria: 12.0, status_sensor: Some(25.0) };
    let d2 = Drone { id: String::from("BETA-02"), bateria: 80.0, status_sensor: None };

    // 2. Coletando alertas (Tratamento de Result/Option com Borrowing)
    let mut alerta_final = String::from("NENHUM_ERRO_DETECTADO");
    let mut custo_total: u32 = 0;

    println!("Analisando frota...");

    // Análise do Drone 1
    custo_total += custo_diagnostico;
    if let Err(e) = verificar_saude(&d1) {
        println!("\x1b[31m[ALERTA]: {}\x1b[0m", e);
        alerta_final = e; 
    }

    // Análise do Drone 2
    custo_total += custo_diagnostico;
    if let Err(e) = verificar_saude(&d2) {
        println!("\x1b[31m[ALERTA]: {}\x1b[0m", e);
        // Fantasma do CPU: 'selecionar_prioridade' decide via referência
        // Fazemos o clone apenas se houver mudança de fato (otimização de escrita)
        let melhor_alerta = selecionar_prioridade(&alerta_final, &e);
        if melhor_alerta != alerta_final {
            alerta_final = melhor_alerta.to_string();
        }
    }

    println!("\n\x1b[33m--- RELATÓRIO DE PRIORIDADE ---\x1b[0m");
    println!("ALERTA MAIS CRÍTICO: {}", alerta_final);
    
    // Guardião Financeiro: Integridade bancária no faturamento do Hub
    println!("FATURAMENTO DO HUB: R$ {}.{:02}", custo_total / 100, custo_total % 100);

    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS (Garantia de Qualidade SA-02)
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_bateria_critica() {
        let d = Drone { id: "T".to_string(), bateria: 10.0, status_sensor: Some(1.0) };
        assert!(verificar_saude(&d).is_err());
    }

    #[test]
    fn test_sensor_ausente() {
        let d = Drone { id: "T".to_string(), bateria: 50.0, status_sensor: None };
        assert!(verificar_saude(&d).is_err());
    }

    #[test]
    fn test_selecao_prioridade() {
        let s1 = "Erro curto";
        let s2 = "Erro bem mais longo e detalhado";
        assert_eq!(selecionar_prioridade(s1, s2), s2);
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO INTEGRADOR SA-02 (ELITE)
    ===============================================================

    1. ZERO-COPY BORROWING:
       - O Hub analisa drones de centenas de megabytes (simulados) 
         sem nunca duplicar a memória, apenas movendo referências 
         nos registradores.

    2. LIFETIMES (Tempo de Vida):
       - O compilador Rust atua como um 'garbage collector' em tempo 
         de compilação, garantindo que o alerta retornado nunca 
         seja um ponteiro pendurado (dangling pointer).

    3. GUARDIÃO FINANCEIRO:
       - Processamento de faturamento de serviços de telemetria 
         usando tipos inteiros para precisão absoluta.

    4. ASSUNTOS CORRELATOS:
       - Generics (T).
       - Traits (Interfaces).
       - Smart Pointers (Box, Arc, Mutex).
    ===============================================================
*/

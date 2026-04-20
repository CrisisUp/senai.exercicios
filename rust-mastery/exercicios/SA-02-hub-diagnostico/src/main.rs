/**
 * @file main.rs
 * @brief SA-02: Hub de Diagnóstico de Frota.
 * 
 * Integração de Borrowing, Tratamento de Erros e Lifetimes.
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
 * Usa um empréstimo imutável (&) para não destruir o objeto drone.
 */
fn verificar_saude(d: &Drone) -> Result<(), String> {
    // 1. Verifica sensor (Uso de Option)
    if d.status_sensor.is_none() {
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
 * O lifetime 'a garante que o retorno seja válido enquanto as strings originais existirem.
 */
fn selecionar_prioridade<'a>(erro1: &'a str, erro2: &'a str) -> &'a str {
    if erro1.len() > erro2.len() {
        erro1
    } else {
        erro2
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - HUB DE DIAGNÓSTICO (SA-02)     ");
    println!("===============================================");

    // 1. Instanciando drones (Ownership permanece no main)
    let d1 = Drone { id: String::from("ALPHA-01"), bateria: 12.0, status_sensor: Some(25.0) };
    let d2 = Drone { id: String::from("BETA-02"), bateria: 80.0, status_sensor: None };

    // 2. Coletando alertas (Tratamento de Result/Option com Borrowing)
    let mut alerta_final = String::from("NENHUM_ERRO_DETECTADO");

    println!("Analisando frota...");

    // Análise do Drone 1
    if let Err(e) = verificar_saude(&d1) {
        println!("\x1b[31m[ALERTA]: {}\x1b[0m", e);
        // Note: 'e' é uma String local aqui. Precisamos de uma lógica de comparação.
        alerta_final = e; 
    }

    // Análise do Drone 2
    if let Err(e) = verificar_saude(&d2) {
        println!("\x1b[31m[ALERTA]: {}\x1b[0m", e);
        // Uso de Lifetimes para decidir qual erro é mais detalhado
        // Como 'selecionar_prioridade' retorna &str, usamos .to_string() para guardar.
        alerta_final = selecionar_prioridade(&alerta_final, &e).to_string();
    }

    println!("\n\x1b[33m--- RELATÓRIO DE PRIORIDADE ---\x1b[0m");
    println!("ALERTA MAIS CRÍTICO: {}", alerta_final);

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
    RESUMO TEÓRICO: DESAFIO INTEGRADOR SA-02
    ===============================================================

    1. GESTÃO DE MEMÓRIA COMPARTILHADA:
       - O Hub (main) consegue olhar para os drones através de 
         referências (&), mantendo a integridade dos dados sem 
         precisar cloná-los ou tomar a posse.

    2. ROBUSTEZ DE ERROS:
       - Combinamos Option (para presença de hardware) e Result 
         (para validade de dados), criando uma barreira de 
         segurança contra falhas físicas.

    3. CONFIABILIDADE DE REFERÊNCIAS:
       - O uso de Lifetimes garante que o Hub nunca retorne um 
         alerta que aponte para uma memória que já foi liberada.

    4. EVOLUÇÃO PEDAGÓGICA:
       - O aluno agora entende como o Rust gerencia a memória em 
         tempo de compilação, permitindo sistemas rápidos e seguros.
    ===============================================================
*/

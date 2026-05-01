#[allow(dead_code)]
const ANSI_RESET: &str = "\033[0m";
#[allow(dead_code)]
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Diagnóstico de Sensores (Atividade 05 - Refatoração de Elite).
 * 
 * @section MemoryMap
 * - Ownership: Result e Option transferem a posse de seus valores internos para o chamador.
 * - Borrowing: As mensagens de erro e sucesso são movidas (Move) ao serem retornadas como String.
 * - Stack vs Heap: f64 reside no stack. Strings de erro dinâmicas (format!) residem no Heap.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/**
 * Simula a leitura de um hardware.
 * @return Some(f64) se o sensor estiver conectado, None se estiver ausente.
 */
fn ler_temperatura_sensor(id: i32) -> Option<f64> {
    match id {
        1 => Some(25.5),
        2 => Some(120.0), // Superaquecido
        _ => None,        // Sensor não encontrado
    }
}

/**
 * @section Fantasma do CPU
 * Valida se a temperatura está dentro dos limites operacionais.
 * Usamos &'static str para erros constantes, evitando alocações no Heap.
 */
fn validar_leitura(temp: f64) -> Result<f64, &'static str> {
    if temp > 100.0 {
        Err("CRÍTICO: Superaquecimento detectado!")
    } else if temp < -20.0 {
        Err("ALERTA: Sensor congelado!")
    } else {
        Ok(temp)
    }
}

/**
 * Une as operações de busca e validação.
 * Usa o poder do Rust para propagar falhas de forma limpa.
 */
fn gerar_diagnostico(id: i32) -> Result<String, String> {
    // Lida com Option (Sensor presente?)
    let temp = ler_temperatura_sensor(id)
        .ok_or_else(|| format!("ERRO: Sensor ID {} não encontrado!", id))?;

    // Lida com Result (Temperatura segura?)
    // O operador '?' propaga o erro. Convertemos o &'static str para String aqui se necessário.
    let temp_valida = validar_leitura(temp).map_err(|e| e.to_string())?;

    Ok(format!("Sensor {}: Operação normal ({:.1}°C)", id, temp_valida))
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - DIAGNÓSTICO DE HARDWARE (ELITE)");
    println!("===============================================");

    let ids = [1, 2, 99]; // Array no Stack (Fantasma do CPU)

    for &id in &ids {
        match gerar_diagnostico(id) {
            Ok(msg) => println!("\x1b[32m[OK]: {}\x1b[0m", msg),
            Err(erro) => println!("\x1b[31m[FALHA]: {}\x1b[0m", erro),
        }
    }

    println!("===============================================");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_sensor_ausente() {
        let res = gerar_diagnostico(99);
        assert!(res.is_err());
        assert!(res.unwrap_err().contains("não encontrado"));
    }

    #[test]
    fn test_sensor_superaquecido() {
        let res = gerar_diagnostico(2);
        assert!(res.is_err());
        assert_eq!(res.unwrap_err(), "CRÍTICO: Superaquecimento detectado!");
    }

    #[test]
    fn test_sensor_sucesso() {
        let res = gerar_diagnostico(1);
        assert!(res.is_ok());
        assert_eq!(res.unwrap(), "Sensor 1: Operação normal (25.5°C)");
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: TRATAMENTO DE ERROS MODERNO
    ===============================================================
    1. SEGURANÇA TOTAL: Rust removeu o NULL, forçando o tratamento
       exclusivo de dados existentes (Some/Ok).
    2. ERROS COMO VALORES: Diferente de C++, erros em Rust não
       interrompem o fluxo do sistema a menos que explicitado (panic).
    3. PROPAGAÇÃO (Interrogação ?): Facilita o encadeamento de 
       chamadas que podem falhar sem aninhamento excessivo.

    ASSUNTOS CORRELATOS:
    - Custom Error Enums (thiserror).
    - Error trait e dyn Error.
    - anyhow crate para aplicações.
    ===============================================================
*/


/**
 * @file main.rs
 * @brief Atividade 05: Diagnóstico de Sensores (Option e Result).
 *
 * Aprendizados: Tratamento de Erros, Option, Result, Operador ?.
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
 * Valida se a temperatura está dentro dos limites operacionais.
 * @return Ok(f64) se for seguro, Err(String) caso contrário.
 */
fn validar_leitura(temp: f64) -> Result<f64, String> {
    if temp > 100.0 {
        Err(String::from("CRÍTICO: Superaquecimento detectado!"))
    } else if temp < -20.0 {
        Err(String::from("ALERTA: Sensor congelado!"))
    } else {
        Ok(temp)
    }
}

/**
 * Une as operações de busca e validação.
 * Usa o poder do Rust para propagar falhas de forma limpa.
 */
fn gerar_diagnostico(id: i32) -> Result<String, String> {
    // 1. Lida com Option (Sensor presente?)
    // O método .ok_or() converte Option em Result
    let temp =
        ler_temperatura_sensor(id).ok_or(format!("ERRO: Sensor ID {} não encontrado!", id))?;

    // 2. Lida com Result (Temperatura segura?)
    // O operador '?' diz: "Se der erro, retorne o erro agora. Se der Ok, me dê o valor."
    let temp_valida = validar_leitura(temp)?;

    Ok(format!(
        "Sensor {}: Operação normal ({:.1}°C)",
        id, temp_valida
    ))
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - DIAGNÓSTICO DE HARDWARE        ");
    println!("===============================================");

    let ids = vec![1, 2, 99]; // Sucesso, Erro de Validação, Erro de Presença

    for id in ids {
        match gerar_diagnostico(id) {
            Ok(msg) => println!("\x1b[32m[OK]: {}\x1b[0m", msg),
            Err(erro) => println!("\x1b[31m[FALHA]: {}\x1b[0m", erro),
        }
    }

    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_sensor_ausente() {
        let res = gerar_diagnostico(99);
        assert!(res.is_err());
        assert_eq!(res.unwrap_err(), "ERRO: Sensor ID 99 não encontrado!");
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

    1. O FIM DO NULL:
       - No Rust, não existe o conceito de ponteiro nulo que quebra
         o programa. Se um dado pode faltar, você DEVE usar Option.
       - O compilador te obriga a tratar o caso 'None' antes de
         acessar o valor.

    2. RESULT vs EXCEÇÕES:
       - Rust não usa try-catch. Erros são valores de retorno.
       - Isso torna as falhas EXPLÍCITAS. Você olha para a assinatura
         da função e sabe exatamente o que pode dar errado.

    3. OPERADOR INTERROGAÇÃO (?):
       - É o "açúcar sintático" do Rust. Ele limpa o código,
         evitando matches repetitivos para cada pequena operação.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende a escrever código "feliz" (happy path) de
         forma linear, enquanto o tratamento de erros acontece nos
         bastidores de forma segura.
    ===============================================================
*/

/**
 * @file main.rs
 * @brief Atividade 06: Auditoria de Logs (Lifetimes).
 * 
 * Aprendizados: Lifetime Annotations ('a), Referências Seguras.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/**
 * Função que compara dois logs e retorna o mais longo.
 * O lifetime 'a garante que a referência retornada seja válida
 * enquanto AMBOS os logs de entrada forem válidos.
 * 
 * Sem as anotações 'a, o Rust não saberia de qual parâmetro 
 * vem o retorno e daria erro de compilação.
 */
fn extrair_log_prioritario<'a>(log1: &'a str, log2: &'a str) -> &'a str {
    if log1.len() > log2.len() {
        log1
    } else {
        log2
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - AUDITORIA DE LOGS (LIFETIMES)  ");
    println!("===============================================");

    // Caso 1: Ambos os logs vivem o tempo todo (escopo do main)
    let log_gps = String::from("ERRO_GPS_SINAL_FRACO_SETOR_ALFA");
    let log_bat = String::from("BATERIA_85_PORCENTO");

    let prioritario = extrair_log_prioritario(&log_gps, &log_bat);
    
    println!("\x1b[33m[AUDITORIA]:\x1b[0m Log Prioritário Detectado:");
    println!(">> {}", prioritario);

    // Caso 2: Respeitando escopos aninhados
    let log_externo = String::from("SISTEMA_OK");
    {
        let log_interno = String::from("ALERTA_INTERNO_TURBULENCIA_DETECTADA");
        let res = extrair_log_prioritario(&log_externo, &log_interno);
        println!("\n[ESCOPO INTERNO]: O mais importante é: {}", res);
    } 
    // Se tentássemos usar 'res' aqui fora, o compilador daria erro, 
    // pois 'log_interno' (de onde 'res' pode ter vindo) morreu.

    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_extracao_maior_log() {
        let s1 = "curto";
        let s2 = "log_bem_mais_longo";
        let res = extrair_log_prioritario(s1, s2);
        assert_eq!(res, "log_bem_mais_longo");
    }

    #[test]
    fn test_logs_iguais() {
        let s1 = "abc";
        let s2 = "def";
        let res = extrair_log_prioritario(s1, s2);
        assert_eq!(res, "def"); // Pela lógica da função (else)
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: LIFETIMES (TEMPOS DE VIDA)
    ===============================================================

    1. O QUE SÃO?
       - No Rust, referências não podem durar mais do que os dados
         originais (Ownership). Lifetimes são como o Rust prova
         isso matematicamente.

    2. ANOTAÇÃO <'a>:
       - Não é um tipo de dado. É uma "promessa" ao compilador:
         "Eu garanto que o dado que estou retornando viverá 
         pelo menos tanto quanto o menor dos meus parâmetros."

    3. POR QUE É SEGURO?
       - Evita o erro de "Dangling Reference" (Referência Pendente).
       - Em C++, é fácil retornar uma referência para uma variável
         local que morre ao fim da função. No Rust, isso é
         fisicamente impossível de compilar.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende a pensar na hierarquia de vida dos objetos, 
         tornando-se um programador muito mais atento à gestão 
         de memória e escopo.
    ===============================================================
*/

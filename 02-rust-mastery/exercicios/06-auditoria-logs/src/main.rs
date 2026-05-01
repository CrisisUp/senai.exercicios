const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Auditoria de Logs de Voo (Atividade 06 - Refatoração de Elite).
 * 
 * @section MemoryMap
 * - Ownership: Strings originais são as donas dos dados no Heap.
 * - Borrowing: Lifetimes ('a) descrevem que a referência de retorno vive tanto quanto as de entrada.
 * - Stack vs Heap: Referências (&str) residem no Stack, apontando para dados no Heap (String) ou no Data Segment (static str).
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/**
 * @section Fantasma do CPU
 * Função que compara dois logs e retorna o mais longo via referência.
 * Evita o custo de alocar uma nova String no Heap para o resultado.
 */
fn extrair_log_prioritario<'a>(log1: &'a str, log2: &'a str) -> &'a str {
    // O compilador garante que o retorno é válido para o menor lifetime entre log1 e log2.
    if log1.len() > log2.len() {
        log1
    } else {
        log2
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - AUDITORIA DE LOGS (ELITE)      ");
    println!("===============================================");

    let log_gps = String::from("ERRO_GPS_SINAL_FRACO_SETOR_ALFA");
    let log_bat = String::from("BATERIA_85_PORCENTO");

    // O retorno 'prioritario' herda o lifetime das referências passadas.
    let prioritario = extrair_log_prioritario(&log_gps, &log_bat);
    
    println!("\x1b[33m[AUDITORIA]:\x1b[0m Log Prioritário Detectado:");
    println!(">> {}", prioritario);

    // Demonstração de Escopo e Segurança
    let log_estatico: &'static str = "SISTEMA_OPERACIONAL_OK";
    {
        let log_volatil = String::from("ALERTA_TEMPORARIO_VENTO_FORTE");
        let res = extrair_log_prioritario(log_estatico, &log_volatil);
        println!("\n[ESCOPO INTERNO]: O mais importante é: {}", res);
    } 
    // O Borrow Checker impediria o uso de 'res' aqui, pois ele poderia apontar para 'log_volatil'.

    println!("===============================================");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_extracao_maior_log() {
        assert_eq!(extrair_log_prioritario("curto", "longo"), "longo");
    }

    #[test]
    fn test_comparacao_referencias() {
        let s1 = String::from("teste1");
        let s2 = String::from("teste22");
        let res = extrair_log_prioritario(&s1, &s2);
        assert_eq!(res, "teste22");
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: LIFETIMES E SEGURANÇA DE MEMÓRIA
    ===============================================================
    1. DANGLING POINTERS: O Rust torna impossível retornar uma 
       referência para uma variável que sairá de escopo (local).
    2. LIFETIME ELISION: Em muitos casos, o Rust deduz os lifetimes
       sozinho. Usamos 'a explicitamente quando há ambiguidade.
    3. ZERO-COST ABSTRACTION: Lifetimes são ferramentas de compilação,
       não geram código de máquina adicional.

    ASSUNTOS CORRELATOS:
    - Lifetime Elision Rules.
    - Static Lifetime (&'static).
    - Structs com Lifetimes.
    ===============================================================
*/


/**
 * @file main.rs
 * @brief Sistema de Gestão de Mensagens (Atividade 03 - Refatoração de Elite).
 * 
 * @section MemoryMap
 * - Ownership: Strings são alocadas no Heap. A variável original é a dona do ponteiro.
 * - Borrowing: O uso de &str ou &String permite que funções acessem os dados sem tomar a posse.
 * - Stack vs Heap: O 'Smart Pointer' da String fica no Stack (ponteiro, capacidade, tamanho), 
 *   enquanto o conteúdo textual reside no Heap.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/**
 * @section Consumo de Posse
 * Esta função toma a POSSE (ownership) da string.
 * Útil quando a função precisa transformar os dados ou armazená-los.
 */
fn processar_log_consumo(msg: String) {
    println!("\x1b[34m[CONSUMO]:\x1b[0m Analisando e descartando: {}", msg);
} // 'msg' sofre DROP aqui.

/**
 * @section Fantasma do CPU
 * Esta função usa BORROWING (referência).
 * Evita o custo de alocação no Heap e o uso de .clone() desnecessário.
 */
fn processar_log_referencia(msg: &str) {
    println!("\x1b[32m[REFERÊNCIA]:\x1b[0m Lendo dado compartilhado: {}", msg);
}

/**
 * Esta função cria um novo log e transfere a posse para quem chamou.
 */
fn criar_alerta(nivel: &str) -> String {
    format!("ALERTA_NIVEL_{}", nivel)
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - GESTOR DE MEMÓRIA (ELITE)      ");
    println!("===============================================");

    // 1. Uso de Referência (Otimizado)
    let log_estatitico = String::from("SISTEMA_OK");
    processar_log_referencia(&log_estatitico);
    println!("[INFO]: Log ainda disponível: {}", log_estatitico);

    // 2. Transferência de Posse (Move)
    let log_transitorio = String::from("INICIALIZANDO_DRONE");
    processar_log_consumo(log_transitorio);
    // println!("{}", log_transitorio); // ERRO: value borrowed here after move

    // 3. Custo do Clone (Evitar quando possível)
    let log_importante = String::from("ERRO_GPS_SENSIVEL");
    // Em vez de: processar_log_consumo(log_importante.clone());
    // Preferimos:
    processar_log_referencia(&log_importante);

    // 4. Retorno de Posse
    let alerta = criar_alerta("ALTO");
    println!("\x1b[31m[CENTRAL]: {}\x1b[0m", alerta);

    println!("===============================================");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_criacao_alerta() {
        assert_eq!(criar_alerta("TESTE"), "ALERTA_NIVEL_TESTE");
    }

    #[test]
    fn test_referencia() {
        let s = String::from("Teste");
        processar_log_referencia(&s);
        assert_eq!(s, "Teste"); // Garantimos que a string não foi movida
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: OWNERSHIP E PERFORMANCE
    ===============================================================
    1. MOVE SEMANTICS: Ao contrário do C++, o move em Rust é uma 
       cópia rasa (shallow copy) do stack pointer, invalidando o original.
    2. BORROW CHECKER: Garante que você não tenha referências para 
       dados que já sofreram Drop.
    3. STR vs STRING: 'String' é um buffer expansível no Heap. 
       '&str' é uma fatia (slice) imutável, muito mais eficiente para leitura.

    ASSUNTOS CORRELATOS:
    - Slice types (&[T] e &str).
    - Lifetime annotations (introdução).
    - Smart Pointers (Box, Rc, Arc).
    ===============================================================
*/

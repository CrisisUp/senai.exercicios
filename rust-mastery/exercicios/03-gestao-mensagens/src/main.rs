/**
 * @file main.rs
 * @brief Sistema de Gestão de Mensagens (Atividade 03 - Nível 11).
 * 
 * Aprendizados: Ownership (Posse), Move Semantics, Drop, Clone.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/**
 * Esta função toma a POSSE (ownership) da string.
 * Quando a função termina, 'msg' sai de escopo e a memória é liberada (Drop).
 */
fn processar_log(msg: String) {
    println!("\x1b[34m[PROCESSADOR]:\x1b[0m Analisando: {}", msg);
} // Memória de 'msg' é liberada aqui!

/**
 * Esta função cria um novo log e transfere a posse para quem chamou.
 */
fn criar_alerta(nivel: &str) -> String {
    let alerta = format!("ALERTA_NIVEL_{}", nivel);
    alerta // Retorna a posse para o chamador
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - GESTOR DE MEMÓRIA (OWNERSHIP)  ");
    println!("===============================================");

    // 1. Criando uma String na Heap
    let log_inicial = String::from("SISTEMA_INICIALIZADO");
    
    // 2. TRANSFERÊNCIA DE POSSE (MOVE)
    // Ao passar 'log_inicial', main deixa de ser o dono.
    processar_log(log_inicial);
    
    // println!("{}", log_inicial); // ERRO DE COMPILAÇÃO: value borrowed here after move
    println!("[INFO]: A mensagem original foi 'movida' e destruída.");

    // 3. CLONAGEM (Cópia profunda na memória)
    let log_importante = String::from("ERRO_SENSOR_BATERIA");
    let copia_log = log_importante.clone(); // Duplicamos os dados na Heap
    
    processar_log(copia_log);
    println!("[INFO]: Como clonamos, o log ainda existe aqui: {}", log_importante);

    // 4. RETORNO DE POSSE
    let meu_alerta = criar_alerta("CRITICO");
    println!("\x1b[31m[CENTRAL]: {}\x1b[0m", meu_alerta);

    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_criacao_alerta() {
        let res = criar_alerta("TESTE");
        assert_eq!(res, "ALERTA_NIVEL_TESTE");
    }

    #[test]
    fn test_ownership_transfer() {
        let s = String::from("Olá");
        processar_log(s);
        // assert_eq!(s, "Olá"); // Isso faria o teste nem compilar!
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: OWNERSHIP (PROPRIEDADE)
    ===============================================================

    1. POR QUE EXISTE?
       - No C++, se você esquecer o 'delete', a memória vaza. 
       - No Rust, o compilador rastreia quem é o dono. Quando o 
         dono morre (sai de escopo), o Rust limpa a memória na hora.

    2. O CONCEITO DE MOVE:
       - Por padrão, passar um dado complexo para uma função 
         TRANSFERE a posse. Isso é extremamente rápido, pois não 
         copia os bytes, apenas muda o nome do dono.

    3. CLONE:
       - Deve ser usado com cautela, pois ele realmente copia todo 
         o conteúdo para um novo lugar na memória RAM.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende que memória é um recurso finito e que cada 
         byte deve ter um responsável claro.
    ===============================================================
*/

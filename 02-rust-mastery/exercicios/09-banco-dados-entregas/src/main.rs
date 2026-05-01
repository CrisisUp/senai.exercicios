const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Atividade 09: Banco de Dados de Clientes (HashMap).
 * 
 * @section MemoryMap
 * - **HashMap na Heap:** O HashMap armazena suas chaves e valores na Heap para permitir crescimento dinâmico.
 * - **String vs &str:** Chaves do tipo String vivem na Heap, garantindo que o HashMap possua (Ownership) os dados.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

use std::collections::HashMap;

/// Dados armazenados no banco de dados para cada cliente.
#[derive(Debug)]
struct HistoricoCliente {
    nome: String,
    total_entregas: u32,
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - BANCO DE DADOS DE CLIENTES     ");
    println!("===============================================");

    // 1. Inicializando o HashMap
    // Chave: ID (String) | Valor: Struct HistoricoCliente
    let mut banco_clientes = HashMap::new();

    // 2. Inserindo dados (O Ownership do ID e da Struct passa para o Map)
    // Fantasma do CPU: Referências constantes evitadas aqui para garantir Ownership no Map
    banco_clientes.insert(
        String::from("111.222.333-44"), 
        HistoricoCliente { nome: String::from("João Silva"), total_entregas: 5 }
    );

    banco_clientes.insert(
        String::from("555.666.777-88"), 
        HistoricoCliente { nome: String::from("Maria Oliveira"), total_entregas: 12 }
    );

    // 3. Atualizando dados usando a Entry API (Forma idiomática e segura)
    let id_atualizar = "111.222.333-44";
    println!("\x1b[33m[SISTEMA]:\x1b[0m Incrementando entregas para ID: {}", id_atualizar);
    
    banco_clientes.entry(String::from(id_atualizar))
        .and_modify(|c| c.total_entregas += 1);

    // 4. Simulando Buscas (Tratamento com Option)
    let ids_busca = vec!["111.222.333-44", "000.000.000-00"];

    for id in ids_busca {
        println!("\nBuscando ID: {}...", id);
        match banco_clientes.get(id) {
            Some(cliente) => {
                println!("\x1b[32m[SUCESSO]:\x1b[0m Cliente: {} | Entregas: {}", 
                         cliente.nome, cliente.total_entregas);
            },
            None => {
                println!("\x1b[31m[ERRO]:\x1b[0m Cliente não encontrado no banco de dados.");
            }
        }
    }

    // 5. Listagem Completa (Iteração)
    println!("\n\x1b[36m--- RELATÓRIO GERAL DE CLIENTES ---\x1b[0m");
    for (id, info) in &banco_clientes {
        println!("ID: {} | NOME: {:<15} | TOTAL: {}", id, info.nome, info.total_entregas);
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
    fn test_insercao_e_busca() {
        let mut map = HashMap::new();
        map.insert("ID1".to_string(), HistoricoCliente { nome: "A".to_string(), total_entregas: 1 });
        
        assert!(map.contains_key("ID1"));
        let c = map.get("ID1").unwrap();
        assert_eq!(c.nome, "A");
    }

    #[test]
    fn test_atualizacao_entry() {
        let mut map = HashMap::new();
        map.insert("ID1".to_string(), HistoricoCliente { nome: "A".to_string(), total_entregas: 1 });
        
        map.entry("ID1".to_string()).and_modify(|c| c.total_entregas += 1);
        
        let c = map.get("ID1").unwrap();
        assert_eq!(c.total_entregas, 2);
    }

    #[test]
    fn test_busca_inexistente() {
        let map: HashMap<String, HistoricoCliente> = HashMap::new();
        assert!(map.get("ID_FALSO").is_none());
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: HASHMAPS (DICIONÁRIOS)
    ===============================================================

    1. O QUE É:
       - Uma coleção que armazena pares Chave-Valor. 
       - Diferente do C++, o Rust implementa o HashMap com foco 
         em segurança contra ataques de negação de serviço (DoS) 
         via colisões de hash por padrão (SipHash).

    2. ENTRY API:
       - Permite verificar, inserir ou modificar um valor em uma 
         única operação segura e eficiente.

    3. OWNERSHIP:
       - Ao inserir uma chave ou valor no HashMap, ele se torna 
         o dono do dado.

    4. ASSUNTOS CORRELATOS:
       - BTreeMap: Alternativa para quando chaves ordenadas são necessárias.
       - Custom Hashers: Uso de algoritmos como FxHash para maior performance 
         quando a segurança contra DoS não é o foco principal.
       - Capacity & Rehash: Como pré-alocar memória para evitar realocações.
    ===============================================================
*/


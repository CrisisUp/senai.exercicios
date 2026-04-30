/**
 * @file main.rs
 * @brief Sistema de Triagem e Seguro de Encomendas (Atividade 02 - Refatoração de Elite).
 * 
 * @section MemoryMap
 * - Ownership: O vetor 'encomendas' no main possui a propriedade dos dados.
 * - Borrowing: A função 'calcular_seguro' utiliza referências (&TipoEncomenda) para evitar a movimentação (move) do enum.
 * - Stack vs Heap: O Enum 'TipoEncomenda' e o vetor 'encomendas' (seus elementos) residem no stack, 
 *   enquanto o buffer do vetor reside no Heap.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/// Define os tipos de encomendas disponíveis no sistema.
#[derive(Debug)]
enum TipoEncomenda {
    Fragil,
    Urgente,
    Padrao,
}

/**
 * @section Guardião Financeiro
 * Calcula o valor do seguro em centavos (u64) para evitar erros de ponto flutuante.
 * 
 * @param tipo O tipo da encomenda.
 * @param valor_item_centavos Valor do item em centavos.
 * @return O valor do seguro em centavos.
 */
fn calcular_seguro(tipo: &TipoEncomenda, valor_item_centavos: u64) -> u64 {
    // Fantasma do CPU: Usamos match com referências para evitar clones desnecessários.
    match tipo {
        TipoEncomenda::Fragil => (valor_item_centavos / 10) + 2000, // 10% + R$ 20,00
        TipoEncomenda::Urgente => (valor_item_centavos * 5 / 100) + 5000, // 5% + R$ 50,00
        TipoEncomenda::Padrao => valor_item_centavos * 2 / 100, // 2%
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - TRIAGEM E SEGURO (ELITE)       ");
    println!("===============================================");

    // Lista de encomendas (Tipo, Valor em Centavos)
    let encomendas = vec![
        (TipoEncomenda::Fragil, 100000), // R$ 1000,00
        (TipoEncomenda::Urgente, 50000), // R$ 500,00
        (TipoEncomenda::Padrao, 200000), // R$ 2000,00
    ];

    for (tipo, valor_centavos) in &encomendas {
        let seguro_centavos = calcular_seguro(tipo, *valor_centavos);
        
        println!("TIPO: \x1b[33m{:?}\x1b[0m", tipo);
        println!("Valor do Item: R$ {:.2}", (*valor_centavos as f64) / 100.0);
        println!("Custo Seguro : \x1b[32mR$ {:.2}\x1b[0m", (seguro_centavos as f64) / 100.0);
        println!("-----------------------------------------------");
    }

    println!("===============================================");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_seguro_fragil() {
        assert_eq!(calcular_seguro(&TipoEncomenda::Fragil, 100000), 12000);
    }

    #[test]
    fn test_seguro_urgente() {
        assert_eq!(calcular_seguro(&TipoEncomenda::Urgente, 50000), 7500);
    }

    #[test]
    fn test_seguro_padrao() {
        assert_eq!(calcular_seguro(&TipoEncomenda::Padrao, 200000), 4000);
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ENUMS E SEGURANÇA MONETÁRIA
    ===============================================================
    1. INTEGRIDADE FINANCEIRA: O uso de u64 para representar centavos
       previne erros de arredondamento comuns em f32/f64 (ex: 0.1 + 0.2 != 0.3).
    2. ZERO-COST ENUMS: Enums em Rust não possuem overhead de runtime 
       comparado a classes polimórficas.
    3. EXAUSTIVIDADE: O match garante que se novos tipos forem criados,
       o compilador exigirá o tratamento de seguro.

    ASSUNTOS CORRELATOS:
    - Algebraic Data Types (ADT).
    - Floating point precision pitfalls.
    - Copy vs Clone traits.
    ===============================================================
*/

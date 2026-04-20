/**
 * @file main.rs
 * @brief Sistema de Triagem e Seguro de Encomendas (Atividade 02 - Nível 11).
 * 
 * Aprendizados: Enums, Pattern Matching (match), Debug Trait.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/// Define os tipos de encomendas disponíveis no sistema.
#[derive(Debug)] // Permite imprimir o enum usando {:?}
enum TipoEncomenda {
    Fragil,
    Urgente,
    Padrao,
}

/**
 * Calcula o valor do seguro com base no tipo da encomenda.
 * 
 * @param tipo O tipo da encomenda (Enum).
 * @param valor_item O preço de mercado do item.
 * @return O valor do prêmio do seguro.
 */
fn calcular_seguro(tipo: &TipoEncomenda, valor_item: f64) -> f64 {
    // O 'match' é exaustivo: o Rust garante que todos os casos sejam tratados.
    match tipo {
        TipoEncomenda::Fragil => (valor_item * 0.10) + 20.0,
        TipoEncomenda::Urgente => (valor_item * 0.05) + 50.0,
        TipoEncomenda::Padrao => valor_item * 0.02,
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - TRIAGEM E SEGURO               ");
    println!("===============================================");

    // Lista de encomendas para teste
    let encomendas = vec![
        (TipoEncomenda::Fragil, 1000.0),
        (TipoEncomenda::Urgente, 500.0),
        (TipoEncomenda::Padrao, 2000.0),
    ];

    for (tipo, valor) in &encomendas {
        let seguro = calcular_seguro(tipo, *valor);
        
        println!("TIPO: \x1b[33m{:?}\x1b[0m", tipo);
        println!("Valor do Item: R$ {:.2}", valor);
        println!("Custo Seguro : \x1b[32mR$ {:.2}\x1b[0m", seguro);
        println!("-----------------------------------------------");
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
    fn test_seguro_fragil() {
        // 10% de 1000 = 100 + 20 = 120
        assert_eq!(calcular_seguro(&TipoEncomenda::Fragil, 1000.0), 120.0);
    }

    #[test]
    fn test_seguro_urgente() {
        // 5% de 500 = 25 + 50 = 75
        assert_eq!(calcular_seguro(&TipoEncomenda::Urgente, 500.0), 75.0);
    }

    #[test]
    fn test_seguro_padrao() {
        // 2% de 2000 = 40
        assert_eq!(calcular_seguro(&TipoEncomenda::Padrao, 2000.0), 40.0);
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ENUMS E MATCH
    ===============================================================

    1. PODER DOS ENUMS:
       - Diferente do C++, Enums em Rust podem carregar valores 
         (embora não tenhamos usado dados internos nesta atividade).
       - O 'derive(Debug)' é um exemplo de metaprogramação que 
         implementa código de visualização automaticamente.

    2. SEGURANÇA DO MATCH:
       - Se você adicionar um novo tipo de encomenda (ex: 'Internacional')
         e esquecer de atualizar a função 'calcular_seguro', o 
         código NÃO COMPILARÁ. Isso elimina o erro comum de 
         esquecer 'cases' em switch-statements.

    3. REFERÊNCIAS (&):
       - Note que passamos '&TipoEncomenda'. Isso significa que 
         estamos "emprestando" o valor para a função, em vez de 
         entregá-lo (Ownership). Veremos isso a fundo no Nível 21.
    ===============================================================
*/

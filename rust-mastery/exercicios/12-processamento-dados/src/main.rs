/**
 * @file main.rs
 * @brief Atividade 12: Processamento de Dados de Voo (Closures e Iteradores).
 * 
 * Aprendizados: Closures, Iteradores, filter, map, collect.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

#[derive(Debug, Clone)]
struct LeituraVoo {
    id: u32,
    altitude_m: f64,
    velocidade_kmh: f64,
}

impl LeituraVoo {
    fn new(id: u32, alt: f64, vel: f64) -> Self {
        Self { id, altitude_m: alt, velocidade_kmh: vel }
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - PROCESSAMENTO FUNCIONAL        ");
    println!("===============================================");

    // 1. Ingestão de Dados
    let leituras = vec![
        LeituraVoo::new(1, 150.0, 45.0),
        LeituraVoo::new(2, 500.5, 60.0),
        LeituraVoo::new(3, 10.0, 10.0),
        LeituraVoo::new(4, 300.0, 50.0),
    ];

    println!("Total de leituras capturadas: {}", leituras.len());

    // 2. Filtragem: Selecionar voos em altitude elevada
    let limite_seguranca = 200.0;
    
    // O filter() usa uma closure que recebe uma referência.
    // Retornamos true para manter o item.
    let voos_altos: Vec<LeituraVoo> = leituras.iter()
        .filter(|l| l.altitude_m > limite_seguranca)
        .cloned() // Clona o objeto para o novo vetor
        .collect(); // Transforma o iterador em uma coleção real

    println!("\x1b[33m[ALERTA]:\x1b[0m Voos acima de {:.0}m encontrados: {}", limite_seguranca, voos_altos.len());
    for v in &voos_altos {
        println!("  - Drone {}: Altitude {:.1}m", v.id, v.altitude_m);
    }

    // 3. Transformação: Converter altitudes para Pés (Feet)
    // 1m = 3.28084 ft
    let fator_conversao = 3.28084;
    
    // O map() transforma cada item.
    // Note que podemos capturar 'fator_conversao' dentro da closure!
    let altitudes_feet: Vec<f64> = leituras.iter()
        .map(|l| l.altitude_m * fator_conversao)
        .collect();

    println!("\n\x1b[32m[TELEMETRIA]:\x1b[0m Altitudes em Pés (Feet):");
    for (i, alt) in altitudes_feet.iter().enumerate() {
        println!("  Leitura {}: {:.2} ft", i + 1, alt);
    }

    // 4. Verificação Rápida: Existe algum drone em perigo (altitude < 20m)?
    let perigo = leituras.iter().any(|l| l.altitude_m < 20.0);
    if perigo {
        println!("\n\x1b[31m[PERIGO]: Pelo menos um drone está voando baixo demais!\x1b[0m");
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
    fn test_filtragem_altitude() {
        let dados = vec![
            LeituraVoo::new(1, 100.0, 50.0),
            LeituraVoo::new(2, 300.0, 50.0),
        ];
        let filtrados: Vec<_> = dados.iter().filter(|l| l.altitude_m > 200.0).collect();
        assert_eq!(filtrados.len(), 1);
        assert_eq!(filtrados[0].id, 2);
    }

    #[test]
    fn test_conversao_pes() {
        let l = LeituraVoo::new(1, 10.0, 0.0);
        let feet = l.altitude_m * 3.28084;
        assert!((feet - 32.8084).abs() < 0.0001);
    }

    #[test]
    fn test_verificacao_any() {
        let dados = vec![LeituraVoo::new(1, 5.0, 0.0)];
        assert!(dados.iter().any(|l| l.altitude_m < 10.0));
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: CLOSURES E ITERADORES
    ===============================================================

    1. CLOSURES:
       - São funções anônimas. A sintaxe '|p| { ... }' permite criar
         lógica rápida sem precisar definir uma função completa.
       - Captura de Ambiente: Diferente de funções normais, closures 
         podem ler variáveis que estão fora delas (como o 
         'fator_conversao' no main).

    2. ITERADORES LAZY:
       - 'iter()' não faz nada até que você peça um resultado. 
       - Isso permite encadear múltiplas operações (filter, map, 
         take, etc.) de forma extremamente eficiente, pois o Rust 
         processa tudo em um único loop por baixo dos panos.

    3. COLLECT:
       - É o "consumidor" final. Ele pega os resultados do iterador 
         e os coloca em uma nova coleção (como um Vec).

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende a escrever código declarativo: "O QUE eu quero 
         fazer" (filtrar, mapear) em vez de "COMO fazer" (loops manuais, 
         contadores, ifs aninhados).
    ===============================================================
*/

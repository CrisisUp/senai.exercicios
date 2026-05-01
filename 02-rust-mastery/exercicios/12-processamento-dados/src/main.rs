#[allow(dead_code)]
const ANSI_RESET: &str = "\033[0m";
#[allow(dead_code)]
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief Atividade 12: Processamento de Dados de Voo (Closures e Iteradores).
 * 
 * @section MemoryMap
 * - Heap: Vec<LeituraVoo> armazena as structs na Heap. O uso de .collect() pode gerar novas alocações se não for otimizado.
 * - Stack: Iteradores e closures (se não capturarem por movimento) são geralmente alocados na Stack.
 * - Monomorfização: Closures genéricas são otimizadas pelo compilador para cada local de chamada.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

#[derive(Debug, Clone)]
struct LeituraVoo {
    id: u32,
    altitude_m: f64,
    #[allow(dead_code)]
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
    
    // FANTASMA DO CPU: Evitamos .cloned() para não duplicar dados na Heap.
    // Usamos referências (&LeituraVoo) no novo vetor.
    let voos_altos: Vec<&LeituraVoo> = leituras.iter()
        .filter(|l| l.altitude_m > limite_seguranca)
        .collect(); // Transforma o iterador em uma coleção de referências

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
    RESUMO TEÓRICO: CLOSURES E ITERADORES (Fase 2)
    ===============================================================

    1. CLOSURES E CAPTURA:
       - Closures podem capturar por referência (&T), referência mutável (&mut T)
         ou movimento (T). O compilador escolhe a forma menos restritiva.

    2. ITERADORES E PERFORMANCE:
       - Iteradores em Rust são "Zero-Cost". O compilador frequentemente 
         transforma o encadeamento funcional em um loop assembly altamente 
         otimizado, equivalente ou superior a um loop 'for' manual.

    3. FANTASMA DO CPU (REFERÊNCIAS):
       - Priorizar o uso de referências em iteradores evita clones custosos 
         em structs grandes, economizando ciclos de CPU e alocações na Heap.
    ===============================================================

    ASSUNTOS CORRELATOS:
    - Trait Fn, FnMut e FnOnce.
    - Currying e Partial Application em Rust.
    - Iteradores paralelos com a biblioteca Rayon.
    - Streaming Iterators e GATs (Generic Associated Types).
*/



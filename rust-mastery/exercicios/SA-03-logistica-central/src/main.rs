/**
 * @file main.rs
 * @brief SA-03: Sistema de Logística de Armazém Central.
 * 
 * Integração de Structs, Métodos, Vetores e HashMap.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

use std::collections::HashMap;

/// Representa um item individual no estoque.
#[derive(Debug)]
struct Pacote {
    id: String,
    descricao: String,
    peso_kg: f64,
}

/// Gerencia o estoque central e o índice de busca rápida.
struct Armazem {
    estantes: Vec<Pacote>,
    indice_rastreio: HashMap<String, usize>, // ID -> Posição no Vetor
}

impl Armazem {
    /// Inicializa o armazém com estruturas vazias.
    fn new() -> Self {
        Self {
            estantes: Vec::new(),
            indice_rastreio: HashMap::new(),
        }
    }

    /**
     * Registra a entrada de um novo pacote.
     * Atualiza tanto o estoque físico quanto o índice de busca.
     */
    fn registrar_entrada(&mut self, p: Pacote) {
        let id = p.id.clone();
        let posicao = self.estantes.len();
        
        self.estantes.push(p);
        self.indice_rastreio.insert(id, posicao);
    }

    /**
     * Busca um pacote usando o índice HashMap (O(1)).
     * @return Option com referência para o pacote no estoque.
     */
    fn buscar_pacote(&self, id: &str) -> Option<&Pacote> {
        // Busca a posição no mapa e, se achar, acessa o vetor
        let posicao = self.indice_rastreio.get(id)?;
        self.estantes.get(*posicao)
    }

    /**
     * Calcula o peso total de todo o armazém.
     * Usa iteradores para garantir segurança e performance.
     */
    fn calcular_carga_total(&self) -> f64 {
        self.estantes.iter()
            .map(|p| p.peso_kg)
            .sum()
    }

    /// Exibe o inventário completo.
    fn gerar_relatorio(&self) {
        println!("\x1b[36m--- INVENTÁRIO DO ARMAZÉM CENTRAL ---\x1b[0m");
        for p in &self.estantes {
            println!("ID: {:<10} | ITEM: {:<20} | PESO: {:.2} kg", p.id, p.descricao, p.peso_kg);
        }
        println!("-----------------------------------------------");
        println!("CARGA TOTAL ESTOCADA: \x1b[32m{:.2} kg\x1b[0m", self.calcular_carga_total());
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - LOGÍSTICA CENTRAL (SA-03)      ");
    println!("===============================================");

    let mut central = Armazem::new();

    // 1. Simulando Entradas de Carga
    central.registrar_entrada(Pacote {
        id: String::from("PAC-001"),
        descricao: String::from("Equipamento Médico"),
        peso_kg: 15.5,
    });

    central.registrar_entrada(Pacote {
        id: String::from("PAC-002"),
        descricao: String::from("Suprimentos Alimentares"),
        peso_kg: 42.8,
    });

    central.registrar_entrada(Pacote {
        id: String::from("PAC-003"),
        descricao: String::from("Peças de Drone"),
        peso_kg: 5.2,
    });

    // 2. Gerando Relatório Geral (Iteradores)
    central.gerar_relatorio();

    // 3. Simulando Busca Rápida (HashMap)
    let id_busca = "PAC-002";
    println!("\nBuscando rastreio para o ID: {}...", id_busca);
    
    match central.buscar_pacote(id_busca) {
        Some(pacote) => {
            println!("\x1b[32m[LOCALIZADO]:\x1b[0m {:?}", pacote);
        },
        None => {
            println!("\x1b[31m[NÃO ENCONTRADO]:\x1b[0m ID inválido.");
        }
    }

    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS (Garantia de Qualidade SA-03)
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_entrada_e_busca() {
        let mut a = Armazem::new();
        a.registrar_entrada(Pacote { id: "TEST-1".to_string(), descricao: "D".to_string(), peso_kg: 1.0 });
        
        let res = a.buscar_pacote("TEST-1");
        assert!(res.is_some());
        assert_eq!(res.unwrap().id, "TEST-1");
    }

    #[test]
    fn test_carga_total() {
        let mut a = Armazem::new();
        a.registrar_entrada(Pacote { id: "1".to_string(), descricao: "A".to_string(), peso_kg: 10.0 });
        a.registrar_entrada(Pacote { id: "2".to_string(), descricao: "B".to_string(), peso_kg: 20.0 });
        assert_eq!(a.calcular_carga_total(), 30.0);
    }

    #[test]
    fn test_busca_inexistente() {
        let a = Armazem::new();
        assert!(a.buscar_pacote("FALSO").is_none());
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO INTEGRADOR SA-03
    ===============================================================

    1. INDEXAÇÃO COM HASHMAP:
       - Um dos padrões mais comuns em sistemas reais. O vetor 
         guarda o dado físico, e o HashMap guarda o índice para 
         acesso ultra-rápido.

    2. REFERÊNCIAS vs OWNERSHIP:
       - No método 'buscar_pacote', retornamos 'Option<&Pacote>'.
       - Isso é crucial: queremos que o chamador veja os dados, 
         mas não queremos que ele retire o pacote do armazém!

    3. COMPOSIÇÃO DE COLEÇÕES:
       - Vimos como uma struct pode orquestrar múltiplas coleções 
         diferentes para resolver problemas complexos de performance.

    4. EVOLUÇÃO PEDAGÓGICA:
       - O aluno agora domina o tripé: Modelagem (Structs), 
         Processamento (Iteradores) e Localização (HashMap).
    ===============================================================
*/

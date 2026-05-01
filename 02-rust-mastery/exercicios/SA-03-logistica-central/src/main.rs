const ANSI_RESET: &str = "\033[0m";
const ANSI_GREEN: &str = "\033[32m";
/**
 * @file main.rs
 * @brief SA-03: Sistema de Logística de Armazém Central (Refatoração de Elite).
 * 
 * Integração de Structs, Métodos, Vetores e HashMap com foco em performance industrial.
 * 
 * @section MemoryMap Árvore de Posse e Indexação
 * - `Pacote`: Struct dona de suas Strings (Heap).
 * - `Armazem.estantes`: Vec<Pacote> (Dono físico dos dados na Heap).
 * - `Armazem.indice_rastreio`: HashMap<String, usize> (Dono das chaves de busca).
 * - `registrar_entrada`: Move o pacote para dentro do armazém (Zero Copy do objeto).
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
    valor_centavos: u32, // Guardião Financeiro: Integridade monetária
}

/// Gerencia o estoque central e o índice de busca rápida.
struct Armazem {
    estantes: Vec<Pacote>,
    indice_rastreio: HashMap<String, usize>, // ID -> Posição no Vetor
}

impl Armazem {
    /// Inicializa o armazém com estruturas vazias e pré-alocadas.
    fn new(capacidade: usize) -> Self {
        // Fantasma do CPU: Pré-alocação evita realocações custosas (Performance)
        Self {
            estantes: Vec::with_capacity(capacidade),
            indice_rastreio: HashMap::with_capacity(capacidade),
        }
    }

    /**
     * Registra a entrada de um novo pacote.
     * Atualiza tanto o estoque físico quanto o índice de busca.
     */
    fn registrar_entrada(&mut self, p: Pacote) {
        // Fantasma do CPU: Clonamos apenas o ID porque o HashMap precisa da posse da chave
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
        // Fantasma do CPU: Busca por referência (&str), evitando alocações no lookup
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

    /// Calcula o valor total estocado (Guardião Financeiro).
    fn calcular_valor_total(&self) -> u32 {
        self.estantes.iter()
            .map(|p| p.valor_centavos)
            .sum()
    }

    /// Exibe o inventário completo.
    fn gerar_relatorio(&self) {
        println!("\x1b[36m--- INVENTÁRIO DO ARMAZÉM CENTRAL ---\x1b[0m");
        for p in &self.estantes {
            println!("ID: {:<10} | ITEM: {:<20} | PESO: {:.2} kg | VALOR: R$ {}.{:02}", 
                     p.id, p.descricao, p.peso_kg, p.valor_centavos / 100, p.valor_centavos % 100);
        }
        println!("-----------------------------------------------");
        let valor = self.calcular_valor_total();
        println!("CARGA TOTAL: \x1b[32m{:.2} kg\x1b[0m", self.calcular_carga_total());
        println!("VALOR TOTAL: \x1b[32mR$ {}.{:02}\x1b[0m", valor / 100, valor % 100);
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - LOGÍSTICA CENTRAL (SA-03)      ");
    println!("     REFATORAÇÃO DE ELITE - FANTASMA DO CPU    ");
    println!("===============================================");

    // Inicializamos com capacidade para 100 itens (evita resize)
    let mut central = Armazem::new(100);

    // 1. Simulando Entradas de Carga (Guardião Financeiro ativo)
    central.registrar_entrada(Pacote {
        id: String::from("PAC-001"),
        descricao: String::from("Equipamento Médico"),
        peso_kg: 15.5,
        valor_centavos: 250000, // R$ 2.500,00
    });

    central.registrar_entrada(Pacote {
        id: String::from("PAC-002"),
        descricao: String::from("Suprimentos Alimentares"),
        peso_kg: 42.8,
        valor_centavos: 85050, // R$ 850,50
    });

    central.registrar_entrada(Pacote {
        id: String::from("PAC-003"),
        descricao: String::from("Peças de Drone"),
        peso_kg: 5.2,
        valor_centavos: 12000, // R$ 120,00
    });

    // 2. Gerando Relatório Geral (Iteradores Zero-Cost)
    central.gerar_relatorio();

    // 3. Simulando Busca Rápida (O(1) com HashMap)
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
        let mut a = Armazem::new(10);
        a.registrar_entrada(Pacote { id: "TEST-1".to_string(), descricao: "D".to_string(), peso_kg: 1.0, valor_centavos: 100 });
        
        let res = a.buscar_pacote("TEST-1");
        assert!(res.is_some());
        assert_eq!(res.unwrap().id, "TEST-1");
    }

    #[test]
    fn test_carga_total() {
        let mut a = Armazem::new(10);
        a.registrar_entrada(Pacote { id: "1".to_string(), descricao: "A".to_string(), peso_kg: 10.0, valor_centavos: 0 });
        a.registrar_entrada(Pacote { id: "2".to_string(), descricao: "B".to_string(), peso_kg: 20.0, valor_centavos: 0 });
        assert_eq!(a.calcular_carga_total(), 30.0);
    }

    #[test]
    fn test_valor_total() {
        let mut a = Armazem::new(10);
        a.registrar_entrada(Pacote { id: "1".to_string(), descricao: "A".to_string(), peso_kg: 0.0, valor_centavos: 150 });
        a.registrar_entrada(Pacote { id: "2".to_string(), descricao: "B".to_string(), peso_kg: 0.0, valor_centavos: 250 });
        assert_eq!(a.calcular_valor_total(), 400);
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO INTEGRADOR SA-03 (ELITE)
    ===============================================================

    1. INDEXAÇÃO HÍBRIDA (Vec + HashMap):
       - Garantimos acesso por ordem de entrada (Vec) e por chave 
         ID (HashMap) simultaneamente, com custo de busca O(1).

    2. FANTASMA DO CPU (Otimização de Memória):
       - O uso de 'with_capacity' elimina o custo de realocação 
         dinâmica (malloc/free ocultos) durante o pico de carga.

    3. GUARDIÃO FINANCEIRO:
       - Implementação de auditoria de valor total estocado, crucial 
         para seguros e gestão de ativos logísticos.

    4. ASSUNTOS CORRELATOS:
       - Custom Traits (Eq, Hash).
       - BTreeMap (quando a ordem das chaves importa).
       - Serde (Serialização para JSON/Arquivos).
    ===============================================================
*/


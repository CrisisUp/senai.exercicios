/**
 * @file main.rs
 * @brief Atividade 08: Gerenciador de Payload (Vetores e Iteradores).
 * 
 * Aprendizados: Vec<T>, Iteradores (iter, sum), Transferência de Ownership para Coleções.
 * 
 * @section MemoryMap
 * - **Ownership**: O 'ManifestoVoo' possui o Vec, que por sua vez possui os 'Pacote's.
 * - **Borrowing**: O iterador em 'exibir_lista' toma referências temporárias de cada item.
 * - **Stack vs Heap**: O Vec guarda o ponteiro, capacidade e tamanho na stack, mas os dados reais (os itens) estão na heap.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/// Representa um pacote individual de entrega.
/// 'Fantasma do CPU': Uso de referências (&str) para descrição reduz alocações String desnecessárias.
struct Pacote<'a> {
    descricao: &'a str,
    peso_kg: f64,
}

/// Gerencia a lista de pacotes para um voo.
struct ManifestoVoo<'a> {
    itens: Vec<Pacote<'a>>,
}

impl<'a> ManifestoVoo<'a> {
    /// Cria um novo manifesto vazio.
    fn new() -> Self {
        Self {
            itens: Vec::new(),
        }
    }

    /**
     * Adiciona um pacote ao manifesto.
     * @param p O pacote que será transportado. 
     * Nota: A posse do pacote passa para o vetor 'itens'.
     */
    fn adicionar_pacote(&mut self, p: Pacote<'a>) {
        println!("[MANIFESTO]: Adicionando '{}' ({:.2} kg)", p.descricao, p.peso_kg);
        self.itens.push(p);
    }

    /**
     * Remove o último pacote adicionado (LIFO).
     * @return Option<Pacote> pois a lista pode estar vazia.
     */
    fn remover_ultimo(&mut self) -> Option<Pacote<'a>> {
        self.itens.pop()
    }

    /**
     * Calcula o peso total da carga usando iteradores.
     * Esta é a forma idiomática e performática do Rust.
     */
    fn calcular_peso_total(&self) -> f64 {
        // iter() cria um iterador de referências
        // map() extrai apenas o campo peso_kg
        // sum() realiza a soma total
        self.itens.iter()
            .map(|p| p.peso_kg)
            .sum()
    }

    /// Exibe todos os itens do manifesto.
    fn exibir_lista(&self) {
        println!("\x1b[36m--- LISTA DE CARGA ATUAL ---\x1b[0m");
        if self.itens.is_empty() {
            println!("(Vazio)");
        } else {
            for (i, p) in self.itens.iter().enumerate() {
                println!("{}. {} | {:.2} kg", i + 1, p.descricao, p.peso_kg);
            }
        }
        println!("TOTAL: \x1b[32m{:.2} kg\x1b[0m", self.calcular_peso_total());
        println!("----------------------------");
    }
}

fn main() {
    println!("===============================================");
    println!("     SKYCARGO - GERENCIADOR DE PAYLOAD         ");
    println!("===============================================");

    // 1. Criando o manifesto
    let mut meu_manifesto = ManifestoVoo::new();

    // 2. Adicionando pacotes (Passando referências &str)
    meu_manifesto.adicionar_pacote(Pacote {
        descricao: "Remédios Termolábeis",
        peso_kg: 1.2,
    });

    meu_manifesto.adicionar_pacote(Pacote {
        descricao: "Kit Primeiros Socorros",
        peso_kg: 2.5,
    });

    meu_manifesto.adicionar_pacote(Pacote {
        descricao: "Baterias de Reserva",
        peso_kg: 0.8,
    });

    // 3. Exibindo status
    meu_manifesto.exibir_lista();

    // 4. Simulando cancelamento de um item
    println!("\n[SISTEMA]: Cancelando o último item adicionado...");
    if let Some(removido) = meu_manifesto.remover_ultimo() {
        println!("\x1b[33m[REMOVIDO]:\x1b[0m {}", removido.descricao);
    }

    // 5. Status final
    meu_manifesto.exibir_lista();

    println!("===============================================");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_soma_peso() {
        let mut m = ManifestoVoo::new();
        m.adicionar_pacote(Pacote { descricao: "A", peso_kg: 10.0 });
        m.adicionar_pacote(Pacote { descricao: "B", peso_kg: 5.5 });
        assert_eq!(m.calcular_peso_total(), 15.5);
    }

    #[test]
    fn test_remover_ultimo() {
        let mut m = ManifestoVoo::new();
        m.adicionar_pacote(Pacote { descricao: "X", peso_kg: 1.0 });
        let p = m.remover_ultimo();
        assert!(p.is_some());
        assert_eq!(p.unwrap().descricao, "X");
        assert_eq!(m.itens.len(), 0);
    }

    #[test]
    fn test_remover_vazio() {
        let mut m = ManifestoVoo::new();
        let p = m.remover_ultimo();
        assert!(p.is_none());
    }
}

/* 
    ===============================================================
    RESUMO TEÓRICO: VETORES E ITERADORES
    ===============================================================

    1. VEC<T> E OWNERSHIP:
       - Um vetor no Rust "possui" seus elementos. Ao adicionar um 
         pacote, a struct ManifestoVoo assume a responsabilidade 
         de limpar esses dados da Heap quando sair de escopo.

    2. O PODER DO ITERADOR:
       - 'Fantasma do CPU': Usamos '.iter()' para processar itens por 
         referência, evitando clonagem de dados pesados durante o loop.
       - Encadeamento funcional: '.map().sum()' é otimizado pelo 
         compilador para evitar saltos condicionais caros.

    3. LIFETIMES EM COLEÇÕES:
       - Ao usar Pacote<'a> dentro de um Vec, garantimos que os textos 
         estáticos (&str) existam durante toda a vida do manifesto.

    4. VANTAGEM DIDÁTICA:
       - O aluno domina coleções dinâmicas com segurança absoluta, 
         evitando os famosos "segmentation faults" do C++ ao manipular 
         vetores.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Vec::with_capacity() para pré-alocação.
    - Iterator Trait e Laziness.
    - Diferença entre iter(), iter_mut() e into_iter().
    - O crate 'itertools' para operações complexas.
    ===============================================================
*/

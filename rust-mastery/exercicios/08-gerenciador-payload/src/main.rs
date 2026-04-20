/**
 * @file main.rs
 * @brief Atividade 08: Gerenciador de Payload (Vetores e Iteradores).
 * 
 * Aprendizados: Vec<T>, Iteradores (iter, sum), Transferência de Ownership para Coleções.
 * 
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */

/// Representa um pacote individual de entrega.
struct Pacote {
    descricao: String,
    peso_kg: f64,
}

/// Gerencia a lista de pacotes para um voo.
struct ManifestoVoo {
    itens: Vec<Pacote>,
}

impl ManifestoVoo {
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
    fn adicionar_pacote(&mut self, p: Pacote) {
        println!("[MANIFESTO]: Adicionando '{}' ({:.2} kg)", p.descricao, p.peso_kg);
        self.itens.push(p);
    }

    /**
     * Remove o último pacote adicionado (LIFO).
     * @return Option<Pacote> pois a lista pode estar vazia.
     */
    fn remover_ultimo(&mut self) -> Option<Pacote> {
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

    // 2. Adicionando pacotes (Criação de String e Struct)
    meu_manifesto.adicionar_pacote(Pacote {
        descricao: String::from("Remédios Termolábeis"),
        peso_kg: 1.2,
    });

    meu_manifesto.adicionar_pacote(Pacote {
        descricao: String::from("Kit Primeiros Socorros"),
        peso_kg: 2.5,
    });

    meu_manifesto.adicionar_pacote(Pacote {
        descricao: String::from("Baterias de Reserva"),
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
        m.adicionar_pacote(Pacote { descricao: String::from("A"), peso_kg: 10.0 });
        m.adicionar_pacote(Pacote { descricao: String::from("B"), peso_kg: 5.5 });
        assert_eq!(m.calcular_peso_total(), 15.5);
    }

    #[test]
    fn test_remover_ultimo() {
        let mut m = ManifestoVoo::new();
        m.adicionar_pacote(Pacote { descricao: String::from("X"), peso_kg: 1.0 });
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
       - Um vetor no Rust "possui" seus elementos. Se você adicionar 
         um objeto a um vetor, a variável original perde a posse.
       - Se o vetor for destruído, todos os seus elementos também 
         serão limpos da memória (RAII).

    2. O PODER DO ITERADOR:
       - O método 'iter()' permite percorrer os dados sem retirá-los 
         do vetor (emprestando-os).
       - Encadeamento funcional: '.iter().map().sum()' é mais seguro 
         e geralmente tão rápido quanto um loop 'for' manual.

    3. ENUMERATE:
       - O método '.enumerate()' é útil para obter o índice do item 
         enquanto percorremos a lista.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende a lidar com dados dinâmicos e percebe como 
         o Rust facilita o tratamento de listas vazias através do 
         tipo 'Option' (retorno do pop()).
    ===============================================================
*/

/**
 * @file main.rs
 * @brief Atividade 18: Lista Ligada Manual (Box e Recursão).
 *
 * Aprendizados: Box<T>, Recursividade, Memória na Heap, Enums Recursivos.
 *
 * @author SENAI - Rust Master
 * @date 20/04/2026
 */
use std::io::{self, Write};
use std::mem; // Para troca eficiente de memória

/// Enum que define a estrutura recursiva da lista.
/// Usamos Box para que o tamanho de 'No' seja conhecido pelo compilador.
enum ListaEventos {
    Vazia,
    No(String, Box<ListaEventos>),
}

impl ListaEventos {
    /// Inicializa uma lista vazia.
    fn new() -> Self {
        ListaEventos::Vazia
    }

    /**
     * Adiciona um evento no topo da lista (Cabeça).
     * @param msg A mensagem de log.
     */
    fn adicionar_evento(&mut self, msg: String) {
        // 'mem::take' substitui o valor atual por 'Vazia' temporariamente
        // para que possamos construir o novo Nó com a lista antiga.
        let lista_antiga = mem::take(self);
        *self = ListaEventos::No(msg, Box::new(lista_antiga));
        println!("\x1b[32m[OK]:\x1b[0m Evento registrado no histórico.");
    }

    /**
     * Remove o evento mais recente (LIFO).
     * @return Option<String> com a mensagem do evento.
     */
    fn remover_evento(&mut self) -> Option<String> {
        // Usamos match para desestruturar o nó
        match mem::take(self) {
            ListaEventos::Vazia => None,
            ListaEventos::No(msg, proximo) => {
                // Move o ponteiro da lista para o próximo elemento
                *self = *proximo;
                Some(msg)
            }
        }
    }

    /// Percorre a lista exibindo todos os eventos.
    fn exibir_historico(&self) {
        println!("\n\x1b[36m--- HISTÓRICO DE EVENTOS (Pilha) ---\x1b[0m");
        let mut atual = self;
        let mut count = 1;

        while let ListaEventos::No(msg, proximo) = atual {
            println!("  {:02}. {}", count, msg);
            atual = proximo;
            count += 1;
        }

        if count == 1 {
            println!("  (Nenhum evento registrado)");
        }
        println!("------------------------------------");
    }
}

/// O Rust precisa saber como trocar um valor por ListaEventos::Vazia.
impl Default for ListaEventos {
    fn default() -> Self {
        ListaEventos::Vazia
    }
}

fn main() {
    let mut meu_historico = ListaEventos::new();

    println!("===============================================");
    println!("     SKYCARGO - GESTOR DE HISTÓRICO            ");
    println!("===============================================");

    loop {
        println!("\n1. Adicionar Log");
        println!("2. Remover Último Log");
        println!("3. Ver Histórico Completo");
        println!("0. Sair");
        print!("Escolha: ");
        io::stdout().flush().unwrap();

        let mut escolha = String::new();
        io::stdin().read_line(&mut escolha).unwrap();

        match escolha.trim() {
            "1" => {
                print!("Digite o evento: ");
                io::stdout().flush().unwrap();
                let mut log = String::new();
                io::stdin().read_line(&mut log).unwrap();
                meu_historico.adicionar_evento(log.trim().to_string());
            }
            "2" => match meu_historico.remover_evento() {
                Some(msg) => println!("\x1b[33m[REMOVIDO]:\x1b[0m {}", msg),
                None => println!("\x1b[31m[AVISO]:\x1b[0m Histórico já está vazio."),
            },
            "3" => meu_historico.exibir_historico(),
            "0" => break,
            _ => println!("Opção inválida."),
        }
    }

    println!("Encerrando gestor... Memória da lista será limpa automaticamente.");
}

// -----------------------------------------------------------------------------
// TESTES UNITÁRIOS
// -----------------------------------------------------------------------------
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_pilha_operacoes() {
        let mut lista = ListaEventos::new();
        lista.adicionar_evento("E1".to_string());
        lista.adicionar_evento("E2".to_string());

        assert_eq!(lista.remover_evento(), Some("E2".to_string()));
        assert_eq!(lista.remover_evento(), Some("E1".to_string()));
        assert_eq!(lista.remover_evento(), None);
    }
}

/*
    ===============================================================
    RESUMO TEÓRICO: ESTRUTURAS RECURSIVAS E BOX
    ===============================================================

    1. O DESAFIO DO TAMANHO:
       - No Rust, o tamanho de cada tipo deve ser conhecido em
         tempo de compilação. Uma lista ligada "pura" teria tamanho
         infinito.
       - 'Box<T>' resolve isso: ele é um ponteiro para a Heap. O
         tamanho do Box é apenas o tamanho do endereço de memória
         (fixo).

    2. RECURSIVIDADE SEGURA:
       - Ao contrário do C++, você não precisa se preocupar em deletar
         os nós da lista. O Rust percorre a recursão chamando o
         destrutor de cada Box automaticamente.

    3. MEM::TAKE:
       - Esta é uma ferramenta avançada. Ela permite que "roubemos"
         o valor de uma variável temporariamente, deixando um valor
         padrão (Default) no lugar, para evitar problemas com o
         Borrow Checker durante mudanças estruturais.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende como as coleções de alto nível (como o Vec)
         são construídas por baixo do pano, unindo Enums, Heap e
         Ponteiros.
    ===============================================================
*/

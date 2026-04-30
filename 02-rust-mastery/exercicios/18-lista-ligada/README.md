# 🦀 Atividade 18: Lista Ligada Manual (Box e Recursão)

## 🎯 Estudo de Caso

A "SkyCargo" precisa de um sistema de rastreamento de histórico de voo que funcione como uma pilha de eventos. Como não sabemos quantos eventos ocorrerão e precisamos de inserção rápida no topo, uma **Lista Ligada (Linked List)** é a estrutura ideal. O desafio é implementar isso no Rust, onde o compilador exige que saibamos o tamanho de tudo em tempo de compilação.

## 🛠️ Necessidade Técnica

Estruturas recursivas (onde um nó aponta para outro nó do mesmo tipo) apresentam um desafio no Rust:

* **Recursive Types:** O Rust não permite que uma struct contenha ela mesma diretamente (tamanho infinito).
* **`Box<T>` (Indireção):** Usamos o `Box` para colocar o próximo nó na Heap, transformando um tamanho infinito em um tamanho de ponteiro conhecido (fixo).
* **Enums para Estados:** Usamos Enums para representar se a lista acabou (`None`) ou se há mais um elemento (`Some(Box<Node>)`).

## 📋 Requisitos

1. Criar o enum `ListaEventos` com as variantes `Vazia` e `No(String, Box<ListaEventos>)`.
2. Implementar métodos para a lista:
    * `new()`: Cria uma lista vazia.
    * `adicionar_evento(&mut self, msg: String)`: Insere no topo da lista.
    * `remover_evento(&mut self) -> Option<String>`: Remove do topo.
    * `exibir_historico(&self)`: Percorre a lista recursivamente ou via loop.
3. Criar um menu interativo para o usuário adicionar e remover logs de eventos.

## ⚠️ Análise de Falha Crítica
- **Deadlocks:** Não se aplica a estruturas de dados de thread única como esta, a menos que envolvidas em `Arc<Mutex<T>>`. O risco principal aqui é o **Stack Overflow** em listas extremamente longas devido à recursão profunda durante a destruição automática (Drop).
- **Send/Sync Violations:** `Box<T>` implementa `Send` e `Sync` se `T` implementar `Send` e `Sync`. Nossa lista de `String` é segura para ser movida entre threads (`Send`), mas não compartilhada simultaneamente sem sincronização.
- **Stack vs Heap:** O Enum `ListaEventos` reside na **Stack**, mas sua variante `No` contém um `Box` que aponta para o próximo nó no **Heap**. Cada nó adicionado aloca um novo bloco de memória no Heap, garantindo persistência fora do escopo da função de inserção.

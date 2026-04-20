# 🦀 Atividade 08: Gerenciador de Payload (Vetores e Coleções)

## 🎯 Estudo de Caso

Um drone de entrega precisa de um **Manifesto de Voo** que liste todos os pacotes a serem transportados. Como o número de pacotes varia a cada viagem, não podemos usar arrays de tamanho fixo. Precisamos de uma coleção dinâmica que permita adicionar, remover e processar itens de forma eficiente e segura.

## 🛠️ Necessidade Técnica

Em Rust, o **`Vec<T>`** (Vetor) é a coleção dinâmica padrão, equivalente ao `std::vector` do C++:

* **Alocação na Heap:** O vetor cresce conforme necessário, gerenciando a reatribuição de memória automaticamente.
* **Ownership e Vetores:** Quando você coloca um objeto dentro de um vetor, o vetor se torna o novo dono dele.
* **Iteradores:** Rust fornece ferramentas poderosas para percorrer coleções de forma funcional (`iter`, `map`, `sum`).

## 📋 Requisitos

1. Criar a struct `Pacote` com `descricao` (String) e `peso` (f64).
2. Criar a struct `ManifestoVoo` que contém um `Vec<Pacote>`.
3. Implementar métodos para:
    * `adicionar_pacote(&mut self, p: Pacote)`: Adiciona um novo item.
    * `remover_ultimo(&mut self) -> Option<Pacote>`: Remove e retorna o último pacote.
    * `calcular_peso_total(&self) -> f64`: Soma o peso de todos os itens usando iteradores.
4. O programa deve exibir a lista completa de pacotes e o peso total da carga.

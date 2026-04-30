# 🦀 Atividade 09: Banco de Dados de Clientes (HashMap)

## 🎯 Estudo de Caso

A "SkyCargo" precisa de um sistema rápido para localizar clientes e verificar o número de entregas realizadas por cada um. Como o volume de clientes é grande, uma busca linear em um vetor seria lenta. Precisamos de uma estrutura de dados de "chave-valor" (Dicionário) que permita acesso instantâneo via ID do cliente.

## 🛠️ Necessidade Técnica

Em Rust, o **`HashMap<K, V>`** é a coleção ideal para mapear chaves únicas para valores:

* **Acesso Direto:** Localiza um valor em tempo constante (O(1)) em média.
* **Segurança de Chaves:** Não permite duplicatas (inserir uma chave existente sobrescreve o valor anterior).
* **Option no Get:** O método `.get()` sempre retorna um `Option`, protegendo o programa caso a chave não exista.

## 📋 Requisitos

1. Criar a struct `HistoricoCliente` com `nome` (String) e `total_entregas` (u32).
2. Criar um `HashMap<String, HistoricoCliente>` onde a chave é o ID (CPF/CNPJ).
3. Implementar funções para:
    * Adicionar ou atualizar um cliente.
    * Incrementar o contador de entregas de um cliente existente.
    * Buscar informações de um cliente pelo ID.
4. O programa deve exibir o banco de dados completo e simular buscas com sucesso e falha.

## 🛡️ Análise de Falha Crítica

Nesta atividade, exploramos os limites de segurança das coleções:

1.  **Riscos de Hash Collision:** O `HashMap` padrão do Rust usa o algoritmo *SipHash*, que é resistente a ataques de colisão de hash (DoS). No entanto, em sistemas de tempo real crítico, a variação de tempo (O(1) médio vs O(n) no pior caso) deve ser considerada.
2.  **Panic em Option/Result:** O uso de `.unwrap()` em chaves inexistentes causaria um `panic`. Demonstramos como o `match` ou `if let` garantem a sobrevivência do software mesmo com entradas inválidas.
3.  **Trait Bounds Complexity:** Embora não seja o foco aqui, a complexidade aumenta quando as chaves não implementam `Eq` ou `Hash`, o que impediria o uso no `HashMap`.

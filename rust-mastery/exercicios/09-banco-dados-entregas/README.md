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

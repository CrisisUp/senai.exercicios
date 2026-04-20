# 🦀 Atividade 12: Processamento de Dados de Voo (Closures e Iteradores)

## 🎯 Estudo de Caso

A "SkyCargo" coleta milhares de pontos de dados de seus drones: altitude, velocidade, temperatura e nível de bateria. Para realizar análises em tempo real, precisamos filtrar leituras anômalas (ex: picos de altitude) e converter unidades (ex: de metros para pés) de forma rápida e eficiente. O processamento deve ser feito de forma funcional para evitar erros de estado compartilhado.

## 🛠️ Necessidade Técnica

Em Rust, o processamento de coleções é feito via **Iteradores** e **Closures**:

* **Closures (`|args| { code }`):** Funções anônimas que podem capturar variáveis do ambiente. São ideais para passar lógica personalizada para métodos de coleções.
* **Iteradores (Laziness):** Os iteradores do Rust são "preguiçosos". Eles não fazem nada até serem consumidos (ex: via `collect()` ou `sum()`).
* **Métodos Poderosos:**
  * `filter()`: Seleciona itens com base em uma condição.
  * `map()`: Transforma cada item da coleção.
  * `any()` / `all()`: Verificações rápidas de condições.

## 📋 Requisitos

1. Criar a struct `LeituraVoo` com `id`, `altitude` e `velocidade`.
2. Implementar uma função que recebe um vetor de leituras e retorna apenas aquelas acima de uma determinada altitude (usando `filter`).
3. Implementar uma função que converte as altitudes de metros para pés (usando `map`).
4. Demonstrar o uso de uma closure que captura uma variável externa para ajustar um limite de tolerância.
5. Criar testes unitários para validar a filtragem e a transformação.

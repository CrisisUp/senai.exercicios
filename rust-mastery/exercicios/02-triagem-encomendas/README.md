# 🦀 Atividade 02: Triagem de Encomendas (Enums e Pattern Matching)

## 🎯 Estudo de Caso

A "SkyCargo" agora precisa classificar as encomendas recebidas no centro de distribuição. As encomendas podem ser de três tipos:

1. **Frágil** (exige manuseio especial).
2. **Urgente** (prioridade máxima).
3. **Padrão** (transporte normal).

O sistema deve calcular o custo de seguro com base no tipo da encomenda.

## 🛠️ Necessidade Técnica

Em Rust, os **Enums** são muito mais do que simples listas de constantes. Eles podem conter dados associados:

* **Enums com Dados:** Permitem modelar estados complexos de forma segura.
* **Pattern Matching (`match`):** É o controle de fluxo definitivo do Rust. Ele obriga você a tratar todos os casos possíveis (exaustividade), eliminando erros de lógica.
* **Derivação de Traits (`#[derive(Debug)]`):** Facilita a impressão de estruturas para depuração.

## 📋 Requisitos

### 1. Definir um enum `TipoEncomenda` com variantes para Frágil, Urgente e Padrão

### 2. Implementar uma função `calcular_seguro(tipo: TipoEncomenda, valor_item: f64) -> f64`

### 3. Regras de Seguro

* **Frágil:** 10% do valor do item + R$ 20,00 de taxa de manuseio.
* **Urgente:** 5% do valor do item + R$ 50,00 de taxa de prioridade.
* **Padrão:** Apenas 2% do valor do item.

### 4. O programa deve exibir um relatório formatado para cada tipo de teste

## 🛡️ Análise de Falha Crítica (Refatoração de Elite)

*   **Riscos de Panic:** O uso de `f64` para cálculos monetários pode levar a erros de precisão e, em casos extremos de conversão, falhas silenciosas. A refatoração para `u64` elimina imprecisões de ponto flutuante.
*   **Use-after-move:** O Rust impede este erro nativamente. Ao passar referências (`&`), garantimos que o dono da encomenda (`encomendas` vector) mantenha a posse dos dados durante a iteração.
*   **Borrow Checker Errors:** Ao iterar com `&encomendas`, criamos referências compartilhadas. Tentar modificar a encomenda dentro do loop causaria um erro de compilação, garantindo a integridade dos dados de triagem.
*   **Memory Overheads:** O uso de `Enum` em Rust é extremamente eficiente (o tamanho é o da maior variante + tag). Evitamos alocações desnecessárias no Heap ao usar tipos primitivos e referências.

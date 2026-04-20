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

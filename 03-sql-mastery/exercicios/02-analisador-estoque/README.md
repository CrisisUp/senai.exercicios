# 🗄️ Atividade 02: Analisador de Estoque (Agregações e Agrupamentos)

## 🎯 Estudo de Caso

A "SkyStore" precisa de uma visão executiva do seu estoque. O gerente não quer ver uma lista de produtos, mas sim os **números consolidados**:

1. Qual o valor total investido em estoque?
2. Quantos produtos temos em cada categoria?
3. Qual a média de preço dos itens de "Energia"?
4. Quais categorias possuem mais de 2 itens cadastrados?

## 🛠️ Necessidade Técnica

As **Funções de Agregação** permitem realizar cálculos sobre um conjunto de linhas e retornar um único valor:

* **COUNT():** Conta o número de registros.
* **SUM():** Soma os valores de uma coluna numérica.
* **AVG():** Calcula a média aritmética.
* **MIN() / MAX():** Encontra os valores extremos.
* **GROUP BY:** Agrupa as linhas para que as funções acima operem em subconjuntos (ex: por categoria).
* **HAVING:** Filtra os resultados **depois** do agrupamento (equivalente ao WHERE, mas para grupos).

## 📋 Requisitos

1. Recriar a estrutura da SkyStore.
2. Inserir uma massa de dados mais robusta (pelo menos 8 itens em 4 categorias diferentes).
3. Realizar 4 consultas analíticas:
    * Valor total do estoque (Preço * Estoque).
    * Quantidade de produtos por categoria.
    * Média de preço por categoria.
    * Filtrar categorias que possuem soma de estoque maior que 20 unidades.

## ⚠️ Análise de Falha Crítica

**Risco:** Imprecisão em Cálculos de Ponto Flutuante (REAL vs INTEGER).
**Cenário:** Ao utilizar o tipo `REAL` para valores monetários, o banco de dados pode arredondar centavos em operações de soma em larga escala devido à representação binária de números decimais.
**Solução:** Implementar o padrão 'Guardião Financeiro', utilizando `INTEGER` para armazenar o valor em centavos (ex: R$ 10,50 vira 1050), garantindo precisão absoluta.

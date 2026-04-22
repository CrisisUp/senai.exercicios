# 🗄️ Atividade 08: Consultas Complexas (WITH / CTE)

## 🎯 Estudo de Caso

A diretoria da "SkyCargo" solicitou um relatório de desempenho de vendas. Eles querem ver o faturamento total de cada mês, mas com um detalhe: ao lado de cada valor mensal, deve aparecer a **Média de Faturamento Anual** e a **Diferença (Variação)** para saber se o mês foi acima ou abaixo da média. Tentar fazer isso com subconsultas comuns deixa o código SQL "sujo" e difícil de manter.

## 🛠️ Necessidade Técnica

As **CTEs (Common Table Expressions)**, definidas pela cláusula **`WITH`**, funcionam como tabelas temporárias nomeadas que existem apenas durante a execução daquela query:

* **Legibilidade:** Divide uma query gigante em blocos lógicos pequenos e nomeados.
* **Reusabilidade:** Você pode consultar a mesma CTE várias vezes dentro da mesma query.
* **Organização:** Separa a lógica de "preparação dos dados" da lógica de "exibição final".

## ⚠️ Análise de Falha Crítica: Recursion Bloat em CTEs

Embora poderosas, as CTEs recursivas podem causar o **Recursion Bloat** (Inchaço por Recursão). Se a condição de parada não for bem definida ou o conjunto de dados for cíclico, a query pode consumir toda a memória RAM ou gerar um estouro de pilha.
*   **Impacto:** Queda do serviço de banco de dados e lentidão sistêmica.
*   **Prevenção:** Sempre utilizar cláusulas `LIMIT` em testes e garantir que o grafo de dados seja um DAG (Grafo Acíclico Dirigido).

## 📋 Requisitos

1. Criar a tabela `vendas` (id, data, valor).
2. Inserir uma massa de dados abrangendo pelo menos 4 meses diferentes.
3. Criar uma query usando `WITH` para:
    * Bloco 1: Somar o faturamento por mês.
    * Bloco 2: Calcular a média geral de todos os meses.
    * Consulta Final: Unir os dois blocos para mostrar Mês, Valor, Média e Diferença.

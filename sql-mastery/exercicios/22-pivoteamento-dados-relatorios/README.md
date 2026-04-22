# 🗄️ Atividade 22: Relatórios Executivos (Pivoteamento com CASE WHEN)

## 🎯 Estudo de Caso

A diretoria da "SkyCargo" quer uma visão panorâmica das operações mensais. Eles não querem uma lista longa com o nome do mês em cada linha. Eles querem uma **Tabela Cruzada (Cross-Tab)** onde as categorias de drones (Resgate, Carga, Agro) apareçam nas linhas e os trimestres do ano (Q1, Q2) apareçam como **colunas**. Isso permite comparar o desempenho dos setores lado a lado.

## 🛠️ Necessidade Técnica

O **Pivoteamento (Pivot)** é a técnica de transformar valores de linhas em cabeçalhos de colunas. No SQLite, fazemos isso usando:

* **CASE WHEN:** Avalia uma condição e retorna um valor.
* **Agregações (SUM/COUNT):** Somam os resultados do `CASE` para consolidar o dado na coluna certa.
* **GROUP BY:** Agrupa pela dimensão das linhas (ex: categoria).

## 📋 Requisitos

1. Criar a tabela `operacoes_voo` (id, categoria, mes, lucro).
2. Inserir dados simulando lucro para diferentes meses e tipos de drone.
3. Criar uma consulta que gere colunas para "Jan", "Fev" e "Mar", mostrando o lucro somado de cada categoria.
4. Adicionar uma coluna de "Total Acumulado" no final da linha.

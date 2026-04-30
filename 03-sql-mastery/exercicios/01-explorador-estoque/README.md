# 🗄️ Atividade 01: Explorador de Estoque (SELECT e Filtros Básicos)

STATUS: Padrão de Engenharia de Elite Aplicado

## 🎯 Estudo de Caso

A "SkyStore" vende peças de reposição para drones. O gerente precisa de relatórios rápidos para saber quais itens estão caros, quais estão em falta e quais são os nomes dos produtos cadastrados.

## 🛠️ Necessidade Técnica

Em SQL, o comando **`SELECT`** é a fundação da análise de dados. No entanto, para sistemas industriais, a busca deve ser indexada e a precisão financeira deve ser absoluta.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL ENGENHARIA DE DADOS)

- RISCO DE SQL INJECTION: Se o campo `WHERE nome = '...'` for preenchido diretamente via input do usuário sem sanitização, um invasor pode apagar o banco de dados inteiro.
- RISCO DE FULL TABLE SCAN: Consultas em colunas não-indexadas (como `categoria`) obrigam o banco a ler cada linha do disco. Em tabelas de 100 milhões de linhas, isso trava o servidor de dados.
- RISCO DE IMPRECISÃO REAL: Usar o tipo `REAL` para preços causa erros de arredondamento em somatórios de grandes lotes. É obrigatório o uso de **Centavos Inteiros**.

## 📋 Requisitos de Elite

1. Criar a tabela `produtos` com integridade de tipos (Guardião Financeiro).
2. População de dados simulando um inventário real de drones.
3. Consultas otimizadas evitando o uso de curingas desnecessários (`*`).

# 🗄️ Atividade 01: Explorador de Estoque (SELECT e Filtros Básicos)

## 🎯 Estudo de Caso

A "SkyStore" vende peças de reposição para drones. O gerente precisa de relatórios rápidos para saber quais itens estão caros, quais estão em falta e quais são os nomes dos produtos cadastrados.

## 🛠️ Necessidade Técnica

Em SQL, o comando **`SELECT`** é a fundação de tudo:

* **SELECT *:** Busca todas as colunas.
* **WHERE:** Filtra as linhas com base em condições (Ex: `preco > 100`).
* **ORDER BY:** Organiza os resultados (ASC ou DESC).
* **LIMIT:** Restringe a quantidade de linhas retornadas.

## 📋 Requisitos

1. Criar a tabela `produtos` com: id, nome, categoria, preco e estoque.
2. Inserir pelo menos 5 produtos (Baterias, Hélices, Sensores).
3. Realizar 3 consultas:
    * Listar todos os nomes e preços.
    * Filtrar produtos com preço acima de R$ 500,00.
    * Listar o produto mais caro da loja.

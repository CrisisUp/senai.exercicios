# 🗄️ Atividade 03: Relacionamento de Fornecedores (JOINs e Chaves Estrangeiras)

## 🎯 Estudo de Caso
A "SkyStore" percebeu que manter o nome do fornecedor dentro da tabela de produtos era ineficiente (se o fornecedor mudasse de nome, teríamos que atualizar centenas de linhas). Agora, vamos separar os dados: teremos uma tabela exclusiva para **Fornecedores** e ligaremos os **Produtos** a elas através de um código de identificação.

## 🛠️ Necessidade Técnica
Relacionar tabelas é o "R" do RDBMS (Relational Database Management System):
*   **Chave Primária (PK):** O RG único de uma linha (ex: `fornecedor.id`).
*   **Chave Estrangeira (FK):** Uma coluna em uma tabela que aponta para a PK de outra (ex: `produto.fornecedor_id`).
*   **INNER JOIN:** O comando "mágico" que junta as duas tabelas apenas onde há correspondência.
*   **Normalização:** O processo de organizar os dados para evitar repetições desnecessárias.

## 📋 Requisitos
1. Criar a tabela `fornecedores` (id, nome, pais).
2. Alterar/Criar a tabela `produtos` para incluir a coluna `fornecedor_id`.
3. Inserir 3 fornecedores (Brasil, China, Alemanha).
4. Inserir 5 produtos vinculados a esses fornecedores.
5. Realizar consultas que mostrem o nome do produto ao lado do nome do seu fornecedor.

# 🦀🗄️ Atividade Integradora: A Ponte Rust-SQL

## 🎯 Estudo de Caso

A "SkyCargo" precisa de um software de alta performance para extrair relatórios do banco de dados de estoque. Em vez de usar o terminal do SQLite, o usuário quer uma ferramenta profissional escrita em **Rust** que formate os dados e realize validações extras na memória.

## 🛠️ Necessidade Técnica

Este exercício demonstra a simbiose entre as duas linguagens:

* **Rust (Backend):** Gerencia a conexão, trata erros de rede/disco e exibe os dados.
* **SQL (Persistência):** Fornece os dados estruturados via comandos `SELECT`.
* **Biblioteca `rusqlite`:** Atua como o tradutor entre o mundo das tabelas e o mundo das structs.

## 📋 Requisitos

1. Conectar ao banco de dados existente em `sql-mastery/exercicios/01-explorador-estoque/database.db`.
2. Definir uma struct `Produto` no Rust.
3. Executar uma query SQL para buscar todos os itens.
4. Mapear cada linha da tabela para uma instância da struct Rust.
5. Exibir um relatório formatado no terminal.

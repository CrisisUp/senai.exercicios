# 🦀🗄️ Atividade Integradora 26: Migrações Automáticas (Schema Evolution)

## 🎯 Estudo de Caso

A "SkyCargo" possui centenas de drones operando em campo. Toda vez que lançamos uma atualização de software, precisamos garantir que o banco de dados interno de cada drone seja atualizado (novas tabelas para novos sensores, etc.). Não podemos pedir para o piloto rodar comandos SQL manualmente. O software em **Rust** deve detectar a versão atual do banco e aplicar as mudanças necessárias automaticamente ao iniciar.

## 🛠️ Necessidade Técnica

* **Versionamento de Banco:** Criaremos uma tabela técnica `schema_version` para saber em qual estágio o banco está.
* **Idempotência:** Scripts que podem ser rodados várias vezes sem causar erro.
* **Controle de Transação:** Usaremos transações para que, se uma migração falhar, o banco não fique em um estado inconsistente ("quebrado").

## 📋 Requisitos

1. Criar um "Motor de Migração" simples no Rust.
2. Migração 1: Criar a tabela `telemetria_v2` se ela não existir.
3. Migração 2: Adicionar a coluna `sinal_wifi` à tabela.
4. O programa deve exibir o progresso das atualizações e a versão final do esquema.

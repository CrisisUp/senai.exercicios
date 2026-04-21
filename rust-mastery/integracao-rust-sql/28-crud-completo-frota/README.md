# 🦀🗄️ Atividade Integradora 28: CRUD Completo (Gestor de Frota)

## 🎯 Estudo de Caso

A transportadora "SkyCargo" precisa de um sistema administrativo para gerenciar sua frota de drones. O operador deve ser capaz de realizar as quatro operações fundamentais em tempo real. Este será o coração administrativo da nossa aplicação.

## 🛠️ Necessidade Técnica

Dominar o ciclo **CRUD** unindo Rust e SQL:

* **Create (INSERT):** Adicionar novos drones.
* **Read (SELECT):** Listar todos os drones ou buscar um específico.
* **Update (UPDATE):** Alterar o status (ex: de 'Pronto' para 'Manutenção').
* **Delete (DELETE):** Remover drones que saíram de linha.
* **UX de Terminal:** Criar um menu robusto que trate entradas inválidas do usuário.

## 📋 Requisitos

1. Criar o banco de dados `frota_pro.db`.
2. Implementar a tabela `drones` (id, serial, modelo, status).
3. Desenvolver o menu interativo com as 4 opções de CRUD + Sair.
4. Usar **Prepared Statements** para todas as operações de escrita.
5. Exibir mensagens de sucesso e erro coloridas para o operador.

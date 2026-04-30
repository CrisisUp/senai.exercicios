# 🦀🗄️ Atividade Integradora 27: SQL Assíncrono com Tokio (Alta Performance)

## 🎯 Estudo de Caso

A "SkyCargo" desenvolveu um sistema de voo autônomo de alta frequência. O drone precisa tomar decisões de navegação a cada 10ms, mas também precisa salvar seu histórico no banco de dados. Em linguagens comuns, o drone "travaria" (bloqueio de I/O) enquanto o disco rígido grava o dado. Com **Rust Assíncrono**, o drone continua voando enquanto a gravação acontece nos bastidores.

## 🛠️ Necessidade Técnica

* **Async/Await:** Permite escrever código que "espera sem bloquear".
* **Tokio Runtime:** O motor que gerencia milhares de tarefas simultâneas em poucas threads.
* **sqlx:** Driver de banco de dados 100% assíncrono. Diferente do `rusqlite`, ele não para o programa enquanto espera o banco responder.

## 📋 Requisitos

1. Criar um banco de dados `telemetria_async.db` usando `sqlx`.
2. Implementar uma tarefa assíncrona que simula o drone "voando" (imprime no console com um timer).
3. Implementar outra tarefa assíncrona que insere dados no banco.
4. Demonstrar que as duas tarefas rodam de forma concorrente sem que uma atrase a outra.

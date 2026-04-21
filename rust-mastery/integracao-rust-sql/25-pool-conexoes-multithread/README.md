# 🦀🗄️ Atividade Integradora 25: A Frota Multithread (Connection Pooling)

## 🎯 Estudo de Caso

A central da "SkyCargo" recebe telemetria de 50 drones ao mesmo tempo. Cada drone roda em sua própria **Thread** no Rust. Precisamos salvar esses logs no banco de dados sem que uma thread tenha que esperar a outra fechar a conexão. Usaremos um **Pool de Conexões** para garantir que o banco seja acessado em paralelo com segurança.

## 🛠️ Necessidade Técnica

* **r2d2:** É um gestor de conexões genérico. Ele cria um "estoque" de conexões prontas para uso.
* **Arc (Atomic Reference Count):** Usaremos o `Arc` para compartilhar o Pool inteiro entre todas as threads.
* **Concorrência Real:** Veremos o Rust e o SQL trabalhando juntos em múltiplos núcleos da CPU.

## 📋 Requisitos

1. Configurar um Pool de Conexões para o banco da Atividade 09 de SQL (`produtos_estoque`).
2. Criar 10 Threads de simulação.
3. Cada thread deve "pedir" uma conexão ao Pool, inserir um log e devolvê-la automaticamente.
4. Provar que os dados foram inseridos via múltiplas conexões simultâneas.

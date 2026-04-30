# 🦀🗄️ Atividade Integradora 31: Gestor de Frota Pro (Async + Repository Pattern)

## 🎯 Estudo de Caso
O sistema administrativo da "SkyCargo" (da Atividade 28) precisa ser refatorado para suportar o crescimento da empresa. O objetivo é remover o acoplamento direto com o SQLite e transformar toda a operação em **Assíncrona**, garantindo que a interface não trave enquanto o banco de dados processa grandes volumes de dados.

## 🛠️ Necessidade Técnica (O Salto para Sênior)
Esta atividade introduz padrões de arquitetura de software profissional:
*   **Repository Pattern:** Criamos uma camada de abstração para o banco de dados. O código principal não sabe como os dados são salvos, ele apenas chama o "Repositório".
*   **Async Traits:** Como o Rust não suporta nativamente `async` dentro de `traits`, usaremos o crate `async-trait`.
*   **SQLx (Async):** Migração do `rusqlite` síncrono para o `sqlx` assíncrono.
*   **Injeção de Dependência:** Passamos o repositório como argumento, facilitando testes futuros.

## 📋 Requisitos
1. Definir o Trait `DroneRepository` com métodos para Criar, Listar e Deletar.
2. Implementar o `SqliteDroneRepository` usando `sqlx`.
3. Desenvolver o `main` como um loop assíncrono (`#[tokio::main]`).
4. Demonstrar a listagem e o cadastro de drones sem bloquear a thread principal.

# 🦀🗄️ Atividade Integradora 32: Relacionamentos Muitos-para-Muitos

## 🎯 Estudo de Caso
A "SkyCargo" precisa de um sistema de **Habilitação de Pilotos**. Diferente de um cargo fixo, um piloto pode estar habilitado para voar vários modelos de drones (ex: X-10 e B-22), e cada drone pode ser operado por qualquer piloto que tenha a certificação necessária. Precisamos gerenciar essas conexões dinamicamente.

## 🛠️ Necessidade Técnica
Esta é a modelagem relacional mais complexa (N:N):
*   **Tabela Pilotos:** Dados cadastrais dos operadores.
*   **Tabela Drones:** Dados da frota.
*   **Tabela de Ligação (`habilitacoes`):** Contém apenas pares de IDs (piloto_id, drone_id).
*   **SQL JOINs:** Para listar quais pilotos podem voar qual drone.
*   **Rust Mapping:** Como lidar com listas de objetos dentro de outros objetos.

## 📋 Requisitos
1. Criar as 3 tabelas no banco `certificacoes.db`.
2. Implementar funções no Rust para:
    - Cadastrar Piloto.
    - Vincular Piloto a um Drone (Habilitação).
    - Listar todos os pilotos e, para cada um, mostrar a lista de drones que ele está apto a voar.
3. Usar **Subqueries** ou **JOINs** no Rust para consolidar a informação.

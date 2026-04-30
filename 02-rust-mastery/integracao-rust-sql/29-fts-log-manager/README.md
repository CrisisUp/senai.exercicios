# 🦀🗄️ Atividade Integradora 29: CRUD com Motor de Busca (FTS5 e Rust)

## 🎯 Estudo de Caso

Os pilotos da "SkyCargo" precisam registrar relatórios detalhados de incidentes durante os voos. Como o volume de texto é alto, um sistema de busca comum (LIKE) seria ineficiente. Precisamos de um **Gestor de Incidentes** que utilize o motor de busca **FTS5** do SQLite, permitindo que o operador encontre, atualize ou remova logs baseando-se em palavras-chave.

## 🛠️ Necessidade Técnica

Implementar um ciclo CRUD completo sobre uma **Tabela Virtual**:

* **Create:** Inserir texto livre no índice FTS5.
* **Read (Search):** Usar o operador `MATCH` para localizar incidentes por palavras-chave (ex: "motor", "fumaça").
* **Update:** Corrigir relatórios já registrados.
* **Delete:** Remover registros obsoletos da tabela virtual.

## 📋 Requisitos

1. Criar o banco de dados `incidentes_pro.db`.
2. Implementar a tabela virtual `logs_incidentes` usando o módulo `fts5`.
3. Desenvolver o menu interativo:
    - Registrar Incidente.
    - Buscar por Palavra-Chave (Power Search).
    - Listar Tudo.
    - Editar Incidente por ID.
    - Excluir Incidente por ID.
4. Exibir os resultados em um formato de fácil leitura no terminal.

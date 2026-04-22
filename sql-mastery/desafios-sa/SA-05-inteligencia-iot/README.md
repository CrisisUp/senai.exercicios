# 📡 SA-05: Hub de Inteligência IoT (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyCargo" opera drones com sensores variados e relatórios de pilotos em texto
livre. O sistema central precisa:

1. Armazenar telemetria flexível (JSON).
2. Permitir buscas rápidas por palavras-chave nos relatórios (ex: "turbulência").
3. Manter a performance alta indexando apenas drones com bateria baixa (< 20%).

## 🛠️ Necessidade Técnica

Este desafio integra os conhecimentos das Atividades 13, 14 e 15:

1. **JSON & UPSERT (Atividade 13):** Gerenciar o estado dos sensores e atualizar registros existentes sem duplicidade.
2. **FTS5 (Atividade 14):** Criar um mecanismo de busca para os relatórios descritivos dos drones.
3. **Índices Parciais (Atividade 15):** Otimizar a busca de emergência apenas para o que é crítico.

## 📋 Requisitos Funcionais

1. Criar a tabela `telemetria_iot` com `serial` (UNIQUE) e `dados_json`.
2. Criar a tabela virtual `busca_relatorios` usando `fts5`.
3. Implementar um **Índice Parcial** que aponte para seriais de drones cujo JSON
indique bateria < 20.
4. Criar um script que insira novos dados via **UPSERT**.
5. Realizar uma consulta combinada: Buscar drones que reportaram "falha" no texto
(FTS5) E que tenham bateria baixa no JSON.

## 🏗️ Estrutura de Arquivos Obrigatória

- `README.md`: Requisitos.
- `queries.sql`: A arquitetura integrada.
- `INTERACAO_SQLITE.md`: Guia de busca avançada.

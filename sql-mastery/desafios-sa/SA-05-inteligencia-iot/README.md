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

## ⚠️ Análise de Falha Crítica (Riscos de Elite)

A operação de ecossistemas IoT e busca textual exige vigilância contra falhas arquiteturais que podem comprometer a integridade e a performance:

1.  **Riscos de Performance de Índices Parciais:** Se a cláusula `WHERE` do índice não for idêntica à usada nas consultas, o SQLite ignorará o índice, forçando um *Full Table Scan* em milhões de registros de telemetria, elevando o consumo de CPU e latência.
2.  **Corrupção Multi-banco:** Em operações que utilizam `ATTACH DATABASE`, falhas de energia ou interrupções durante transações distribuídas sem o uso de `BEGIN IMMEDIATE` podem levar a estados inconsistentes entre os arquivos `.db`, corrompendo a sincronia entre metadados e logs.
3.  **Latência de Dashboard:** A ausência de Views materializadas ou o uso excessivo de `json_extract` em tempo real em dashboards de alta frequência pode gerar gargalos de I/O, tornando a visualização de dados críticos lenta e inútil para tomadas de decisão em tempo real.
4.  **Insegurança de Dados:** A falta de sanitização em buscas FTS5 ou a ausência de Triggers de imutabilidade em tabelas de auditoria permite que atacantes ou erros sistêmicos apaguem rastros de falhas, comprometendo a perícia técnica pós-incidente.

## 🏗️ Estrutura de Arquivos Obrigatória

- `README.md`: Requisitos.
- `queries.sql`: A arquitetura integrada.
- `INTERACAO_SQLITE.md`: Guia de busca avançada.

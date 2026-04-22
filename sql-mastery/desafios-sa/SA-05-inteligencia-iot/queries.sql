/**
 * @file queries.sql
 * @brief Hub de Inteligência IoT com JSON, FTS5 e Índices Parciais.
 * @details Este script demonstra a integração de busca textual avançada, 
 * manipulação de dados semi-estruturados (JSON) e otimização por índices parciais.
 * @author Arquiteto de Sistemas
 * @date 2026-04-19
 *
 * @section ExecutionPlan
 * - FTS5: Utilizado para busca de texto livre nos relatórios com performance O(log n).
 * - Índices Parciais: Otimização cirúrgica para identificar drones com bateria < 20% sem indexar toda a tabela.
 * - JSON Optimization: Uso de `json_extract` e `json_valid` para integridade de dados.
 */

-- =============================================================================
-- 1. ARQUITETURA DE DADOS (DDL)
-- =============================================================================

-- Tabela Física com Telemetria JSON e Guardião Financeiro
CREATE TABLE IF NOT EXISTS telemetria_iot (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    serial TEXT UNIQUE NOT NULL,
    dados_json TEXT CHECK(json_valid(dados_json)),
    custo_operacional_centavos INTEGER DEFAULT 0 -- 💰 Guardião Financeiro
);

-- Tabela Virtual para busca textual (FTS5)
CREATE VIRTUAL TABLE IF NOT EXISTS busca_relatorios USING fts5(
    serial,
    relatorio_texto,
    tokenize = "unicode61"
);

-- Índice Parcial para otimização de Drones Críticos
CREATE INDEX IF NOT EXISTS idx_drones_criticos ON telemetria_iot(serial)
WHERE json_extract(dados_json, '$.bateria') < 20;

-- Limpando dados para o desafio
DELETE FROM telemetria_iot;
DELETE FROM busca_relatorios;

-- =============================================================================
-- 2. OPERAÇÃO DE DADOS (UPSERT E INSERÇÃO)
-- =============================================================================

-- Registrando Drone 1 (Bateria Alta, Sem problemas)
INSERT INTO telemetria_iot (serial, dados_json, custo_operacional_centavos)
VALUES ('SN-001', '{"bateria": 85, "temp": 25.0}', 1250) -- R$ 12,50
ON CONFLICT(serial) DO UPDATE SET 
    dados_json = excluded.dados_json,
    custo_operacional_centavos = excluded.custo_operacional_centavos;

INSERT INTO busca_relatorios (serial, relatorio_texto)
VALUES ('SN-001', 'Voo operando em condições normais.');

-- Registrando Drone 2 (Bateria Baixa, Relatou Falha)
INSERT INTO telemetria_iot (serial, dados_json, custo_operacional_centavos)
VALUES ('SN-002', '{"bateria": 12, "temp": 45.5}', 3500) -- R$ 35,00
ON CONFLICT(serial) DO UPDATE SET 
    dados_json = excluded.dados_json,
    custo_operacional_centavos = excluded.custo_operacional_centavos;

INSERT INTO busca_relatorios (serial, relatorio_texto)
VALUES ('SN-002', 'Alerta: Houve uma falha no motor esquerdo durante o pouso.');

-- =============================================================================
-- 3. CONSULTA DE INTELIGÊNCIA INTEGRADA
-- =============================================================================

-- Queremos drones que tenham "falha" no texto E bateria < 20 no JSON.
-- Otimizado pelo índice parcial idx_drones_criticos.
SELECT t.serial,
    json_extract(t.dados_json, '$.bateria') AS "Bateria %",
    t.custo_operacional_centavos / 100.0 AS "Custo (R$)",
    b.relatorio_texto AS "Relato do Piloto"
FROM telemetria_iot t
    JOIN busca_relatorios b ON t.serial = b.serial
WHERE b.relatorio_texto MATCH 'falha'
    AND json_extract(t.dados_json, '$.bateria') < 20;

-- =============================================================================
-- RESUMO TEÓRICO
-- =============================================================================
/*
1. FTS5 (Full-Text Search): Cria uma estrutura de dados externa (Shadow Tables) que 
   permite buscas por palavras-chave em milissegundos, independente do tamanho do texto.
2. JSON em SQLite: Permite armazenar dados semi-estruturados mantendo a validação
   via CHECK(json_valid()).
3. Índices Parciais: Reduzem o tamanho do arquivo de índice ao filtrar apenas o que 
   importa (bateria < 20), acelerando buscas críticas.
4. Integridade Monetária: O uso de INTEGER para centavos evita erros de arredondamento
   IEEE 754 comuns em tipos REAL/FLOAT.
*/

-- =============================================================================
-- ASSUNTOS CORRELATOS
-- =============================================================================
/*
- SQLite Virtual Tables (Shadow Tables).
- Tokenização de texto (Porter, Unicode61).
- Plano de Execução (EXPLAIN QUERY PLAN).
- Normalização vs Desnormalização (JSON).
*/

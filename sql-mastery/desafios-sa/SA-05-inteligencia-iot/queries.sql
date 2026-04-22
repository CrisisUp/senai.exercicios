-- =============================================================================
-- DESAFIO INTEGRADOR SA-05: HUB DE INTELIGÊNCIA IoT
-- OBJETIVO: Integrar JSON, FTS5 e Índices Parciais.
-- =============================================================================
-- 1. ARQUITETURA DE DADOS
-- Tabela Física com Telemetria JSON
CREATE TABLE IF NOT EXISTS telemetria_iot (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    serial TEXT UNIQUE NOT NULL,
    dados_json TEXT CHECK(json_valid(dados_json))
);
-- Tabela Virtual para busca textual (FTS5)
CREATE VIRTUAL TABLE IF NOT EXISTS busca_relatorios USING fts5(
    serial,
    relatorio_texto,
    tokenize = "unicode61"
);
-- Índice Parcial para otimização de Drones Críticos
-- Nota: Extraímos o valor da bateria do JSON para indexar apenas os em perigo.
CREATE INDEX IF NOT EXISTS idx_drones_criticos ON telemetria_iot(serial)
WHERE json_extract(dados_json, '$.bateria') < 20;
-- Limpando dados para o desafio
DELETE FROM telemetria_iot;
DELETE FROM busca_relatorios;
-- 2. OPERAÇÃO DE DADOS (UPSERT E INSERÇÃO)
-- Registrando Drone 1 (Bateria Alta, Sem problemas)
INSERT INTO telemetria_iot (serial, dados_json)
VALUES ('SN-001', '{"bateria": 85, "temp": 25.0}') ON CONFLICT(serial) DO
UPDATE
SET dados_json = excluded.dados_json;
INSERT INTO busca_relatorios (serial, relatorio_texto)
VALUES ('SN-001', 'Voo operando em condições normais.');
-- Registrando Drone 2 (Bateria Baixa, Relatou Falha)
INSERT INTO telemetria_iot (serial, dados_json)
VALUES ('SN-002', '{"bateria": 12, "temp": 45.5}') ON CONFLICT(serial) DO
UPDATE
SET dados_json = excluded.dados_json;
INSERT INTO busca_relatorios (serial, relatorio_texto)
VALUES (
        'SN-002',
        'Alerta: Houve uma falha no motor esquerdo durante o pouso.'
    );
-- 3. CONSULTA DE INTELIGÊNCIA INTEGRADA
-- Queremos drones que tenham "falha" no texto E bateria < 20 no JSON.
SELECT t.serial,
    json_extract(t.dados_json, '$.bateria') AS "Bateria %",
    b.relatorio_texto AS "Relato do Piloto"
FROM telemetria_iot t
    JOIN busca_relatorios b ON t.serial = b.serial
WHERE b.relatorio_texto MATCH 'falha'
    AND json_extract(t.dados_json, '$.bateria') < 20;
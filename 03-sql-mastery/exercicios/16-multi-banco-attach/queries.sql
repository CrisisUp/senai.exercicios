/**
 * @file queries.sql
 * @brief Multi-Banco e Arquivamento (ATTACH DATABASE).
 * @author Gemini CLI
 * @date 2026-04-19
 * @section ExecutionPlan Performance de Cross-DB Queries e Consolidação via UNION ALL.
 */

-- ==============================================================================
-- ATIVIDADE 16: MULTI-BANCO (ATTACH)
-- OBJETIVO: Cruzar dados de arquivos de banco de dados diferentes.
-- ==============================================================================

-- 1. SETUP DO BANCO SECUNDÁRIO (Arquivo Morto)
-- Vamos criar o arquivo fisicamente e popular.
ATTACH DATABASE 'arquivo_morto.db' AS morto;

CREATE TABLE IF NOT EXISTS morto.drones_velhos (
    id INTEGER PRIMARY KEY,
    serial TEXT,
    motivo_baixa TEXT,
    valor_sucata_cents INTEGER NOT NULL CHECK (valor_sucata_cents >= 0)
);

DELETE FROM morto.drones_velhos;
INSERT INTO morto.drones_velhos (serial, motivo_baixa, valor_sucata_cents) VALUES 
('OLD-001', 'Desgaste de motor', 50000),
('OLD-005', 'Acidente em 2024', 15000);

-- 2. SETUP DO BANCO PRINCIPAL (Dentro da sessão atual)
CREATE TABLE IF NOT EXISTS drones_ativos (
    id INTEGER PRIMARY KEY,
    serial TEXT,
    status TEXT,
    valor_estimado_cents INTEGER NOT NULL CHECK (valor_estimado_cents >= 0)
);

DELETE FROM drones_ativos;
INSERT INTO drones_ativos (serial, status, valor_estimado_cents) VALUES 
('SN-X10', 'Em Voo', 1200000),
('SN-B02', 'Pronto', 850000);

-- 3. CONSULTA CROSS-DATABASE (Unindo os dois mundos)
-- Usamos o prefixo 'morto.' para acessar o arquivo externo.
-- @section ExecutionPlan: O banco realiza scan em ambas as tabelas de arquivos diferentes.

SELECT 
    serial, 
    'ATIVO' AS situacao,
    valor_estimado_cents / 100.0 AS valor_real
FROM drones_ativos
UNION ALL
SELECT 
    serial, 
    'APOSENTADO' AS situacao,
    valor_sucata_cents / 100.0 AS valor_real
FROM morto.drones_velhos;

-- Auditoria de execução Cross-DB
EXPLAIN QUERY PLAN
SELECT serial FROM drones_ativos
UNION ALL
SELECT serial FROM morto.drones_velhos;

/* 
    ===============================================================
    RESUMO TEÓRICO: ATTACH E NAMESPACES
    ===============================================================

    1. ATTACH DATABASE: 
       - Transforma o SQLite em um sistema multi-banco. 
       - Útil para backups, migrações de dados e sharding manual.

    2. O ALIAS (AS morto): 
       - Define como você chamará o banco externo nas queries. 

    3. GUARDIÃO FINANCEIRO:
       - Implementado via INTEGER para garantir precisão em 
         valores de ativos e sucata.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Transações Atômicas Multi-banco (Two-Phase Commit).
    - Detaching Databases (DETACH).
    - VACUUM INTO para backups externos.
    ===============================================================
*/

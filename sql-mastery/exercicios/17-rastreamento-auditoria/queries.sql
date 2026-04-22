/**
 * @file queries.sql
 * @brief Rastreamento de Auditoria (Shadow Tables).
 * @author Gemini CLI
 * @date 2026-04-19
 * @section ExecutionPlan Impacto de Write Amplification em Shadow Tables e Auditoria.
 */

-- ==============================================================================
-- ATIVIDADE 17: RASTREAMENTO DE AUDITORIA (AUDIT TRAIL)
-- OBJETIVO: Implementar uma "Caixa Preta" para mudanças no banco de dados.
-- ==============================================================================

-- 1. Setup das Tabelas com Guardião Financeiro
CREATE TABLE IF NOT EXISTS configuracao_drones (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    serial TEXT UNIQUE NOT NULL,
    firmware_versao TEXT NOT NULL,
    custo_licenca_cents INTEGER NOT NULL DEFAULT 0 CHECK (custo_licenca_cents >= 0)
);

-- Tabela de Auditoria (Shadow Table)
CREATE TABLE IF NOT EXISTS auditoria_logs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    tabela_nome TEXT,
    registro_id INTEGER,
    coluna TEXT,
    valor_antigo TEXT,
    valor_novo TEXT,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP
);

DELETE FROM configuracao_drones;
DELETE FROM auditoria_logs;

-- 2. CRIAÇÃO DO GATILHO DE AUDITORIA (UPDATE)
-- Este gatilho verifica se a versão do firmware mudou e loga os dois estados.
-- @section ExecutionPlan: O trigger adiciona um passo extra de INSERT a cada UPDATE.
CREATE TRIGGER IF NOT EXISTS trg_auditoria_firmware
AFTER UPDATE OF firmware_versao ON configuracao_drones 
FOR EACH ROW 
BEGIN
    INSERT INTO auditoria_logs (
        tabela_nome,
        registro_id,
        coluna,
        valor_antigo,
        valor_novo
    )
    VALUES (
        'configuracao_drones',
        OLD.id,
        'firmware_versao',
        OLD.firmware_versao,
        NEW.firmware_versao
    );
END;

-- 3. TESTE DE AUDITORIA
-- A: Inserindo drone inicial (Padrão Guardião Financeiro)
INSERT INTO configuracao_drones (serial, firmware_versao, custo_licenca_cents)
VALUES ('SN-ALPHA', 'v1.0.0', 15000); -- R$ 150,00

-- B: Realizando um Update (Simulando uma atualização de sistema)
UPDATE configuracao_drones
SET firmware_versao = 'v1.2.5'
WHERE serial = 'SN-ALPHA';

-- 4. CONSULTA DE AUDITORIA
-- O resultado mostrará a "história" da mudança sem que tenhamos feito o log manual.
SELECT 
    l.data_hora,
    c.serial,
    l.coluna,
    l.valor_antigo,
    l.valor_novo,
    c.custo_licenca_cents / 100.0 AS custo_real
FROM auditoria_logs l
JOIN configuracao_drones c ON l.registro_id = c.id;

-- Auditoria do Plano de Execução
EXPLAIN QUERY PLAN
SELECT * FROM auditoria_logs WHERE registro_id = 1;

/* 
 ===============================================================
 RESUMO TEÓRICO: AUDIT TRAILS (GOVERNANÇA)
 ===============================================================
 
 1. TRANSPARÊNCIA: 
 - Triggers de auditoria garantem que nenhuma mudança seja 
 "silenciosa".

 2. OLD vs NEW: 
 - Referências internas que capturam o estado antes e depois.
 
 3. GUARDIÃO FINANCEIRO:
 - Mantém a precisão monetária mesmo em registros históricos.

 ===============================================================
 ASSUNTOS CORRELATOS:
 - Change Data Capture (CDC).
 - Temporal Tables (Padrão SQL:2011).
 - SQLite Session Extension.
 ===============================================================
 */

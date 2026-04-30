/**
 * @file queries.sql
 * @brief Gerenciamento de transações granulares: SAVEPOINTs e ROLLBACK TO.
 * @author SENAI C++ Engenheiro de Elite
 * @date 2026-04-19
 */

-- ==============================================================================
-- 1. SETUP DA TABELA DE MANUTENÇÃO E FATURAMENTO
-- ==============================================================================

-- Tabela de Progresso (Guardião Financeiro: custo_cents)
CREATE TABLE IF NOT EXISTS manutencao_progresso (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id TEXT NOT NULL,
    etapa TEXT NOT NULL,
    custo_cents INTEGER, -- Integridade Financeira
    status TEXT NOT NULL
);

DELETE FROM manutencao_progresso;

-- ==============================================================================
-- 2. TRANSAÇÃO LONGA COM CHECKPOINTS (Savepoints)
-- ==============================================================================

BEGIN TRANSACTION;

-- ETAPA 1: Limpeza Física (Custo: R$ 50,00)
INSERT INTO manutencao_progresso (drone_id, etapa, custo_cents, status)
VALUES ('DRONE-777', '1. Limpeza Física', 5000, 'CONCLUÍDO');

SAVEPOINT sp_limpeza;

-- ETAPA 2: Calibragem (Custo: R$ 120,50)
INSERT INTO manutencao_progresso (drone_id, etapa, custo_cents, status)
VALUES ('DRONE-777', '2. Calibragem de Sensores', 12050, 'CONCLUÍDO');

SAVEPOINT sp_calibragem;

-- ETAPA 3: Atualização de Firmware (VAI FALHAR!)
INSERT INTO manutencao_progresso (drone_id, etapa, custo_cents, status)
VALUES ('DRONE-777', '3. Firmware v4.0', 0, 'ERRO CRÍTICO');

-- ==============================================================================
-- 3. @section ExecutionPlan (O Pulo do Gato: Recuperação Parcial)
-- ==============================================================================

-- O banco desfaz apenas as operações após o checkpoint solicitado.
ROLLBACK TO sp_calibragem;

-- Tentativa de Recuperação (Firmware estável: R$ 80,00)
INSERT INTO manutencao_progresso (drone_id, etapa, custo_cents, status)
VALUES ('DRONE-777', '3. Firmware v3.9 Stable', 8000, 'CONCLUÍDO');

-- Persistência Final (Libera locks e grava no HD)
COMMIT;

-- Auditoria de Integridade Financeira
SELECT 
    drone_id, 
    SUM(custo_cents) / 100.0 AS "Total Faturado R$"
FROM manutencao_progresso
GROUP BY drone_id;

/* 
 ==============================================================================
 RESUMO TEÓRICO: SAVEPOINTS E GRANULARIDADE
 ==============================================================================
 
 1. ATOMICIDADE PARCIAL: 
 - Savepoints permitem quebrar o "Tudo ou Nada" do ACID em sub-etapas, 
 mantendo a integridade sem recomeçar do zero.
 
 2. GUARDIÃO FINANCEIRO (INTEGER Cents): 
 - O faturamento parcial das etapas deve ser somado como inteiros para evitar 
 divergências de caixa em centavos durante o fechamento.
 
 3. @section ExecutionPlan (Maintenance Overhead):
 - Cada SAVEPOINT gera uma entrada na tabela de símbolos de transação e aumenta 
 o tamanho do log temporário (undo log).

 ==============================================================================
 ASSUNTOS CORRELATOS:
 - Transações Aninhadas (Nested Transactions).
 - Deadlock Detection em transações longas.
 - Two-Phase Commit (2PC) em sistemas distribuídos.
 - Isolation Levels (Read Committed vs Serializable).
 ==============================================================================
 */

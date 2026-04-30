/**
 * @file queries.sql
 * @brief Resolução de Conflitos Profunda e Gerenciamento de Colisões.
 * @author Gemini CLI Agent
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * - INSERT OR IGNORE: Otimizado para ignorar falhas de UNIQUE sem interromper o pipeline.
 * - INSERT OR REPLACE: Operação destrutiva (DELETE + INSERT) que impacta o B-Tree e triggers.
 * - CHECK Constraints: Validação em nível de motor para garantir integridade atômica.
 * - Guardião Financeiro: Uso de INTEGER para centavos, evitando erros de arredondamento de ponto flutuante.
 */

-- 1. Setup da Tabela
CREATE TABLE IF NOT EXISTS frota_internacional (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  serial TEXT UNIQUE NOT NULL,
  horas_voo REAL CHECK (horas_voo >= 0),
  custo_reparo_centavos INTEGER DEFAULT 0 CHECK (custo_reparo_centavos >= 0) -- Guardião Financeiro
);

DELETE FROM frota_internacional;

-- Inserindo dado inicial (O drone original)
INSERT INTO frota_internacional (serial, horas_voo, custo_reparo_centavos)
VALUES ('DRONE-GLOBAL-01', 50.0, 150050); -- R$ 1.500,50

-- 2. TESTE: INSERT OR IGNORE
-- Se o serial já existe, o banco apenas ignora e não dá erro.
-- O valor continuará sendo 50.0 e o custo 150050.
INSERT
  OR IGNORE INTO frota_internacional (serial, horas_voo, custo_reparo_centavos)
VALUES ('DRONE-GLOBAL-01', 999.0, 200000);

-- 3. TESTE: INSERT OR REPLACE
-- Se o serial já existe, o banco apaga a linha antiga e insere a nova.
-- Note que o ID pode mudar e registros dependentes seriam afetados.
INSERT
  OR REPLACE INTO frota_internacional (serial, horas_voo, custo_reparo_centavos)
VALUES ('DRONE-GLOBAL-01', 75.0, 180000);

-- 4. TESTE: ERRO DE REGRA (CHECK)
-- Tentando inserir valor inválido (financeiro negativo). O banco barrou?
-- INSERT OR ABORT INTO frota_internacional (serial, custo_reparo_centavos) VALUES ('DRONE-ERRO', -50);

-- 5. CONSULTA DE PROVA
SELECT 
    id, 
    serial, 
    horas_voo, 
    custo_reparo_centavos,
    PRINTF('R$ %.2f', custo_reparo_centavos / 100.0) AS custo_formatado
FROM frota_internacional;

/* 
 ===============================================================
 RESUMO TEÓRICO: POLÍTICAS DE CONFLITO
 ===============================================================
 
 1. REPLACE: Funciona como um "Super Update", mas é tecnicamente 
    um DELETE seguido de INSERT. Cuidado com ON DELETE CASCADE.
 2. IGNORE: Silencia erros de constraint. Útil em cargas massivas
    onde duplicatas são esperadas e devem ser descartadas.
 3. ABORT vs ROLLBACK: ABORT cancela o comando; ROLLBACK desfaz 
    toda a transação ativa.
 
 ASSUNTOS CORRELATOS:
 - UPSERT (INSERT ... ON CONFLICT): Abordagem mais moderna e granular.
 - Database Triggers for Conflict Logging.
 - MVCC (Multi-Version Concurrency Control) e Lock Contention.
 ===============================================================
 */
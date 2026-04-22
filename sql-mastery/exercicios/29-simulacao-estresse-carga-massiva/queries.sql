/**
 * @file queries.sql
 * @brief Teste de estresse e carga massiva (1 milhão de registros) com integridade financeira.
 * @author SENAI C++ Engenheiro de Elite
 * @date 2026-04-19
 */

-- ==============================================================================
-- 1. SETUP DO AMBIENTE DE ESTRESSE
-- ==============================================================================

-- Tabela de Logs de Estresse (Guardião Financeiro: centavos em logs de auditoria)
CREATE TABLE IF NOT EXISTS estresse_logs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id TEXT,
    msg TEXT,
    custo_operacional_cents INTEGER -- Integridade Financeira
);

CREATE INDEX IF NOT EXISTS idx_estresse_drone ON estresse_logs(drone_id);
DELETE FROM estresse_logs;

-- ==============================================================================
-- 2. A EXPLOSÃO DE DADOS (The Big Bang - 1 Milhão de Linhas)
-- ==============================================================================

-- CTE Recursiva para gerar a massa crítica.
-- Nota: 1.000 x 1.000 via CROSS JOIN = 1.000.000 de registros.
WITH RECURSIVE gerador(n) AS (
    SELECT 1 UNION ALL SELECT n + 1 FROM gerador WHERE n < 1000
)
INSERT INTO estresse_logs (drone_id, msg, custo_operacional_cents)
SELECT 
    'DRONE-' || a.n,
    'Log de telemetria número ' || b.n,
    (a.n + b.n) * 5 -- R$ 0,05 incrementais
FROM gerador a
CROSS JOIN gerador b;

-- ==============================================================================
-- 3. @section ExecutionPlan (Performance sob Pressão)
-- ==============================================================================

-- Verificação da eficiência do índice com volume massivo.
EXPLAIN QUERY PLAN
SELECT SUM(custo_operacional_cents) / 100.0 AS "Custo Total R$"
FROM estresse_logs
WHERE drone_id = 'DRONE-500';

-- Auditoria Final
SELECT COUNT(*) AS "Total de Registros" FROM estresse_logs;

/* 
 ==============================================================================
 RESUMO TEÓRICO: CARGA MASSIVA E ESCALABILIDADE
 ==============================================================================
 
 1. DATA EXPLOSION: 
 - O uso de CROSS JOIN permite simular cenários de produção de anos em segundos. 
 
 2. GUARDIÃO FINANCEIRO (INTEGER Cents): 
 - Mesmo em simulações de estresse, a precisão financeira deve ser mantida. 
 Cálculos sobre milhões de linhas usando floats acumulariam erros inaceitáveis.
 
 3. I/O OVERHEAD:
 - Inserir 1 milhão de linhas gera um volume imenso de escrita em disco. 
 Se o banco não usar WAL, as operações de leitura concorrentes serão paralisadas.

 ==============================================================================
 ASSUNTOS CORRELATOS:
 - Write-Ahead Logging (WAL) vs Journaling Mode.
 - Bulk Insert (COPY no PostgreSQL) vs Insert em Lote.
 - Sharding e Particionamento de Tabelas Massivas.
 - Benchmarking de Latência (Percentis P95/P99).
 ==============================================================================
 */

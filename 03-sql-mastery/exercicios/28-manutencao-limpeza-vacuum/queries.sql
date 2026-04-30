/**
 * @file queries.sql
 * @brief Manutenção profunda de banco de dados: VACUUM, ANALYZE e Fragmentação.
 * @author SENAI C++ Engenheiro de Elite
 * @date 2026-04-19
 */

-- ==============================================================================
-- 1. SETUP DA TABELA PESADA (Simulando Acúmulo de Dados)
-- ==============================================================================

-- Tabela de Logs Financeiros (Guardião Financeiro: centavos inteiros)
CREATE TABLE IF NOT EXISTS logs_financeiros (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP,
    valor_cents INTEGER,
    status TEXT
);

DELETE FROM logs_financeiros;

-- População Massiva (10.000 registros para sentir o peso)
WITH RECURSIVE contador(n) AS (
    SELECT 1 UNION ALL SELECT n + 1 FROM contador WHERE n < 10000
)
INSERT INTO logs_financeiros (valor_cents, status)
SELECT n * 10, 'PROCESSADO' FROM contador;

-- ==============================================================================
-- 2. VERIFICAÇÃO DE FRAGMENTAÇÃO (Heap Bloat)
-- ==============================================================================

SELECT 'Páginas ANTES da exclusão:' AS status, page_count FROM pragma_page_count();

-- Simulação de Limpeza de Legado (Excluímos 90% dos dados)
DELETE FROM logs_financeiros WHERE id > 1000;

-- O "Falso Vazio": O arquivo no HD continua com o mesmo tamanho (Heap Bloat).
SELECT 'Páginas APÓS DELETE (sem VACUUM):' AS status, page_count FROM pragma_page_count();

-- ==============================================================================
-- 3. @section ExecutionPlan (Otimização e I/O Cost)
-- ==============================================================================

-- Antes do ANALYZE, o banco pode usar estatísticas obsoletas.
EXPLAIN QUERY PLAN
SELECT * FROM logs_financeiros WHERE valor_cents > 5000;

-- Execução do VACUUM (Bloqueio Exclusivo!)
VACUUM;

-- Atualização de Estatísticas (Reduz o I/O Cost do planejador)
ANALYZE;

SELECT 'Páginas APÓS VACUUM (Limpeza Real):' AS status, page_count FROM pragma_page_count();

/* 
 ==============================================================================
 RESUMO TEÓRICO: MANUTENÇÃO E PERFORMANCE
 ==============================================================================
 
 1. HEAP BLOAT E FRAGMENTAÇÃO: 
 - Quando linhas são deletadas, o banco não devolve o espaço ao OS imediatamente. 
 - Páginas vazias continuam ocupando RAM e disco, degradando a performance.
 
 2. VACUUM (I/O Cost): 
 - O comando VACUUM reconstrói o arquivo. É uma operação cara que requer 
 espaço extra em disco (quase o dobro do tamanho original temporariamente).
 
 3. GUARDIÃO FINANCEIRO (INTEGER Cents): 
 - Manter a precisão nos logs financeiros (centavos inteiros) é vital mesmo em 
 tabelas de log massivas.

 ==============================================================================
 ASSUNTOS CORRELATOS:
 - Auto-Vacuum (Full vs Incremental) no SQLite.
 - Autovacuum Workers no PostgreSQL e Dead Tuples.
 - Fragmentação de Índices B-Tree.
 - Estratégias de Archiving (Moving logs to cold storage).
 ==============================================================================
 */

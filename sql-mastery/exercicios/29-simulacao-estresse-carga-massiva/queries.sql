-- ==============================================================================
-- ATIVIDADE 29: TESTE DE ESTRESSE (DATA EXPLOSION)
-- OBJETIVO: Gerar e auditar 1 milhão de registros via SQL.
-- ==============================================================================
-- 1. Setup do Ambiente
CREATE TABLE IF NOT EXISTS estresse_logs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id TEXT,
    msg TEXT
);
CREATE INDEX IF NOT EXISTS idx_estresse_drone ON estresse_logs(drone_id);
DELETE FROM estresse_logs;
-- 2. A EXPLOSÃO DE DADOS (The Big Bang)
-- Criamos 1.000 números e multiplicamos por eles mesmos (1.000 * 1.000 = 1.000.000)
-- Nota: Esta operação pode levar alguns segundos.
WITH RECURSIVE gerador(n) AS (
    SELECT 1
    UNION ALL
    SELECT n + 1
    FROM gerador
    WHERE n < 1000
)
INSERT INTO estresse_logs (drone_id, msg)
SELECT 'DRONE-' || a.n,
    'Log de telemetria número ' || b.n
FROM gerador a
    CROSS JOIN gerador b;
-- 3. AUDITORIA DE MASSA
SELECT COUNT(*) AS "Total de Registros Inseridos"
FROM estresse_logs;
-- 4. TESTE DE PERFORMANCE SOB PESO
-- Mesmo com 1 milhão de linhas, o índice deve retornar o resultado instantaneamente.
EXPLAIN QUERY PLAN
SELECT *
FROM estresse_logs
WHERE drone_id = 'DRONE-500';
SELECT *
FROM estresse_logs
WHERE drone_id = 'DRONE-500'
LIMIT 5;
/* 
 ===============================================================
 RESUMO TEÓRICO: TESTE DE ESTRESSE
 ===============================================================
 
 1. CROSS JOIN (Produto Cartesiano): 
 - É a arma de destruição em massa do SQL. Une cada linha da 
 Tabela A com TODAS as linhas da Tabela B. 
 - Usado para gerar massa de teste ou simular todas as 
 combinações possíveis de um sistema.
 
 2. LIMITES DO SQLITE: 
 - O SQLite aguenta até 140 Terabytes de dados. 1 milhão de 
 linhas é apenas o aquecimento.
 
 3. VANTAGEM DIDÁTICA: 
 - O aluno perde o medo de grandes volumes e aprende a confiar 
 nos seus índices. Se a query ficar lenta com 1 milhão, o 
 problema não é o volume, é a arquitetura (falta de índice).
 ===============================================================
 */
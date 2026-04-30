-- ##############################################################################
-- # ATIVIDADE 37: UPGRADE INDUSTRIAL - PARTICIONAMENTO E PERFORMANCE (CORRIGIDO)
-- ##############################################################################

-- 1. Preparação dos Shards (Arquivos físicos separados)
-- Shard Abril
.open historico_abril.db
DROP TABLE IF EXISTS telemetria;
CREATE TABLE telemetria (id INTEGER PRIMARY KEY, veiculo_id INTEGER, velocidade REAL, data_hora DATETIME);
CREATE INDEX idx_veiculo_abr ON telemetria(veiculo_id);
INSERT INTO telemetria (veiculo_id, velocidade, data_hora) VALUES (101, 80.5, '2026-04-10 10:00:00');
INSERT INTO telemetria (veiculo_id, velocidade, data_hora) VALUES (102, 90.0, '2026-04-15 11:30:00');

-- Shard Maio
.open historico_maio.db
DROP TABLE IF EXISTS telemetria;
CREATE TABLE telemetria (id INTEGER PRIMARY KEY, veiculo_id INTEGER, velocidade REAL, data_hora DATETIME);
CREATE INDEX idx_veiculo_mai ON telemetria(veiculo_id);
INSERT INTO telemetria (veiculo_id, velocidade, data_hora) VALUES (101, 82.0, '2026-05-01 08:00:00');
INSERT INTO telemetria (veiculo_id, velocidade, data_hora) VALUES (103, 75.5, '2026-05-05 14:20:00');

-- 2. Conexão Federada no Orquestrador
.open logispeed_master.db
ATTACH DATABASE 'historico_abril.db' AS abr;
ATTACH DATABASE 'historico_maio.db' AS mai;

-- 3. CONSULTA FEDERADA DE ALTA PERFORMANCE
-- Em vez de uma VIEW persistente (proibida com ATTACH), usamos uma CTE ou UNION direta.
-- Isso garante que o otimizador de cada banco seja utilizado individualmente.

SELECT "\x1b[1;36m=== RESULTADO DA BUSCA FEDERADA (LOGISPEED 9.0) ===\x1b[0m";

SELECT 
    'ABRIL' as shard, veiculo_id, velocidade, data_hora FROM abr.telemetria WHERE veiculo_id = 101
UNION ALL
    SELECT 'MAIO' as shard, veiculo_id, velocidade, data_hora FROM mai.telemetria WHERE veiculo_id = 101
ORDER BY data_hora DESC;

-- 4. VALIDAÇÃO DO PLANO DE EXECUÇÃO (EXPLAIN)
-- Deve mostrar o uso dos índices específicos de cada shard.
SELECT "\n\x1b[1;33m[ANÁLISE DE QUERY PLAN]\x1b[0m";
EXPLAIN QUERY PLAN
SELECT veiculo_id FROM abr.telemetria WHERE veiculo_id = 101
UNION ALL
SELECT veiculo_id FROM mai.telemetria WHERE veiculo_id = 101;

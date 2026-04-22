-- ==============================================================================
-- DESAFIO INTEGRADOR SA-06: CENTRAL DE AUDITORIA E ROTAS
-- OBJETIVO: Integrar Federação, Grafos e Auditoria.
-- ==============================================================================
-- 1. SETUP DE FEDERAÇÃO
-- Conectando ao arquivo morto da atividade 16
ATTACH DATABASE '../../exercicios/16-multi-banco-attach/arquivo_morto.db' AS backup;
-- 2. ARQUITETURA LOCAL (DDL)
-- Tabela de Rotas
CREATE TABLE IF NOT EXISTS rotas_globais (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    origem TEXT NOT NULL,
    destino TEXT NOT NULL,
    distancia REAL NOT NULL
);
-- Tabela de Auditoria
CREATE TABLE IF NOT EXISTS log_auditoria_rotas (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    rota_id INTEGER,
    valor_antigo REAL,
    valor_novo REAL,
    data_log TEXT DEFAULT CURRENT_TIMESTAMP
);
DELETE FROM rotas_globais;
DELETE FROM log_auditoria_rotas;
-- 3. AUTOMAÇÃO DE AUDITORIA (TRIGGER)
CREATE TRIGGER IF NOT EXISTS trg_audit_distancia
AFTER
UPDATE OF distancia ON rotas_globais BEGIN
INSERT INTO log_auditoria_rotas (rota_id, valor_antigo, valor_novo)
VALUES (OLD.id, OLD.distancia, NEW.distancia);
END;
-- 4. POPULANDO DADOS
INSERT INTO rotas_globais (origem, destino, distancia)
VALUES ('LONDRES', 'PARIS', 344.0),
    ('PARIS', 'BERLIM', 1054.0),
    ('LONDRES', 'MADRI', 1263.0);
-- 5. OPERAÇÃO E TESTE
-- Mudando a distância Londres-Madri para simular novo trajeto
UPDATE rotas_globais
SET distancia = 1300.0
WHERE origem = 'LONDRES'
    AND destino = 'MADRI';
-- 6. CONSULTA DE INTELIGÊNCIA FINAL (RECURSIVO + CROSS-DB)
-- Queremos a rota Londres -> Berlim e ver se há algum alerta de drone aposentado.
WITH RECURSIVE navegador AS (
    SELECT destino,
        distancia AS km,
        origem || ' -> ' || destino AS caminho
    FROM rotas_globais
    WHERE origem = 'LONDRES'
    UNION ALL
    SELECT r.destino,
        n.km + r.distancia,
        n.caminho || ' -> ' || r.destino
    FROM rotas_globais r
        JOIN navegador n ON r.origem = n.destino
)
SELECT n.caminho,
    n.km,
    (
        SELECT COUNT(*)
        FROM backup.drones_velhos
    ) AS "Drones em Quarentena"
FROM navegador n
WHERE n.destino = 'BERLIM';
-- Visualizando Auditoria
SELECT *
FROM log_auditoria_rotas;
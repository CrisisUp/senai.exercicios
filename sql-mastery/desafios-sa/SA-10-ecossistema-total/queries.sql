-- ==============================================================================
-- DESAFIO FINAL SA-10: O MONUMENTO (ECOSSISTEMA TOTAL)
-- OBJETIVO: Unir todo o conhecimento da trilha em uma arquitetura de elite.
-- ==============================================================================
PRAGMA foreign_keys = ON;
-- -----------------------------------------------------------------------------
-- 1. MÓDULO DE ESTRUTURA (DDL)
-- -----------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS drones (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    serial TEXT UNIQUE NOT NULL,
    modelo TEXT NOT NULL,
    status TEXT DEFAULT 'OCIOSO'
);
CREATE TABLE IF NOT EXISTS historico_operacoes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id INTEGER,
    distancia REAL,
    telemetria_json TEXT CHECK(json_valid(telemetria_json)),
    data_missao TEXT DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (drone_id) REFERENCES drones(id) ON DELETE CASCADE
);
CREATE TABLE IF NOT EXISTS componentes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    pai_id INTEGER,
    drone_id INTEGER,
    FOREIGN KEY (pai_id) REFERENCES componentes(id) ON DELETE CASCADE,
    FOREIGN KEY (drone_id) REFERENCES drones(id) ON DELETE CASCADE
);
-- Indexação para buscas instantâneas
CREATE INDEX IF NOT EXISTS idx_ops_drone ON historico_operacoes(drone_id);
-- -----------------------------------------------------------------------------
-- 2. MÓDULO DE SEGURANÇA (TRIGGERS)
-- -----------------------------------------------------------------------------
-- Bloqueia alteração em drones que estão em missão ativa
CREATE TRIGGER IF NOT EXISTS trg_proteger_em_missao BEFORE
UPDATE ON drones
    WHEN OLD.status = 'EM_MISSAO' BEGIN
SELECT RAISE(
        ABORT,
        'BLOQUEIO DE SEGURANÇA: Impossível alterar status de drone em voo ativo!'
    );
END;
-- -----------------------------------------------------------------------------
-- 3. MÓDULO DE AUTOMAÇÃO (DML & ETL)
-- -----------------------------------------------------------------------------
DELETE FROM componentes;
DELETE FROM historico_operacoes;
DELETE FROM drones;
-- Populando Drones
INSERT INTO drones (serial, modelo, status)
VALUES ('SN-X10', 'Falcon-X', 'PRONTO'),
    ('SN-B22', 'Heavy-Lift', 'EM_MISSAO'),
    ('SN-C33', 'Agro-Vision', 'OCIOSO');
-- Populando Árvore de Peças (Recursivo)
INSERT INTO componentes (id, nome, pai_id, drone_id)
VALUES (1, 'CHASSI-01', NULL, 1),
    (2, 'BRACO-L', 1, 1),
    (3, 'MOTOR-L1', 2, 1),
    (4, 'CAMERA-RGB', NULL, 1);
-- -----------------------------------------------------------------------------
-- 4. MÓDULO DE INTELIGÊNCIA (VIEWS & WINDOW FUNCTIONS)
-- -----------------------------------------------------------------------------
-- Dashboard de Performance de Elite
CREATE VIEW IF NOT EXISTS v_dashboard_elite AS
SELECT d.serial,
    d.modelo,
    h.distancia,
    json_extract(h.telemetria_json, '$.bateria') AS "Bateria %",
    ROUND(
        AVG(h.distancia) OVER(
            PARTITION BY d.serial
            ORDER BY h.data_missao ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
        ),
        2
    ) AS "Média Móvel (3 voos)",
    RANK() OVER(
        ORDER BY h.distancia DESC
    ) AS "Rank de Distância"
FROM drones d
    JOIN historico_operacoes h ON d.id = h.drone_id;
-- -----------------------------------------------------------------------------
-- 5. SIMULAÇÃO DE CARGA (JSON & UPSERT)
-- -----------------------------------------------------------------------------
INSERT INTO historico_operacoes (drone_id, distancia, telemetria_json)
VALUES (1, 45.5, '{"bateria": 88, "sat": 12}'),
    (1, 50.2, '{"bateria": 75, "sat": 10}'),
    (2, 120.0, '{"bateria": 45, "sat": 8}');
-- -----------------------------------------------------------------------------
-- 6. CONSULTA FINAL DE MESTRE
-- -----------------------------------------------------------------------------
-- Verificando o Dashboard
SELECT *
FROM v_dashboard_elite;
-- Verificando a hierarquia (Recursivo)
WITH RECURSIVE arvore AS (
    SELECT id,
        nome,
        0 as nivel
    FROM componentes
    WHERE pai_id IS NULL
        AND drone_id = 1
    UNION ALL
    SELECT c.id,
        c.nome,
        a.nivel + 1
    FROM componentes c
        JOIN arvore a ON c.pai_id = a.id
)
SELECT nivel,
    printf('%' || (nivel * 3) || 's', '') || nome as Estrutura
FROM arvore;
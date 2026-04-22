-- ==============================================================================
-- DESAFIO INTEGRADOR SA-04: DATA WAREHOUSE LOGÍSTICO
-- OBJETIVO: Integrar Window Functions, CTEs Recursivas e Integridade Total.
-- ==============================================================================

-- 0. Configurações de Ambiente
PRAGMA foreign_keys = ON;

-- 1. ARQUITETURA DE TABELAS (DDL)

-- Tabela de Frota com Restrições
CREATE TABLE IF NOT EXISTS frota (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    serial TEXT UNIQUE NOT NULL,
    modelo TEXT NOT NULL,
    regiao TEXT NOT NULL
);

-- Tabela de Histórico com Limpeza em Cascata
CREATE TABLE IF NOT EXISTS historico_viagens (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id INTEGER,
    distancia_km REAL NOT NULL,
    data_missao TEXT DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (drone_id) REFERENCES frota(id) ON DELETE CASCADE
);

-- Tabela de Componentes (Estrutura Recursiva)
CREATE TABLE IF NOT EXISTS componentes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    pai_id INTEGER,
    drone_id INTEGER, -- Link direto com o dono original
    FOREIGN KEY (pai_id) REFERENCES componentes(id) ON DELETE CASCADE,
    FOREIGN KEY (drone_id) REFERENCES frota(id) ON DELETE CASCADE
);

-- Limpando dados para o desafio final
DELETE FROM componentes;
DELETE FROM historico_viagens;
DELETE FROM frota;

-- 2. POPULAÇÃO DE DADOS

-- Inserindo Frota
INSERT INTO frota (id, serial, modelo, regiao) VALUES 
(1, 'SN-X10', 'Falcon-X', 'Americas'),
(2, 'SN-X11', 'Falcon-X', 'Americas'),
(3, 'SN-E01', 'Eagle-Pro', 'Europa'),
(4, 'SN-E02', 'Eagle-Pro', 'Europa');

-- Inserindo Viagens
INSERT INTO historico_viagens (drone_id, distancia_km) VALUES 
(1, 150.5), (1, 200.0), -- X10 (Americas): 350.5
(2, 50.0), (2, 80.0),   -- X11 (Americas): 130.0
(3, 300.0),             -- E01 (Europa): 300.0
(4, 310.0), (4, 45.0);  -- E02 (Europa): 355.0

-- Inserindo Hierarquia de Peças (Exemplo para o Drone 1)
INSERT INTO componentes (id, nome, pai_id, drone_id) VALUES 
(1, 'CHASSI-MASTER', NULL, 1),
(2, 'BRACO-ALFA', 1, 1),
(3, 'MOTOR-KV1000', 2, 1),
(4, 'HELICE-CARBONO', 3, 1),
(5, 'SENSOR-GPS', NULL, 1);

-- 3. INTELIGÊNCIA ANALÍTICA (VIEWS E CTEs)

-- [A] DASHBOARD DE PERFORMANCE REGIONAL (Window Functions)
CREATE VIEW IF NOT EXISTS v_ranking_produtividade AS
SELECT f.regiao, f.modelo, f.serial,
       SUM(v.distancia_km) AS "Km Totais",
       RANK() OVER(PARTITION BY f.regiao ORDER BY SUM(v.distancia_km) DESC) AS "Rank na Região",
       ROUND(AVG(SUM(v.distancia_km)) OVER(PARTITION BY f.regiao), 2) AS "Média da Região"
FROM frota f
JOIN historico_viagens v ON f.id = v.drone_id
GROUP BY f.serial;

-- 4. CONSULTA FINAL DE AUDITORIA
-- Verificando o Ranking Regional
SELECT * FROM v_ranking_produtividade;

-- Verificando a Árvore de Peças do Drone 1 (Recursivo)
WITH RECURSIVE bom_drone AS (
    SELECT id, nome, pai_id, 0 AS nivel
    FROM componentes
    WHERE pai_id IS NULL AND drone_id = 1
    UNION ALL
    SELECT c.id, c.nome, c.pai_id, b.nivel + 1
    FROM componentes c
    JOIN bom_drone b ON c.pai_id = b.id
)
SELECT nivel, printf('%' || (nivel * 3) || 's', '') || nome AS "Peça"
FROM bom_drone;

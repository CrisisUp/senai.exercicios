-- ==============================================================================
-- DESAFIO INTEGRADOR SA-03: SISTEMA DE MANUTENÇÃO PREVENTIVA
-- OBJETIVO: Integrar Indexação, CTEs e Gatilhos Automáticos.
-- ==============================================================================
-- 1. ARQUITETURA DO SISTEMA (DDL)
CREATE TABLE IF NOT EXISTS frota_drones (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    modelo TEXT NOT NULL,
    horas_totais REAL DEFAULT 0.0
);
CREATE TABLE IF NOT EXISTS log_voos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id INTEGER,
    horas_viagem REAL,
    data_voo TEXT DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (drone_id) REFERENCES frota_drones(id)
);
CREATE TABLE IF NOT EXISTS alertas_manutencao (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id INTEGER,
    mensagem TEXT,
    data_alerta TEXT DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (drone_id) REFERENCES frota_drones(id)
);
-- Otimização de busca no histórico
CREATE INDEX IF NOT EXISTS idx_log_drone ON log_voos(drone_id);
-- Limpando dados para o desafio
DELETE FROM alertas_manutencao;
DELETE FROM log_voos;
DELETE FROM frota_drones;
-- 2. AUTOMAÇÃO (TRIGGERS)
-- Gatilho para atualizar o horímetro e disparar alerta de revisão
CREATE TRIGGER IF NOT EXISTS trg_pos_voo
AFTER
INSERT ON log_voos BEGIN -- A: Atualiza o horímetro do drone
UPDATE frota_drones
SET horas_totais = horas_totais + NEW.horas_viagem
WHERE id = NEW.drone_id;
-- B: Verifica se atingiu 100 horas e gera alerta
INSERT INTO alertas_manutencao (drone_id, mensagem)
SELECT NEW.drone_id,
    'REVISÃO NECESSÁRIA: Drone ultrapassou 100 horas de voo.'
FROM frota_drones
WHERE id = NEW.drone_id
    AND horas_totais >= 100.0
    AND NOT EXISTS (
        SELECT 1
        FROM alertas_manutencao
        WHERE drone_id = NEW.drone_id
    );
END;
-- 3. POPULAÇÃO INICIAL
INSERT INTO frota_drones (modelo, horas_totais)
VALUES ('X-Resgate 01', 95.0),
    ('B-Carga 05', 40.0),
    ('C-Agro 12', 10.0);
-- 4. SIMULAÇÃO DE OPERAÇÃO
-- Drone 1 voa 6 horas (vai bater 101h -> Alerta automático)
INSERT INTO log_voos (drone_id, horas_viagem)
VALUES (1, 6.0);
-- Drone 2 voa 10 horas (vai bater 50h -> Sem alerta)
INSERT INTO log_voos (drone_id, horas_viagem)
VALUES (2, 10.0);
-- 5. RELATÓRIO DE INTELIGÊNCIA (CTE)
-- Objetivo: Mostrar drones acima da média de uso da frota
WITH media_uso AS (
    SELECT AVG(horas_totais) as media_frota
    FROM frota_drones
)
SELECT d.modelo,
    d.horas_totais AS "Horas Acumuladas",
    ROUND(m.media_frota, 2) AS "Média da Frota",
    CASE
        WHEN d.horas_totais > m.media_frota THEN 'ALTO USO'
        ELSE 'USO NORMAL'
    END AS "Status de Utilização"
FROM frota_drones d,
    media_uso m;
-- Verificando alertas gerados
SELECT *
FROM alertas_manutencao;
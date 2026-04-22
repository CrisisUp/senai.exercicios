-- ==============================================================================
-- DESAFIO INTEGRADOR SA-09: MONITORAMENTO GLOBAL E SEGURANÇA
-- OBJETIVO: Unir Normalização Global com Radar de Segurança.
-- ==============================================================================
-- 1. ARQUITETURA (DDL)
CREATE TABLE IF NOT EXISTS taxas (moeda TEXT PRIMARY KEY, fator REAL);
CREATE TABLE IF NOT EXISTS operacoes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    usuario TEXT,
    valor_local REAL,
    moeda TEXT,
    latencia_ms REAL,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP
);
CREATE TABLE IF NOT EXISTS alertas (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    mensagem TEXT,
    data_alerta TEXT DEFAULT CURRENT_TIMESTAMP
);
-- 2. AUTOMAÇÃO (TRIGGER)
CREATE TRIGGER IF NOT EXISTS trg_seguranca_global
AFTER
INSERT ON operacoes BEGIN -- Alerta de Brute Force (Forense)
INSERT INTO alertas (mensagem)
SELECT 'CIBER_ATAQUE: Acesso rápido detectado para ' || NEW.usuario
FROM (
        SELECT data_hora
        FROM operacoes
        WHERE usuario = NEW.usuario
            AND id < NEW.id
        ORDER BY id DESC
        LIMIT 1
    ) AS anterior
WHERE (
        unixepoch(NEW.data_hora) - unixepoch(anterior.data_hora)
    ) < 2;
-- Alerta de Latência (SRE)
INSERT INTO alertas (mensagem)
SELECT 'PERFORMANCE: Operação lenta (' || NEW.latencia_ms || ' ms)'
WHERE NEW.latencia_ms > 500.0;
END;
-- 3. POPULAÇÃO
INSERT INTO taxas
VALUES ('USD', 5.5),
    ('EUR', 6.0),
    ('BRL', 1.0);
-- 4. CONSULTA ANALÍTICA GLOBAL
CREATE VIEW IF NOT EXISTS v_financeiro_global AS
SELECT o.usuario,
    o.valor_local || ' ' || o.moeda AS "Valor Original",
    ROUND(o.valor_local * t.fator, 2) AS "Convertido BRL",
    o.latencia_ms AS "Latência"
FROM operacoes o
    JOIN taxas t ON o.moeda = t.moeda;
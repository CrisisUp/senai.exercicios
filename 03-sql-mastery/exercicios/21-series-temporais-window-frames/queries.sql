/**
 * @file queries.sql
 * @brief Séries Temporais e Window Frames (Média Móvel).
 * @author Gemini CLI
 * @date 2026-04-21
 * @section ExecutionPlan Análise de Overheads de Windowing e Frames Deslizantes.
 */

-- ==============================================================================
-- ATIVIDADE 21: SÉRIES TEMPORAIS (WINDOW FRAMES)
-- OBJETIVO: Calcular médias móveis para detecção de tendências de queda.
-- ==============================================================================

-- 1. Setup da Tabela de Telemetria com Guardião Financeiro
CREATE TABLE IF NOT EXISTS leituras_bateria (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id TEXT NOT NULL,
    nivel_bateria REAL NOT NULL,
    -- @note Guardião Financeiro: custo_estimado_voo_cents (INTEGER)
    custo_estimado_voo_cents INTEGER DEFAULT 0,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP
);

DELETE FROM leituras_bateria;

-- 2. Populando com Série Temporal (Simulação de Voo)
INSERT INTO leituras_bateria (drone_id, nivel_bateria, custo_estimado_voo_cents, data_hora)
VALUES 
    ('X-1', 100.0, 500, '2026-04-21 10:00:00'),
    ('X-1', 98.5, 505, '2026-04-21 10:01:00'),
    ('X-1', 97.2, 510, '2026-04-21 10:02:00'),
    ('X-1', 96.0, 515, '2026-04-21 10:03:00'),
    ('X-1', 94.1, 520, '2026-04-21 10:04:00'),
    ('X-1', 88.0, 550, '2026-04-21 10:05:00'), -- Queda brusca detectada aqui
    ('X-1', 87.5, 555, '2026-04-21 10:06:00'),
    ('X-1', 86.8, 560, '2026-04-21 10:07:00'),
    ('X-1', 80.0, 600, '2026-04-21 10:08:00'), -- Segunda queda brusca
    ('X-1', 79.5, 605, '2026-04-21 10:09:00');

-- 3. CONSULTA DE MÉDIA MÓVEL (WINDOW FRAMES)
-- @section ExecutionPlan: O motor utiliza B-Tree na data_hora para evitar Full Table Scan.
SELECT data_hora,
    nivel_bateria AS "Atual (%)",
    -- Calcula a média da linha atual + as 2 anteriores
    ROUND(
        AVG(nivel_bateria) OVER(
            ORDER BY data_hora ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
        ),
        2
    ) AS "Média Móvel (3 pts)",
    -- Calcula o custo acumulado em centavos (Guardião Financeiro)
    SUM(custo_estimado_voo_cents) OVER(
        ORDER BY data_hora ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
    ) / 100.0 AS "Custo Acumulado (R$)"
FROM leituras_bateria;

-- 4. VALIDAÇÃO DE PERFORMANCE
EXPLAIN QUERY PLAN
SELECT AVG(nivel_bateria) OVER(ORDER BY data_hora) FROM leituras_bateria;

/* 
 ===============================================================
 RESUMO TEÓRICO: WINDOW FRAMES (SÉRIES TEMPORAIS)
 ===============================================================
 
 1. O QUE SÃO FRAMES?
 - Define um "sub-grupo deslizante" relativo à linha atual, permitindo
   cálculos granulares sem perder a visibilidade do registro individual.
 
 2. ROWS BETWEEN:
 - Controla a janela física de linhas. '2 PRECEDING' olha para o passado
   imediato, ideal para detectar anomalias em tempo real.
 
 3. GUARDIÃO FINANCEIRO:
 - Mesmo em telemetria, custos de operação são armazenados como 
   INTEGER (cents) para evitar drift financeiro em agregações massivas.
 
 ===============================================================
 ASSUNTOS CORRELATOS:
 - Time-series Databases (InfluxDB, TimescaleDB).
 - Exponential Moving Average (EMA).
 - Kalman Filters para suavização de sensores.
 ===============================================================
 */

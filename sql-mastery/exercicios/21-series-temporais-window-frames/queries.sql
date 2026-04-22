-- ==============================================================================
-- ATIVIDADE 21: SÉRIES TEMPORAIS (WINDOW FRAMES)
-- OBJETIVO: Calcular médias móveis para detecção de tendências de queda.
-- ==============================================================================
-- 1. Setup da Tabela de Telemetria
CREATE TABLE IF NOT EXISTS leituras_bateria (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id TEXT NOT NULL,
    nivel_bateria REAL NOT NULL,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP
);
DELETE FROM leituras_bateria;
-- 2. Populando com Série Temporal (Simulação de Voo)
INSERT INTO leituras_bateria (drone_id, nivel_bateria, data_hora)
VALUES ('X-1', 100.0, '2026-04-21 10:00:00'),
    ('X-1', 98.5, '2026-04-21 10:01:00'),
    ('X-1', 97.2, '2026-04-21 10:02:00'),
    ('X-1', 96.0, '2026-04-21 10:03:00'),
    ('X-1', 94.1, '2026-04-21 10:04:00'),
    ('X-1', 88.0, '2026-04-21 10:05:00'),
    -- Queda brusca detectada aqui
    ('X-1', 87.5, '2026-04-21 10:06:00'),
    ('X-1', 86.8, '2026-04-21 10:07:00'),
    ('X-1', 80.0, '2026-04-21 10:08:00'),
    -- Segunda queda brusca
    ('X-1', 79.5, '2026-04-21 10:09:00');
-- 3. CONSULTA DE MÉDIA MÓVEL (WINDOW FRAMES)
SELECT data_hora,
    nivel_bateria AS "Atual (%)",
    -- Calcula a média da linha atual + as 2 anteriores
    ROUND(
        AVG(nivel_bateria) OVER(
            ORDER BY data_hora ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
        ),
        2
    ) AS "Média Móvel (3 pts)",
    -- Calcula o quanto o drone caiu em relação à tendência recente
    ROUND(
        nivel_bateria - AVG(nivel_bateria) OVER(
            ORDER BY data_hora ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
        ),
        2
    ) AS "Desvio"
FROM leituras_bateria;
/* 
 ===============================================================
 RESUMO TEÓRICO: WINDOW FRAMES (SÉRIES TEMPORAIS)
 ===============================================================
 
 1. O QUE SÃO FRAMES?
 - Enquanto o 'PARTITION BY' define o grupo todo, o Frame 
 define um "sub-grupo deslizante" relativo à linha atual.
 
 2. ROWS BETWEEN:
 - Permite navegar no tempo. 
 - '2 PRECEDING' significa: olhe para 2 minutos atrás.
 
 3. ANÁLISE DE NEGÓCIO: 
 - Se o "Desvio" for um número negativo alto (ex: -5.0), 
 significa que a bateria caiu muito mais rápido do que 
 a média recente. É o gatilho perfeito para um pouso de 
 emergência.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende a lidar com dados de Stream e Sensores, 
 transformando o banco de dados em uma ferramenta de Análise 
 Preditiva.
 ===============================================================
 */
/**
 * @file atividade-40-analytics.sql
 * @brief Implementação/Componente atividade-40-analytics.sql
 * @author Cristiano
 * @date 2026
 */
-- ##############################################################################
-- # ATIVIDADE 40: DATA WAREHOUSE E ANÁLISE DE SÉRIES TEMPORAIS
-- ##############################################################################

.open logispeed_analytics.db

-- 1. Criação da Tabela de Telemetria de Alta Frequência
CREATE TABLE IF NOT EXISTS telemetria_analitica (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    caminhao_id INTEGER,
    timestamp DATETIME,
    velocidade REAL,
    combustivel_litros REAL,
    km_total REAL
);

-- 2. População de Massa de Dados para Teste (Caminhão 101 - Viagem de 1 dia)
DELETE FROM telemetria_analitica;
INSERT INTO telemetria_analitica (caminhao_id, timestamp, velocidade, combustivel_litros, km_total) VALUES
(101, '2026-04-27 08:00:00', 0, 500.0, 10000.0),
(101, '2026-04-27 08:10:00', 80, 495.0, 10013.0),
(101, '2026-04-27 08:20:00', 85, 490.0, 10027.0),
(101, '2026-04-27 08:30:00', 90, 485.0, 10042.0),
(101, '2026-04-27 08:40:00', 120, 478.0, 10062.0), -- Pico de velocidade
(101, '2026-04-27 08:50:00', 80, 440.0, 10075.0), -- ANOMALIA: Queda brusca de combustível (478 -> 440 em 10 min)
(101, '2026-04-27 09:00:00', 80, 435.0, 10088.0);

-- 3. ANÁLISE 1: Média Móvel (Suavização de Ruído)
-- Usamos Window Function para calcular a média de velocidade dos últimos 3 registros
.print "\n\x1b[1;36m=== RELATÓRIO 1: MÉDIA MÓVEL DE VELOCIDADE (CAMINHÃO 101) ===\x1b[0m"
.mode column
.headers on
SELECT 
    timestamp,
    velocidade as vel_real,
    ROUND(AVG(velocidade) OVER (
        PARTITION BY caminhao_id 
        ORDER BY timestamp 
        ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
    ), 2) as media_movel_3pts
FROM telemetria_analitica;

-- 4. ANÁLISE 2: Detecção de Anomalias (Possível Roubo/Vazamento)
-- Comparamos o nível de combustível atual com o anterior (LAG)
.print "\n\x1b[1;31m=== RELATÓRIO 2: DETECÇÃO DE ANOMALIAS DE COMBUSTÍVEL ===\x1b[0m"
WITH DeltaCombustivel AS (
    SELECT 
        caminhao_id,
        timestamp,
        combustivel_litros as atual,
        LAG(combustivel_litros) OVER (PARTITION BY caminhao_id ORDER BY timestamp) as anterior,
        km_total - LAG(km_total) OVER (PARTITION BY caminhao_id ORDER BY timestamp) as km_percorrido
    FROM telemetria_analitica
)
SELECT 
    timestamp,
    atual,
    anterior,
    (anterior - atual) as consumo_litros,
    km_percorrido,
    CASE 
        WHEN (anterior - atual) > 20 AND km_percorrido < 15 THEN '!!! ALERTA: QUEDA SUSPEITA !!!'
        ELSE 'NORMAL'
    END as status_integridade
FROM DeltaCombustivel
WHERE anterior IS NOT NULL;

-- 5. ANÁLISE 3: Ranking de Performance Industrial
-- Simulando outros caminhões para o ranking
INSERT INTO telemetria_analitica (caminhao_id, timestamp, velocidade, combustivel_litros, km_total) VALUES
(102, '2026-04-27 09:00:00', 75, 480.0, 5000.0),
(103, '2026-04-27 09:00:00', 95, 420.0, 8500.0);

.print "\n\x1b[1;32m[RANKING DE FROTA]\x1b[0m Ranking de Velocidade Média por Veículo:"
SELECT 
    caminhao_id,
    ROUND(AVG(velocidade), 2) as media_geral,
    RANK() OVER (ORDER BY AVG(velocidade) DESC) as posicao_ranking
FROM telemetria_analitica
GROUP BY caminhao_id;

-- 6. CONCLUSÃO TÉCNICA
.print "\n\x1b[1;33m[ANÁLISE DE ELITE]\x1b[0m"
.print "O uso de Window Functions transformou o SQLite em um motor de BI."
.print "Detectamos uma anomalia às 08:50 onde o combustível caiu 38L em 13km."
.print "Este rastro analítico é a base para o SRE (Site Reliability Engineering) de dados."

/* @section ExecutionPlan
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

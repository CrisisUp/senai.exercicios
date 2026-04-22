-- ==============================================================================
-- ATIVIDADE 26: OPERAÇÕES INTERNACIONAIS (CÂMBIO E FUSO)
-- OBJETIVO: Normalizar tempo em UTC e converter moedas dinamicamente.
-- ==============================================================================
-- 1. Setup das Tabelas
CREATE TABLE IF NOT EXISTS taxas_cambio (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    moeda TEXT NOT NULL,
    taxa_para_brl REAL NOT NULL,
    data_referencia TEXT DEFAULT CURRENT_DATE
);
CREATE TABLE IF NOT EXISTS entregas_globais (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id TEXT,
    custo_local REAL,
    moeda TEXT,
    data_utc TEXT NOT NULL
);
DELETE FROM taxas_cambio;
DELETE FROM entregas_globais;
-- 2. POPULAÇÃO DE DADOS
-- Taxas: 1 Libra = 7.00 Reais | 1 Dólar = 5.50 Reais
INSERT INTO taxas_cambio (moeda, taxa_para_brl)
VALUES ('GBP', 7.00),
    ('USD', 5.50),
    ('BRL', 1.00);
-- Entregas registradas em UTC
INSERT INTO entregas_globais (drone_id, custo_local, moeda, data_utc)
VALUES ('DRONE-LND', 50.0, 'GBP', '2026-04-21 12:00:00'),
    -- Almoço em Londres
    ('DRONE-SP', 120.0, 'BRL', '2026-04-21 12:00:00'),
    -- Mesma hora UTC, mas SP é manhã
    ('DRONE-NY', 30.0, 'USD', '2026-04-21 12:00:00');
-- 3. CONSULTA DE NORMALIZAÇÃO GLOBAL
SELECT drone_id AS "ID",
    data_utc AS "Hora UTC",
    -- Fuso Londres: UTC +1 (Horário de Verão)
    datetime(data_utc, '+1 hours') AS "Hora Londres",
    -- Fuso São Paulo: UTC -3
    datetime(data_utc, '-3 hours') AS "Hora São Paulo",
    custo_local || ' ' || e.moeda AS "Custo Local",
    -- Conversão Financeira via JOIN com a tabela de taxas
    ROUND(custo_local * t.taxa_para_brl, 2) AS "Total em BRL"
FROM entregas_globais e
    JOIN taxas_cambio t ON e.moeda = t.moeda;
/* 
 ===============================================================
 RESUMO TEÓRICO: O BANCO DE DADOS GLOBAL
 ===============================================================
 
 1. DATETIME(col, offset): 
 - Esta função é o padrão para lidar com fusos. 
 - Lembre-se: O banco nunca "sabe" o fuso, ele apenas soma 
 ou subtrai horas conforme você manda.
 
 2. INTEGRIDADE MONETÁRIA: 
 - Nunca salve o valor convertido no registro da venda. 
 - Se a taxa for corrigida depois, você perde a rastreabilidade. 
 - O JOIN com a tabela de taxas garante que o cálculo seja 
 auditável.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende a construir sistemas que não quebram ao cruzar 
 fronteiras, preparando-o para o mercado de multinacionais e 
 serviços em nuvem.
 ===============================================================
 */
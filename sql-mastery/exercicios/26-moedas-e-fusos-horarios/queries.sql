/**
 * @file queries.sql
 * @brief Operações Internacionais, Moedas e Fusos Horários.
 * @author Gemini CLI Agent
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * - UTC Normalization: O uso de DATETIME/STRFTIME em UTC garante uma B-Tree cronológica sem furos de DST.
 * - Time Offsets: O cálculo de fuso no SELECT é puramente computacional (O(1)) sem impacto em I/O.
 * - Câmbio Dinâmico: O JOIN com a tabela de taxas é otimizado se houver índice em (moeda, data_referencia).
 * - Guardião Financeiro: Uso de INTEGER cents para evitar Floating Point Drift em conversões massivas.
 */

-- 1. Setup das Tabelas
CREATE TABLE IF NOT EXISTS taxas_cambio (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    moeda TEXT NOT NULL,
    taxa_para_brl_fator INTEGER NOT NULL, -- Ex: 7.00 -> 70000 (fator 10000)
    data_referencia TEXT DEFAULT CURRENT_DATE
);

CREATE TABLE IF NOT EXISTS entregas_globais (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id TEXT,
    custo_local_centavos INTEGER, -- Guardião Financeiro
    moeda TEXT,
    data_utc TEXT NOT NULL
);

DELETE FROM taxas_cambio;
DELETE FROM entregas_globais;

-- 2. POPULAÇÃO DE DADOS
-- Taxas com fator 10.000 (1 Libra = 70.000 unidades de fator)
INSERT INTO taxas_cambio (moeda, taxa_para_brl_fator)
VALUES ('GBP', 70000),
    ('USD', 55000),
    ('BRL', 10000);

-- Entregas registradas em UTC
INSERT INTO entregas_globais (drone_id, custo_local_centavos, moeda, data_utc)
VALUES ('DRONE-LND', 5000, 'GBP', '2026-04-21 12:00:00'), -- £ 50,00
    ('DRONE-SP', 12000, 'BRL', '2026-04-21 12:00:00'), -- R$ 120,00
    ('DRONE-NY', 3000, 'USD', '2026-04-21 12:00:00');  -- $ 30,00

-- 3. CONSULTA DE NORMALIZAÇÃO GLOBAL
SELECT drone_id AS "ID",
    data_utc AS "Hora UTC",
    -- Fuso Londres: UTC +1 (Horário de Verão)
    datetime(data_utc, '+1 hours') AS "Hora Londres",
    -- Fuso São Paulo: UTC -3
    datetime(data_utc, '-3 hours') AS "Hora São Paulo",
    PRINTF('%d %s', e.custo_local_centavos / 100.0, e.moeda) AS "Custo Local",
    -- Conversão Financeira: (custo_cents * fator) / 10000.0 / 100.0 para chegar em BRL formatado
    PRINTF('R$ %.2f', (e.custo_local_centavos * t.taxa_para_brl_fator) / 10000.0 / 100.0) AS "Total em BRL"
FROM entregas_globais e
    JOIN taxas_cambio t ON e.moeda = t.moeda;

/* 
 ===============================================================
 RESUMO TEÓRICO: O BANCO DE DADOS GLOBAL
 ===============================================================
 
 1. DATETIME(col, offset): Padrão para fusos, sempre sobre UTC.
 2. INTEGRIDADE MONETÁRIA: Uso de INTEGER cents e fatores de câmbio
    evita imprecisões decimais em conversões repetidas.
 3. UTC NORMALIZATION: Essencial para logs unificados em sistemas
    distribuídos globalmente.

 ASSUNTOS CORRELATOS:
 - ISO 8601 (Standard for Date and Time).
 - ISO 4217 (Currency Codes).
 - Floating Point Arithmetic (IEEE 754).
 ===============================================================
 */
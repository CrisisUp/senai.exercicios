/**
 * @file queries.sql
 * @brief Otimização de Espaço e Cálculo (Índices Parciais e Colunas Virtuais).
 * @author Gemini CLI
 * @date 2026-04-19
 * @section ExecutionPlan Foco em Performance de Índices Parciais e Colunas Virtuais.
 */

-- ==============================================================================
-- ATIVIDADE 15: OTIMIZAÇÃO DE ESPAÇO (ÍNDICES PARCIAIS E COLUNAS GERADAS)
-- OBJETIVO: Reduzir uso de disco e acelerar cálculos repetitivos.
-- ==============================================================================

-- 1. Criação da Tabela com COLUNA VIRTUAL e Guardião Financeiro
-- O campo 'score_saude' não existe fisicamente no HD, é calculado na hora.
-- 'custo_manutencao_cents' segue o padrão Guardião Financeiro (INTEGER).
CREATE TABLE IF NOT EXISTS status_frota (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    serial TEXT NOT NULL,
    bateria REAL NOT NULL,
    horas_voo REAL NOT NULL,
    custo_manutencao_cents INTEGER NOT NULL CHECK (custo_manutencao_cents >= 0),
    score_saude REAL GENERATED ALWAYS AS (bateria * horas_voo) VIRTUAL
);

DELETE FROM status_frota;

-- 2. População com dados variados
INSERT INTO status_frota (serial, bateria, horas_voo, custo_manutencao_cents)
VALUES 
    ('X1-OK', 95.0, 10.0, 5000),       -- R$ 50,00
    ('X2-PERIGO', 12.0, 50.0, 25000),  -- R$ 250,00 (Indexado)
    ('X3-OK', 80.0, 20.0, 7500),       -- R$ 75,00
    ('X4-CRITICO', 5.0, 100.0, 55000); -- R$ 550,00 (Indexado)

-- 3. CRIAÇÃO DE ÍNDICE PARCIAL
-- Este índice é minúsculo, pois ignora todos os drones com bateria saudável.
CREATE INDEX IF NOT EXISTS idx_emergencia ON status_frota(serial)
WHERE bateria < 20.0;

-- 4. CONSULTAS E AUDITORIA
-- [A] CONSULTANDO A COLUNA VIRTUAL E FINANCEIRO
SELECT 
    serial,
    score_saude,
    custo_manutencao_cents / 100.0 AS custo_manutencao_real
FROM status_frota;

-- [B] AUDITORIA DE PERFORMANCE (ÍNDICE PARCIAL)
-- @section ExecutionPlan: Quando filtramos por bateria < 20, o banco usa o índice inteligente.
EXPLAIN QUERY PLAN
SELECT *
FROM status_frota
WHERE bateria < 20.0;

-- [C] COMPARAÇÃO: Busca por drone saudável (Full Scan)
-- Como o índice ignora drones saudáveis, aqui o banco terá que ler tudo.
EXPLAIN QUERY PLAN
SELECT *
FROM status_frota
WHERE bateria > 50.0;

/* 
 ===============================================================
 RESUMO TEÓRICO: ENGENHARIA DE ARMAZENAMENTO
 ===============================================================
 
 1. COLUNAS VIRTUAIS (VIRTUAL):
 - Eliminam a redundância de dados. Se os valores base mudam, 
 o resultado muda automaticamente sem riscos de inconsistência.
 
 2. ÍNDICES PARCIAIS (WHERE):
 - São a solução definitiva para o dilema do espaço vs. velocidade. 
 - Ideais para filtrar estados raros (erros, pendências, alertas).
 
 3. GUARDIÃO FINANCEIRO:
 - Uso de INTEGER para centavos evita erros de arredondamento 
 de ponto flutuante (IEEE 754) em sistemas críticos.

 ===============================================================
 ASSUNTOS CORRELATOS:
 - SQLite Query Planner e estatísticas de índices (ANALYZE).
 - Índices de Cobertura (Covering Indexes).
 - Determinação de Funções (Deterministic vs Non-deterministic).
 ===============================================================
 */

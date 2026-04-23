/**
 * @file queries.sql
 * @brief Atividade 08: Consultas Complexas (WITH / CTE)
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * Foco em B-Trees e Tabelas Temporárias:
 * - O SQLite avalia as CTEs como tabelas temporárias internas (Ephemeral Tables).
 * - Se a CTE for simples, o otimizador pode "achatar" (flatten) a consulta para evitar materialização.
 * - Complexidade: O custo de materializar a CTE + o custo do join final.
 */
-- ==============================================================================
-- ATIVIDADE 08: CONSULTAS COMPLEXAS (WITH / CTE)
-- OBJETIVO: Criar relatórios analíticos modulares e legíveis.
-- ==============================================================================
-- 1. Setup do Banco
-- @note Guardião Financeiro: valor_cents (INTEGER) para evitar imprecisão em agregações de SUM e AVG.
CREATE TABLE IF NOT EXISTS vendas (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    data_venda TEXT NOT NULL,
    valor_cents INTEGER NOT NULL
);
DELETE FROM vendas;
-- Populando com dados de diferentes meses (Valores em centavos)
INSERT INTO vendas (data_venda, valor_cents)
VALUES ('2026-01-10', 500000),
    -- R$ 5.000,00
    ('2026-01-20', 300000),
    -- R$ 3.000,00
    ('2026-02-05', 400000),
    -- R$ 4.000,00
    ('2026-02-15', 200000),
    -- R$ 2.000,00
    ('2026-03-12', 1000000),
    -- R$ 10.000,00
    ('2026-04-01', 1200000),
    -- R$ 12.000,00
    ('2026-04-20', 800000);
-- R$ 8.000,00
-- 2. CONSULTA ANALÍTICA USANDO CTE (WITH)
WITH -- Primeiro Bloco: Consolidação Mensal
faturamento_mensal AS (
    SELECT strftime('%m', data_venda) AS mes,
        SUM(valor_cents) AS total_mes_cents
    FROM vendas
    GROUP BY mes
),
-- Segundo Bloco: Média Global
media_global AS (
    SELECT AVG(total_mes_cents) AS media_anual_cents
    FROM faturamento_mensal
) -- Consulta Final: Unindo os blocos para análise comparativa
SELECT f.mes AS "Mês",
    (f.total_mes_cents / 100.0) AS "Faturamento (R$)",
    ROUND(m.media_anual_cents / 100.0, 2) AS "Média Geral (R$)",
    ROUND(
        (f.total_mes_cents - m.media_anual_cents) / 100.0,
        2
    ) AS "Variação"
FROM faturamento_mensal f,
    media_global m;
/* 
 ===============================================================
 RESUMO TEÓRICO: CTE (COMMON TABLE EXPRESSIONS)
 ===============================================================
 
 1. O QUE SÃO?
 - São subconsultas nomeadas que você define no topo da query. 
 - Elas funcionam como "variáveis" que guardam tabelas inteiras.
 
 2. VANTAGEM DIDÁTICA: 
 - Imagine tentar calcular a variação sem CTE. Você teria que 
 repetir o SELECT SUM(...) várias vezes dentro da mesma query. 
 - CTEs deixam o código modular e muito mais fácil de depurar.
 
 3. STRFTIME:
 - Função do SQLite usada para extrair partes da data (ex: '%m' 
 para o mês).
 
 4. GUARDIÃO FINANCEIRO:
 - Realizar cálculos de SUM e AVG sobre INTEGER cents garante que 
 a precisão seja mantida até a última casa decimal antes da 
 formatação final para exibição.
 
 VANTAGEM PARA O ENGENHEIRO: 
 CTEs são a base para o SQL moderno e profissional, permitindo 
 a criação de algoritmos complexos de análise de dados (BI).
 
 ASSUNTOS CORRELATOS:
 - Recursive CTEs (Para hierarquias e grafos).
 - Materialized vs Non-materialized CTEs.
 - Data Cleaning com CTEs.
 ===============================================================
 */
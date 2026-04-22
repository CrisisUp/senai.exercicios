/**
 * @file queries.sql
 * @brief Atividade 10: Inteligência Analítica (Window Functions)
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * Foco em B-Trees e Windowing:
 * - O SQLite executa Window Functions utilizando um processador de janelas que pode exigir memória adicional para armazenar o conjunto de resultados antes da ordenação final.
 * - Complexidade: O(n log n) devido à ordenação implícita necessária para RANK() e PARTITION BY.
 * - Índices nas colunas de PARTITION BY e ORDER BY podem otimizar significativamente a performance.
 */

-- ==============================================================================
-- ATIVIDADE 10: INTELIGÊNCIA ANALÍTICA (WINDOW FUNCTIONS)
-- OBJETIVO: Criar rankings e métricas comparativas sem perder o detalhe das linhas.
-- ==============================================================================

-- 1. Setup das Tabelas
-- @note Guardião Financeiro: valor_comissao_cents (INTEGER) para garantir precisão em cálculos de bônus e premiações.
CREATE TABLE IF NOT EXISTS desempenho_pilotos (
   id INTEGER PRIMARY KEY AUTOINCREMENT,
   nome TEXT NOT NULL,
   regiao TEXT NOT NULL,
   entregas INTEGER NOT NULL,
   valor_comissao_cents INTEGER DEFAULT 0
);

DELETE FROM desempenho_pilotos;

INSERT INTO desempenho_pilotos (nome, regiao, entregas, valor_comissao_cents)
VALUES ('Carlos', 'Sudeste', 150, 75000), -- R$ 750,00
   ('Ana', 'Sudeste', 200, 100000),      -- R$ 1.000,00
   ('Marcos', 'Sudeste', 120, 60000),    -- R$ 600,00
   ('Julia', 'Sul', 90, 45000),          -- R$ 450,00
   ('Roberto', 'Sul', 110, 55000),       -- R$ 550,00
   ('Fernanda', 'Norte', 45, 22500),     -- R$ 225,00
   ('Tiago', 'Norte', 60, 30000);        -- R$ 300,00

-- 2. CONSULTAS DE INTELIGÊNCIA

-- [A] RANKING GERAL (Simples)
-- ROW_NUMBER() apenas numera de 1 a N.
SELECT nome,
   entregas,
   ROW_NUMBER() OVER(
      ORDER BY entregas DESC
   ) AS "Posição Geral"
FROM desempenho_pilotos;

-- [B] RANKING REGIONAL (PARTITION BY)
-- A "Janela" é particionada por região. O ranking reinicia em cada grupo.
SELECT regiao,
   nome,
   entregas,
   RANK() OVER(
      PARTITION BY regiao
      ORDER BY entregas DESC
   ) AS "Posição na Região"
FROM desempenho_pilotos;

-- [C] ANÁLISE DE PARTICIPAÇÃO (%) E FINANCEIRA
-- Comparamos o piloto com a soma total da sua região na mesma linha.
SELECT nome,
   regiao,
   entregas,
   (valor_comissao_cents / 100.0) AS comissao_reais,
   SUM(entregas) OVER(PARTITION BY regiao) AS "Total da Região",
   ROUND(
      CAST(entregas AS REAL) * 100 / SUM(entregas) OVER(PARTITION BY regiao),
      2
   ) AS "% de Participação"
FROM desempenho_pilotos
ORDER BY regiao,
   "% de Participação" DESC;

/* 
 ===============================================================
 RESUMO TEÓRICO: WINDOW FUNCTIONS (O TOPO DA ANALÍTICA)
 ===============================================================
 
 1. DIFERENÇA DO GROUP BY:
 - GROUP BY: Colapsa as linhas (reduz o número de linhas na saída).
 - WINDOW: Mantém as linhas (a saída tem o mesmo número de linhas da entrada).
 
 2. PARTITION BY: 
 - Cria sub-grupos virtuais para o cálculo sem reduzir o detalhamento da linha individual.
 
 3. CÁLCULOS MISTOS:
 - Conseguimos comparar valores da linha atual com agregações do grupo (janela) sem subqueries ou JOINs.

 4. GUARDIÃO FINANCEIRO:
 - Ao realizar rankings de performance vinculados a bônus (cents), garantimos que o arredondamento 
 de percentuais de participação não afete o valor exato a ser pago em dinheiro.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende o recurso mais moderno e eficiente do SQL para criação de 
 dashboards e ferramentas de análise competitiva.

 ASSUNTOS CORRELATOS:
 - Sliding Window Frames (ROWS BETWEEN 3 PRECEDING AND CURRENT ROW).
 - LAG() e LEAD() para análise de crescimento (YoY, MoM).
 - NTILE() para criação de quartis e decis de performance.
 ===============================================================
 */

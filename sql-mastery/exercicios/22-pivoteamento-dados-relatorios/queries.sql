/**
 * @file queries.sql
 * @brief Relatórios Executivos com Pivoteamento (Cross-Tab).
 * @author Gemini CLI
 * @date 2026-04-21
 * @section ExecutionPlan Estratégia de Agregação via CASE WHEN e Group By.
 */

-- ==============================================================================
-- ATIVIDADE 22: RELATÓRIOS EXECUTIVOS (PIVOTEAMENTO)
-- OBJETIVO: Transformar linhas em colunas para análise comparativa.
-- ==============================================================================

-- 1. Setup da Tabela de Operações com Guardião Financeiro
CREATE TABLE IF NOT EXISTS operacoes_voo (
   id INTEGER PRIMARY KEY AUTOINCREMENT,
   categoria TEXT NOT NULL,
   mes TEXT NOT NULL,
   -- @note Guardião Financeiro: lucro_cents (INTEGER) para precisão absoluta
   lucro_cents INTEGER NOT NULL
);

DELETE FROM operacoes_voo;

-- 2. Populando com dados para o Primeiro Trimestre (Q1)
INSERT INTO operacoes_voo (categoria, mes, lucro_cents)
VALUES 
   ('Resgate', 'Jan', 500000), -- R$ 5.000,00
   ('Resgate', 'Fev', 450000),
   ('Resgate', 'Mar', 600000),
   ('Carga', 'Jan', 800000),
   ('Carga', 'Fev', 900000),
   ('Carga', 'Mar', 850000),
   ('Agro', 'Jan', 200000),
   ('Agro', 'Fev', 300000),
   ('Agro', 'Mar', 1200000);

-- 3. CONSULTA DE PIVOTEAMENTO (TABELA CRUZADA)
-- @section ExecutionPlan: O SUM(CASE...) evita subconsultas caras por coluna.
SELECT categoria AS "Categoria de Drone",
   -- Coluna Janeiro (Convertendo centavos para real na visualização)
   SUM(CASE WHEN mes = 'Jan' THEN lucro_cents ELSE 0 END) / 100.0 AS "Jan (R$)",
   -- Coluna Fevereiro
   SUM(CASE WHEN mes = 'Fev' THEN lucro_cents ELSE 0 END) / 100.0 AS "Fev (R$)",
   -- Coluna Março
   SUM(CASE WHEN mes = 'Mar' THEN lucro_cents ELSE 0 END) / 100.0 AS "Mar (R$)",
   -- Coluna Total (Soma da Linha)
   SUM(lucro_cents) / 100.0 AS "Total Trimestre (R$)"
FROM operacoes_voo
GROUP BY categoria
ORDER BY "Total Trimestre (R$)" DESC;

-- 4. VALIDAÇÃO DE PERFORMANCE
EXPLAIN QUERY PLAN
SELECT categoria, SUM(lucro_cents) FROM operacoes_voo GROUP BY categoria;

/* 
 ===============================================================
 RESUMO TEÓRICO: PIVOT COM CASE WHEN
 ===============================================================
 
 1. LÓGICA DE COLUNA: 
 - O 'CASE WHEN' atua como um filtro individual para cada coluna. 
   Os valores que não atendem ao critério são neutralizados (ELSE 0).
 
 2. AGREGAÇÃO COMPILADA: 
 - O 'SUM' consolida os resultados do CASE em uma única linha por grupo,
   gerando a estrutura de matriz (Cross-Tab).
 
 3. GUARDIÃO FINANCEIRO:
 - Ao pivotar valores monetários, o uso de INTEGER (centavos) garante que
   a soma total seja idêntica à soma dos componentes, sem erros de precisão.
 
 ===============================================================
 ASSUNTOS CORRELATOS:
 - PIVOT/UNPIVOT nativos (T-SQL, Oracle).
 - OLAP Cubes e Data Warehousing.
 - Transformação de Dados Long-to-Wide (Pandas, R).
 ===============================================================
 */

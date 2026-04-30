/**
 * @file queries.sql
 * @brief Inteligência de Rotas (Graph Pathfinding com CTE Recursiva).
 * @author Gemini CLI
 * @date 2026-04-19
 * @section ExecutionPlan Estratégia de Navegação Recursiva e Prevenção de Ciclos.
 */

-- ==============================================================================
-- ATIVIDADE 18: INTELIGÊNCIA DE ROTAS (GRAPH NAVIGATION)
-- OBJETIVO: Resolver problemas de logística e caminhos usando SQL.
-- ==============================================================================

-- 1. Setup do Mapa de Conexões com Guardião Financeiro
CREATE TABLE IF NOT EXISTS conexoes_bases (
    origem TEXT NOT NULL,
    destino TEXT NOT NULL,
    distancia REAL NOT NULL,
    custo_frete_cents INTEGER NOT NULL DEFAULT 0 CHECK (custo_frete_cents >= 0)
);

DELETE FROM conexoes_bases;

-- Populando o Grafo (O mapa de rede)
INSERT INTO conexoes_bases (origem, destino, distancia, custo_frete_cents) VALUES 
('BASE-A', 'BASE-B', 150.0, 5000),   -- R$ 50,00
('BASE-B', 'BASE-C', 200.0, 7500),   -- R$ 75,00
('BASE-B', 'BASE-D', 450.0, 15000),  -- R$ 150,00
('BASE-C', 'BASE-D', 100.0, 3000),   -- R$ 30,00
('BASE-D', 'BASE-E', 300.0, 12000);  -- R$ 120,00

-- 2. CONSULTA DE NAVEGAÇÃO RECURSIVA
-- @section ExecutionPlan: A CTE recursiva expande a árvore de busca em memória.
WITH RECURSIVE navegador_rotas AS (
    -- [A] ÂNCORA: Iniciar na BASE-A
    SELECT 
        destino, 
        distancia AS km_total, 
        custo_frete_cents AS custo_total_cents,
        origem || ' -> ' || destino AS trajeto,
        1 AS paradas
    FROM conexoes_bases
    WHERE origem = 'BASE-A'

    UNION ALL

    -- [B] MEMBRO RECURSIVO: Buscar o próximo salto
    SELECT 
        c.destino, 
        n.km_total + c.distancia, 
        n.custo_total_cents + c.custo_frete_cents,
        n.trajeto || ' -> ' || c.destino,
        n.paradas + 1
    FROM conexoes_bases c
    JOIN navegador_rotas n ON c.origem = n.destino
    -- Prevenção de Ciclos (Não passar pela mesma base duas vezes)
    WHERE n.trajeto NOT LIKE '%' || c.destino || '%'
      AND n.paradas < 10 -- Limite de segurança contra explosão de caminhos
)
-- Consulta Final: Verificando as opções para chegar na BASE-D
SELECT 
    trajeto AS "Rota Completa",
    km_total AS "Distância Total",
    custo_total_cents / 100.0 AS "Custo Total (R$)",
    paradas AS "Qtd de Saltos"
FROM navegador_rotas
WHERE destino = 'BASE-D'
ORDER BY km_total ASC;

-- Auditoria da Performance de Recursão
EXPLAIN QUERY PLAN
WITH RECURSIVE t(n) AS (VALUES(1) UNION ALL SELECT n+1 FROM t WHERE n<5)
SELECT * FROM t;

/* 
    ===============================================================
    RESUMO TEÓRICO: NAVEGAÇÃO EM GRAFOS (LOGÍSTICA)
    ===============================================================

    1. O QUE É UM GRAFO EM SQL?
       - Representação de conexões entre Nodes (Bases) e Edges (Rotas).

    2. ACÚMULO DE DADOS NA RECURSÃO:
       - Soma de quilometragem e custos financeiros em tempo real.

    3. GUARDIÃO FINANCEIRO:
       - Garante que o custo total da logística seja exato (INTEGER).

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Algoritmo de Dijkstra em SQL.
    - Hierarchical Data (Adjacency List vs Nested Sets).
    - Window Functions vs Recursion.
    ===============================================================
*/

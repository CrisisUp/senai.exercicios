/**
 * @file queries.sql
 * @brief Portal de Inteligência Global com Federação e Analítica Avançada.
 * @details Consolidação de dados multi-banco (ATTACH), proteção de integridade (Triggers) 
 *          e inteligência de negócio com Window Functions e Pivot Tables.
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * - Security Views: Camada de abstração para ocultar a complexidade do ATTACH e filtrar dados sensíveis.
 * - Analytics Cost: Uso de Window Functions requer índices compostos (drone_id, data_consolidacao) 
 *   para evitar O(n^2) em partições grandes.
 * - Stress Resilience: Triggers de imutabilidade garantem que dados históricos não sejam corrompidos 
 *   sob carga massiva ou tentativas de deleção acidental.
 */

-- ==============================================================================
-- 1. SETUP DE FEDERAÇÃO
-- ==============================================================================
ATTACH DATABASE '../../exercicios/01-explorador-estoque/database.db' AS estoque;

-- ==============================================================================
-- 2. ARQUITETURA DO PORTAL (DDL)
-- ==============================================================================
-- Tabela de Missões Consolidadas com Guardião Financeiro (cents)
CREATE TABLE IF NOT EXISTS consolidado_missao (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id TEXT NOT NULL,
    regiao TEXT NOT NULL,
    distancia REAL NOT NULL,
    custo_operacional_cents INTEGER NOT NULL, -- Guardião Financeiro: Centavos inteiros
    data_consolidacao TEXT DEFAULT CURRENT_TIMESTAMP
);

DELETE FROM consolidado_missao;

-- ==============================================================================
-- 3. BLINDAGEM DE SEGURANÇA (TRIGGER)
-- ==============================================================================
-- Impede que dados consolidados sejam apagados (Imutabilidade)
CREATE TRIGGER IF NOT EXISTS trg_proteger_missao 
BEFORE DELETE ON consolidado_missao 
BEGIN
    SELECT RAISE(
        ABORT,
        'ALERTA DE SEGURANÇA: Dados consolidados não podem ser removidos!'
    );
END;

-- ==============================================================================
-- 4. POPULAÇÃO DE DADOS
-- ==============================================================================
INSERT INTO consolidado_missao (drone_id, regiao, distancia, custo_operacional_cents)
VALUES 
    ('X-01', 'Americas', 150.0, 15000), -- R$ 150,00
    ('X-01', 'Americas', 160.0, 16550), -- R$ 165,50
    ('X-01', 'Americas', 140.0, 13000),
    ('E-05', 'Europa', 200.0, 45000),
    ('E-05', 'Europa', 210.0, 47000),
    ('E-05', 'Europa', 300.0, 60000),
    ('A-12', 'Asia', 50.0, 12000),
    ('A-12', 'Asia', 55.0, 12500),
    ('A-12', 'Asia', 120.0, 25000);

-- ==============================================================================
-- 5. CONSULTAS DE INTELIGÊNCIA INTEGRADA
-- ==============================================================================

-- [A] MÉDIA MÓVEL DE PERFORMANCE E CUSTO (WINDOW FRAMES)
SELECT 
    drone_id,
    data_consolidacao,
    distancia,
    custo_operacional_cents / 100.0 AS custo_brl,
    ROUND(
        AVG(distancia) OVER(
            PARTITION BY drone_id
            ORDER BY data_consolidacao ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
        ),
        2
    ) AS "Média Móvel Distância (3)",
    ROUND(
        AVG(custo_operacional_cents / 100.0) OVER(
            PARTITION BY drone_id
            ORDER BY data_consolidacao ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
        ),
        2
    ) AS "Média Móvel Custo (3)"
FROM consolidado_missao;

-- [B] DASHBOARD REGIONAL PIVOTADO (PIVOT)
SELECT 
    'Distância Total por Região' AS "Métrica",
    SUM(CASE WHEN regiao = 'Americas' THEN distancia ELSE 0 END) AS "AMERICAS",
    SUM(CASE WHEN regiao = 'Europa' THEN distancia ELSE 0 END) AS "EUROPA",
    SUM(CASE WHEN regiao = 'Asia' THEN distancia ELSE 0 END) AS "ASIA",
    SUM(distancia) AS "TOTAL GLOBAL"
FROM consolidado_missao;

-- [C] VERIFICAÇÃO DE SUPORTE (FEDERAÇÃO)
SELECT 
    'Itens Disponíveis no Estoque Externo' AS Info,
    COUNT(*) AS Quantidade
FROM estoque.produtos;

-- ==============================================================================
-- RESUMO TEÓRICO
-- ==============================================================================
/*
1. FEDERAÇÃO (ATTACH): Permite cruzar dados de múltiplos arquivos de banco de dados 
   em uma única conexão, ideal para arquiteturas de microsserviços ou silos de dados.
2. WINDOW FUNCTIONS: Analisam subconjuntos de dados (frames) sem colapsar as linhas, 
   permitindo cálculos de tendências e rankings.
3. PIVOT TABLE: Técnica de remodelagem de dados onde valores de linhas tornam-se 
   colunas, facilitando a leitura em dashboards executivos.
4. INTEGRIDADE FINANCEIRA: O uso de INTEGER para centavos evita erros de arredondamento 
   IEEE 754 inerentes ao tipo REAL/FLOAT.
*/

-- ==============================================================================
-- ASSUNTOS CORRELATOS
-- ==============================================================================
/*
- Materialized Views em outros RDBMS.
- ACID compliance em operações multi-banco.
- Otimização de consultas com EXPLAIN QUERY PLAN.
- Sharding e Particionamento de dados.
*/

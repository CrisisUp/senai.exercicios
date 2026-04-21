-- ==============================================================================
-- ATIVIDADE 08: CONSULTAS COMPLEXAS (WITH / CTE)
-- OBJETIVO: Criar relatórios analíticos modulares e legíveis.
-- ==============================================================================
-- 1. Setup do Banco
CREATE TABLE IF NOT EXISTS vendas (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    data_venda TEXT NOT NULL,
    valor REAL NOT NULL
);
DELETE FROM vendas;
-- Populando com dados de diferentes meses
INSERT INTO vendas (data_venda, valor)
VALUES ('2026-01-10', 5000.00),
    ('2026-01-20', 3000.00),
    ('2026-02-05', 4000.00),
    ('2026-02-15', 2000.00),
    ('2026-03-12', 10000.00),
    ('2026-04-01', 12000.00),
    ('2026-04-20', 8000.00);
-- 2. CONSULTA ANALÍTICA USANDO CTE (WITH)
WITH -- Primeiro Bloco: Consolidação Mensal
faturamento_mensal AS (
    SELECT strftime('%m', data_venda) AS mes,
        SUM(valor) AS total_mes
    FROM vendas
    GROUP BY mes
),
-- Segundo Bloco: Média Global
media_global AS (
    SELECT AVG(total_mes) AS media_anual
    FROM faturamento_mensal
) -- Consulta Final: Unindo os blocos para análise comparativa
SELECT f.mes AS "Mês",
    f.total_mes AS "Faturamento (R$)",
    ROUND(m.media_anual, 2) AS "Média Geral (R$)",
    ROUND(f.total_mes - m.media_anual, 2) AS "Variação"
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
 
 VANTAGEM PARA O ENGENHEIRO: 
 CTEs são a base para o SQL moderno e profissional, permitindo 
 a criação de algoritmos complexos de análise de dados (BI).
 ===============================================================
 */
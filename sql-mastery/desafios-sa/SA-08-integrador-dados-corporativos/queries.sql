-- ==============================================================================
-- DESAFIO INTEGRADOR SA-08: INTEGRADOR CORPORATIVO
-- OBJETIVO: Integrar ETL, Resolução de Conflitos e Pivoteamento.
-- ==============================================================================

-- 1. ARQUITETURA DO SISTEMA (DDL)

CREATE TABLE IF NOT EXISTS faturamento_frota (
    serial TEXT NOT NULL,
    mes TEXT NOT NULL,
    categoria TEXT NOT NULL,
    lucro REAL NOT NULL,
    PRIMARY KEY (serial, mes) -- Chave Composta para detectar conflitos
);

-- 2. PIPELINE ETL (Simulado no script, mas executado via .import)
-- O aluno deve usar o INTERACAO_SQLITE.md para carregar o CSV.

-- 3. CONSULTA ANALÍTICA (PIVOTEAMENTO)
-- Gera o dashboard final para a diretoria.
CREATE VIEW IF NOT EXISTS v_dashboard_mensal AS
SELECT categoria,
       SUM(CASE WHEN mes = 'Jan' THEN lucro ELSE 0 END) AS "Janeiro",
       SUM(CASE WHEN mes = 'Fev' THEN lucro ELSE 0 END) AS "Fevereiro",
       SUM(lucro) AS "Total Acumulado"
FROM faturamento_frota
GROUP BY categoria;

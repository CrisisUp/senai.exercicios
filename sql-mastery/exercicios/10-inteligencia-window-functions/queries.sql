-- ==============================================================================
-- ATIVIDADE 10: INTELIGÊNCIA ANALÍTICA (WINDOW FUNCTIONS)
-- OBJETIVO: Criar rankings e métricas comparativas sem perder o detalhe das linhas.
-- ==============================================================================
-- 1. Setup das Tabelas
CREATE TABLE IF NOT EXISTS desempenho_pilotos (
   id INTEGER PRIMARY KEY AUTOINCREMENT,
   nome TEXT NOT NULL,
   regiao TEXT NOT NULL,
   entregas INTEGER NOT NULL
);
DELETE FROM desempenho_pilotos;
INSERT INTO desempenho_pilotos (nome, regiao, entregas)
VALUES ('Carlos', 'Sudeste', 150),
   ('Ana', 'Sudeste', 200),
   ('Marcos', 'Sudeste', 120),
   ('Julia', 'Sul', 90),
   ('Roberto', 'Sul', 110),
   ('Fernanda', 'Norte', 45),
   ('Tiago', 'Norte', 60);
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
-- [C] ANÁLISE DE PARTICIPAÇÃO (%)
-- Comparamos o piloto com a soma total da sua região na mesma linha.
SELECT nome,
   regiao,
   entregas,
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
 - Cria sub-grupos virtuais para o cálculo. 
 - No desafio B, o Rust "separa" o Sudeste do Sul antes de dar a medalha de 1º lugar.
 
 3. CÁLCULOS MISTOS:
 - No desafio C, conseguimos dividir um valor da linha atual pelo total do grupo 
 sem precisar fazer um JOIN complexo ou Subquery.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende o recurso mais moderno e eficiente do SQL para criação de 
 dashboards e ferramentas de análise competitiva.
 ===============================================================
 */
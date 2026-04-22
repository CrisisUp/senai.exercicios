-- ==============================================================================
-- ATIVIDADE 22: RELATÓRIOS EXECUTIVOS (PIVOTEAMENTO)
-- OBJETIVO: Transformar linhas em colunas para análise comparativa.
-- ==============================================================================
-- 1. Setup da Tabela de Operações
CREATE TABLE IF NOT EXISTS operacoes_voo (
   id INTEGER PRIMARY KEY AUTOINCREMENT,
   categoria TEXT NOT NULL,
   mes TEXT NOT NULL,
   lucro REAL NOT NULL
);
DELETE FROM operacoes_voo;
-- 2. Populando com dados para o Primeiro Trimestre (Q1)
INSERT INTO operacoes_voo (categoria, mes, lucro)
VALUES ('Resgate', 'Jan', 5000.0),
   ('Resgate', 'Fev', 4500.0),
   ('Resgate', 'Mar', 6000.0),
   ('Carga', 'Jan', 8000.0),
   ('Carga', 'Fev', 9000.0),
   ('Carga', 'Mar', 8500.0),
   ('Agro', 'Jan', 2000.0),
   ('Agro', 'Fev', 3000.0),
   ('Agro', 'Mar', 12000.0);
-- 3. CONSULTA DE PIVOTEAMENTO (TABELA CRUZADA)
SELECT categoria AS "Categoria de Drone",
   -- Coluna Janeiro
   SUM(
      CASE
         WHEN mes = 'Jan' THEN lucro
         ELSE 0
      END
   ) AS "Jan",
   -- Coluna Fevereiro
   SUM(
      CASE
         WHEN mes = 'Fev' THEN lucro
         ELSE 0
      END
   ) AS "Fev",
   -- Coluna Março
   SUM(
      CASE
         WHEN mes = 'Mar' THEN lucro
         ELSE 0
      END
   ) AS "Mar",
   -- Coluna Total (Soma da Linha)
   SUM(lucro) AS "Total Trimestre (Q1)"
FROM operacoes_voo
GROUP BY categoria
ORDER BY "Total Trimestre (Q1)" DESC;
/* 
 ===============================================================
 RESUMO TEÓRICO: PIVOT COM CASE WHEN
 ===============================================================
 
 1. LOGÍQUICA DE COLUNA: 
 - O 'CASE WHEN' atua como um filtro individual para cada coluna. 
 - Se o mês for 'Jan', o valor vai para a coluna Jan. Se não, soma zero.
 
 2. AGREGAÇÃO COMPILADA: 
 - O 'SUM' ao redor do CASE é o que consolida todos os registros 
 daquela categoria no mês correto.
 
 3. VANTAGEM DIDÁTICA: 
 - O aluno aprende a preparar dados para ferramentas de 
 visualização (Excel, PowerBI, Tableau) que esperam dados 
 em formato de matriz.
 
 4. FLEXIBILIDADE:
 - Você pode pivotar qualquer coisa: lucro por região, 
 erros por tipo de motor, ou voos por dia da semana.
 ===============================================================
 */
/**
 * @file queries.sql
 * @brief Analisador de Estoque com Agregações e Agrupamentos.
 * @section ExecutionPlan O custo computacional das agregações (SUM, AVG, COUNT) 
 * sem índices na coluna de agrupamento é de O(n), exigindo um Table Scan completo.
 * @author Gemini CLI
 * @date 2026-04-19
 */
-- ==============================================================================
-- ATIVIDADE 02: ANALISADOR DE ESTOQUE (AGREGAÇÕES)
-- OBJETIVO: Consolidar dados para tomada de decisão gerencial.
-- ==============================================================================
-- 1. Criação da Tabela (Caso não exista)
-- Aplicando Guardião Financeiro: preco_centavos como INTEGER
CREATE TABLE IF NOT EXISTS produtos (
   id INTEGER PRIMARY KEY AUTOINCREMENT,
   nome TEXT NOT NULL,
   categoria TEXT,
   preco_centavos INTEGER,
   -- Armazena R$ 10,50 como 1050
   estoque INTEGER
);
-- Limpando para garantir dados novos na atividade 2
DELETE FROM produtos;
-- 2. População de Dados (Massa Analítica)
INSERT INTO produtos (nome, categoria, preco_centavos, estoque)
VALUES ('Bateria Lipo 4S', 'Energia', 45000, 15),
   ('Bateria Lipo 6S', 'Energia', 78000, 8),
   ('Hélice Carbono 12x4', 'Propulsão', 8550, 40),
   ('Hélice Plástico 10x4', 'Propulsão', 2500, 100),
   ('Sensor GPS Alfa', 'Navegação', 120000, 5),
   ('Sensor Compass', 'Navegação', 35000, 12),
   ('Câmera Térmica X1', 'Visão', 350000, 2),
   ('Câmera 4K Ultra', 'Visão', 180000, 4);
-- 3. CONSULTAS ANALÍTICAS
-- [A] VALOR FINANCEIRO TOTAL DO ESTOQUE
-- Nota: Cálculo em centavos para evitar erros de ponto flutuante.
SELECT SUM(preco_centavos * estoque) / 100.0 AS "Valor Total do Patrimônio (R$)"
FROM produtos;
-- [B] QUANTIDADE DE PRODUTOS E SOMA DE ESTOQUE POR CATEGORIA
-- O GROUP BY divide a tabela em categorias antes de contar.
SELECT categoria,
   COUNT(id) AS "Tipos de Itens",
   SUM(estoque) AS "Total em Unidades"
FROM produtos
GROUP BY categoria;
-- [C] MÉDIA DE PREÇO E PRODUTO MAIS BARATO POR CATEGORIA
SELECT categoria,
   ROUND(AVG(preco_centavos) / 100.0, 2) AS "Preço Médio (R$)",
   MIN(preco_centavos) / 100.0 AS "Preço Mínimo (R$)"
FROM produtos
GROUP BY categoria
ORDER BY "Preço Médio (R$)" DESC;
-- [D] FILTRAGEM DE GRUPOS (HAVING)
-- Listar categorias que possuem mais de 50 unidades totais no estoque.
SELECT categoria,
   SUM(estoque) AS "Total"
FROM produtos
GROUP BY categoria
HAVING "Total" > 50;
/* 
 ===============================================================
 RESUMO TEÓRICO: AGREGAÇÕES E AGRUPAMENTOS
 ===============================================================
 
 1. FUNÇÕES ESCALARES vs AGREGAÇÃO:
 - Escalares operam em uma linha (ex: preco * 2).
 - Agregação operam em N linhas (ex: SUM, AVG).
 
 2. O PAPEL DO GROUP BY:
 - Sem o GROUP BY, a agregação olha para a tabela inteira.
 - Com ele, a agregação olha para cada "balde" de dados.
 
 3. HAVING:
 - É o "WHERE dos Grupos". Se você quer filtrar o resultado 
 de uma soma ou média, deve usar HAVING.
 
 4. GUARDIÃO FINANCEIRO:
 - A escolha de INTEGER para centavos elimina erros de 
 arredondamento inerentes ao tipo REAL/FLOAT.
 
 VANTAGEM DIDÁTICA: 
 O aluno deixa de ver o banco como uma lista de compras e passa 
 a vê-lo como uma fonte de Business Intelligence (BI).
 ===============================================================
 */
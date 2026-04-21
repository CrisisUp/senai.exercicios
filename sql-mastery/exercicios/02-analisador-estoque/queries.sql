-- ==============================================================================
-- ATIVIDADE 02: ANALISADOR DE ESTOQUE (AGREGAÇÕES)
-- OBJETIVO: Consolidar dados para tomada de decisão gerencial.
-- ==============================================================================

-- 1. Criação da Tabela (Caso não exista)
CREATE TABLE IF NOT EXISTS produtos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    categoria TEXT,
    preco REAL,
    estoque INTEGER
);

-- Limpando para garantir dados novos na atividade 2
DELETE FROM produtos;

-- 2. População de Dados (Massa Analítica)
INSERT INTO produtos (nome, categoria, preco, estoque) VALUES 
('Bateria Lipo 4S', 'Energia', 450.00, 15),
('Bateria Lipo 6S', 'Energia', 780.00, 8),
('Hélice Carbono 12x4', 'Propulsão', 85.50, 40),
('Hélice Plástico 10x4', 'Propulsão', 25.00, 100),
('Sensor GPS Alfa', 'Navegação', 1200.00, 5),
('Sensor Compass', 'Navegação', 350.00, 12),
('Câmera Térmica X1', 'Visão', 3500.00, 2),
('Câmera 4K Ultra', 'Visão', 1800.00, 4);

-- 3. CONSULTAS ANALÍTICAS

-- [A] VALOR FINANCEIRO TOTAL DO ESTOQUE
-- Nota: Podemos fazer cálculos aritméticos dentro das funções de agregação.
SELECT SUM(preco * estoque) AS "Valor Total do Patrimônio" 
FROM produtos;

-- [B] QUANTIDADE DE PRODUTOS E SOMA DE ESTOQUE POR CATEGORIA
-- O GROUP BY divide a tabela em categorias antes de contar.
SELECT categoria, 
       COUNT(*) AS "Tipos de Itens", 
       SUM(estoque) AS "Total em Unidades"
FROM produtos
GROUP BY categoria;

-- [C] MÉDIA DE PREÇO E PRODUTO MAIS BARATO POR CATEGORIA
SELECT categoria, 
       ROUND(AVG(preco), 2) AS "Preço Médio", 
       MIN(preco) AS "Preço Mínimo"
FROM produtos
GROUP BY categoria
ORDER BY "Preço Médio" DESC;

-- [D] FILTRAGEM DE GRUPOS (HAVING)
-- Listar categorias que possuem mais de 50 unidades totais no estoque.
-- WHERE filtra linhas individuais; HAVING filtra os resultados do GROUP BY.
SELECT categoria, SUM(estoque) AS "Total"
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

    VANTAGEM DIDÁTICA: 
    O aluno deixa de ver o banco como uma lista de compras e passa 
    a vê-lo como uma fonte de Business Intelligence (BI).
    ===============================================================
*/

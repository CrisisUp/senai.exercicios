-- ==============================================================================
-- ATIVIDADE 04: EVOLUÇÃO DO ESQUEMA (ALTER TABLE)
-- OBJETIVO: Modificar a estrutura de uma tabela existente.
-- ==============================================================================
-- 1. Preparação: Garantir que a tabela base exista
CREATE TABLE IF NOT EXISTS produtos (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  nome TEXT NOT NULL,
  categoria TEXT,
  preco REAL,
  estoque INTEGER
);
-- Populando com dados iniciais (caso o banco esteja vazio)
INSERT INTO produtos (nome, categoria, preco, estoque)
SELECT 'Bateria Lipo 4S',
  'Energia',
  450.00,
  15
WHERE NOT EXISTS (
    SELECT 1
    FROM produtos
    WHERE nome = 'Bateria Lipo 4S'
  );
INSERT INTO produtos (nome, categoria, preco, estoque)
SELECT 'Sensor GPS Alfa',
  'Navegação',
  1200.00,
  5
WHERE NOT EXISTS (
    SELECT 1
    FROM produtos
    WHERE nome = 'Sensor GPS Alfa'
  );
-- 2. EVOLUÇÃO DO BANCO (ALTER TABLE)
-- Adicionando coluna de Avaliação
ALTER TABLE produtos
ADD COLUMN avaliacao INTEGER;
-- Adicionando coluna de Desconto com Valor Padrão
ALTER TABLE produtos
ADD COLUMN desconto REAL DEFAULT 0.0;
-- 3. MANUTENÇÃO DE DADOS (UPDATE)
-- Dando 5 estrelas para o GPS
UPDATE produtos
SET avaliacao = 5
WHERE nome = 'Sensor GPS Alfa';
-- Aplicando desconto de 10% na Bateria (450 * 0.10 = 45.0)
UPDATE produtos
SET desconto = 45.0
WHERE nome = 'Bateria Lipo 4S';
-- 4. CONSULTAS COM CÁLCULOS DINÂMICOS
-- [A] LISTAR PREÇO ORIGINAL, DESCONTO E PREÇO FINAL
SELECT nome,
  preco AS "Preço Base",
  desconto AS "Valor Desconto",
  (preco - desconto) AS "Preço Final"
FROM produtos;
-- [B] LISTAR APENAS PRODUTOS COM 5 ESTRELAS
SELECT *
FROM produtos
WHERE avaliacao = 5;
/* 
 ===============================================================
 RESUMO TEÓRICO: EVOLUÇÃO E MANUTENÇÃO
 ===============================================================
 
 1. ALTER TABLE: 
 - É uma operação de DDL (Data Definition Language). 
 - No SQLite, você pode adicionar colunas facilmente, mas 
 remover colunas (DROP COLUMN) é restrito em versões antigas.
 
 2. UPDATE:
 - É uma operação de DML (Data Manipulation Language).
 - MUITO CUIDADO: Se você esquecer o 'WHERE', atualizará 
 todas as linhas da tabela de uma vez!
 
 3. VALORES DEFAULT:
 - Garantem que o banco não quebre as aplicações antigas que 
 não conhecem as novas colunas, pois elas sempre terão 
 um valor inicial seguro (ex: 0.0).
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende que o software é vivo e que o banco de dados 
 deve acompanhar essa evolução sem precisar ser destruído.
 ===============================================================
 */
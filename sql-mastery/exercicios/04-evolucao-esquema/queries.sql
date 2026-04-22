/**
 * @file queries.sql
 * @brief Evolução do Esquema com ALTER TABLE e Manutenção de Dados.
 * @section ExecutionPlan A adição de colunas (ALTER TABLE ADD COLUMN) no SQLite 
 * é uma operação O(1). Já o UPDATE em colunas não indexadas requer um Table Scan (O(n)).
 * @author Gemini CLI
 * @date 2026-04-19
 */

-- ==============================================================================
-- ATIVIDADE 04: EVOLUÇÃO DO ESQUEMA (ALTER TABLE)
-- OBJETIVO: Modificar a estrutura de uma tabela existente.
-- ==============================================================================

-- 1. Preparação: Garantir que a tabela base exista
-- Aplicando Guardião Financeiro: preco_centavos
CREATE TABLE IF NOT EXISTS produtos (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  nome TEXT NOT NULL,
  categoria TEXT,
  preco_centavos INTEGER,
  estoque INTEGER
);

-- Populando com dados iniciais
INSERT INTO produtos (nome, categoria, preco_centavos, estoque)
SELECT 'Bateria Lipo 4S', 'Energia', 45000, 15
WHERE NOT EXISTS (SELECT 1 FROM produtos WHERE nome = 'Bateria Lipo 4S');

INSERT INTO produtos (nome, categoria, preco_centavos, estoque)
SELECT 'Sensor GPS Alfa', 'Navegação', 120000, 5
WHERE NOT EXISTS (SELECT 1 FROM produtos WHERE nome = 'Sensor GPS Alfa');

-- 2. EVOLUÇÃO DO BANCO (ALTER TABLE)
-- Adicionando coluna de Avaliação
ALTER TABLE produtos ADD COLUMN avaliacao INTEGER;

-- Adicionando coluna de Desconto com Valor Padrão (Em centavos)
ALTER TABLE produtos ADD COLUMN desconto_centavos INTEGER DEFAULT 0;

-- 3. MANUTENÇÃO DE DADOS (UPDATE)
-- Dando 5 estrelas para o GPS
UPDATE produtos
SET avaliacao = 5
WHERE nome = 'Sensor GPS Alfa';

-- Aplicando desconto de R$ 45,00 na Bateria (4500 centavos)
UPDATE produtos
SET desconto_centavos = 4500
WHERE nome = 'Bateria Lipo 4S';

-- 4. CONSULTAS COM CÁLCULOS DINÂMICOS

-- [A] LISTAR PREÇO ORIGINAL, DESCONTO E PREÇO FINAL
-- Colunas explícitas e conversão para visualização.
SELECT nome,
  preco_centavos / 100.0 AS "Preço Base (R$)",
  desconto_centavos / 100.0 AS "Valor Desconto (R$)",
  (preco_centavos - desconto_centavos) / 100.0 AS "Preço Final (R$)"
FROM produtos;

-- [B] LISTAR APENAS PRODUTOS COM 5 ESTRELAS
-- Otimizado: sem SELECT *
SELECT id, nome, categoria, avaliacao
FROM produtos
WHERE avaliacao = 5;

/* 
 ===============================================================
 RESUMO TEÓRICO: EVOLUÇÃO E MANUTENÇÃO
 ===============================================================
 
 1. ALTER TABLE: 
 - Operação de DDL para alterar a estrutura. No SQLite, adicionar 
 colunas é extremamente performático (O(1)).
 
 2. UPDATE:
 - Operação de DML. A falta de um 'WHERE' pode ser catastrófica, 
 alterando todos os registros do banco de uma vez.
 
 3. VALORES DEFAULT:
 - Cruciais para manter a compatibilidade com sistemas legados 
 que ainda não enviam dados para as novas colunas.

 4. GUARDIÃO FINANCEIRO:
 - Ao migrar esquemas, garantir que novos campos monetários 
 (como descontos e taxas) sigam o padrão INTEGER (centavos) 
 para evitar divergências em balanços contábeis.
 ===============================================================
 */

/**
 * @file queries.sql
 * @brief Relacionamento de Fornecedores com JOINs e Chaves Estrangeiras.
 * @section ExecutionPlan O custo de um INNER JOIN sem índices nas chaves 
 * estrangeiras pode chegar a O(n * m). A criação de índices no campo 
 * de ligação reduz para O(n * log m).
 * @author Gemini CLI
 * @date 2026-04-19
 */
-- ==============================================================================
-- ATIVIDADE 03: RELACIONAMENTO DE FORNECEDORES (JOINs)
-- OBJETIVO: Normalizar o banco e conectar tabelas via Chaves Estrangeiras.
-- ==============================================================================
-- 1. Criação da Tabela de Fornecedores (A tabela "Pai")
CREATE TABLE IF NOT EXISTS fornecedores (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    pais TEXT
);
-- 2. Criação da Tabela de Produtos (A tabela "Filha")
-- Aplicando Guardião Financeiro: preco_centavos como INTEGER
CREATE TABLE IF NOT EXISTS produtos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    preco_centavos INTEGER,
    -- R$ 10,50 vira 1050
    fornecedor_id INTEGER,
    FOREIGN KEY (fornecedor_id) REFERENCES fornecedores(id)
);
-- Limpando dados antigos
DELETE FROM produtos;
DELETE FROM fornecedores;
-- 3. Inserção de Fornecedores
INSERT INTO fornecedores (nome, pais)
VALUES ('TecnoDrone Brasil', 'Brasil'),
    ('Global Sensors Co.', 'China'),
    ('AeroParts GmbH', 'Alemanha');
-- 4. Inserção de Produtos vinculados (Guardião Financeiro aplicado)
INSERT INTO produtos (nome, preco_centavos, fornecedor_id)
VALUES ('Bateria Lipo 4S', 45000, 1),
    ('Frame Carbono', 22000, 1),
    ('Sensor GPS Alfa', 120000, 2),
    ('Compass Digital', 35000, 2),
    ('Motor Brushless X', 55000, 3);
-- 5. CONSULTAS COM JOIN
-- [A] LISTAR PRODUTO E O NOME DO FORNECEDOR (INNER JOIN)
-- Colunas explícitas para otimização e clareza.
SELECT p.nome AS "Produto",
    f.nome AS "Fornecedor"
FROM produtos p
    INNER JOIN fornecedores f ON p.fornecedor_id = f.id;
-- [B] LISTAR APENAS PRODUTOS DE FORNECEDORES ESTRANGEIROS
SELECT p.nome AS "Produto",
    p.preco_centavos / 100.0 AS "Preço (R$)",
    f.pais AS "País"
FROM produtos p
    INNER JOIN fornecedores f ON p.fornecedor_id = f.id
WHERE f.pais <> 'Brasil';
-- [C] CONTAR QUANTOS PRODUTOS CADA FORNECEDOR POSSUI
-- LEFT JOIN garante que fornecedores sem produtos também apareçam (evita orfandade no relatório).
SELECT f.nome AS "Fornecedor",
    COUNT(p.id) AS "Qtd Produtos"
FROM fornecedores f
    LEFT JOIN produtos p ON f.id = p.fornecedor_id
GROUP BY f.nome;
/* 
 ===============================================================
 RESUMO TEÓRICO: JOINs E NORMALIZAÇÃO
 ===============================================================
 
 1. POR QUE NORMALIZAR?
 - Evita redundância. Em vez de escrever "TecnoDrone Brasil" 
 100 vezes na tabela de produtos, escrevemos o ID '1'.
 
 2. INNER JOIN vs LEFT JOIN:
 - INNER: Retorna apenas quando há o par perfeito. Risco de omitir dados sem FK.
 - LEFT: Retorna TODOS da esquerda, preenchendo a direita com NULL se não houver par.
 
 3. GUARDIÃO FINANCEIRO:
 - Todas as tabelas que lidam com valores monetários devem usar INTEGER para 
 garantir que cálculos de impostos e fretes sejam precisos ao centavo.
 
 4. ALIAS DE TABELA (p, f):
 - Facilita a leitura e evita ambiguidade em colunas com nomes iguais (ex: id).
 ===============================================================
 */
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
-- Nota: A coluna 'fornecedor_id' faz o link com a tabela fornecedores.
CREATE TABLE IF NOT EXISTS produtos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    preco REAL,
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
-- 4. Inserção de Produtos vinculados
-- 1 = TecnoDrone, 2 = Global Sensors, 3 = AeroParts
INSERT INTO produtos (nome, preco, fornecedor_id)
VALUES ('Bateria Lipo 4S', 450.00, 1),
    ('Frame Carbono', 220.00, 1),
    ('Sensor GPS Alfa', 1200.00, 2),
    ('Compass Digital', 350.00, 2),
    ('Motor Brushless X', 550.00, 3);
-- 5. CONSULTAS COM JOIN (A grande mágica)
-- [A] LISTAR PRODUTO E O NOME DO FORNECEDOR (INNER JOIN)
SELECT produtos.nome AS "Produto",
    fornecedores.nome AS "Fornecedor"
FROM produtos
    INNER JOIN fornecedores ON produtos.fornecedor_id = fornecedores.id;
-- [B] LISTAR APENAS PRODUTOS DE FORNECEDORES ESTRANGEIROS
SELECT p.nome,
    p.preco,
    f.pais
FROM produtos p
    INNER JOIN fornecedores f ON p.fornecedor_id = f.id
WHERE f.pais <> 'Brasil';
-- [C] CONTAR QUANTOS PRODUTOS CADA FORNECEDOR POSSUI
SELECT f.nome,
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
 
 2. INNER JOIN:
 - Retorna apenas quando há o par perfeito (Produto + Fornecedor).
 - Se um produto não tiver fornecedor, ele some da lista.
 
 3. LEFT JOIN:
 - Retorna TODOS da tabela da esquerda (Fornecedores) mesmo 
 que não tenham produtos vinculados na direita.
 
 4. ALIAS DE TABELA (p, f):
 - Usar 'produtos p' facilita a escrita da query, 
 diminuindo a verbosidade.
 ===============================================================
 */
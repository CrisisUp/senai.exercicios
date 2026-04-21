-- ==============================================================================
-- ATIVIDADE 01: EXPLORADOR DE ESTOQUE (SELECT BÁSICO)
-- OBJETIVO: Criar o banco da SkyStore e realizar as primeiras extrações.
-- ==============================================================================

-- 1. Criação da Tabela
CREATE TABLE IF NOT EXISTS produtos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    categoria TEXT,
    preco REAL,
    estoque INTEGER
);

-- 2. Inserção de Dados (População)
INSERT INTO produtos (nome, categoria, preco, estoque) VALUES 
('Bateria Lipo 4S', 'Energia', 450.00, 15),
('Hélice Carbono 12x4', 'Propulsão', 85.50, 40),
('Sensor GPS Alfa', 'Navegação', 1200.00, 5),
('Câmera Térmica X1', 'Visão', 3500.00, 2),
('Frame em Fibra 250mm', 'Estrutura', 220.00, 10);

-- 3. CONSULTAS DE DESAFIO

-- [A] LISTAR NOME E PREÇO (FORMATO TABULAR)
SELECT nome, preco FROM produtos;

-- [B] FILTRAR PRODUTOS CAROS (ACIMA DE R$ 500)
SELECT * FROM produtos 
WHERE preco > 500;

-- [C] BUSCAR O PRODUTO MAIS CARO DA LOJA
SELECT nome, preco FROM produtos 
ORDER BY preco DESC 
LIMIT 1;

-- [D] CONSULTA COM ALIAS (Renomeando colunas na saída)
SELECT nome AS "Nome do Produto", estoque AS "Quantidade Disponível" 
FROM produtos 
WHERE estoque < 10;

/* 
    ===============================================================
    RESUMO TEÓRICO: O CORAÇÃO DO SQL
    ===============================================================

    1. SELECT: É a projeção. Define quais COLUNAS você quer ver.
    2. FROM: Define de qual TABELA os dados virão.
    3. WHERE: É o filtro. Define quais LINHAS atendem ao critério.
    4. ORDER BY: Define a ordem (ASC ou DESC).
    5. LIMIT: Define o tamanho da amostra (Top N).

    VANTAGEM DIDÁTICA: 
    Ao separar a criação (DDL) da consulta (DML), o aluno percebe que 
    os dados são persistentes e as perguntas (queries) podem mudar.
    ===============================================================
*/

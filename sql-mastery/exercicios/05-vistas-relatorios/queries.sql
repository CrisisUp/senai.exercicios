/**
 * @file queries.sql
 * @brief Vistas e Relatórios com CREATE VIEW para Abstração de Complexidade.
 * @section ExecutionPlan Views no SQLite não são materializadas; a query da view 
 * é integrada à query principal. O custo é o da query base, mas views complexas 
 * empilhadas podem ofuscar o uso de índices para o otimizador.
 * @author Gemini CLI
 * @date 2026-04-19
 */

-- ==============================================================================
-- ATIVIDADE 05: VISTAS E RELATÓRIOS (VIEWS)
-- OBJETIVO: Criar abstrações para simplificar consultas complexas.
-- ==============================================================================

-- 1. Setup do Banco (Tabelas e Dados)
CREATE TABLE IF NOT EXISTS fornecedores (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL
);

-- Aplicando Guardião Financeiro: preco_centavos, desconto_centavos
CREATE TABLE IF NOT EXISTS produtos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    preco_centavos INTEGER,
    desconto_centavos INTEGER DEFAULT 0,
    fornecedor_id INTEGER,
    FOREIGN KEY (fornecedor_id) REFERENCES fornecedores(id)
);

DELETE FROM produtos;
DELETE FROM fornecedores;

INSERT INTO fornecedores (nome)
VALUES ('TecnoDrone'),
    ('AeroParts');

INSERT INTO produtos (nome, preco_centavos, desconto_centavos, fornecedor_id)
VALUES ('Bateria Lipo 4S', 45000, 4500, 1),
    ('Frame Carbono', 22000, 0, 1),
    ('GPS Alfa', 120000, 10000, 2),
    ('Motor X', 55000, 0, 2);

-- 2. CRIAÇÃO DAS VISTAS (VIEWS)

-- [A] VISTA DE CATÁLOGO (JOIN Escondido)
-- Colunas explícitas para garantir integridade.
CREATE VIEW IF NOT EXISTS v_catalogo_completo AS
SELECT p.id,
    p.nome AS "Produto",
    p.preco_centavos / 100.0 AS "Preço (R$)",
    f.nome AS "Fornecedor"
FROM produtos p
    INNER JOIN fornecedores f ON p.fornecedor_id = f.id;

-- [B] VISTA DE PROMOÇÕES (Cálculo Escondido)
CREATE VIEW IF NOT EXISTS v_promocoes_ativas AS
SELECT nome AS "Produto",
    preco_centavos / 100.0 AS "Preço Original (R$)",
    desconto_centavos / 100.0 AS "Desconto (R$)",
    (preco_centavos - desconto_centavos) / 100.0 AS "Preço Final (R$)"
FROM produtos
WHERE desconto_centavos > 0;

-- 3. CONSULTAS SOBRE AS VIEWS

-- Listar catálogo completo (Colunas explícitas)
SELECT id, "Produto", "Preço (R$)", "Fornecedor"
FROM v_catalogo_completo;

-- Listar apenas itens em promoção
SELECT "Produto", "Preço Original (R$)", "Preço Final (R$)"
FROM v_promocoes_ativas;

/* 
 ===============================================================
 RESUMO TEÓRICO: VISTAS (TABELAS VIRTUAIS)
 ===============================================================
 
 1. O QUE É UMA VIEW?
 - É apenas um SELECT "congelado" com um nome. Não ocupa espaço de dados.
 
 2. VANTAGENS:
 - Simplicidade: Usuários finais não precisam saber fazer JOIN.
 - Segurança: Pode ocultar colunas sensíveis (ex: custo_centavos).
 
 3. LIMITAÇÕES:
 - O custo computacional é recalculado a cada execução (no SQLite).
 
 4. GUARDIÃO FINANCEIRO:
 - Mesmo em Views, os cálculos de preços devem ser realizados a partir 
 de INTEGER (centavos) para manter a integridade decimal na exibição.
 ===============================================================
 */

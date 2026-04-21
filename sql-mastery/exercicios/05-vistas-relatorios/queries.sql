-- ==============================================================================
-- ATIVIDADE 05: VISTAS E RELATÓRIOS (VIEWS)
-- OBJETIVO: Criar abstrações para simplificar consultas complexas.
-- ==============================================================================
-- 1. Setup do Banco (Tabelas e Dados)
CREATE TABLE IF NOT EXISTS fornecedores (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL
);
CREATE TABLE IF NOT EXISTS produtos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    preco REAL,
    desconto REAL DEFAULT 0.0,
    fornecedor_id INTEGER,
    FOREIGN KEY (fornecedor_id) REFERENCES fornecedores(id)
);
DELETE FROM produtos;
DELETE FROM fornecedores;
INSERT INTO fornecedores (nome)
VALUES ('TecnoDrone'),
    ('AeroParts');
INSERT INTO produtos (nome, preco, desconto, fornecedor_id)
VALUES ('Bateria Lipo 4S', 450.0, 45.0, 1),
    ('Frame Carbono', 220.0, 0.0, 1),
    ('GPS Alfa', 1200.0, 100.0, 2),
    ('Motor X', 550.0, 0.0, 2);
-- 2. CRIAÇÃO DAS VISTAS (VIEWS)
-- [A] VISTA DE CATÁLOGO (JOIN Escondido)
CREATE VIEW IF NOT EXISTS v_catalogo_completo AS
SELECT p.id,
    p.nome AS "Produto",
    p.preco,
    f.nome AS "Fornecedor"
FROM produtos p
    INNER JOIN fornecedores f ON p.fornecedor_id = f.id;
-- [B] VISTA DE PROMOÇÕES (Cálculo Escondido)
CREATE VIEW IF NOT EXISTS v_promocoes_ativas AS
SELECT nome,
    preco AS "Preço Original",
    desconto,
    (preco - desconto) AS "Preço Final"
FROM produtos
WHERE desconto > 0;
-- 3. CONSULTAS SOBRE AS VIEWS
-- Note como a query fica curta e legível!
-- Listar catálogo completo
SELECT *
FROM v_catalogo_completo;
-- Listar apenas itens em promoção da TecnoDrone (Usando a View + Filtro)
SELECT *
FROM v_promocoes_ativas;
/* 
 ===============================================================
 RESUMO TEÓRICO: VISTAS (TABELAS VIRTUAIS)
 ===============================================================
 
 1. O QUE É UMA VIEW?
 - É apenas um SELECT "congelado" com um nome. 
 - Ela não ocupa espaço em disco (além da definição da query), 
 pois os dados continuam nas tabelas originais.
 
 2. VANTAGENS:
 - Simplicidade: Usuários finais não precisam saber fazer JOIN.
 - Manutenção: Se a regra de desconto mudar, você altera o 
 SELECT da View em um só lugar.
 
 3. LIMITAÇÕES:
 - No SQLite, Views são geralmente de "somente leitura" para 
 o SELECT (você não dá UPDATE em uma View complexa).
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende o conceito de INTERFACE no banco de dados. 
 A View é a interface entre o banco e o usuário/aplicação.
 ===============================================================
 */
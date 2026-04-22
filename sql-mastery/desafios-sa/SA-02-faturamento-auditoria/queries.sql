-- ==============================================================================
-- DESAFIO INTEGRADOR SA-02: FATURAMENTO E AUDITORIA
-- OBJETIVO: Integrar Evolução de Esquema, Transações e Views.
-- ==============================================================================
-- 1. Setup da Estrutura Base
CREATE TABLE IF NOT EXISTS estoque_geral (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    item TEXT NOT NULL,
    quantidade INTEGER
);
CREATE TABLE IF NOT EXISTS pedidos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    data_faturamento TEXT
);
CREATE TABLE IF NOT EXISTS itens_pedido (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    pedido_id INTEGER,
    produto TEXT,
    valor_unitario REAL,
    quantidade INTEGER,
    FOREIGN KEY (pedido_id) REFERENCES pedidos(id)
);
-- Limpando para o desafio
DELETE FROM itens_pedido;
DELETE FROM pedidos;
DELETE FROM estoque_geral;
INSERT INTO estoque_geral (item, quantidade)
VALUES ('Motor Brushless', 20),
    ('Hélice Carbono', 50);
-- 2. EVOLUÇÃO DO ESQUEMA (Requisito: ALTER TABLE)
ALTER TABLE itens_pedido
ADD COLUMN imposto_valor REAL DEFAULT 0.0;
-- 3. TRANSAÇÃO DE VENDA BLINDADA (Requisito: BEGIN/COMMIT)
BEGIN TRANSACTION;
-- Passo A: Registrar o Pedido
INSERT INTO pedidos (data_faturamento)
VALUES ('2026-04-20');
-- Passo B: Registrar Itens com cálculo de imposto (10% de 550.0 = 55.0)
INSERT INTO itens_pedido (
        pedido_id,
        produto,
        valor_unitario,
        quantidade,
        imposto_valor
    )
VALUES (1, 'Motor Brushless', 550.0, 2, 55.0);
-- Passo C: Baixar Estoque
UPDATE estoque_geral
SET quantidade = quantidade - 2
WHERE item = 'Motor Brushless';
COMMIT;
-- 4. CRIAÇÃO DA VISTA DE AUDITORIA (Requisito: VIEW)
CREATE VIEW IF NOT EXISTS v_auditoria_financeira AS
SELECT p.id AS "Nº Pedido",
    p.data_faturamento AS "Data",
    SUM(i.valor_unitario * i.quantidade) AS "Valor Bruto",
    SUM(i.imposto_valor * i.quantidade) AS "Total Impostos",
    SUM(
        (i.valor_unitario - i.imposto_valor) * i.quantidade
    ) AS "Valor Líquido"
FROM pedidos p
    JOIN itens_pedido i ON p.id = i.pedido_id
GROUP BY p.id;
-- 5. CONSULTA DE PROVA
SELECT *
FROM v_auditoria_financeira;
SELECT *
FROM estoque_geral;
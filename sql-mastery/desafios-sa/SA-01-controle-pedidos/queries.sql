-- ==============================================================================
-- DESAFIO INTEGRADOR SA-01: CONTROLE DE PEDIDOS
-- OBJETIVO: Integrar SELECT, Agregações e JOINs em um cenário real.
-- ==============================================================================
-- 1. Criação das Tabelas (DDL)
CREATE TABLE IF NOT EXISTS clientes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    cidade TEXT
);
CREATE TABLE IF NOT EXISTS pedidos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    cliente_id INTEGER,
    data_pedido TEXT,
    status TEXT,
    FOREIGN KEY (cliente_id) REFERENCES clientes(id)
);
CREATE TABLE IF NOT EXISTS itens_pedido (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    pedido_id INTEGER,
    produto TEXT NOT NULL,
    valor_unitario REAL,
    quantidade INTEGER,
    FOREIGN KEY (pedido_id) REFERENCES pedidos(id)
);
-- Limpando dados para o desafio
DELETE FROM itens_pedido;
DELETE FROM pedidos;
DELETE FROM clientes;
-- 2. Inserção de Dados (População)
INSERT INTO clientes (nome, cidade)
VALUES ('Indústrias DroneX', 'São Paulo'),
    ('Logística Norte', 'Manaus'),
    ('AgroTec Digital', 'Cuiabá');
INSERT INTO pedidos (cliente_id, data_pedido, status)
VALUES (1, '2026-04-10', 'Entregue'),
    (1, '2026-04-15', 'Pendente'),
    (2, '2026-04-12', 'Entregue'),
    (2, '2026-04-18', 'Em Transporte'),
    (3, '2026-04-20', 'Pendente');
INSERT INTO itens_pedido (pedido_id, produto, valor_unitario, quantidade)
VALUES (1, 'Bateria Lipo 4S', 450.00, 10),
    (1, 'Hélice Carbono', 85.00, 20),
    (2, 'Sensor GPS', 1200.00, 2),
    (3, 'Câmera Térmica', 3500.00, 1),
    (3, 'Frame 250mm', 220.00, 5),
    (4, 'Antena Long Range', 350.00, 2),
    (4, 'Cabo RF', 45.00, 10),
    (5, 'Kit Calibragem', 1500.00, 1),
    (5, 'Motor Brushless', 550.00, 4),
    (1, 'Carregador Balanceado', 250.00, 2);
-- 3. CONSULTAS DE NEGÓCIO (O Desafio)
-- [A] RELATÓRIO DE FATURAMENTO POR CLIENTE
-- Une clientes -> pedidos -> itens para saber quanto cada empresa já gastou.
SELECT c.nome,
    SUM(i.valor_unitario * i.quantidade) AS "Total Gasto"
FROM clientes c
    JOIN pedidos p ON c.id = p.cliente_id
    JOIN itens_pedido i ON p.id = i.pedido_id
GROUP BY c.nome
ORDER BY "Total Gasto" DESC;
-- [B] LISTAGEM DE ITENS PENDENTES (LOGÍSTICA)
-- Mostra quais produtos precisam ser separados para entrega.
SELECT p.id AS "Nº Pedido",
    i.produto,
    i.quantidade,
    c.nome AS "Cliente"
FROM pedidos p
    JOIN itens_pedido i ON p.id = i.pedido_id
    JOIN clientes c ON p.cliente_id = c.id
WHERE p.status = 'Pendente';
-- [C] TICKET MÉDIO DOS PEDIDOS
-- Calcula o valor médio de cada pedido feito na SkyCargo.
SELECT AVG(Sub.TotalPedido) AS "Ticket Médio da Empresa"
FROM (
        SELECT pedido_id,
            SUM(valor_unitario * quantidade) AS TotalPedido
        FROM itens_pedido
        GROUP BY pedido_id
    ) AS Sub;
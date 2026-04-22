/**
 * @file queries.sql
 * @brief Sistema de Controle de Pedidos - SA-01
 * @author Gemini CLI Agent
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * O plano de execução foca na integridade referencial e eficiência de junções (JOINs).
 * - Uso de FOREIGN KEYs para evitar orfandade de itens.
 * - Joins entre clientes, pedidos e itens para consolidação de faturamento.
 * - Agregações (SUM, AVG) para geração de KPIs de negócio.
 * - Estratégia "Guardião Financeiro": Valores monetários armazenados como INTEGER (centavos)
 *   para garantir precisão absoluta e evitar erros de ponto flutuante.
 */

-- ==============================================================================
-- 1. Criação das Tabelas (DDL)
-- ==============================================================================
PRAGMA foreign_keys = ON;

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
    valor_unitario_centavos INTEGER NOT NULL, -- Guardião Financeiro: Centavos inteiros
    quantidade INTEGER NOT NULL,
    FOREIGN KEY (pedido_id) REFERENCES pedidos(id)
);

-- Limpando dados para o desafio
DELETE FROM itens_pedido;
DELETE FROM pedidos;
DELETE FROM clientes;

-- ==============================================================================
-- 2. Inserção de Dados (População) - Valores em Centavos
-- ==============================================================================
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

INSERT INTO itens_pedido (pedido_id, produto, valor_unitario_centavos, quantidade)
VALUES (1, 'Bateria Lipo 4S', 45000, 10),     -- R$ 450,00
    (1, 'Hélice Carbono', 8500, 20),           -- R$ 85,00
    (2, 'Sensor GPS', 120000, 2),             -- R$ 1200,00
    (3, 'Câmera Térmica', 350000, 1),         -- R$ 3500,00
    (3, 'Frame 250mm', 22000, 5),             -- R$ 220,00
    (4, 'Antena Long Range', 35000, 2),       -- R$ 350,00
    (4, 'Cabo RF', 4500, 10),                 -- R$ 45,00
    (5, 'Kit Calibragem', 150000, 1),         -- R$ 1500,00
    (5, 'Motor Brushless', 55000, 4),         -- R$ 550,00
    (1, 'Carregador Balanceado', 25000, 2);   -- R$ 250,00

-- ==============================================================================
-- 3. CONSULTAS DE NEGÓCIO (O Desafio)
-- ==============================================================================

-- [A] RELATÓRIO DE FATURAMENTO POR CLIENTE
-- Une clientes -> pedidos -> itens para saber quanto cada empresa já gastou.
-- Nota: O resultado é dividido por 100.0 para exibição formatada.
SELECT c.nome,
    SUM(i.valor_unitario_centavos * i.quantidade) / 100.0 AS "Total Gasto (R$)"
FROM clientes c
    JOIN pedidos p ON c.id = p.cliente_id
    JOIN itens_pedido i ON p.id = i.pedido_id
GROUP BY c.nome
ORDER BY "Total Gasto (R$)" DESC;

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
SELECT AVG(Sub.TotalPedidoCentavos) / 100.0 AS "Ticket Médio da Empresa (R$)"
FROM (
        SELECT pedido_id,
            SUM(valor_unitario_centavos * quantidade) AS TotalPedidoCentavos
        FROM itens_pedido
        GROUP BY pedido_id
    ) AS Sub;

/*
Resumo Teórico:
1. Normalização: A divisão em três tabelas (Clientes, Pedidos, Itens) elimina a redundância e protege a integridade dos dados.
2. Joins (Junções): O INNER JOIN é fundamental para consolidar dados espalhados, permitindo visões de negócio como o faturamento por cliente.
3. Agregações: SUM e AVG permitem transformar linhas de dados em métricas financeiras (KPIs).
4. Guardião Financeiro: O uso de INTEGER para centavos é uma prática de elite para evitar os erros inerentes à representação de ponto flutuante em sistemas financeiros.

Assuntos Correlatos:
- Transações ACID: Como garantir que um pedido e seus itens sejam salvos simultaneamente ou nenhum deles seja.
- Índices (INDEX): Como acelerar buscas em tabelas com milhões de pedidos.
- Views: Criar relatórios virtuais para simplificar consultas complexas para o usuário final.
- Stored Procedures e Triggers: Automação de lógica de negócio dentro do banco de dados.
*/

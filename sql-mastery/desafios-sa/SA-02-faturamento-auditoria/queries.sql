/**
 * @file queries.sql
 * @brief Sistema de Faturamento e Auditoria - SA-02
 * @author Gemini CLI Agent
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * O plano de execução garante a atomicidade das transações financeiras e a integridade do estoque.
 * - Uso de BEGIN/COMMIT para garantir que a venda e a baixa de estoque ocorram juntas.
 * - Views consolidadas para facilitar a auditoria sem necessidade de Joins manuais repetitivos.
 * - Evolução de Esquema via ALTER TABLE para adaptar o sistema a novas regras fiscais.
 * - Estratégia "Guardião Financeiro": Todos os valores monetários são INTEGER (centavos).
 */

-- ==============================================================================
-- 1. Setup da Estrutura Base
-- ==============================================================================
PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS estoque_geral (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    item TEXT NOT NULL,
    quantidade INTEGER NOT NULL CHECK (quantidade >= 0)
);

CREATE TABLE IF NOT EXISTS pedidos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    data_faturamento TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS itens_pedido (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    pedido_id INTEGER,
    produto TEXT NOT NULL,
    valor_unitario_centavos INTEGER NOT NULL, -- Guardião Financeiro
    quantidade INTEGER NOT NULL,
    FOREIGN KEY (pedido_id) REFERENCES pedidos(id)
);

-- Limpando para o desafio
DELETE FROM itens_pedido;
DELETE FROM pedidos;
DELETE FROM estoque_geral;

INSERT INTO estoque_geral (item, quantidade)
VALUES ('Motor Brushless', 20),
    ('Hélice Carbono', 50);

-- ==============================================================================
-- 2. EVOLUÇÃO DO ESQUEMA (Requisito: ALTER TABLE)
-- ==============================================================================
-- Adicionando imposto em centavos para manter a precisão absoluta
ALTER TABLE itens_pedido
ADD COLUMN imposto_centavos INTEGER DEFAULT 0;

-- ==============================================================================
-- 3. TRANSAÇÃO DE VENDA BLINDADA (Requisito: BEGIN/COMMIT)
-- ==============================================================================
BEGIN TRANSACTION;

-- Passo A: Registrar o Pedido
INSERT INTO pedidos (data_faturamento)
VALUES ('2026-04-20');

-- Passo B: Registrar Itens com cálculo de imposto (10% de 550.00 = 55.00)
-- 550.00 -> 55000 centavos | 55.00 -> 5500 centavos
INSERT INTO itens_pedido (
        pedido_id,
        produto,
        valor_unitario_centavos,
        quantidade,
        imposto_centavos
    )
VALUES (1, 'Motor Brushless', 55000, 2, 5500);

-- Passo C: Baixar Estoque
UPDATE estoque_geral
SET quantidade = quantidade - 2
WHERE item = 'Motor Brushless';

COMMIT;

-- ==============================================================================
-- 4. CRIAÇÃO DA VISTA DE AUDITORIA (Requisito: VIEW)
-- ==============================================================================
CREATE VIEW IF NOT EXISTS v_auditoria_financeira AS
SELECT p.id AS "Nº Pedido",
    p.data_faturamento AS "Data",
    SUM(i.valor_unitario_centavos * i.quantidade) / 100.0 AS "Valor Bruto (R$)",
    SUM(i.imposto_centavos * i.quantidade) / 100.0 AS "Total Impostos (R$)",
    SUM(
        (i.valor_unitario_centavos - i.imposto_centavos) * i.quantidade
    ) / 100.0 AS "Valor Líquido (R$)"
FROM pedidos p
    JOIN itens_pedido i ON p.id = i.pedido_id
GROUP BY p.id;

-- ==============================================================================
-- 5. CONSULTA DE PROVA
-- ==============================================================================
SELECT * FROM v_auditoria_financeira;
SELECT * FROM estoque_geral;

/*
Resumo Teórico:
1. Transações ACID: O uso de BEGIN/COMMIT garante que todas as operações de uma venda (pedido, itens, estoque) ocorram com sucesso ou falhem juntas (Atomicidade).
2. Atomicidade e Consistência: O CHECK (quantidade >= 0) na tabela de estoque impede vendas acima do disponível, mesmo que o código da aplicação falhe.
3. Views: Simplificam relatórios complexos, ocultando a lógica de Join e cálculos matemáticos por trás de uma interface de "tabela virtual".
4. Guardião Financeiro: A transição de REAL para INTEGER (centavos) elimina o risco de dízimas periódicas no cálculo de impostos e lucros.

Assuntos Correlatos:
- Transações Aninhadas (SAVEPOINTS): Como fazer Rollback parcial de uma transação.
- Gatilhos (TRIGGERS): Como automatizar a atualização de estoque sempre que um item de pedido for inserido.
- Normalização de Impostos: Criar tabelas de alíquotas por tipo de produto para evitar valores fixos (Hardcoded).
- Locks de Banco de Dados: Como o SQL protege os dados contra acesso simultâneo em ambientes de alta concorrência.
*/

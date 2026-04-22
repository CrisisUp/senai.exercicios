/**
 * @file queries.sql
 * @brief Atividade 09: Automação com Gatilhos (TRIGGERS)
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * Foco em B-Trees e Side-Effects:
 * - O gatilho (Trigger) é executado como parte da transação original do INSERT.
 * - O custo do INSERT passa a incluir o custo de um UPDATE (O(log n) na B-Tree de produtos).
 * - O SQLite utiliza um motor de máquina virtual (VDBE) para executar o bytecode do gatilho.
 */

-- ==============================================================================
-- ATIVIDADE 09: AUTOMAÇÃO COM GATILHOS (TRIGGERS)
-- OBJETIVO: Automatizar a baixa de estoque através de gatilhos internos.
-- ==============================================================================

-- 1. Setup das Tabelas
-- @note Guardião Financeiro: valor_venda_cents (INTEGER) para registrar o montante financeiro da venda.
CREATE TABLE IF NOT EXISTS produtos_estoque (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    quantidade INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS vendas_registro (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    produto_id INTEGER,
    qtd_vendida INTEGER,
    valor_venda_cents INTEGER,
    FOREIGN KEY (produto_id) REFERENCES produtos_estoque(id)
);

-- Limpando dados
DELETE FROM vendas_registro;
DELETE FROM produtos_estoque;

-- Inserindo estoque inicial
INSERT INTO produtos_estoque (nome, quantidade)
VALUES ('Hélice Carbono', 100),
    ('GPS Industrial', 10);

-- 2. CRIAÇÃO DO GATILHO (TRIGGER)
-- Este código "observa" a tabela vendas_registro.
-- Sempre que um INSERT acontecer, ele executa o UPDATE abaixo.
CREATE TRIGGER IF NOT EXISTS trg_baixar_estoque
AFTER
INSERT ON vendas_registro 
BEGIN
    UPDATE produtos_estoque
    SET quantidade = quantidade - NEW.qtd_vendida
    WHERE id = NEW.produto_id;
END;

-- 3. TESTE DE AUTOMAÇÃO
-- Consulta ANTES da venda
SELECT *
FROM produtos_estoque;

-- Realizando uma venda (Note que NÃO damos comando de baixa de estoque aqui!)
INSERT INTO vendas_registro (produto_id, qtd_vendida, valor_venda_cents)
VALUES (1, 20, 15000); -- R$ 150,00

INSERT INTO vendas_registro (produto_id, qtd_vendida, valor_venda_cents)
VALUES (2, 2, 85000); -- R$ 850,00

-- Consulta DEPOIS da venda
-- O estoque deve estar: Hélice = 80, GPS = 8.
SELECT 
    id, 
    nome, 
    quantidade 
FROM produtos_estoque;

-- Verificando registro financeiro
SELECT 
    id, 
    produto_id, 
    qtd_vendida, 
    (valor_venda_cents / 100.0) AS valor_reais 
FROM vendas_registro;

/* 
 ===============================================================
 RESUMO TEÓRICO: TRIGGERS (O CÉREBRO DO BANCO)
 ===============================================================
 
 1. O QUE SÃO?
 - São procedimentos automáticos. Você define o EVENTO 
 (INSERT/UPDATE/DELETE) e o MOMENTO (BEFORE/AFTER).
 
 2. NEW e OLD:
 - Palavras-chave especiais. 
 - NEW: Acessa os dados que acabaram de chegar no INSERT.
 - OLD: Acessa os dados que existiam antes no DELETE ou UPDATE.
 
 3. VANTAGEM DIDÁTICA: 
 - O aluno percebe que o banco de dados pode ter "Lógica de 
 Negócio" embutida, garantindo que regras críticas nunca 
 sejam ignoradas por programadores distraídos.

 4. GUARDIÃO FINANCEIRO:
 - Integrar o registro financeiro (cents) com gatilhos de estoque 
 garante a consistência entre o fluxo de caixa e o fluxo físico.
 
 5. PERIGO:
 - Muitos Triggers podem deixar o banco lento e dificultar a 
 depuração, pois as coisas acontecem "por baixo dos panos". 
 Use com sabedoria!

 ASSUNTOS CORRELATOS:
 - INSTEAD OF Triggers (Para Views).
 - Recursive Triggers (Desabilitados por padrão no SQLite).
 - RAISE() function para validação dentro de Triggers.
 ===============================================================
 */

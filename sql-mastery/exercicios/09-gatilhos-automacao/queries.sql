-- ==============================================================================
-- ATIVIDADE 09: AUTOMAÇÃO COM GATILHOS (TRIGGERS)
-- OBJETIVO: Automatizar a baixa de estoque através de gatilhos internos.
-- ==============================================================================
-- 1. Setup das Tabelas
CREATE TABLE IF NOT EXISTS produtos_estoque (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    quantidade INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS vendas_registro (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    produto_id INTEGER,
    qtd_vendida INTEGER,
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
INSERT ON vendas_registro BEGIN
UPDATE produtos_estoque
SET quantidade = quantidade - NEW.qtd_vendida
WHERE id = NEW.produto_id;
END;
-- 3. TESTE DE AUTOMAÇÃO
-- Consulta ANTES da venda
SELECT *
FROM produtos_estoque;
-- Realizando uma venda (Note que NÃO damos comando de baixa de estoque aqui!)
INSERT INTO vendas_registro (produto_id, qtd_vendida)
VALUES (1, 20);
INSERT INTO vendas_registro (produto_id, qtd_vendida)
VALUES (2, 2);
-- Consulta DEPOIS da venda
-- O estoque deve estar: Hélice = 80, GPS = 8.
SELECT *
FROM produtos_estoque;
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
 
 4. PERIGO:
 - Muitos Triggers podem deixar o banco lento e dificultar a 
 depuração, pois as coisas acontecem "por baixo dos panos". 
 Use com sabedoria!
 ===============================================================
 */
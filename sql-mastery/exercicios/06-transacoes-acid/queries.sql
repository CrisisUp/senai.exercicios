-- ==============================================================================
-- ATIVIDADE 06: TRANSAÇÕES E INTEGRIDADE (ACID)
-- OBJETIVO: Garantir que operações complexas sejam atômicas.
-- ==============================================================================
-- 1. Setup do Ambiente
CREATE TABLE IF NOT EXISTS estoque_geral (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    item TEXT NOT NULL,
    quantidade INTEGER
);
CREATE TABLE IF NOT EXISTS carga_drone (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    item TEXT NOT NULL,
    quantidade INTEGER
);
DELETE FROM estoque_geral;
DELETE FROM carga_drone;
INSERT INTO estoque_geral (item, quantidade)
VALUES ('Bateria Lipo 4S', 100);
INSERT INTO carga_drone (item, quantidade)
VALUES ('Bateria Lipo 4S', 0);
-- 2. DEMONSTRAÇÃO 1: SUCESSO (COMMIT)
BEGIN TRANSACTION;
-- Passo 1: Retirar do armazém
UPDATE estoque_geral
SET quantidade = quantidade - 5
WHERE item = 'Bateria Lipo 4S';
-- Passo 2: Adicionar ao drone
UPDATE carga_drone
SET quantidade = quantidade + 5
WHERE item = 'Bateria Lipo 4S';
COMMIT;
-- Salva permanentemente
-- 3. DEMONSTRAÇÃO 2: FALHA E RECUPERAÇÃO (ROLLBACK)
BEGIN TRANSACTION;
-- Passo 1: Retirar mais 50 unidades do armazém
UPDATE estoque_geral
SET quantidade = quantidade - 50
WHERE item = 'Bateria Lipo 4S';
-- O sistema percebe um erro (simulado)! 
-- Queremos cancelar tudo o que foi feito dentro desta transação.
ROLLBACK;
-- 4. CONSULTA FINAL PARA PROVAR A INTEGRIDADE
-- O resultado deve mostrar 95 no estoque e 5 no drone (a falha de 50 foi anulada).
SELECT *
FROM estoque_geral;
SELECT *
FROM carga_drone;
/* 
 ===============================================================
 RESUMO TEÓRICO: TRANSAÇÕES (A BARREIRA DE SEGURANÇA)
 ===============================================================
 
 1. ATOMICIDADE (TUDO OU NADA):
 - Uma transação é um contrato com o banco de dados. 
 - O banco garante que o sistema nunca ficará "pela metade".
 
 2. COMMIT:
 - É a confirmação final. Somente após este comando os outros 
 usuários do banco verão as mudanças.
 
 3. ROLLBACK:
 - É o botão "Desfazer" de emergência. Ele volta o banco para 
 o estado EXATO de antes do BEGIN TRANSACTION.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende a lidar com cenários críticos de falha, onde o 
 erro humano ou técnico não deve corromper a integridade dos dados.
 ===============================================================
 */
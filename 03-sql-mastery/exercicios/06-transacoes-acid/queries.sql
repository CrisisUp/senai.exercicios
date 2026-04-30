/**
 * @file queries.sql
 * @brief Atividade 06: Transações e Integridade (ACID)
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * Foco em B-Trees para Índices e Complexidade:
 * - Operações de INSERT/UPDATE em tabelas com chaves primárias utilizam a B-Tree da chave.
 * - Complexidade O(log n) para localização de registros e atualização.
 * - COMMIT garante persistência via WAL (Write-Ahead Logging) ou Journaling.
 */
-- ==============================================================================
-- ATIVIDADE 06: TRANSAÇÕES E INTEGRIDADE (ACID)
-- OBJETIVO: Garantir que operações complexas sejam atômicas.
-- ==============================================================================
-- 1. Setup do Ambiente
-- @note Guardião Financeiro: Usamos INTEGER para valor_unitario_cents para evitar imprecisão de ponto flutuante.
CREATE TABLE IF NOT EXISTS estoque_geral (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    item TEXT NOT NULL,
    quantidade INTEGER,
    valor_unitario_cents INTEGER NOT NULL -- Valor em centavos (ex: 1000 = R$ 10,00)
);
CREATE TABLE IF NOT EXISTS carga_drone (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    item TEXT NOT NULL,
    quantidade INTEGER
);
DELETE FROM estoque_geral;
DELETE FROM carga_drone;
INSERT INTO estoque_geral (item, quantidade, valor_unitario_cents)
VALUES ('Bateria Lipo 4S', 100, 45000);
-- R$ 450,00
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
SELECT id,
    item,
    quantidade,
    valor_unitario_cents,
    (valor_unitario_cents / 100.0) AS valor_reais -- Formatação apenas na saída
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
 
 4. GUARDIÃO FINANCEIRO:
 - A utilização de INTEGER para valores monetários (centavos) é 
 uma prática fundamental de engenharia para evitar erros de 
 arredondamento acumulados em cálculos complexos.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende a lidar com cenários críticos de falha, onde o 
 erro humano ou técnico não deve corromper a integridade dos dados.
 
 ASSUNTOS CORRELATOS:
 - Isolation Levels (Read Uncommitted, Serializable).
 - WAL (Write-Ahead Logging).
 - Savepoints em transações aninhadas.
 ===============================================================
 */
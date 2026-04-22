/**
 * @file queries.sql
 * @brief A Fortaleza de Dados (Segurança e Integridade).
 * @author Gemini CLI
 * @date 2026-04-19
 * @section ExecutionPlan Estratégias de Defesa Ativa via CHECK e Triggers Preventivos.
 */

-- ==============================================================================
-- ATIVIDADE 20: A FORTALEZA DE DADOS (SEGURANÇA TOTAL)
-- OBJETIVO: Implementar camadas de proteção interna no banco.
-- ==============================================================================

-- 1. Criação da Tabela de Usuários com Blindagem de Entrada e Guardião Financeiro
CREATE TABLE IF NOT EXISTS usuarios_central (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    email TEXT NOT NULL CHECK (email LIKE '%@%'),
    -- Validação básica de formato e integridade financeira
    saldo_cents INTEGER DEFAULT 0 CHECK (saldo_cents >= 0)
);

-- 2. Criação da Tabela Imutável (Caixa Preta)
CREATE TABLE IF NOT EXISTS caixa_preta (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    log_msg TEXT NOT NULL,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP
);

DELETE FROM usuarios_central;
DELETE FROM caixa_preta;

-- 3. BLOQUEIO DE SEGURANÇA (TRIGGER PREVENTIVO)
-- @section ExecutionPlan: Triggers BEFORE abortam a operação antes do custo de I/O.
CREATE TRIGGER IF NOT EXISTS trg_bloquear_delecao_log 
BEFORE DELETE ON caixa_preta 
BEGIN
    SELECT RAISE(
        ABORT,
        'ERRO DE SEGURANÇA: Registros da Caixa Preta são IMUTÁVEIS e não podem ser apagados!'
    );
END;

-- Este gatilho impede que qualquer pessoa altere um log já registrado.
CREATE TRIGGER IF NOT EXISTS trg_bloquear_update_log 
BEFORE UPDATE ON caixa_preta 
BEGIN
    SELECT RAISE(
        ABORT,
        'ERRO DE SEGURANÇA: Registros da Caixa Preta não podem ser alterados após o registro!'
    );
END;

-- 4. POPULANDO DADOS INICIAIS
INSERT INTO usuarios_central (nome, email, saldo_cents)
VALUES ('Admin Principal', 'admin@skycargo.com', 100000); -- R$ 1.000,00

INSERT INTO caixa_preta (log_msg)
VALUES ('Sistema de Fortaleza de Dados Iniciado.');

-- 5. TESTES DE SEGURANÇA (Consulte o plano de execução para ver a interrupção)
-- @section ExecutionPlan: O banco avalia as constraints antes da inserção física.
EXPLAIN QUERY PLAN
INSERT INTO usuarios_central (nome, email, saldo_cents) VALUES ('Hacker', 'h@h.com', -10);

-- 6. CONSULTA FINAL
SELECT 
    nome,
    email,
    saldo_cents / 100.0 AS saldo_real
FROM usuarios_central;

/* 
 ===============================================================
 RESUMO TEÓRICO: A FORTALEZA SQL
 ===============================================================
 
 1. RAISE(ABORT, 'msg'): 
 - Interrompe imediatamente qualquer transação que viole a 
 política de segurança.

 2. CHECK CONSTRAINTS: 
 - Garantem que os dados sigam o domínio de negócio (Email, Saldo).

 3. GUARDIÃO FINANCEIRO:
 - Saldo em centavos (INTEGER) impede erros de flutuantes.

 ===============================================================
 ASSUNTOS CORRELATOS:
 - SQL Injection Prevention (Prepared Statements).
 - Role-Based Access Control (RBAC).
 - SQL Cipher (Criptografia de banco de dados).
 ===============================================================
 */

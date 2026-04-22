-- ==============================================================================
-- ATIVIDADE 20: A FORTALEZA DE DADOS (SEGURANÇA TOTAL)
-- OBJETIVO: Implementar camadas de proteção interna no banco.
-- ==============================================================================
-- 1. Criação da Tabela de Usuários com Blindagem de Entrada
CREATE TABLE IF NOT EXISTS usuarios_central (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    email TEXT NOT NULL CHECK (email LIKE '%@%'),
    -- Validação básica de formato
    saldo REAL DEFAULT 0.0 CHECK (saldo >= 0.0) -- Impede saldos negativos
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
-- Este gatilho impede que qualquer pessoa apague um log da caixa preta.
CREATE TRIGGER IF NOT EXISTS trg_bloquear_delecao_log BEFORE DELETE ON caixa_preta BEGIN
SELECT RAISE(
        ABORT,
        'ERRO DE SEGURANÇA: Registros da Caixa Preta são IMUTÁVEIS e não podem ser apagados!'
    );
END;
-- Este gatilho impede que qualquer pessoa altere um log já registrado.
CREATE TRIGGER IF NOT EXISTS trg_bloquear_update_log BEFORE
UPDATE ON caixa_preta BEGIN
SELECT RAISE(
        ABORT,
        'ERRO DE SEGURANÇA: Registros da Caixa Preta não podem ser alterados após o registro!'
    );
END;
-- 4. POPULANDO DADOS INICIAIS
INSERT INTO usuarios_central (nome, email, saldo)
VALUES ('Admin Principal', 'admin@skycargo.com', 1000.0);
INSERT INTO caixa_preta (log_msg)
VALUES ('Sistema de Fortaleza de Dados Iniciado.');
-- 5. TESTES DE SEGURANÇA (Estes devem falhar conforme o planejado)
-- [A] Teste: Email Inválido
-- INSERT INTO usuarios_central (nome, email) VALUES ('Hacker', 'email_sem_arroba');
-- [B] Teste: Saldo Negativo
-- INSERT INTO usuarios_central (nome, email, saldo) VALUES ('Hacker', 'h@h.com', -50.0);
-- [C] Teste: Tentar apagar a história (Gera erro do Trigger)
-- DELETE FROM caixa_preta;
/* 
 ===============================================================
 RESUMO TEÓRICO: A FORTALEZA SQL
 ===============================================================
 
 1. RAISE(ABORT, 'msg'): 
 - É a arma definitiva do DBA. Permite que você crie mensagens 
 de erro customizadas que interrompem o hacker ou o erro humano.
 
 2. CHECK (email LIKE '%@%'): 
 - Garante que a integridade do dado comece na fonte. Se o dado 
 não presta, ele nem entra no HD.
 
 3. IMUTABILIDADE:
 - Ao bloquear UPDATE e DELETE via Triggers, você cria uma 
 tabela de "Somente Inserção", ideal para logs financeiros, 
 médicos ou de segurança.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende que o banco de dados não é uma vítima passiva das 
 aplicações, mas sim um agente ativo de segurança e conformidade.
 ===============================================================
 */
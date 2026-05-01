/**
 * @file atividade-38-seguranca.sql
 * @brief Implementação/Componente atividade-38-seguranca.sql
 * @author Cristiano
 * @date 2026
 */
-- ##############################################################################
-- # ATIVIDADE 38: SEGURANÇA E AUDITORIA FORENSE (VERSÃO FINAL BLINDADA)
-- ##############################################################################

.open logispeed_blindado.db

-- 1. Estrutura
CREATE TABLE IF NOT EXISTS telemetria_global (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    velocidade REAL,
    status TEXT DEFAULT 'ATIVO'
);

CREATE TABLE IF NOT EXISTS cofre_auditoria (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    detalhes TEXT,
    data_auditoria DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- 2. TRIGGER DE ELITE: Simulando Deleção Lógica + Auditoria
-- Em vez de apagar, o sistema marca como 'DELETADO' e audita.
CREATE TRIGGER IF NOT EXISTS trg_auditoria_imutavel
BEFORE DELETE ON telemetria_global
BEGIN
    -- 1. Salva a evidência (Isso persistirá se não usarmos RAISE ABORT)
    INSERT INTO cofre_auditoria (detalhes) 
    VALUES ('TENTATIVA DE DELEÇÃO ID:' || OLD.id || ' VEL:' || OLD.velocidade);
    
    -- 2. Realiza a "Deleção Lógica" em vez da física
    UPDATE telemetria_global SET status = 'BLOQUEADO/AUDITADO' WHERE id = OLD.id;
    
    -- 3. Aborta a deleção física mas SEM reverter a transação de log (usando IGNORE)
    SELECT RAISE(IGNORE);
END;

-- 3. Teste
INSERT INTO telemetria_global (velocidade) VALUES (110.5); -- Excesso

.print "\n\x1b[1;31m[ATAQUE]\x1b[0m Tentando apagar evidência..."
DELETE FROM telemetria_global WHERE velocidade > 100;

.print "\n\x1b[1;32m[RESULTADO]\x1b[0m Verificando se o dado original ainda existe (como BLOQUEADO):"
SELECT * FROM telemetria_global;

.print "\n\x1b[1;32m[COFRE]\x1b[0m Verificando o rastro de auditoria:"
SELECT * FROM cofre_auditoria;

/* @section ExecutionPlan
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

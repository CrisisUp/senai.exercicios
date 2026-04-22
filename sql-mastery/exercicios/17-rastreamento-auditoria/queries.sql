-- ==============================================================================
-- ATIVIDADE 17: RASTREAMENTO DE AUDITORIA (AUDIT TRAIL)
-- OBJETIVO: Implementar uma "Caixa Preta" para mudanças no banco de dados.
-- ==============================================================================
-- 1. Setup das Tabelas
CREATE TABLE IF NOT EXISTS configuracao_drones (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    serial TEXT UNIQUE NOT NULL,
    firmware_versao TEXT NOT NULL
);
-- Tabela de Auditoria (Shadow Table)
CREATE TABLE IF NOT EXISTS auditoria_logs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    tabela_nome TEXT,
    registro_id INTEGER,
    coluna TEXT,
    valor_antigo TEXT,
    valor_novo TEXT,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP
);
DELETE FROM configuracao_drones;
DELETE FROM auditoria_logs;
-- 2. CRIAÇÃO DO GATILHO DE AUDITORIA (UPDATE)
-- Este gatilho verifica se a versão do firmware mudou e loga os dois estados.
CREATE TRIGGER IF NOT EXISTS trg_auditoria_firmware
AFTER
UPDATE OF firmware_versao ON configuracao_drones FOR EACH ROW BEGIN
INSERT INTO auditoria_logs (
        tabela_nome,
        registro_id,
        coluna,
        valor_antigo,
        valor_novo
    )
VALUES (
        'configuracao_drones',
        OLD.id,
        'firmware_versao',
        OLD.firmware_versao,
        NEW.firmware_versao
    );
END;
-- 3. TESTE DE AUDITORIA
-- A: Inserindo drone inicial
INSERT INTO configuracao_drones (serial, firmware_versao)
VALUES ('SN-ALPHA', 'v1.0.0');
-- B: Realizando um Update (Simulando uma atualização de sistema)
UPDATE configuracao_drones
SET firmware_versao = 'v1.2.5'
WHERE serial = 'SN-ALPHA';
-- 4. CONSULTA DE AUDITORIA
-- O resultado mostrará a "história" da mudança sem que tenhamos feito o log manual.
SELECT *
FROM auditoria_logs;
/* 
 ===============================================================
 RESUMO TEÓRICO: AUDIT TRAILS (GOVERNANÇA)
 ===============================================================
 
 1. TRANSPARÊNCIA: 
 - Triggers de auditoria garantem que nenhuma mudança seja 
 "silenciosa". Isso é requisito legal em muitos setores.
 
 2. OLD vs NEW: 
 - OLD.coluna: O valor que o banco ia apagar.
 - NEW.coluna: O valor que o banco acabou de escrever.
 
 3. MANUTENÇÃO:
 - Você pode criar gatilhos para DELETE também, capturando 
 os dados antes que eles sumam para sempre.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende que o banco de dados pode ser auto-explicativo 
 e que o histórico é tão valioso quanto o estado atual.
 ===============================================================
 */
-- ==============================================================================
-- DESAFIO FINAL SA-08: O GUARDIÃO DE MISSÕES CRÍTICAS (CORRIGIDO)
-- OBJETIVO: Sistema de Segurança, Câmbio e Resiliência Operacional.
-- ==============================================================================
PRAGMA foreign_keys = ON;
-- 1. MÓDULO DE SEGURANÇA E AUDITORIA
CREATE TABLE IF NOT EXISTS acessos_audit (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    usuario TEXT,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP,
    latencia_ms REAL
);
CREATE TABLE IF NOT EXISTS alertas_seguranca (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    tipo TEXT,
    mensagem TEXT,
    data_alerta TEXT DEFAULT CURRENT_TIMESTAMP
);
-- Trigger Sentinela Corrigido
CREATE TRIGGER IF NOT EXISTS trg_radar_operacional
AFTER
INSERT ON acessos_audit BEGIN -- A: Alerta de Lentidão
INSERT INTO alertas_seguranca (tipo, mensagem)
SELECT 'SRE_LATENCIA',
    'ALERTA: Operação lenta (' || NEW.latencia_ms || ' ms)'
WHERE NEW.latencia_ms > 500.0;
-- B: Alerta de Brute Force
INSERT INTO alertas_seguranca (tipo, mensagem)
SELECT 'CIBER_ATAQUE',
    'ALERTA: Brute Force detectado para: ' || NEW.usuario
FROM (
        SELECT data_hora
        FROM acessos_audit
        WHERE usuario = NEW.usuario
            AND id < NEW.id
        ORDER BY id DESC
        LIMIT 1
    ) AS anterior
WHERE (
        unixepoch(NEW.data_hora) - unixepoch(anterior.data_hora)
    ) < 2;
END;
-- 2. MÓDULO DE FATURAMENTO GLOBAL
CREATE TABLE IF NOT EXISTS cambio (moeda TEXT PRIMARY KEY, taxa_brl REAL);
INSERT
    OR REPLACE INTO cambio
VALUES ('USD', 5.50),
    ('EUR', 6.00),
    ('BRL', 1.00);
-- 3. MÓDULO DE RESILIÊNCIA
CREATE TABLE IF NOT EXISTS manutencao_critica (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_serial TEXT,
    etapa TEXT,
    status TEXT
);
-- 4. SIMULAÇÃO E TESTE
-- Inserindo logs rápidos
INSERT INTO acessos_audit (usuario, data_hora, latencia_ms)
VALUES ('Hacker_Bot', '2026-04-21 12:00:00', 10.0);
INSERT INTO acessos_audit (usuario, data_hora, latencia_ms)
VALUES ('Hacker_Bot', '2026-04-21 12:00:01', 800.0);
-- Simulação de Manutenção
BEGIN TRANSACTION;
INSERT INTO manutencao_critica (drone_serial, etapa, status)
VALUES ('X10', '1. Hardware', 'OK');
SAVEPOINT sp1;
INSERT INTO manutencao_critica (drone_serial, etapa, status)
VALUES ('X10', '2. Software', 'FALHA');
ROLLBACK TO sp1;
INSERT INTO manutencao_critica (drone_serial, etapa, status)
VALUES ('X10', '2. Software (Re-tentativa)', 'OK');
COMMIT;
-- 5. RELATÓRIO FINAL
SELECT *
FROM alertas_seguranca;
SELECT *
FROM manutencao_critica;
-- ==============================================================================
-- ATIVIDADE 23: RESOLUÇÃO DE CONFLITOS (INSERT OR...)
-- OBJETIVO: Gerenciar colisões de dados e violações de regras.
-- ==============================================================================
-- 1. Setup da Tabela
CREATE TABLE IF NOT EXISTS frota_internacional (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  serial TEXT UNIQUE NOT NULL,
  horas_voo REAL CHECK (horas_voo >= 0)
);
DELETE FROM frota_internacional;
-- Inserindo dado inicial (O drone original)
INSERT INTO frota_internacional (serial, horas_voo)
VALUES ('DRONE-GLOBAL-01', 50.0);
-- 2. TESTE: INSERT OR IGNORE
-- Se o serial já existe, o banco apenas ignora e não dá erro.
-- O valor continuará sendo 50.0 (o antigo).
INSERT
  OR IGNORE INTO frota_internacional (serial, horas_voo)
VALUES ('DRONE-GLOBAL-01', 999.0);
-- 3. TESTE: INSERT OR REPLACE
-- Se o serial já existe, o banco apaga a linha antiga e insere a nova.
-- O valor mudará para 75.0 (o novo). Note que o ID pode mudar!
INSERT
  OR REPLACE INTO frota_internacional (serial, horas_voo)
VALUES ('DRONE-GLOBAL-01', 75.0);
-- 4. TESTE: ERRO DE REGRA (CHECK)
-- Tentando inserir valor inválido. O banco barrou?
-- Usamos ABORT (padrão) para parar o comando.
-- INSERT OR ABORT INTO frota_internacional (serial, horas_voo) VALUES ('DRONE-ERRO', -10.0);
-- 5. CONSULTA DE PROVA
SELECT *
FROM frota_internacional;
/* 
 ===============================================================
 RESUMO TEÓRICO: POLÍTICAS DE CONFLITO
 ===============================================================
 
 1. REPLACE: 
 - Funciona como um "Super Update". 
 - Perigo: Se houver Chaves Estrangeiras ligadas ao ID, elas 
 podem ser afetadas (CASCADE) porque o REPLACE deleta a 
 linha antes de inserir a nova.
 
 2. IGNORE: 
 - Ideal para sincronização "Burra": você joga todos os dados 
 e o banco só aceita o que for novo, sem reclamar dos velhos.
 
 3. ABORT vs ROLLBACK:
 - ABORT: Para o comando atual, mas mantém o que comandos 
 anteriores da mesma transação fizeram.
 - ROLLBACK: Para tudo e desfaz toda a transação desde o BEGIN.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende a lidar com "Fluxos de Erro" de forma elegante, 
 sem precisar de IFs complexos na linguagem de programação.
 ===============================================================
 */
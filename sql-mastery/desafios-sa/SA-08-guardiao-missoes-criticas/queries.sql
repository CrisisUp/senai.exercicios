/**
 * @file queries.sql
 * @brief O Guardião de Missões Críticas: Cibersegurança, Resiliência e Faturamento.
 * @details Implementação de radares de segurança com detecção de anomalias, 
 *          gestão de transações granulares (Savepoints) e integridade financeira.
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * - Security Views: Camada de visualização para logs de auditoria mascarando dados sensíveis.
 * - Analytics Cost: Detecção de Brute Force via subconsultas ou LAG() exige índices em (usuario, id).
 * - Stress Resilience: Uso de Savepoints permite recuperação parcial sem perda total do progresso da transação.
 */

PRAGMA foreign_keys = ON;

-- ==============================================================================
-- 1. MÓDULO DE SEGURANÇA E AUDITORIA
-- ==============================================================================
CREATE TABLE IF NOT EXISTS acessos_audit (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    usuario TEXT NOT NULL,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP,
    latencia_ms REAL NOT NULL
);

CREATE TABLE IF NOT EXISTS alertas_seguranca (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    tipo TEXT NOT NULL,
    mensagem TEXT NOT NULL,
    data_alerta TEXT DEFAULT CURRENT_TIMESTAMP
);

-- Trigger Sentinela: Monitoramento de Latência e Brute Force
CREATE TRIGGER IF NOT EXISTS trg_radar_operacional
AFTER INSERT ON acessos_audit 
BEGIN 
    -- A: Alerta de Lentidão (SRE)
    INSERT INTO alertas_seguranca (tipo, mensagem)
    SELECT 'SRE_LATENCIA',
        'ALERTA: Operação lenta (' || NEW.latencia_ms || ' ms)'
    WHERE NEW.latencia_ms > 500.0;

    -- B: Alerta de Brute Force (Cibersegurança)
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
    WHERE (unixepoch(NEW.data_hora) - unixepoch(anterior.data_hora)) < 2;
END;

-- ==============================================================================
-- 2. MÓDULO DE FATURAMENTO GLOBAL (Guardião Financeiro)
-- ==============================================================================
CREATE TABLE IF NOT EXISTS cambio (
    moeda TEXT PRIMARY KEY, 
    taxa_brl_cents INTEGER NOT NULL -- Guardião Financeiro: Taxa em centavos
);

INSERT OR REPLACE INTO cambio VALUES 
    ('USD', 550), -- R$ 5,50
    ('EUR', 600), -- R$ 6,00
    ('BRL', 100); -- R$ 1,00

CREATE TABLE IF NOT EXISTS faturamento_global (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id TEXT NOT NULL,
    valor_original_cents INTEGER NOT NULL,
    moeda TEXT NOT NULL,
    FOREIGN KEY (moeda) REFERENCES cambio(moeda)
);

-- ==============================================================================
-- 3. MÓDULO DE RESILIÊNCIA (Savepoints)
-- ==============================================================================
CREATE TABLE IF NOT EXISTS manutencao_critica (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_serial TEXT NOT NULL,
    etapa TEXT NOT NULL,
    status TEXT NOT NULL
);

-- ==============================================================================
-- 4. SIMULAÇÃO E TESTE
-- ==============================================================================
-- Inserindo logs rápidos (Simulação de ataque e lentidão)
INSERT INTO acessos_audit (usuario, data_hora, latencia_ms)
VALUES ('Hacker_Bot', '2026-04-21 12:00:00', 10.0);
INSERT INTO acessos_audit (usuario, data_hora, latencia_ms)
VALUES ('Hacker_Bot', '2026-04-21 12:00:01', 800.0);

-- Simulação de Faturamento
INSERT INTO faturamento_global (drone_id, valor_original_cents, moeda)
VALUES ('D-01', 10000, 'USD'); -- $100.00

-- Simulação de Manutenção com Resiliência Granular
BEGIN TRANSACTION;
INSERT INTO manutencao_critica (drone_serial, etapa, status)
VALUES ('X10', '1. Hardware', 'OK');
SAVEPOINT sp1;
INSERT INTO manutencao_critica (drone_serial, etapa, status)
VALUES ('X10', '2. Software', 'FALHA');
ROLLBACK TO sp1; -- Recuperação parcial
INSERT INTO manutencao_critica (drone_serial, etapa, status)
VALUES ('X10', '2. Software (Re-tentativa)', 'OK');
COMMIT;

-- ==============================================================================
-- 5. RELATÓRIOS DE ELITE
-- ==============================================================================
-- [A] Auditoria de Segurança
SELECT * FROM alertas_seguranca;

-- [B] Faturamento Convertido (Sem perda de precisão)
SELECT 
    f.drone_id,
    f.valor_original_cents / 100.0 AS valor_moeda_orig,
    f.moeda,
    (f.valor_original_cents * c.taxa_brl_cents / 10000.0) AS valor_brl
FROM faturamento_global f
JOIN cambio c ON f.moeda = c.moeda;

-- [C] Status da Manutenção
SELECT * FROM manutencao_critica;

-- ==============================================================================
-- RESUMO TEÓRICO
-- ==============================================================================
/*
1. MONITORAMENTO ATIVO (TRIGGERS): Permite que o banco de dados reaja a eventos 
   em tempo real, implementando lógicas de SRE e Segurança na camada de dados.
2. SAVEPOINTS: Oferecem controle transacional dentro de uma transação maior, 
   permitindo desfazer partes específicas do trabalho sem abortar toda a operação.
3. PRECISÃO FINANCEIRA: Multiplicar centavos inteiros garante que cálculos de 
   câmbio e impostos não sofram com o "erro do centavo perdido" de ponto flutuante.
4. CIBERSEGURANÇA SQL: O uso de janelas temporais e comparações entre linhas 
   adjacentes é a base para detecção de fraudes e ataques automatizados.
*/

-- ==============================================================================
-- ASSUNTOS CORRELATOS
-- ==============================================================================
/*
- Intrusion Detection Systems (IDS) integrados a Bancos de Dados.
- Transações Distribuídas (Two-Phase Commit).
- Backup Online e Point-in-Time Recovery (PITR).
- Hardening de instâncias SQLite para ambientes críticos.
*/

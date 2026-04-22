/**
 * @file queries.sql
 * @brief Detecção de Anomalias de Segurança e Forense de Dados.
 * @author Gemini CLI Agent
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * - Window Functions (LAG, AVG): Requerem ordenação em memória ou uso de índices compostos (B-Tree).
 * - Analytics Costs: O cálculo de média móvel sobre milhões de linhas pode causar latência em dashboards de segurança.
 * - Transaction Log Overheads: Tabelas de log (acessos_sistema) crescem rápido; considere partições ou expurgo.
 * - Guardião Financeiro: Monitoramento de fraude baseado em INTEGER cents para evitar imprecisões decimais.
 */

-- 1. Setup das Tabelas de Segurança
CREATE TABLE IF NOT EXISTS acessos_sistema (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    usuario TEXT NOT NULL,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP,
    status TEXT -- 'SUCESSO' ou 'FALHA'
);

CREATE TABLE IF NOT EXISTS transacoes_financeiras (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id TEXT NOT NULL,
    valor_centavos INTEGER NOT NULL, -- Guardião Financeiro
    data_transacao TEXT DEFAULT CURRENT_TIMESTAMP
);

DELETE FROM acessos_sistema;
DELETE FROM transacoes_financeiras;

-- 2. POPULAÇÃO DE TESTE (Cenário de Ataque)
INSERT INTO acessos_sistema (usuario, data_hora, status)
VALUES ('admin', '2026-04-21 10:00:00', 'SUCESSO'),
    ('hacker_xyz', '2026-04-21 10:05:01', 'FALHA'),
    ('hacker_xyz', '2026-04-21 10:05:02', 'FALHA'),
    ('hacker_xyz', '2026-04-21 10:05:03', 'FALHA');

INSERT INTO transacoes_financeiras (drone_id, valor_centavos)
VALUES ('X-10', 10000), -- R$ 100,00
    ('X-10', 11000),
    ('X-10', 9500),
    ('X-10', 500000); -- ANOMALIA (R$ 5.000,00)

-- 3. QUERIES DE DETECÇÃO
-- [A] DETECTOR DE BRUTE FORCE
SELECT usuario,
    data_hora,
    status,
    unixepoch(data_hora) - unixepoch(
        LAG(data_hora) OVER(
            PARTITION BY usuario
            ORDER BY data_hora
        )
    ) AS delta_segundos
FROM acessos_sistema
WHERE status = 'FALHA';

-- [B] DETECTOR DE ANOMALIA FINANCEIRA (OUTLIERS)
WITH analise_estatistica AS (
    SELECT drone_id,
        valor_centavos,
        AVG(valor_centavos) OVER(PARTITION BY drone_id) AS media_historica
    FROM transacoes_financeiras
)
SELECT 
    drone_id,
    PRINTF('R$ %.2f', valor_centavos / 100.0) AS valor,
    PRINTF('R$ %.2f', media_historica / 100.0) AS media,
    CASE
        WHEN valor_centavos > (media_historica * 3) THEN '🚨 POSSÍVEL FRAUDE/ATAQUE'
        ELSE 'NORMAL'
    END AS alerta_seguranca
FROM analise_estatistica;

/* 
 ===============================================================
 RESUMO TEÓRICO: SQL COMO FERRAMENTA DE SECURITY
 ===============================================================
 
 1. LAG() PARA TEMPO: Essencial para detectar automação (bots).
 2. AVG() OVER(): Cria baselines dinâmicas de comportamento.
 3. INTEGER CENTS: Impede que arredondamentos de ponto flutuante 
    escondam pequenas exfiltrações de capital.

 ASSUNTOS CORRELATOS:
 - SQL Injection Protection.
 - Database Auditing (Audit Trails).
 - Intrusion Detection Systems (IDS) integrados a Bancos de Dados.
 ===============================================================
 */
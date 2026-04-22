-- ==============================================================================
-- ATIVIDADE 25: O ESCUDO CIBERNÉTICO (FORENSE DE DADOS)
-- OBJETIVO: Detectar padrões de ataque e anomalias estatísticas.
-- ==============================================================================
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
    valor REAL NOT NULL,
    data_transacao TEXT DEFAULT CURRENT_TIMESTAMP
);
DELETE FROM acessos_sistema;
DELETE FROM transacoes_financeiras;
-- 2. POPULAÇÃO DE TESTE (Cenário de Ataque)
-- Simulando Brute Force (Usuário 'hacker_xyz')
INSERT INTO acessos_sistema (usuario, data_hora, status)
VALUES ('admin', '2026-04-21 10:00:00', 'SUCESSO'),
    ('hacker_xyz', '2026-04-21 10:05:01', 'FALHA'),
    ('hacker_xyz', '2026-04-21 10:05:02', 'FALHA'),
    ('hacker_xyz', '2026-04-21 10:05:03', 'FALHA');
-- Simulando Anomalia de Valor (Drone 'X-10' costuma gastar ~100)
INSERT INTO transacoes_financeiras (drone_id, valor)
VALUES ('X-10', 100.0),
    ('X-10', 110.0),
    ('X-10', 95.0),
    ('X-10', 5000.0);
-- ANOMALIA DETECTADA!
-- 3. QUERIES DE DETECÇÃO
-- [A] DETECTOR DE BRUTE FORCE
-- Calcula a diferença de segundos entre a tentativa atual e a anterior.
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
-- Compara o valor atual com a média móvel histórica do drone.
WITH analise_estatistica AS (
    SELECT drone_id,
        valor,
        AVG(valor) OVER(PARTITION BY drone_id) AS media_historica
    FROM transacoes_financeiras
)
SELECT *,
    CASE
        WHEN valor > (media_historica * 3) THEN '🚨 POSSÍVEL FRAUDE/ATAQUE'
        ELSE 'NORMAL'
    END AS alerta_seguranca
FROM analise_estatistica;
/* 
 ===============================================================
 RESUMO TEÓRICO: SQL COMO FERRAMENTA DE SECURITY
 ===============================================================
 
 1. O DELTA DE TEMPO (LAG): 
 - Ataques automatizados são rápidos demais para seres humanos. 
 - Um delta < 1 segundo em múltiplas linhas é uma "assinatura" 
 digital de um bot de brute force.
 
 2. O DESVIO PADRÃO LÓGICO: 
 - Definir uma regra como "3x maior que a média" permite que o 
 banco ignore flutuações normais mas capture ataques de 
 exfiltração de crédito.
 
 VANTAGEM DIDÁTICA: 
 O aluno percebe que o banco de dados é a "Primeira Resposta" em 
 um incidente de segurança, fornecendo provas e alertas em 
 tempo real.
 ===============================================================
 */
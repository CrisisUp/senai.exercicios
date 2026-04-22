-- ==============================================================================
-- ATIVIDADE 27: SENTINELA DE PERFORMANCE
-- OBJETIVO: Automatizar a detecção de lentidão no banco de dados.
-- ==============================================================================
-- 1. Setup das Tabelas de Monitoramento
CREATE TABLE IF NOT EXISTS operacoes_rastreio (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    operacao_nome TEXT NOT NULL,
    tempo_ms REAL NOT NULL,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP
);
CREATE TABLE IF NOT EXISTS incidentes_performance (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    operacao_nome TEXT,
    latencia_ms REAL,
    criticidade TEXT,
    data_alerta TEXT DEFAULT CURRENT_TIMESTAMP
);
DELETE FROM operacoes_rastreio;
DELETE FROM incidentes_performance;
-- 2. CRIAÇÃO DO GATILHO SENTINELA (Trigger de Performance)
-- Este gatilho observa cada registro de tempo e decide se gera um alerta.
CREATE TRIGGER IF NOT EXISTS trg_analisador_latencia
AFTER
INSERT ON operacoes_rastreio BEGIN -- Alerta de Criticidade ALTA (> 500ms)
INSERT INTO incidentes_performance (operacao_nome, latencia_ms, criticidade)
SELECT NEW.operacao_nome,
    NEW.tempo_ms,
    'ALTA (SRE Necessário)'
WHERE NEW.tempo_ms > 500.0;
-- Alerta de Criticidade MÉDIA (200ms - 500ms)
INSERT INTO incidentes_performance (operacao_nome, latencia_ms, criticidade)
SELECT NEW.operacao_nome,
    NEW.tempo_ms,
    'MÉDIA (Observar)'
WHERE NEW.tempo_ms > 200.0
    AND NEW.tempo_ms <= 500.0;
END;
-- 3. TESTE DE MONITORAMENTO (Simulação de Carga)
-- Operação Rápida (Normal)
INSERT INTO operacoes_rastreio (operacao_nome, tempo_ms)
VALUES ('Busca GPS Drone X1', 15.2);
-- Operação Lenta (Alerta Médio)
INSERT INTO operacoes_rastreio (operacao_nome, tempo_ms)
VALUES ('Relatório Trimestral Vendas', 350.0);
-- Operação Crítica (Alerta Alto)
INSERT INTO operacoes_rastreio (operacao_nome, tempo_ms)
VALUES ('Backup em Nuvem Externo', 1200.0);
-- 4. CONSULTA DOS INCIDENTES
-- O banco detectou e moveu os problemas para a tabela de incidentes sozinho!
SELECT *
FROM incidentes_performance;
/* 
 ===============================================================
 RESUMO TEÓRICO: OBSERVABILIDADE NO SQL
 ===============================================================
 
 1. O BANCO COMO MONITOR: 
 - Ao invés de esperar a aplicação travar, o banco registra sua 
 própria latência e gera evidências.
 
 2. GATILHOS CONDICIONAIS: 
 - Usamos o 'INSERT INTO ... SELECT ... WHERE' dentro do Trigger 
 para criar uma lógica de "Se... Então" complexa.
 
 3. SRE (Site Reliability Engineering):
 - É a disciplina de garantir que sistemas fiquem online. 
 - Ter uma tabela de incidentes no banco facilita a criação de 
 dashboards no Grafana ou ferramentas de alerta (Slack/Email).
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende que performance não é apenas "rodar rápido", mas 
 sim "medir e avisar quando não está rodando rápido".
 ===============================================================
 */
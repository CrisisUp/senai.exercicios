/**
 * @file queries.sql
 * @brief Monitoramento de performance e sentinela de latência com lógica financeira.
 * @author SENAI C++ Engenheiro de Elite
 * @date 2026-04-19
 */

-- ==============================================================================
-- 1. SETUP DO SENTINELA (Monitoramento e Alertas)
-- ==============================================================================

-- Tabela de Rastreio: Onde cada operação registra seu tempo de execução.
CREATE TABLE IF NOT EXISTS operacoes_rastreio (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    operacao_nome TEXT NOT NULL,
    tempo_ms REAL NOT NULL,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP
);

-- Tabela de Incidentes: Onde o banco "grita" se algo estiver lento.
CREATE TABLE IF NOT EXISTS incidentes_performance (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    operacao_nome TEXT,
    latencia_ms REAL,
    criticidade TEXT,
    data_alerta TEXT DEFAULT CURRENT_TIMESTAMP
);

-- Guardião Financeiro: Integridade bancária com centavos inteiros.
-- Toda operação financeira deve ser rastreada por performance.
CREATE TABLE IF NOT EXISTS transacoes_financeiras (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    cliente_id INTEGER,
    valor_cents INTEGER, -- Integridade: Guardião Financeiro
    tipo TEXT CHECK(tipo IN ('DEBITO', 'CREDITO'))
);

DELETE FROM operacoes_rastreio;
DELETE FROM incidentes_performance;
DELETE FROM transacoes_financeiras;

-- ==============================================================================
-- 2. CRIAÇÃO DO GATILHO SENTINELA (Trigger de Performance)
-- ==============================================================================

CREATE TRIGGER IF NOT EXISTS trg_analisador_latencia
AFTER INSERT ON operacoes_rastreio 
BEGIN 
    -- Alerta de Criticidade ALTA (> 500ms)
    INSERT INTO incidentes_performance (operacao_nome, latencia_ms, criticidade)
    SELECT NEW.operacao_nome, NEW.tempo_ms, 'ALTA (SRE Necessário)'
    WHERE NEW.tempo_ms > 500.0;

    -- Alerta de Criticidade MÉDIA (200ms - 500ms)
    INSERT INTO incidentes_performance (operacao_nome, latencia_ms, criticidade)
    SELECT NEW.operacao_nome, NEW.tempo_ms, 'MÉDIA (Observar)'
    WHERE NEW.tempo_ms > 200.0 AND NEW.tempo_ms <= 500.0;
END;

-- ==============================================================================
-- 3. TESTE DE MONITORAMENTO (Simulação de Carga e Integridade)
-- ==============================================================================

-- Simulação de Transação Financeira (Guardião Financeiro)
INSERT INTO transacoes_financeiras (cliente_id, valor_cents, tipo)
VALUES (101, 150050, 'CREDITO'); -- R$ 1.500,50

-- Registro de Performance desta Transação (Simulação de sucesso rápido)
INSERT INTO operacoes_rastreio (operacao_nome, tempo_ms)
VALUES ('Processamento Pix R$ 1500,50', 15.2);

-- Simulação de Operação Lenta (Alerta Médio)
INSERT INTO operacoes_rastreio (operacao_nome, tempo_ms)
VALUES ('Relatório Trimestral Vendas', 350.0);

-- Simulação de Operação Crítica (Alerta Alto)
INSERT INTO operacoes_rastreio (operacao_nome, tempo_ms)
VALUES ('Backup em Nuvem Externo', 1200.0);

-- ==============================================================================
-- 4. @section ExecutionPlan (Monitoramento de I/O e Overheads)
-- ==============================================================================
-- O plano de execução para monitoramento deve garantir que o rastreio não 
-- se torne o próprio gargalo.
EXPLAIN QUERY PLAN
SELECT * FROM incidentes_performance WHERE criticidade = 'ALTA (SRE Necessário)';

-- Consulta dos Incidentes Gerados Automaticamente
SELECT * FROM incidentes_performance;

/* 
 ==============================================================================
 RESUMO TEÓRICO: OBSERVABILIDADE E SENTINELAS
 ==============================================================================
 
 1. O BANCO COMO MONITOR: 
 - O banco registra sua própria latência e gera evidências (logs de incidentes) 
 sem depender exclusivamente da camada de aplicação.
 
 2. GUARDIÃO FINANCEIRO (INTEGER Cents): 
 - Para evitar erros de arredondamento de ponto flutuante (IEEE 754), 
 armazenamos valores monetários como números inteiros em centavos.
 
 3. SOBRECARGA DE ESCRITA (I/O Cost):
 - Cada trigger adiciona uma micro-latência à operação original. 
 Em sistemas de altíssimo tráfego, o monitoramento deve ser amostral ou assíncrono.

 ==============================================================================
 ASSUNTOS CORRELATOS:
 - SRE (Site Reliability Engineering) e SLIs/SLOs de banco de dados.
 - Observabilidade Distribuída (Tracing e OpenTelemetry).
 - Políticas de Retenção de Dados (Data TTL) para evitar Heap Bloat.
 - Monitoramento de IOPS e Latência de Disco a nível de Sistema Operacional.
 ==============================================================================
 */

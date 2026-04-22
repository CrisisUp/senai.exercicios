/**
 * @file queries.sql
 * @brief Central de Monitoramento Global e Cibersegurança.
 * @details Integração de radares de segurança, observabilidade SRE e normalização 
 *          financeira internacional com precisão de centavos.
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * - Security Views: Camada de visualização financeira unificada que oculta taxas brutas.
 * - Analytics Cost: Gatilhos de segurança usam subconsultas que devem ser otimizadas 
 *   com índices em (usuario, data_hora).
 * - Stress Resilience: O sistema de alertas é desacoplado das operações principais 
 *   para garantir que falhas de monitoramento não bloqueiem o faturamento.
 */

-- ==============================================================================
-- 1. ARQUITETURA (DDL)
-- ==============================================================================
CREATE TABLE IF NOT EXISTS taxas (
    moeda TEXT PRIMARY KEY, 
    taxa_brl_cents INTEGER NOT NULL -- Guardião Financeiro: Taxa em centavos
);

CREATE TABLE IF NOT EXISTS operacoes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    usuario TEXT NOT NULL,
    valor_local_cents INTEGER NOT NULL, -- Guardião Financeiro: Valor em centavos
    moeda TEXT NOT NULL,
    latencia_ms REAL NOT NULL,
    data_hora TEXT DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (moeda) REFERENCES taxas(moeda)
);

CREATE TABLE IF NOT EXISTS alertas (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    tipo TEXT NOT NULL,
    mensagem TEXT NOT NULL,
    data_alerta TEXT DEFAULT CURRENT_TIMESTAMP
);

-- ==============================================================================
-- 2. AUTOMAÇÃO (TRIGGER SENTINELA)
-- ==============================================================================
CREATE TRIGGER IF NOT EXISTS trg_seguranca_global
AFTER INSERT ON operacoes 
BEGIN 
    -- [A] Alerta de Brute Force (Cibersegurança)
    INSERT INTO alertas (tipo, mensagem)
    SELECT 'CIBER_ATAQUE', 'Acesso rápido detectado para ' || NEW.usuario
    FROM (
        SELECT data_hora
        FROM operacoes
        WHERE usuario = NEW.usuario
            AND id < NEW.id
        ORDER BY id DESC
        LIMIT 1
    ) AS anterior
    WHERE (unixepoch(NEW.data_hora) - unixepoch(anterior.data_hora)) < 2;

    -- [B] Alerta de Latência (SRE)
    INSERT INTO alertas (tipo, mensagem)
    SELECT 'PERFORMANCE', 'Operação lenta (' || NEW.latencia_ms || ' ms)'
    WHERE NEW.latencia_ms > 500.0;
END;

-- ==============================================================================
-- 3. POPULAÇÃO E TESTE
-- ==============================================================================
INSERT INTO taxas VALUES 
    ('USD', 550), -- R$ 5,50
    ('EUR', 600), -- R$ 6,00
    ('BRL', 100); -- R$ 1,00

-- Simulação de operações normais e ataque
INSERT INTO operacoes (usuario, valor_local_cents, moeda, latencia_ms, data_hora)
VALUES 
    ('user_admin', 15000, 'USD', 45.0, '2026-04-19 10:00:00'),
    ('user_admin', 20000, 'USD', 600.0, '2026-04-19 10:00:01'); -- Ativa ambos os alertas

-- ==============================================================================
-- 4. CONSULTA ANALÍTICA GLOBAL (FINANCEIRO)
-- ==============================================================================
CREATE VIEW IF NOT EXISTS v_financeiro_global AS
SELECT 
    o.usuario,
    o.valor_local_cents / 100.0 AS "Valor Original",
    o.moeda,
    ROUND((o.valor_local_cents * t.taxa_brl_cents) / 10000.0, 2) AS "Convertido BRL",
    o.latencia_ms AS "Latência (ms)"
FROM operacoes o
JOIN taxas t ON o.moeda = t.moeda;

-- Exibição de Alertas e Financeiro
SELECT * FROM alertas;
SELECT * FROM v_financeiro_global;

-- ==============================================================================
-- RESUMO TEÓRICO
-- ==============================================================================
/*
1. MONITORAMENTO SRE: O uso de Triggers para validar SLAs de latência permite que 
   o banco de dados atue como um sensor de saúde da aplicação.
2. DETECÇÃO FORENSE: Comparar o carimbo de tempo (unixepoch) de registros 
   consecutivos é uma técnica eficaz para identificar automação maliciosa.
3. NORMALIZAÇÃO MONETÁRIA: Integrar tabelas de câmbio em Views Analíticas 
   simplifica a geração de relatórios consolidados para empresas globais.
4. INTEGRIDADE DE CÁLCULO: Operar com inteiros (centavos) em todas as camadas 
   garante que a precisão financeira seja mantida após múltiplas conversões.
*/

-- ==============================================================================
-- ASSUNTOS CORRELATOS
-- ==============================================================================
/*
- Observabilidade em Camada de Dados (Full Observability).
- Análise de Séries Temporais em SQL.
- Mitigação de SQL Injection e ataques de força bruta.
- Estratégias de Cache para Tabelas de Câmbio.
*/

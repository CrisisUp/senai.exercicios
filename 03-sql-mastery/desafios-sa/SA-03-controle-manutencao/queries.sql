/**
 * @file queries.sql
 * @brief Sistema de Manutenção Preventiva - SA-03
 * @author Gemini CLI Agent
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * O plano de execução prioriza a automação via Triggers e a eficiência em relatórios analíticos via CTEs.
 * - Uso de INDEX em log_voos(drone_id) para otimizar o histórico de performance.
 * - Gatilho pós-inserção para atualização em cascata de horímetros e alertas.
 * - CTE (Common Table Expressions) para cálculos comparativos complexos de frota.
 * - Estratégia "Guardião Financeiro": Faturamento por voo armazenado como INTEGER (centavos).
 */

-- ==============================================================================
-- 1. ARQUITETURA DO SISTEMA (DDL)
-- ==============================================================================
PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS frota_drones (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    modelo TEXT NOT NULL,
    horas_totais REAL DEFAULT 0.0,
    faturamento_acumulado_centavos INTEGER DEFAULT 0 -- Guardião Financeiro
);

CREATE TABLE IF NOT EXISTS log_voos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id INTEGER,
    horas_viagem REAL NOT NULL,
    faturamento_viagem_centavos INTEGER NOT NULL, -- Guardião Financeiro (ex: R$ 100,00 por hora)
    data_voo TEXT DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (drone_id) REFERENCES frota_drones(id)
);

CREATE TABLE IF NOT EXISTS alertas_manutencao (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id INTEGER,
    mensagem TEXT,
    data_alerta TEXT DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (drone_id) REFERENCES frota_drones(id)
);

-- Otimização de busca no histórico
CREATE INDEX IF NOT EXISTS idx_log_drone ON log_voos(drone_id);

-- Limpando dados para o desafio
DELETE FROM alertas_manutencao;
DELETE FROM log_voos;
DELETE FROM frota_drones;

-- ==============================================================================
-- 2. AUTOMAÇÃO (TRIGGERS)
-- ==============================================================================
-- Gatilho para atualizar o horímetro, faturamento e disparar alerta de revisão
CREATE TRIGGER IF NOT EXISTS trg_pos_voo
AFTER INSERT ON log_voos 
BEGIN 
    -- A: Atualiza o horímetro e o faturamento do drone
    UPDATE frota_drones
    SET horas_totais = horas_totais + NEW.horas_viagem,
        faturamento_acumulado_centavos = faturamento_acumulado_centavos + NEW.faturamento_viagem_centavos
    WHERE id = NEW.drone_id;

    -- B: Verifica se atingiu 100 horas e gera alerta
    INSERT INTO alertas_manutencao (drone_id, mensagem)
    SELECT NEW.drone_id,
        'REVISÃO NECESSÁRIA: Drone ultrapassou 100 horas de voo.'
    FROM frota_drones
    WHERE id = NEW.drone_id
        AND horas_totais >= 100.0
        AND NOT EXISTS (
            SELECT 1
            FROM alertas_manutencao
            WHERE drone_id = NEW.drone_id
        );
END;

-- ==============================================================================
-- 3. POPULAÇÃO INICIAL
-- ==============================================================================
INSERT INTO frota_drones (modelo, horas_totais, faturamento_acumulado_centavos)
VALUES ('X-Resgate 01', 95.0, 950000), -- 9500.00
    ('B-Carga 05', 40.0, 400000),     -- 4000.00
    ('C-Agro 12', 10.0, 100000);      -- 1000.00

-- ==============================================================================
-- 4. SIMULAÇÃO DE OPERAÇÃO
-- ==============================================================================
-- Drone 1 voa 6 horas (vai bater 101h -> Alerta automático)
-- Faturamento: 6h * R$ 100,00 = R$ 600,00 (60000 centavos)
INSERT INTO log_voos (drone_id, horas_viagem, faturamento_viagem_centavos)
VALUES (1, 6.0, 60000);

-- Drone 2 voa 10 horas (vai bater 50h -> Sem alerta)
-- Faturamento: 10h * R$ 80,00 = R$ 800,00 (80000 centavos)
INSERT INTO log_voos (drone_id, horas_viagem, faturamento_viagem_centavos)
VALUES (2, 10.0, 80000);

-- ==============================================================================
-- 5. RELATÓRIO DE INTELIGÊNCIA (CTE)
-- ==============================================================================
-- Objetivo: Mostrar drones acima da média de uso da frota e seu faturamento em Reais
WITH media_uso AS (
    SELECT AVG(horas_totais) as media_frota
    FROM frota_drones
)
SELECT d.modelo,
    d.horas_totais AS "Horas Acumuladas",
    d.faturamento_acumulado_centavos / 100.0 AS "Faturamento Total (R$)",
    ROUND(m.media_frota, 2) AS "Média da Frota",
    CASE
        WHEN d.horas_totais > m.media_frota THEN 'ALTO USO'
        ELSE 'USO NORMAL'
    END AS "Status de Utilização"
FROM frota_drones d,
    media_uso m;

-- Verificando alertas gerados
SELECT * FROM alertas_manutencao;

/*
Resumo Teórico:
1. Triggers (Gatilhos): Fundamentais para automação reativa, garantindo que regras de negócio (como alertas de manutenção) sejam disparadas sem intervenção da aplicação.
2. CTEs (Common Table Expressions): Facilitam a legibilidade de consultas complexas, permitindo definir tabelas temporárias nomeadas que agem como subconsultas reutilizáveis.
3. Indexação: O índice em chaves estrangeiras (`drone_id`) é vital para manter a performance de Join e filtros em tabelas de log que crescem rapidamente.
4. Guardião Financeiro: O uso de INTEGER para faturamento em centavos assegura que os relatórios de lucratividade da frota sejam precisos, eliminando erros de floating point.

Assuntos Correlatos:
- Window Functions: Como usar RANK() e OVER() para classificar os drones mais produtivos da frota.
- Particionamento de Tabelas: Como gerenciar logs de voo de bilhões de linhas dividindo-os por data.
- Auditoria de Gatilhos: Como registrar quem ou qual processo disparou uma alteração automática.
- Manutenção Preditiva com IA: Integrar os logs de SQL com modelos de Machine Learning para prever falhas antes das 100 horas.
*/

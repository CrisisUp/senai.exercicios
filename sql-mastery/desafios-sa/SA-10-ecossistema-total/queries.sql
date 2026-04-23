/**
 * @file queries.sql
 * @brief Sistema Operacional de Dados SkyCargo - Ecossistema Total (SA-10)
 * @details Implementação de arquitetura de elite integrando DDL, DML, Triggers,
 *          Views, Window Functions e CTEs Recursivas. Focado em resiliência e
 *          integridade financeira através do padrão Guardião Financeiro.
 * @author Gemini CLI Agent
 * @date 2026-04-19
 *
 * @section ExecutionPlan
 * O ecossistema SkyCargo foi desenhado para máxima resiliência e visibilidade total.
 * A "Visão Total" é alcançada através da v_dashboard_elite, que consolida:
 * 1. Telemetria JSON (flexibilidade de dados brutos de sensores).
 * 2. Métricas de Performance (Média Móvel e Ranking via Window Functions).
 * 3. Integridade Financeira (Cálculo preciso via Guardião Financeiro - Centavos Inteiros).
 *
 * O custo computacional dessa visão é mitigado por índices estratégicos nas colunas
 * de partição e ordenação (drone_id, data_missao), evitando Full Table Scans 
 * e otimizando o motor de Window Functions para grandes volumes de dados.
 */
PRAGMA foreign_keys = ON;
-- -----------------------------------------------------------------------------
-- 1. MÓDULO DE ESTRUTURA (DDL)
-- -----------------------------------------------------------------------------
-- Tabela de Ativos (Drones)
CREATE TABLE IF NOT EXISTS drones (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    serial TEXT UNIQUE NOT NULL,
    modelo TEXT NOT NULL,
    status TEXT DEFAULT 'OCIOSO'
);
-- Tabela de Histórico (Eventos e Telemetria)
-- Implementação do "Guardião Financeiro": Custo em centavos (INTEGER)
CREATE TABLE IF NOT EXISTS historico_operacoes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id INTEGER,
    distancia REAL,
    custo_operacional_centavos INTEGER NOT NULL DEFAULT 0,
    -- Guardião Financeiro
    telemetria_json TEXT CHECK(json_valid(telemetria_json)),
    data_missao TEXT DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (drone_id) REFERENCES drones(id) ON DELETE CASCADE
);
-- Tabela de Componentes (Hierarquia BOM - Bill of Materials)
CREATE TABLE IF NOT EXISTS componentes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    pai_id INTEGER,
    drone_id INTEGER,
    FOREIGN KEY (pai_id) REFERENCES componentes(id) ON DELETE CASCADE,
    FOREIGN KEY (drone_id) REFERENCES drones(id) ON DELETE CASCADE
);
-- Indexação para buscas instantâneas e suporte a Window Functions (Otimização de Plano)
CREATE INDEX IF NOT EXISTS idx_ops_drone_data ON historico_operacoes(drone_id, data_missao);
-- -----------------------------------------------------------------------------
-- 2. MÓDULO DE SEGURANÇA (TRIGGERS)
-- -----------------------------------------------------------------------------
-- Bloqueia alteração em drones que estão em missão ativa (Blindagem de Estado)
CREATE TRIGGER IF NOT EXISTS trg_proteger_em_missao BEFORE
UPDATE ON drones
    WHEN OLD.status = 'EM_MISSAO' BEGIN
SELECT RAISE(
        ABORT,
        'BLOQUEIO DE SEGURANÇA: Impossível alterar status de drone em voo ativo!'
    );
END;
-- -----------------------------------------------------------------------------
-- 3. MÓDULO DE AUTOMAÇÃO E ETL (DML)
-- -----------------------------------------------------------------------------
-- Limpeza para demonstração (Idempotência)
DELETE FROM componentes;
DELETE FROM historico_operacoes;
DELETE FROM drones;
-- Populando Drones
INSERT INTO drones (serial, modelo, status)
VALUES ('SN-X10', 'Falcon-X', 'PRONTO'),
    ('SN-B22', 'Heavy-Lift', 'EM_MISSAO'),
    ('SN-C33', 'Agro-Vision', 'OCIOSO');
-- Populando Árvore de Peças (Hierarquia de Componentes)
INSERT INTO componentes (id, nome, pai_id, drone_id)
VALUES (1, 'CHASSI-01', NULL, 1),
    (2, 'BRACO-L', 1, 1),
    (3, 'MOTOR-L1', 2, 1),
    (4, 'CAMERA-RGB', NULL, 1);
-- -----------------------------------------------------------------------------
-- 4. MÓDULO DE INTELIGÊNCIA (VIEWS & WINDOW FUNCTIONS)
-- -----------------------------------------------------------------------------
DROP VIEW IF EXISTS v_dashboard_elite;
CREATE VIEW v_dashboard_elite AS
SELECT d.serial,
    d.modelo,
    h.distancia,
    printf('R$ %.2f', h.custo_operacional_centavos / 100.0) AS "Custo Operacional",
    -- Formatação Financeira
    json_extract(h.telemetria_json, '$.bateria') AS "Bateria %",
    ROUND(
        AVG(h.distancia) OVER(
            PARTITION BY d.serial
            ORDER BY h.data_missao ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
        ),
        2
    ) AS "Média Móvel (3 voos)",
    RANK() OVER(
        ORDER BY h.distancia DESC
    ) AS "Rank Global Distância"
FROM drones d
    JOIN historico_operacoes h ON d.id = h.drone_id;
-- -----------------------------------------------------------------------------
-- 5. SIMULAÇÃO DE CARGA (JSON & FINANCIAL INTEGRITY)
-- -----------------------------------------------------------------------------
-- Inserindo dados com integridade de centavos (Guardião Financeiro)
INSERT INTO historico_operacoes (
        drone_id,
        distancia,
        custo_operacional_centavos,
        telemetria_json
    )
VALUES (1, 45.5, 15075, '{"bateria": 88, "sat": 12}'),
    -- R$ 150,75
    (1, 50.2, 18500, '{"bateria": 75, "sat": 10}'),
    -- R$ 185,00
    (2, 120.0, 45000, '{"bateria": 45, "sat": 8}');
-- R$ 450,00
-- -----------------------------------------------------------------------------
-- 6. CONSULTA FINAL DE MESTRE
-- -----------------------------------------------------------------------------
-- 6.1 Verificando o Dashboard consolidado (Ecossistema Total)
SELECT *
FROM v_dashboard_elite;
-- 6.2 Verificando a hierarquia de hardware (CTE Recursiva)
WITH RECURSIVE arvore AS (
    SELECT id,
        nome,
        0 as nivel
    FROM componentes
    WHERE pai_id IS NULL
        AND drone_id = 1
    UNION ALL
    SELECT c.id,
        c.nome,
        a.nivel + 1
    FROM componentes c
        JOIN arvore a ON c.pai_id = a.id
)
SELECT nivel,
    COALESCE(printf('%' || (nivel * 3) || 's', ''), '') || nome as Estrutura_BOM
FROM arvore;
/*
 * ==============================================================================
 * RESUMO TEÓRICO: ARQUITETURA DE ECOSSISTEMA TOTAL
 * ==============================================================================
 * 1. INTEGRIDADE REFERENCIAL: Uso de Foreign Keys com ON DELETE CASCADE para 
 *    garantir que a deleção de um drone remova automaticamente seus componentes 
 *    e histórico, evitando dados órfãos.
 * 2. SEGURANÇA ATIVA: Triggers implementam regras de negócio no nível do motor 
 *    do banco (Blindagem), impedindo estados inválidos (ex: alterar drone em voo).
 * 3. WINDOW FUNCTIONS: Uso de RANK() e AVG() OVER para analytics em tempo real 
 *    sem a necessidade de tabelas de agregação lentas ou processamento externo.
 * 4. HIERARQUIA RECURSIVA: CTEs (Common Table Expressions) permitem navegar em 
 *    estruturas complexas de hardware (BOM) com profundidade arbitrária.
 * 5. GUARDIÃO FINANCEIRO: Armazenamento de valores monetários em INTEGERS 
 *    (centavos) elimina imprecisões de ponto flutuante (IEEE 754), garantindo 
 *    estabilidade bancária em cálculos de custo e receita.
 * 6. SISTEMAS HÍBRIDOS (JSON): O uso de campos JSON permite armazenar telemetria 
 *    semi-estruturada, mantendo a performance do SQL relacional para buscas.
 * ==============================================================================
 */
-- Assuntos Correlatos: Planos de Execução (EXPLAIN QUERY PLAN), Índices de Cobertura, 
-- Normalização vs Desnormalização, ACID Compliance e Sharding.
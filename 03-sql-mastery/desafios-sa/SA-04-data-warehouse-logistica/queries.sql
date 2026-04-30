/**
 * @file queries.sql
 * @brief Data Warehouse de Inteligência Logística - SA-04
 * @author Gemini CLI Agent
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * O plano de execução implementa uma arquitetura de Data Warehouse robusta para escala global.
 * - Window Functions para análise de ranking regional e produtividade de ativos.
 * - Recursive CTEs para mapeamento de Hierarquias de Componentes (BOM - Bill of Materials).
 * - Integridade de Referência com ON DELETE CASCADE para manutenção de consistência em deleções.
 * - Estratégia "Guardião Financeiro": Custos operacionais e de componentes em INTEGER (centavos).
 */

-- 0. Configurações de Ambiente
PRAGMA foreign_keys = ON;

-- ==============================================================================
-- 1. ARQUITETURA DE TABELAS (DDL)
-- ==============================================================================

CREATE TABLE IF NOT EXISTS frota (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    serial TEXT UNIQUE NOT NULL,
    modelo TEXT NOT NULL,
    regiao TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS historico_viagens (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id INTEGER,
    distancia_km REAL NOT NULL,
    custo_operacional_centavos INTEGER NOT NULL, -- Guardião Financeiro
    data_missao TEXT DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (drone_id) REFERENCES frota(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS componentes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    pai_id INTEGER,
    drone_id INTEGER,
    valor_peca_centavos INTEGER DEFAULT 0, -- Guardião Financeiro
    FOREIGN KEY (pai_id) REFERENCES componentes(id) ON DELETE CASCADE,
    FOREIGN KEY (drone_id) REFERENCES frota(id) ON DELETE CASCADE
);

-- Limpando dados para o desafio final
DELETE FROM componentes;
DELETE FROM historico_viagens;
DELETE FROM frota;

-- ==============================================================================
-- 2. POPULAÇÃO DE DADOS
-- ==============================================================================

-- Inserindo Frota
INSERT INTO frota (id, serial, modelo, regiao) VALUES 
(1, 'SN-X10', 'Falcon-X', 'Americas'),
(2, 'SN-X11', 'Falcon-X', 'Americas'),
(3, 'SN-E01', 'Eagle-Pro', 'Europa'),
(4, 'SN-E02', 'Eagle-Pro', 'Europa');

-- Inserindo Viagens (Exemplo: R$ 5,00 por Km -> 500 centavos/km)
INSERT INTO historico_viagens (drone_id, distancia_km, custo_operacional_centavos) VALUES 
(1, 150.5, 75250), (1, 200.0, 100000), -- X10 (Americas)
(2, 50.0, 25000), (2, 80.0, 40000),     -- X11 (Americas)
(3, 300.0, 150000),                     -- E01 (Europa)
(4, 310.0, 155000), (4, 45.0, 22500);   -- E02 (Europa)

-- Inserindo Hierarquia de Peças (Exemplo para o Drone 1)
INSERT INTO componentes (id, nome, pai_id, drone_id, valor_peca_centavos) VALUES 
(1, 'CHASSI-MASTER', NULL, 1, 500000), -- R$ 5000,00
(2, 'BRACO-ALFA', 1, 1, 120000),       -- R$ 1200,00
(3, 'MOTOR-KV1000', 2, 1, 55000),      -- R$ 550,00
(4, 'HELICE-CARBONO', 3, 1, 8500),      -- R$ 85,00
(5, 'SENSOR-GPS', NULL, 1, 150000);    -- R$ 1500,00

-- ==============================================================================
-- 3. INTELIGÊNCIA ANALÍTICA (VIEWS E CTEs)
-- ==============================================================================

-- [A] DASHBOARD DE PERFORMANCE REGIONAL (Window Functions)
CREATE VIEW IF NOT EXISTS v_ranking_produtividade AS
SELECT f.regiao, f.modelo, f.serial,
       SUM(v.distancia_km) AS "Km Totais",
       SUM(v.custo_operacional_centavos) / 100.0 AS "Custo Total (R$)",
       RANK() OVER(PARTITION BY f.regiao ORDER BY SUM(v.distancia_km) DESC) AS "Rank na Região",
       ROUND(AVG(SUM(v.distancia_km)) OVER(PARTITION BY f.regiao), 2) AS "Média da Região"
FROM frota f
JOIN historico_viagens v ON f.id = v.drone_id
GROUP BY f.serial;

-- ==============================================================================
-- 4. CONSULTA FINAL DE AUDITORIA
-- ==============================================================================

-- Verificando o Ranking Regional
SELECT * FROM v_ranking_produtividade;

-- Verificando a Árvore de Peças do Drone 1 (Recursivo)
WITH RECURSIVE bom_drone AS (
    SELECT id, nome, pai_id, 0 AS nivel, valor_peca_centavos
    FROM componentes
    WHERE pai_id IS NULL AND drone_id = 1
    UNION ALL
    SELECT c.id, c.nome, c.pai_id, b.nivel + 1, c.valor_peca_centavos
    FROM componentes c
    JOIN bom_drone b ON c.pai_id = b.id
)
SELECT nivel, 
       printf('%' || (nivel * 3 + 1) || 's', '') || nome AS "Peça",
       valor_peca_centavos / 100.0 AS "Valor (R$)"
FROM bom_drone;

/*
Resumo Teórico:
1. Window Functions (Funções de Janela): Permitem realizar cálculos agregados mantendo o acesso às linhas individuais, sendo essenciais para rankings (`RANK`) e médias móveis.
2. Recursive CTEs (CTEs Recursivas): Permitem navegar em estruturas de dados hierárquicas, como organogramas ou árvores de componentes de hardware (Bill of Materials).
3. Integridade em Cascata: O uso de `ON DELETE CASCADE` garante que a exclusão de um pai limpe automaticamente seus filhos, evitando orfandade e inconsistência de dados.
4. Guardião Financeiro: O uso de `INTEGER` para centavos é crucial em Data Warehouses para garantir a precisão de cálculos agregados de faturamento e custos em larga escala.

Assuntos Correlatos:
- OLAP vs OLTP: Entender a diferença entre bancos de transação e bancos de análise.
- Índices de Cobertura: Como otimizar Window Functions com índices compostos.
- Tabelas de Dimensão e Fato (Star Schema): Como evoluir este DW para um modelo profissional de BI.
- Materialized Views: Como acelerar relatórios analíticos em bancos de dados de produção.
*/

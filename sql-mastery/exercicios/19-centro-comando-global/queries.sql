/**
 * @file queries.sql
 * @brief Centro de Comando Global (Consolidação Multi-Banco).
 * @author Gemini CLI
 * @date 2026-04-19
 * @section ExecutionPlan Estratégia de Federação de Dados e Cross-Database Joins.
 */

-- ==============================================================================
-- ATIVIDADE 19: CENTRO DE COMANDO GLOBAL (CROSS-DATABASE)
-- OBJETIVO: Unir dados de sub-sistemas isolados em uma única inteligência.
-- ==============================================================================

-- 1. ANEXANDO OS SUB-SISTEMAS (Caminhos relativos às atividades anteriores)
-- @section ExecutionPlan: O banco gerencia conexões a múltiplos arquivos simultaneamente.
ATTACH DATABASE '../01-explorador-estoque/database.db' AS estoque;
ATTACH DATABASE '../12-integridade-cascata/database.db' AS frota;
ATTACH DATABASE '../18-inteligencia-rotas-grafos/database.db' AS rotas;

-- 2. CONSULTA DE INTELIGÊNCIA GLOBAL
-- Unindo dados de 3 bancos diferentes em um único relatório de prontidão.
WITH -- Seleciona um drone da frota (Ativ 12)
drone_selecionado AS (
    SELECT serial, modelo
    FROM frota.drones_frota
    LIMIT 1
), 
-- Seleciona a conexão de maior distância do nosso mapa (Ativ 18)
missao_longa AS (
    SELECT origem, destino, distancia
    FROM rotas.conexoes_bases
    ORDER BY distancia DESC
    LIMIT 1
), 
-- Seleciona a peça mais cara do estoque para backup (Ativ 01)
-- Nota: produtos.preco é INTEGER (cents) em Ativ 01.
peca_critica AS (
    SELECT nome, preco AS preco_cents
    FROM estoque.produtos
    ORDER BY preco DESC
    LIMIT 1
)
SELECT 
    d.serial AS "Drone Ativo",
    (m.origem || ' -> ' || m.destino) AS "Rota de Missão",
    m.distancia AS "Distância (km)",
    p.nome AS "Equipamento de Reserva",
    p.preco_cents / 100.0 AS "Valor Backup (R$)"
FROM drone_selecionado d,
    missao_longa m,
    peca_critica p;

-- Auditoria de execução global
EXPLAIN QUERY PLAN
SELECT * FROM estoque.produtos JOIN frota.drones_frota;

/* 
 ===============================================================
 RESUMO TEÓRICO: FEDERAÇÃO DE DADOS
 ===============================================================
 
 1. DATA FEDERATION:
 - Técnica que permite consultar dados distribuídos em múltiplos 
 bancos como se fossem um único repositório lógico.

 2. GUARDIÃO FINANCEIRO:
 - Mantido através da importação de campos INTEGER de sub-sistemas 
 externos para garantir que a consolidação financeira seja precisa.

 ===============================================================
 ASSUNTOS CORRELATOS:
 - Microservices Database patterns.
 - Virtual Data Warehousing.
 - SQLite VFS (Virtual File System) para bancos em rede.
 ===============================================================
 */

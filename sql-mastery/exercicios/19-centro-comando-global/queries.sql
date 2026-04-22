-- ==============================================================================
-- ATIVIDADE 19: CENTRO DE COMANDO GLOBAL (CROSS-DATABASE) - CORRIGIDA
-- OBJETIVO: Unir dados de sub-sistemas isolados em uma única inteligência.
-- ==============================================================================
-- 1. ANEXANDO OS SUB-SISTEMAS
ATTACH DATABASE '../01-explorador-estoque/database.db' AS estoque;
ATTACH DATABASE '../12-integridade-cascata/database.db' AS frota;
ATTACH DATABASE '../18-inteligencia-rotas-grafos/database.db' AS rotas;
-- 2. CONSULTA DE INTELIGÊNCIA GLOBAL
WITH -- Seleciona um drone da frota (Ativ 12)
drone_selecionado AS (
    SELECT serial,
        modelo
    FROM frota.drones_frota
    LIMIT 1
), -- Seleciona a conexão de maior distância do nosso mapa (Ativ 18)
missao_longa AS (
    SELECT origem,
        destino,
        distancia
    FROM rotas.conexoes_bases
    ORDER BY distancia DESC
    LIMIT 1
), -- Seleciona a peça mais cara do estoque para backup (Ativ 01)
peca_critica AS (
    SELECT nome
    FROM estoque.produtos
    ORDER BY preco DESC
    LIMIT 1
)
SELECT d.serial AS "Drone Ativo",
    (m.origem || ' -> ' || m.destino) AS "Rota de Missão",
    m.distancia AS "Distância (km)",
    p.nome AS "Equipamento de Reserva"
FROM drone_selecionado d,
    missao_longa m,
    peca_critica p;
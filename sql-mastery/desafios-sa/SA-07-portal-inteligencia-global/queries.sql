-- ==============================================================================
-- DESAFIO INTEGRADOR SA-07: PORTAL DE INTELIGÊNCIA GLOBAL
-- OBJETIVO: Consolidar Segurança, Federação e Analítica Avançada.
-- ==============================================================================
-- 1. SETUP DE FEDERAÇÃO
ATTACH DATABASE '../../exercicios/01-explorador-estoque/database.db' AS estoque;
-- 2. ARQUITETURA DO PORTAL (DDL)
-- Tabela de Missões Consolidadas
CREATE TABLE IF NOT EXISTS consolidado_missao (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id TEXT NOT NULL,
    regiao TEXT NOT NULL,
    distancia REAL NOT NULL,
    data_consolidacao TEXT DEFAULT CURRENT_TIMESTAMP
);
DELETE FROM consolidado_missao;
-- 3. BLINDAGEM DE SEGURANÇA (TRIGGER)
-- Impede que dados consolidados sejam apagados (Imutabilidade)
CREATE TRIGGER IF NOT EXISTS trg_proteger_missao BEFORE DELETE ON consolidado_missao BEGIN
SELECT RAISE(
        ABORT,
        'ALERTA DE SEGURANÇA: Dados consolidados não podem ser removidos!'
    );
END;
-- 4. POPULAÇÃO DE DADOS
INSERT INTO consolidado_missao (drone_id, regiao, distancia)
VALUES ('X-01', 'Americas', 150.0),
    ('X-01', 'Americas', 160.0),
    ('X-01', 'Americas', 140.0),
    ('E-05', 'Europa', 200.0),
    ('E-05', 'Europa', 210.0),
    ('E-05', 'Europa', 300.0),
    ('A-12', 'Asia', 50.0),
    ('A-12', 'Asia', 55.0),
    ('A-12', 'Asia', 120.0);
-- 5. CONSULTAS DE INTELIGÊNCIA INTEGRADA
-- [A] MÉDIA MÓVEL DE PERFORMANCE (WINDOW FRAMES)
-- Ajuda a identificar se o drone está perdendo rendimento nas últimas 3 missões.
SELECT drone_id,
    data_consolidacao,
    distancia,
    ROUND(
        AVG(distancia) OVER(
            PARTITION BY drone_id
            ORDER BY data_consolidacao ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
        ),
        2
    ) AS "Média Móvel (3 Missões)"
FROM consolidado_missao;
-- [B] DASHBOARD REGIONAL PIVOTADO (PIVOT)
-- Transforma regiões em colunas para comparação rápida.
SELECT 'Distância Total por Região' AS "Métrica",
    SUM(
        CASE
            WHEN regiao = 'Americas' THEN distancia
            ELSE 0
        END
    ) AS "AMERICAS",
    SUM(
        CASE
            WHEN regiao = 'Europa' THEN distancia
            ELSE 0
        END
    ) AS "EUROPA",
    SUM(
        CASE
            WHEN regiao = 'Asia' THEN distancia
            ELSE 0
        END
    ) AS "ASIA",
    SUM(distancia) AS "TOTAL GLOBAL"
FROM consolidado_missao;
-- [C] VERIFICAÇÃO DE SUPORTE (FEDERAÇÃO)
-- Verifica se temos peças no estoque anexado enquanto olhamos o portal.
SELECT 'Itens Disponíveis no Estoque Externo' AS Info,
    COUNT(*)
FROM estoque.produtos;
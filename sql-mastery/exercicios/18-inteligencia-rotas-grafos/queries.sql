-- ==============================================================================
-- ATIVIDADE 18: INTELIGÊNCIA DE ROTAS (GRAPH NAVIGATION)
-- OBJETIVO: Resolver problemas de logística e caminhos usando SQL.
-- ==============================================================================

-- 1. Setup do Mapa de Conexões
CREATE TABLE IF NOT EXISTS conexoes_bases (
    origem TEXT NOT NULL,
    destino TEXT NOT NULL,
    distancia REAL NOT NULL
);

DELETE FROM conexoes_bases;

-- Populando o Grafo (O mapa de rede)
INSERT INTO conexoes_bases (origem, destino, distancia) VALUES 
('BASE-A', 'BASE-B', 150.0),
('BASE-B', 'BASE-C', 200.0),
('BASE-B', 'BASE-D', 450.0),
('BASE-C', 'BASE-D', 100.0),
('BASE-D', 'BASE-E', 300.0);

-- 2. CONSULTA DE NAVEGAÇÃO RECURSIVA
-- Queremos sair da BASE-A e ver todas as formas de chegar a outros lugares.

WITH RECURSIVE navegador_rotas AS (
    -- [A] ÂNCORA: Iniciar na BASE-A
    SELECT destino, 
           distancia AS km_total, 
           origem || ' -> ' || destino AS trajeto,
           1 AS paradas
    FROM conexoes_bases
    WHERE origem = 'BASE-A'

    UNION ALL

    -- [B] MEMBRO RECURSIVO: Buscar o próximo salto
    SELECT c.destino, 
           n.km_total + c.distancia, 
           n.trajeto || ' -> ' || c.destino,
           n.paradas + 1
    FROM conexoes_bases c
    JOIN navegador_rotas n ON c.origem = n.destino
    -- Prevenção de Ciclos (Não passar pela mesma base duas vezes)
    WHERE n.trajeto NOT LIKE '%' || c.destino || '%'
)
-- Consulta Final: Verificando as opções para chegar na BASE-D
SELECT trajeto AS "Rota Completa",
       km_total AS "Distância Total",
       paradas AS "Qtd de Saltos"
FROM navegador_rotas
WHERE destino = 'BASE-D'
ORDER BY km_total ASC;

/* 
    ===============================================================
    RESUMO TEÓRICO: NAVEGAÇÃO EM GRAFOS (LOGÍSTICA)
    ===============================================================

    1. O QUE É UM GRAFO EM SQL?
       - É uma tabela onde cada registro representa uma conexão entre 
         dois pontos (Nodes). Muito usado em redes sociais (amizades) 
         e logística (rotas).

    2. ACÚMULO DE DADOS NA RECURSÃO:
       - 'n.km_total + c.distancia': Estamos somando os valores de 
         cada trecho conforme o SQL "anda" pelo mapa.

    3. PREVENÇÃO DE LOOPS (CICLOS):
       - 'NOT LIKE %destino%': Impede que o drone fique voando em 
         círculos entre bases, o que faria a query travar o banco.

    VANTAGEM DIDÁTICA: 
    O aluno aprende que o SQL é uma ferramenta matemática poderosa, 
    capaz de resolver problemas de "Caminho Mais Curto" (Shortest Path) 
    que normalmente exigiriam algoritmos complexos em outras linguagens.
    ===============================================================
*/

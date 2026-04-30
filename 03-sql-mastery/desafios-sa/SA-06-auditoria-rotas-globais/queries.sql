/**
 * @file queries.sql
 * @brief Central de Auditoria e Rotas Globais com Federação e Grafos.
 * @details Demonstra o uso de ATCH DATABASE para junção de bancos externos, 
 * CTEs recursivas para navegação em grafos e Triggers para auditoria.
 * @author Arquiteto de Sistemas
 * @date 2026-04-19
 *
 * @section ExecutionPlan
 * - Cross-DB Joins: Otimização de junção entre bancos locais e externos via ATTACH.
 * - Recursive CTE: Algoritmo de busca em profundidade para rotas de transporte.
 * - Triggers de Auditoria: Garantia de imutabilidade e rastreabilidade de mudanças de custo.
 */

-- ==============================================================================
-- 1. SETUP DE FEDERAÇÃO
-- ==============================================================================
-- Conectando ao arquivo morto da atividade 16 (Drones Aposentados)
ATTACH DATABASE '../../exercicios/16-multi-banco-attach/arquivo_morto.db' AS backup;

-- ==============================================================================
-- 2. ARQUITETURA LOCAL (DDL)
-- ==============================================================================

-- Tabela de Rotas com Guardião Financeiro
CREATE TABLE IF NOT EXISTS rotas_globais (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    origem TEXT NOT NULL,
    destino TEXT NOT NULL,
    distancia REAL NOT NULL,
    custo_base_centavos INTEGER DEFAULT 0 -- 💰 Guardião Financeiro
);

-- Tabela de Auditoria
CREATE TABLE IF NOT EXISTS log_auditoria_rotas (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    rota_id INTEGER,
    valor_antigo REAL,
    valor_novo REAL,
    data_log TEXT DEFAULT CURRENT_TIMESTAMP
);

DELETE FROM rotas_globais;
DELETE FROM log_auditoria_rotas;

-- ==============================================================================
-- 3. AUTOMAÇÃO DE AUDITORIA (TRIGGER)
-- ==============================================================================
CREATE TRIGGER IF NOT EXISTS trg_audit_distancia
AFTER UPDATE OF distancia ON rotas_globais 
BEGIN
    INSERT INTO log_auditoria_rotas (rota_id, valor_antigo, valor_novo)
    VALUES (OLD.id, OLD.distancia, NEW.distancia);
END;

-- ==============================================================================
-- 4. POPULANDO DADOS
-- ==============================================================================
INSERT INTO rotas_globais (origem, destino, distancia, custo_base_centavos)
VALUES ('LONDRES', 'PARIS', 344.0, 50000), -- R$ 500,00
       ('PARIS', 'BERLIM', 1054.0, 120000), -- R$ 1.200,00
       ('LONDRES', 'MADRI', 1263.0, 150000); -- R$ 1.500,00

-- ==============================================================================
-- 5. OPERAÇÃO E TESTE
-- ==============================================================================
-- Mudando a distância Londres-Madri para simular novo trajeto e disparar o Trigger
UPDATE rotas_globais
SET distancia = 1300.0
WHERE origem = 'LONDRES' AND destino = 'MADRI';

-- ==============================================================================
-- 6. CONSULTA DE INTELIGÊNCIA FINAL (RECURSIVO + CROSS-DB)
-- ==============================================================================

-- Busca de rota Londres -> Berlim cruzando com dados do banco externo
WITH RECURSIVE navegador AS (
    SELECT destino,
        distancia AS km,
        custo_base_centavos AS custo,
        origem || ' -> ' || destino AS caminho
    FROM rotas_globais
    WHERE origem = 'LONDRES'
    UNION ALL
    SELECT r.destino,
        n.km + r.distancia,
        n.custo + r.custo_base_centavos,
        n.caminho || ' -> ' || r.destino
    FROM rotas_globais r
        JOIN navegador n ON r.origem = n.destino
)
SELECT n.caminho,
    n.km,
    n.custo / 100.0 AS "Custo Total (R$)",
    (SELECT COUNT(*) FROM backup.drones_velhos) AS "Drones em Quarentena"
FROM navegador n
WHERE n.destino = 'BERLIM';

-- ==============================================================================
-- RESUMO TEÓRICO
-- ==============================================================================
/*
1. Federação de Dados (ATTACH): Permite que o SQLite atue como um hub, realizando 
   JOINs entre múltiplos arquivos de banco de dados físicos em uma única conexão.
2. CTEs Recursivas: Utilizadas para processar estruturas de grafos (nós e arestas), 
   essenciais para cálculos de logística e hierarquias.
3. Triggers de Auditoria: Garantem que toda alteração em dados sensíveis seja 
   registrada automaticamente, evitando "pontos cegos" no sistema.
4. Integridade Monetária: Uso de INTEGER para centavos elimina o risco de erros de 
   precisão em cálculos financeiros globais.
*/

-- ==============================================================================
-- ASSUNTOS CORRELATOS
-- ==============================================================================
/*
- Algoritmo de Dijkstra (Caminho mais curto).
- Modo WAL (Write-Ahead Logging) em ambientes distribuídos.
- Segurança de Federação (Restrições de ATTACH).
- Views Materializadas para Performance de Grafos.
*/

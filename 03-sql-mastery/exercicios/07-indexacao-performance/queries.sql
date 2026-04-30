/**
 * @file queries.sql
 * @brief Atividade 07: Engenharia de Performance (Indexação e Planos de Busca)
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * Foco em B-Trees para Índices e Complexidade:
 * - O SQLite utiliza B-Trees para armazenar tanto as tabelas (B-Tree de dados) quanto os índices (B-Tree de chaves).
 * - Sem índice: O(n) - Full Table Scan (Leitura sequencial de todas as páginas).
 * - Com índice: O(log n) - Index Seek (Busca binária balanceada na árvore).
 * - O índice `idx_drone_id` armazena pares (drone_id, rowid), permitindo saltar diretamente para a linha na B-Tree de dados.
 */
-- ==============================================================================
-- ATIVIDADE 07: ENGENHARIA DE PERFORMANCE (INDEXAÇÃO)
-- OBJETIVO: Otimizar buscas em grandes volumes de dados.
-- ==============================================================================
-- 1. Criação da Tabela de Logs
-- @note Guardião Financeiro: custo_processamento_cents (INTEGER) para precisão de auditoria.
CREATE TABLE IF NOT EXISTS historico_voo (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  drone_id TEXT NOT NULL,
  evento TEXT,
  custo_processamento_cents INTEGER DEFAULT 0,
  data_hora TEXT DEFAULT CURRENT_TIMESTAMP
);
-- Limpando dados para o teste de performance
DELETE FROM historico_voo;
-- 2. Populando o banco com massa de dados (Simulação)
INSERT INTO historico_voo (drone_id, evento, custo_processamento_cents)
VALUES ('DRONE-X1', 'Decolagem autorizada', 50),
  ('DRONE-B2', 'Sinal de GPS estável', 10),
  ('DRONE-X1', 'Ajuste de altitude para 150m', 15),
  ('DRONE-C3', 'Bateria 85%', 5),
  ('DRONE-X1', 'Cruzando setor Alfa', 20),
  ('DRONE-B2', 'Pouso concluído', 45),
  ('DRONE-X1', 'Pouso concluído', 45);
-- 3. ANÁLISE ANTES DO ÍNDICE
-- Este comando revela que o SQLite fará um "SCAN" (ler tudo)
EXPLAIN QUERY PLAN
SELECT *
FROM historico_voo
WHERE drone_id = 'DRONE-X1';
-- 4. CRIAÇÃO DO ÍNDICE (Aceleração)
-- Criamos um índice dedicado à coluna de busca mais comum.
CREATE INDEX IF NOT EXISTS idx_drone_id ON historico_voo(drone_id);
-- 5. ANÁLISE DEPOIS DO ÍNDICE
-- Este comando revela que agora o SQLite fará um "SEARCH" (busca direta via guia)
EXPLAIN QUERY PLAN
SELECT *
FROM historico_voo
WHERE drone_id = 'DRONE-X1';
-- 6. CONSULTA REAL (Rápida e otimizada)
SELECT drone_id,
  evento,
  (custo_processamento_cents / 100.0) AS custo_reais,
  data_hora
FROM historico_voo
WHERE drone_id = 'DRONE-X1';
/* 
 ===============================================================
 RESUMO TEÓRICO: ÍNDICES E PLANOS DE EXECUÇÃO
 ===============================================================
 
 1. SCAN (Lento): 
 - Imagine procurar seu nome em um livro de 500 páginas lendo 
 cada palavra. Isso é o SCAN (Full Table Scan).
 
 2. SEARCH (Rápido): 
 - Imagine usar o índice remissivo no fim do livro para saber 
 que seu nome está na página 42. Isso é o SEARCH (Index Seek).
 
 3. O CUSTO DO ÍNDICE: 
 - Índices ocupam espaço em disco e deixam os INSERTs e UPDATEs 
 um pouco mais lentos (pois o índice deve ser atualizado). 
 - Regra: Crie índices apenas nas colunas usadas no WHERE ou JOIN.
 
 4. GUARDIÃO FINANCEIRO:
 - Mesmo em logs de telemetria, custos de operação devem ser 
 rastreados com INTEGER cents para garantir integridade em 
 relatórios de faturamento de serviços.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende a não apenas "fazer a query funcionar", mas a 
 se preocupar com o custo computacional e a escalabilidade do sistema.
 
 ASSUNTOS CORRELATOS:
 - Covering Indexes (Índices que contêm todas as colunas da query).
 - Indexes on Expressions (Índices em funções como UPPER(col)).
 - Multi-column Indexes (Índices compostos).
 ===============================================================
 */
-- ==============================================================================
-- ATIVIDADE 07: ENGENHARIA DE PERFORMANCE (INDEXAÇÃO)
-- OBJETIVO: Otimizar buscas em grandes volumes de dados.
-- ==============================================================================
-- 1. Criação da Tabela de Logs
CREATE TABLE IF NOT EXISTS historico_voo (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  drone_id TEXT NOT NULL,
  evento TEXT,
  data_hora TEXT DEFAULT CURRENT_TIMESTAMP
);
-- Limpando dados para o teste de performance
DELETE FROM historico_voo;
-- 2. Populando o banco com massa de dados (Simulação)
INSERT INTO historico_voo (drone_id, evento)
VALUES ('DRONE-X1', 'Decolagem autorizada'),
  ('DRONE-B2', 'Sinal de GPS estável'),
  ('DRONE-X1', 'Ajuste de altitude para 150m'),
  ('DRONE-C3', 'Bateria 85%'),
  ('DRONE-X1', 'Cruzando setor Alfa'),
  ('DRONE-B2', 'Pouso concluído'),
  ('DRONE-X1', 'Pouso concluído');
-- 3. ANÁLISE ANTES DO ÍNDICE
-- Este comando revela que o SQLite fará um "SCAN" (ler tudo)
EXPLAIN QUERY PLAN
SELECT *
FROM historico_voo
WHERE drone_id = 'DRONE-X1';
-- 4. CRIAÇÃO DO ÍNDICE (Aceleração)
-- Criamos um índice dedicado à coluna de busca mais comum.
CREATE INDEX idx_drone_id ON historico_voo(drone_id);
-- 5. ANÁLISE DEPOIS DO ÍNDICE
-- Este comando revela que agora o SQLite fará um "SEARCH" (busca direta via guia)
EXPLAIN QUERY PLAN
SELECT *
FROM historico_voo
WHERE drone_id = 'DRONE-X1';
-- 6. CONSULTA REAL (Rápida e otimizada)
SELECT *
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
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende a não apenas "fazer a query funcionar", mas a 
 se preocupar com o custo computacional e a escalabilidade do sistema.
 ===============================================================
 */
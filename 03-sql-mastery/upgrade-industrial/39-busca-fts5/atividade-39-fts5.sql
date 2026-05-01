/**
 * @file atividade-39-fts5.sql
 * @brief Implementação/Componente atividade-39-fts5.sql
 * @author Cristiano
 * @date 2026
 */
-- ##############################################################################
-- # ATIVIDADE 39: SQL FULL TEXT SEARCH (FTS5) - BUSCA INTELIGENTE (REVISADO)
-- ##############################################################################

.open logispeed_search.db

-- 1. Limpeza
DROP TABLE IF EXISTS relatos_manutencao;
DROP TABLE IF EXISTS relatos_fts;

-- 2. Tabela Real
CREATE TABLE relatos_manutencao (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    veiculo_id INTEGER,
    observacao TEXT
);

-- 3. Tabela Virtual FTS5
-- Nota: FTS5 não aceita PK comum, usa 'rowid' por padrão.
CREATE VIRTUAL TABLE relatos_fts USING fts5(
    observacao,
    content='relatos_manutencao',
    content_rowid='id'
);

-- 4. Triggers
CREATE TRIGGER trg_relatos_ai AFTER INSERT ON relatos_manutencao BEGIN
  INSERT INTO relatos_fts(rowid, observacao) VALUES (new.id, new.observacao);
END;

-- 5. Massa de Dados
INSERT INTO relatos_manutencao (veiculo_id, observacao) VALUES 
(101, 'Motor apresentando falha intermitente na partida e aquecimento excessivo.'),
(102, 'Troca de pneus dianteiros realizada devido ao desgaste acentuado na banda de rodagem.'),
(101, 'Verificação do sistema de freio. Pastilhas com desgaste mas ainda operacionais.'),
(103, 'Falha crítica no sistema hidráulico. Vazamento detectado no pistão secundário.'),
(104, 'Limpeza do radiador e substituição do líquido de arrefecimento.');

-- 6. BUSCAS DE ALTA PERFORMANCE
.mode column
.headers on

SELECT "\x1b[1;36m=== BUSCA POR TERMO SIMPLES (FALHA) ===\x1b[0m";
SELECT rowid, observacao FROM relatos_fts WHERE relatos_fts MATCH 'falha';

SELECT "\n\x1b[1;36m=== BUSCA POR PREFIXO (AQUECE*) ===\x1b[0m";
SELECT rowid, observacao FROM relatos_fts WHERE relatos_fts MATCH 'aquece*';

SELECT "\n\x1b[1;36m=== BUSCA POR PROXIMIDADE (FALHA NEAR/2 PARTIDA) ===\x1b[0m";
SELECT rowid, observacao FROM relatos_fts WHERE relatos_fts MATCH 'NEAR(falha partida, 2)';

-- 7. ANÁLISE DE ELITE (BM25 - RANQUEAMENTO POR RELEVÂNCIA)
-- BM25 é o algoritmo que diz qual documento é 'mais importante' para a busca
SELECT "\n\x1b[1;32m[RANQUEAMENTO BM25]\x1b[0m Buscando 'desgaste':";
SELECT 
    rowid, 
    observacao, 
    bm25(relatos_fts) as score 
FROM relatos_fts 
WHERE relatos_fts MATCH 'desgaste' 
ORDER BY score;

/* @section ExecutionPlan
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

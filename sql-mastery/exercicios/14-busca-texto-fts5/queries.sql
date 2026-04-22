/**
 * @file queries.sql
 * @brief Atividade 14: Motor de Busca Inteligente (FTS5).
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * 1. Virtual Table (FTS5): O SQLite cria 3 a 5 tabelas internas para gerenciar o 
 *    índice invertido (palavra -> ID da linha).
 * 2. Tokenização: O texto é quebrado em tokens durante a escrita (Write-time parsing).
 * 3. Operador MATCH: Executa uma busca binária no índice invertido, evitando o 
 *    Table Scan que um LIKE '%texto%' causaria.
 */

-- 1. Criação da Tabela VIRTUAL FTS5 com Guardião Financeiro
-- 'tokenize = unicode61' permite buscar palavras com acentos e cedilha.
CREATE VIRTUAL TABLE IF NOT EXISTS busca_logs USING fts5(
    drone_id,
    relatorio_piloto,
    estimativa_custo_reparo_centavos, -- Guardião Financeiro no motor de busca
    tokenize = "unicode61"
);

-- Limpeza para demonstração
DELETE FROM busca_logs;

-- 2. Populando o índice de texto e valores
INSERT INTO busca_logs (drone_id, relatorio_piloto, estimativa_custo_reparo_centavos)
VALUES 
    ('X-10', 'O motor frontal apresentou vibração excessiva aos 500 metros.', 120000), -- R$ 1.200
    ('B-02', 'Voo estável, sem intercorrências detectadas.', 0),
    ('X-10', 'Pouso forçado devido a fumaça saindo da bateria principal.', 450000),    -- R$ 4.500
    ('C-05', 'Câmera térmica falhou ao identificar o alvo no escuro.', 85000),         -- R$ 850
    ('B-02', 'Bateria com aquecimento acima do normal após subida rápida.', 15000);   -- R$ 150

-- 3. CONSULTAS DE ALTA PERFORMANCE (MATCH)
-- [A] BUSCA SIMPLES POR PALAVRA-CHAVE COM TOTALIZAÇÃO FINANCEIRA
SELECT 
    drone_id,
    relatorio_piloto,
    printf('R$ %.2f', estimativa_custo_reparo_centavos / 100.0) AS "Custo Reparo"
FROM busca_logs
WHERE relatorio_piloto MATCH 'bateria';

-- [B] BUSCA POR PREFIXO (STARTS WITH)
-- Procura palavras que comecem com "vibr" (vibração, vibrou, vibrando)
SELECT * FROM busca_logs WHERE relatorio_piloto MATCH 'vibr*';

-- [C] BUSCA POR MÚLTIPLAS PALAVRAS (AND implícito)
-- Procura onde ocorrem "aquecimento" e "bateria" no mesmo texto
SELECT * FROM busca_logs WHERE relatorio_piloto MATCH 'aquecimento bateria';

/* 
 ===============================================================
 RESUMO TEÓRICO: FTS5 (O GOOGLE NO BANCO DE DADOS)
 ===============================================================
 1. ÍNDICE INVERTIDO: É a tecnologia fundamental por trás de motores de busca. 
    Mapeia palavras para suas ocorrências em vez de linhas para suas colunas.
 2. PERFORMANCE TEXTUAL: O FTS5 reduz a complexidade de busca de O(N) para 
    O(log N) em grandes volumes de texto.
 3. INTEGRIDADE MONETÁRIA: Integrar valores em centavos permite que o sistema 
    não apenas busque erros, mas também calcule o impacto financeiro imediato.
 
 ASSUNTOS CORRELATOS:
 - Tokenizers customizados em C (Stemmers).
 - Ranking de resultados (BM25 algorithm).
 - Comandos 'INSERT INTO busca_logs(busca_logs) VALUES("optimize")'.
 ===============================================================
 */

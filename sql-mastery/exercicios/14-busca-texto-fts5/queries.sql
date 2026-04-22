-- ==============================================================================
-- ATIVIDADE 14: MOTOR DE BUSCA (FTS5)
-- OBJETIVO: Criar um índice de busca textual de alta performance.
-- ==============================================================================
-- 1. Criação da Tabela VIRTUAL FTS5
-- Nota: 'using fts5' avisa ao SQLite para ativar o motor de busca.
CREATE VIRTUAL TABLE IF NOT EXISTS busca_logs USING fts5(
  drone_id,
  relatorio_piloto,
  tokenize = "unicode61" -- Suporta acentos e caracteres globais
);
-- Limpando dados
DELETE FROM busca_logs;
-- 2. Populando o índice de texto
INSERT INTO busca_logs (drone_id, relatorio_piloto)
VALUES (
    'X-10',
    'O motor frontal apresentou vibração excessiva aos 500 metros.'
  ),
  (
    'B-02',
    'Voo estável, sem intercorrências detectadas.'
  ),
  (
    'X-10',
    'Pouso forçado devido a fumaça saindo da bateria principal.'
  ),
  (
    'C-05',
    'Câmera térmica falhou ao identificar o alvo no escuro.'
  ),
  (
    'B-02',
    'Bateria com aquecimento acima do normal após subida rápida.'
  );
-- 3. CONSULTAS DE ALTA PERFORMANCE (MATCH)
-- [A] BUSCA SIMPLES POR PALAVRA-CHAVE
-- Procura qualquer log que contenha a palavra "bateria"
SELECT *
FROM busca_logs
WHERE relatorio_piloto MATCH 'bateria';
-- [B] BUSCA POR PREFIXO (STARTS WITH)
-- Procura palavras que comecem com "vibr" (vibração, vibrou, vibrando)
SELECT *
FROM busca_logs
WHERE relatorio_piloto MATCH 'vibr*';
-- [C] BUSCA POR MÚLTIPLAS PALAVRAS (AND implícito)
-- Procura onde ocorrem "aquecimento" e "bateria" no mesmo texto
SELECT *
FROM busca_logs
WHERE relatorio_piloto MATCH 'aquecimento bateria';
/* 
 ===============================================================
 RESUMO TEÓRICO: FTS5 (O GOOGLE DENTRO DO BANCO)
 ===============================================================
 
 1. TABELAS VIRTUAIS:
 - Elas não guardam os dados como tabelas normais. Elas criam 
 uma estrutura de "Índice Invertido", mapeando cada palavra 
 para a linha onde ela aparece.
 
 2. OPERADOR MATCH:
 - É o comando que ativa o motor de busca. Ele é ordens de 
 magnitude mais rápido que o 'LIKE', especialmente em 
 milhares de parágrafos.
 
 3. TOKENIZAÇÃO:
 - O SQLite quebra a frase "O motor vibrou" em: [O], [motor], 
 [vibrou]. Isso permite buscas parciais e inteligentes.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende que nem todo dado é número ou categoria fixa. 
 Lidar com texto livre exige ferramentas especializadas.
 ===============================================================
 */
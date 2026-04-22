-- ==============================================================================
-- ATIVIDADE 28: MANUTENÇÃO E LIMPEZA (VACUUM)
-- OBJETIVO: Recuperar espaço em disco e otimizar a estrutura do banco.
-- ==============================================================================
-- 1. Setup da Tabela Pesada
CREATE TABLE IF NOT EXISTS logs_temporarios (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  data TEXT,
  conteudo TEXT
);
-- 2. POPULAÇÃO MASSIVA (Simulando meses de uso)
-- Usamos um truque de recursividade para inserir 1000 linhas rápido.
WITH RECURSIVE contador(n) AS (
  SELECT 1
  UNION ALL
  SELECT n + 1
  FROM contador
  WHERE n < 1000
)
INSERT INTO logs_temporarios (data, conteudo)
SELECT '2026-01-01',
  'LOG_PESADO_DE_TELEMETRIA_DRONE_DATA_DUMP_ESTRUTURA_GIGANTE'
FROM contador;
-- 3. VERIFICAÇÃO DE TAMANHO INICIAL
SELECT 'Páginas ANTES da limpeza:' as info,
  page_count
FROM pragma_page_count();
-- 4. O ERRO COMUM: DELETE sem VACUUM
-- Deletamos tudo, mas o arquivo no seu HD continuará com o mesmo tamanho!
DELETE FROM logs_temporarios;
SELECT 'Páginas APÓS DELETE (sem limpeza):' as info,
  page_count
FROM pragma_page_count();
-- 5. A SOLUÇÃO: VACUUM
-- O banco se auto-reorganiza agora.
VACUUM;
SELECT 'Páginas APÓS VACUUM (limpeza real):' as info,
  page_count
FROM pragma_page_count();
-- 6. OTIMIZAÇÃO DE BUSCA
-- Faz o banco olhar no espelho e recalcular seus planos de query.
ANALYZE;
/* 
 ===============================================================
 RESUMO TEÓRICO: MANUTENÇÃO DE BANCO
 ===============================================================
 
 1. FRAGMENTAÇÃO: 
 - Quando você deleta uma linha, o SQLite apenas marca aquele 
 espaço como "Vazio", mas não devolve o espaço para o Windows/Mac. 
 - Isso cria buracos no arquivo (Fragmentação).
 
 2. VACUUM: 
 - Copia os dados válidos para um novo arquivo temporário e 
 sobrescreve o antigo. 
 - É o "Desfragmentador de Disco" do banco de dados.
 
 3. ANALYZE: 
 - Coleta estatísticas sobre os índices. 
 - Exemplo: "O índice X agora é inútil porque 90% dos dados 
 são iguais". Isso faz o banco ignorar o índice e ganhar tempo.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende que ser Arquiteto não é só construir, mas também 
 manter e limpar o sistema para que ele dure anos.
 ===============================================================
 */
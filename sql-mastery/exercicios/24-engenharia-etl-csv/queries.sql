-- ==============================================================================
-- ATIVIDADE 24: ENGENHARIA ETL (EXTRACT, TRANSFORM, LOAD)
-- OBJETIVO: Automatizar a entrada e saída de grandes volumes de dados.
-- ==============================================================================

-- 1. Criação da Tabela de Destino
-- Ela deve bater com a estrutura do CSV (id, nome, regiao, contato)
CREATE TABLE IF NOT EXISTS fornecedores_importados (
    id INTEGER PRIMARY KEY,
    nome TEXT,
    regiao TEXT,
    contato TEXT
);

-- Nota: O comando '.import' deve ser executado no prompt do SQLite, 
-- não dentro de um arquivo .sql de script puro. Veja o INTERACAO_SQLITE.md.

-- 2. TRANSFORMAÇÃO DE DADOS (Pós-Importação)
-- Imagine que queremos padronizar as regiões para letras MAIÚSCULAS.
UPDATE fornecedores_importados SET regiao = UPPER(regiao);

-- 3. CONSULTA PARA EXPORTAÇÃO
-- Esta é a query cujo resultado queremos salvar em um arquivo CSV externo.
SELECT nome, contato FROM fornecedores_importados WHERE regiao = 'NORTE';

/* 
    ===============================================================
    RESUMO TEÓRICO: FLUXO ETL
    ===============================================================

    1. EXTRACT (Extração): 
       - Os dados vêm de fontes "sujas" ou externas (CSV, Excel, XML).

    2. TRANSFORM (Transformação): 
       - O momento em que você limpa o dado (UPPER, TRIM, cálculos). 
       - É onde o Engenheiro de Dados agrega mais valor.

    3. LOAD (Carga): 
       - O dado final entra nas tabelas de produção pronto para uso.

    4. DOT COMMANDS (.):
       - São utilitários do programa 'sqlite3'. Eles não são SQL, 
         mas ferramentas de gestão do banco de dados.

    VANTAGEM DIDÁTICA: 
    O aluno aprende que o banco de dados é um sistema aberto, que 
    recebe e entrega dados para o ecossistema corporativo.
    ===============================================================
*/

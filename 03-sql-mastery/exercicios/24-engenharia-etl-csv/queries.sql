/**
 * @file queries.sql
 * @brief Engenharia ETL e Manipulação de Arquivos Externos.
 * @author Gemini CLI Agent
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * - Batch Inserts: O uso de .import é drasticamente mais rápido que INSERTs individuais.
 * - Analytics Costs: Operações de UPPER e Transformação em massa consomem CPU e geram logs de transação pesados.
 * - Transaction Log Overheads: Importações massivas sem BEGIN/COMMIT explícitos (via shell) podem saturar o journal.
 * - Guardião Financeiro: Implementação de integridade bancária via INTEGER cents em colunas de contrato.
 */

-- 1. Criação da Tabela de Destino
CREATE TABLE IF NOT EXISTS fornecedores_importados (
    id INTEGER PRIMARY KEY,
    nome TEXT,
    regiao TEXT,
    contato TEXT,
    valor_contrato_centavos INTEGER DEFAULT 0 CHECK (valor_contrato_centavos >= 0) -- Guardião Financeiro
);

-- Nota: O comando '.import' deve ser executado no prompt do SQLite.

-- 2. TRANSFORMAÇÃO DE DADOS (Pós-Importação)
-- Padronização de regiões e saneamento de strings.
UPDATE fornecedores_importados 
SET regiao = UPPER(TRIM(regiao));

-- 3. CONSULTA PARA EXPORTAÇÃO
-- Esta é a query cujo resultado queremos salvar em um arquivo CSV externo.
SELECT 
    nome, 
    contato, 
    PRINTF('R$ %.2f', valor_contrato_centavos / 100.0) AS valor_monetario
FROM fornecedores_importados 
WHERE regiao = 'NORTE';

/* 
    ===============================================================
    RESUMO TEÓRICO: FLUXO ETL
    ===============================================================

    1. EXTRACT (Extração): Coleta de fontes externas (CSV, JSON).
    2. TRANSFORM (Transformação): Limpeza e normalização (UPPER, TRIM).
    3. LOAD (Carga): Persistência em tabelas otimizadas.

    ASSUNTOS CORRELATOS:
    - ACID Compliance em Importações Massivas.
    - SQL Injection via CSV (CSV Injection/Formula Injection).
    - Pipeline de Dados (Airflow, DBT, ETL Tools).
    ===============================================================
*/

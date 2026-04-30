/**
 * @file queries.sql
 * @brief Atividade 13: Flexibilidade Moderna (JSON e UPSERT).
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * 1. JSON Valid: O banco aplica uma função de sistema (json_valid) em tempo de inserção.
 * 2. UPSERT: O mecanismo ON CONFLICT desvia a árvore de execução de INSERT para UPDATE 
 *    utilizando a tabela virtual 'excluded' para referenciar os novos dados.
 * 3. JSON Parsing: 'json_extract' é executado linha a linha na fase de projeção do SQL.
 *    Para tabelas grandes, colunas virtuais com INDEX seriam preferíveis.
 */

-- 1. Criação da Tabela com Validação JSON e Guardião Financeiro (Cents inside JSON)
CREATE TABLE IF NOT EXISTS telemetria_avancada (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_serial TEXT UNIQUE NOT NULL,
    dados_json TEXT CHECK(json_valid(dados_json)), -- Blindagem contra JSON malformado
    ultima_atualizacao TEXT DEFAULT CURRENT_TIMESTAMP
);

-- Limpeza para demonstração
DELETE FROM telemetria_avancada;

-- 2. DEMONSTRAÇÃO DE UPSERT (Inserir ou Atualizar) com Guardião Financeiro
-- Primeira inserção: Registra o drone SN-100 (Carga de R$ 2.500,00)
INSERT INTO telemetria_avancada (drone_serial, dados_json)
VALUES (
    'SN-100',
    '{"temp": 25.5, "bateria": 80, "valor_carga_centavos": 250000}'
) ON CONFLICT(drone_serial) DO UPDATE SET 
    dados_json = excluded.dados_json,
    ultima_atualizacao = CURRENT_TIMESTAMP;

-- Segunda inserção (UPSERT): Atualiza o mesmo drone (Carga subiu para R$ 3.000,00)
INSERT INTO telemetria_avancada (drone_serial, dados_json)
VALUES (
    'SN-100',
    '{"temp": 28.0, "bateria": 75, "valor_carga_centavos": 300000}'
) ON CONFLICT(drone_serial) DO UPDATE SET 
    dados_json = excluded.dados_json,
    ultima_atualizacao = CURRENT_TIMESTAMP;

-- Inserindo um drone novo com sensores variados
INSERT INTO telemetria_avancada (drone_serial, dados_json)
VALUES ('SN-200', '{"temp": 22.1, "missao": "resgate", "valor_carga_centavos": 0}');

-- 3. CONSULTAS EM CAMPOS JSON COM CONVERSÃO FINANCEIRA
SELECT 
    drone_serial AS "Drone",
    json_extract(dados_json, '$.temp') AS "Temp",
    json_extract(dados_json, '$.bateria') AS "Bat",
    printf('R$ %.2f', json_extract(dados_json, '$.valor_carga_centavos') / 100.0) AS "Valor Carga",
    ultima_atualizacao
FROM telemetria_avancada;

/* 
 ===============================================================
 RESUMO TEÓRICO: O SQL SEMI-ESTRUTURADO E UPSERT
 ===============================================================
 1. JSON NO SQL: Combina a rigidez do SQL com a agilidade do NoSQL. É ideal 
    para armazenar atributos de hardware que mudam com frequência de versão.
 2. UPSERT (INSERT OR UPDATE): É a solução idiomática para lidar com fluxos 
    de dados (streaming), onde não se sabe se um ID já foi processado.
 3. INTEGRIDADE FINANCEIRA: Mesmo dentro de um JSON, o uso de INTEGER para 
    centavos é obrigatório para garantir cálculos monetários precisos.
 
 ASSUNTOS CORRELATOS:
 - JSON1 Extension: Suporte nativo em C/C++ para o SQLite.
 - Geração de Colunas Virtuais a partir de JSON (Generated Columns).
 - Indexação de JSON (Index on Expression).
 ===============================================================
 */

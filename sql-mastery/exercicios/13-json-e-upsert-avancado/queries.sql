-- ==============================================================================
-- ATIVIDADE 13: FLEXIBILIDADE MODERNA (JSON E UPSERT)
-- OBJETIVO: Gerenciar dados semi-estruturados e resolver conflitos de inserção.
-- ==============================================================================
-- 1. Criação da Tabela com Validação JSON
CREATE TABLE IF NOT EXISTS telemetria_avancada (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_serial TEXT UNIQUE NOT NULL,
    dados_json TEXT CHECK(json_valid(dados_json)),
    -- Blindagem contra JSON malformado
    ultima_atualizacao TEXT DEFAULT CURRENT_TIMESTAMP
);
DELETE FROM telemetria_avancada;
-- 2. DEMONSTRAÇÃO DE UPSERT (Inserir ou Atualizar)
-- Primeira inserção: Registra o drone SN-100
INSERT INTO telemetria_avancada (drone_serial, dados_json)
VALUES (
        'SN-100',
        '{"temp": 25.5, "bateria": 80, "gps": [10.5, -45.2]}'
    ) ON CONFLICT(drone_serial) DO
UPDATE
SET dados_json = excluded.dados_json,
    ultima_atualizacao = CURRENT_TIMESTAMP;
-- Segunda inserção (UPSERT): Atualiza o mesmo drone com novos sensores
-- Note que o JSON mudou de estrutura (agora tem "pressao")
INSERT INTO telemetria_avancada (drone_serial, dados_json)
VALUES (
        'SN-100',
        '{"temp": 28.0, "bateria": 75, "pressao": 1013}'
    ) ON CONFLICT(drone_serial) DO
UPDATE
SET dados_json = excluded.dados_json,
    ultima_atualizacao = CURRENT_TIMESTAMP;
-- Inserindo um drone novo
INSERT INTO telemetria_avancada (drone_serial, dados_json)
VALUES ('SN-200', '{"temp": 22.1, "missao": "resgate"}');
-- 3. CONSULTAS EM CAMPOS JSON
-- Extraímos a temperatura de dentro do JSON como se fosse uma coluna real.
SELECT drone_serial AS "Drone",
    json_extract(dados_json, '$.temp') AS "Temperatura (°C)",
    json_extract(dados_json, '$.bateria') AS "Nível Bateria",
    json_extract(dados_json, '$.pressao') AS "Pressão (hPa)"
FROM telemetria_avancada;
/* 
 ===============================================================
 RESUMO TEÓRICO: O SQL SEMI-ESTRUTURADO
 ===============================================================
 
 1. JSON NO SQL: 
 - Resolve o dilema: "Preciso de velocidade (SQL) ou 
 flexibilidade (NoSQL)?". O SQLite entrega ambos.
 - A função 'json_extract' permite filtrar dados específicos 
 em milissegundos.
 
 2. UPSERT (INSERT OR UPDATE):
 - É a forma industrial de lidar com IDs duplicados. 
 - 'excluded' é uma tabela virtual que contém os dados que 
 você tentou inserir mas que falharam pelo conflito.
 
 3. INTEGRIDADE JSON:
 - Usar 'CHECK(json_valid(...))' impede que o banco aceite 
 texto lixo onde deveria estar um objeto estruturado.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende a lidar com a variabilidade dos dados modernos 
 (sensores IoT) sem precisar refazer o esquema do banco toda semana.
 ===============================================================
 */
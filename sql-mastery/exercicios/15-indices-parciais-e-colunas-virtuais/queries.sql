-- ==============================================================================
-- ATIVIDADE 15: OTIMIZAÇÃO DE ESPAÇO (ÍNDICES PARCIAIS E COLUNAS GERADAS)
-- OBJETIVO: Reduzir uso de disco e acelerar cálculos repetitivos.
-- ==============================================================================
-- 1. Criação da Tabela com COLUNA VIRTUAL
-- O campo 'score_saude' não existe fisicamente no HD, é calculado na hora.
CREATE TABLE IF NOT EXISTS status_frota (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    serial TEXT NOT NULL,
    bateria REAL NOT NULL,
    horas_voo REAL NOT NULL,
    score_saude REAL GENERATED ALWAYS AS (bateria * horas_voo) VIRTUAL
);
DELETE FROM status_frota;
-- 2. População com dados variados
INSERT INTO status_frota (serial, bateria, horas_voo)
VALUES ('X1-OK', 95.0, 10.0),
    -- Score: 950
    ('X2-PERIGO', 12.0, 50.0),
    -- Score: 600 (Indexado)
    ('X3-OK', 80.0, 20.0),
    -- Score: 1600
    ('X4-CRITICO', 5.0, 100.0);
-- Score: 500 (Indexado)
-- 3. CRIAÇÃO DE ÍNDICE PARCIAL
-- Este índice é minúsculo, pois ignora todos os drones com bateria saudável.
CREATE INDEX idx_emergencia ON status_frota(serial)
WHERE bateria < 20.0;
-- 4. CONSULTAS E AUDITORIA
-- [A] CONSULTANDO A COLUNA VIRTUAL
-- Note que não precisamos calcular bateria * horas_voo, o banco faz sozinho!
SELECT serial,
    score_saude
FROM status_frota;
-- [B] AUDITORIA DE PERFORMANCE (ÍNDICE PARCIAL)
-- Quando filtramos por bateria < 20, o banco usa o índice inteligente.
EXPLAIN QUERY PLAN
SELECT *
FROM status_frota
WHERE bateria < 20.0;
-- [C] COMPARAÇÃO: Busca por drone saudável (Full Scan)
-- Como o índice ignora drones saudáveis, aqui o banco terá que ler tudo.
EXPLAIN QUERY PLAN
SELECT *
FROM status_frota
WHERE bateria > 50.0;
/* 
 ===============================================================
 RESUMO TEÓRICO: ENGENHARIA DE ARMAZENAMENTO
 ===============================================================
 
 1. COLUNAS VIRTUAIS (VIRTUAL):
 - Eliminam a redundância de dados. Se os valores base mudam, 
 o resultado muda automaticamente sem riscos de inconsistência.
 
 2. ÍNDICES PARCIAIS (WHERE):
 - São a solução definitiva para o dilema do espaço vs. velocidade. 
 - Ideais para filtrar estados raros (erros, pendências, alertas).
 
 3. VANTAGEM DIDÁTICA: 
 - O aluno aprende a pensar como um DBA (Database Administrator) 
 que precisa economizar recursos de nuvem (AWS/Azure) ao mesmo 
 tempo que mantém o sistema rápido.
 ===============================================================
 */
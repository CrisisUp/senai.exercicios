-- ==============================================================================
-- ATIVIDADE 12: INTEGRIDADE DE FERRO (CONSTRAINTS E CASCATAS)
-- OBJETIVO: Blindar o banco contra dados inválidos e automatizar a limpeza.
-- ==============================================================================
-- 0. Habilitar Suporte a Chaves Estrangeiras (Obrigatório no SQLite)
PRAGMA foreign_keys = ON;
-- 1. Criação da Tabela de Frota com Blindagem
CREATE TABLE IF NOT EXISTS drones_frota (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    serial TEXT UNIQUE NOT NULL,
    -- Impede duplicatas de hardware
    modelo TEXT NOT NULL,
    horas_voo REAL NOT NULL CHECK (horas_voo >= 0) -- Impede horas negativas
);
-- 2. Criação da Tabela de Telemetria com Limpeza Automática
CREATE TABLE IF NOT EXISTS telemetria_historico (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id INTEGER,
    evento TEXT,
    FOREIGN KEY (drone_id) REFERENCES drones_frota(id) ON DELETE CASCADE
);
-- Limpando dados
DELETE FROM telemetria_historico;
DELETE FROM drones_frota;
-- 3. TESTES DE INTEGRIDADE
-- [A] Inserção Válida
INSERT INTO drones_frota (serial, modelo, horas_voo)
VALUES ('SN-001', 'Falcon-X', 10.5);
-- [B] Inserindo Logs para o Drone 1
INSERT INTO telemetria_historico (drone_id, evento)
VALUES (1, 'Voo inaugural'),
    (1, 'Calibragem GPS');
-- [C] TESTE DE ERRO 1: Serial Repetido (Irá falhar)
-- INSERT INTO drones_frota (serial, modelo, horas_voo) VALUES ('SN-001', 'Clone', 5.0);
-- [D] TESTE DE ERRO 2: Horas Negativas (Irá falhar)
-- INSERT INTO drones_frota (serial, modelo, horas_voo) VALUES ('SN-999', 'Bug', -1.0);
-- 4. TESTE DE CASCATA (LIMPEZA AUTOMÁTICA)
-- Consulta antes da exclusão
SELECT 'LOGS ANTES:' as info,
    count(*)
FROM telemetria_historico;
-- Deletando o Drone 1
DELETE FROM drones_frota
WHERE id = 1;
-- Consulta depois da exclusão
-- O resultado deve ser ZERO, provando que o banco deletou os logs sozinho.
SELECT 'LOGS DEPOIS:' as info,
    count(*)
FROM telemetria_historico;
/* 
 ===============================================================
 RESUMO TEÓRICO: CONSTRAINTS E INTEGRIDADE
 ===============================================================
 
 1. CHECK CONSTRAINTS: 
 - É o validador do banco. Ele garante que a regra de negócio 
 seja respeitada na fonte (ex: preco > 0, idade >= 18).
 
 2. UNIQUE: 
 - Garante que a identidade de um objeto seja única no sistema, 
 evitando cadastros fantasmas ou duplicados.
 
 3. ON DELETE CASCADE:
 - Resolve o problema de "Lixo de Memória" no banco. 
 - Sem isso, deletar um pai deixaria os filhos apontando para 
 o nada (órfãos), o que corrompe a lógica de relatórios.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende que o banco de dados é o último guardião da 
 verdade, impedindo erros que a aplicação (Java, Rust, C++) 
 possa ter deixado passar.
 ===============================================================
 */
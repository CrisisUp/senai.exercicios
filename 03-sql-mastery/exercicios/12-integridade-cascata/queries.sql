/**
 * @file queries.sql
 * @brief Atividade 12: Integridade de Ferro (Constraints e Cascatas).
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * O SQLite garante a integridade através de tabelas de sistema que verificam 
 * cada constraint em tempo de inserção/deleção. 
 * 1. CHECK/UNIQUE: Verificação imediata (Fast fail).
 * 2. ON DELETE CASCADE: O banco executa gatilhos internos (Internal Triggers) 
 *    para limpar tabelas filhas.
 * 3. Overhead: Cascatas em massa podem travar o banco. Use transações explicitas.
 */

-- 0. Habilitar Suporte a Chaves Estrangeiras (Obrigatório no SQLite)
PRAGMA foreign_keys = ON;

-- 1. Criação da Tabela de Frota com Blindagem Financeira
CREATE TABLE IF NOT EXISTS drones_frota (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    serial TEXT UNIQUE NOT NULL,
    modelo TEXT NOT NULL,
    horas_voo REAL NOT NULL CHECK (horas_voo >= 0),
    custo_aquisicao_centavos INTEGER DEFAULT 0 -- Guardião Financeiro: Integridade Bancária
);

-- 2. Criação da Tabela de Telemetria com Limpeza Automática
CREATE TABLE IF NOT EXISTS telemetria_historico (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    drone_id INTEGER,
    evento TEXT,
    FOREIGN KEY (drone_id) REFERENCES drones_frota(id) ON DELETE CASCADE
);

-- Limpando dados para a demonstração
DELETE FROM telemetria_historico;
DELETE FROM drones_frota;

-- 3. TESTES DE INTEGRIDADE
-- [A] Inserção Válida
INSERT INTO drones_frota (id, serial, modelo, horas_voo, custo_aquisicao_centavos)
VALUES (1, 'SN-001', 'Falcon-X', 10.5, 550000); -- R$ 5.500,00

-- [B] Inserindo Logs para o Drone 1
INSERT INTO telemetria_historico (drone_id, evento)
VALUES (1, 'Voo inaugural'),
    (1, 'Calibragem GPS');

-- [C] TESTE DE ERRO 1: Serial Repetido (Irá falhar com UNIQUE constraint failed)
-- INSERT INTO drones_frota (serial, modelo, horas_voo) VALUES ('SN-001', 'Clone', 5.0);

-- [D] TESTE DE ERRO 2: Horas Negativas (Irá falhar com CHECK constraint failed)
-- INSERT INTO drones_frota (serial, modelo, horas_voo) VALUES ('SN-999', 'Bug', -1.0);

-- 4. TESTE DE CASCATA (LIMPEZA AUTOMÁTICA)
-- Relatório Antes
SELECT 'LOGS ANTES:' as status,
    count(*) as total
FROM telemetria_historico;

-- Deletando o Drone 1 (O topo da hierarquia)
DELETE FROM drones_frota WHERE id = 1;

-- O resultado deve ser ZERO, provando que o banco deletou os logs sozinho via CASCADE.
SELECT 'LOGS DEPOIS:' as status,
    count(*) as total
FROM telemetria_historico;

/* 
 ===============================================================
 RESUMO TEÓRICO: CONSTRAINTS E INTEGRIDADE REFERENCIAL
 ===============================================================
 1. CHECK CONSTRAINTS: Funcionam como "Unit Tests" em tempo real no banco, 
    impedindo que dados logicamente impossíveis sejam persistidos.
 2. ON DELETE CASCADE: Garante a higienização do banco de dados, removendo 
    referências mortas que poderiam causar inconsistências em relatórios.
 3. INTEGRIDADE FINANCEIRA: Utilizar INTEGER para valores monetários é uma 
    norma de segurança para evitar perdas de precisão em centavos.
 
 ASSUNTOS CORRELATOS:
 - PRAGMA foreign_key_check: Validação de integridade em bancos existentes.
 - Transações ACID: Como o CASCADE se comporta em caso de erro no meio do processo.
 - Diferença entre CASCADE, SET NULL e NO ACTION.
 ===============================================================
 */

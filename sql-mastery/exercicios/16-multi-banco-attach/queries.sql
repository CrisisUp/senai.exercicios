-- ==============================================================================
-- ATIVIDADE 16: MULTI-BANCO (ATTACH)
-- OBJETIVO: Cruzar dados de arquivos de banco de dados diferentes.
-- ==============================================================================

-- 1. SETUP DO BANCO SECUNDÁRIO (Arquivo Morto)
-- Vamos criar o arquivo fisicamente e popular.
ATTACH DATABASE 'arquivo_morto.db' AS morto;

CREATE TABLE IF NOT EXISTS morto.drones_velhos (
    id INTEGER PRIMARY KEY,
    serial TEXT,
    motivo_baixa TEXT
);

DELETE FROM morto.drones_velhos;
INSERT INTO morto.drones_velhos (serial, motivo_baixa) VALUES 
('OLD-001', 'Desgaste de motor'),
('OLD-005', 'Acidente em 2024');

-- 2. SETUP DO BANCO PRINCIPAL (Dentro da sessão atual)
CREATE TABLE IF NOT EXISTS drones_ativos (
    id INTEGER PRIMARY KEY,
    serial TEXT,
    status TEXT
);

DELETE FROM drones_ativos;
INSERT INTO drones_ativos (serial, status) VALUES 
('SN-X10', 'Em Voo'),
('SN-B02', 'Pronto');

-- 3. CONSULTA CROSS-DATABASE (Unindo os dois mundos)
-- Usamos o prefixo 'morto.' para acessar o arquivo externo.

SELECT serial, 'ATIVO' AS situacao FROM drones_ativos
UNION ALL
SELECT serial, 'APOSENTADO' AS situacao FROM morto.drones_velhos;

/* 
    ===============================================================
    RESUMO TEÓRICO: ATTACH E NAMESPACES
    ===============================================================

    1. ATTACH DATABASE: 
       - Transforma o SQLite em um sistema multi-banco. 
       - Útil para backups, migrações de dados e sharding manual.

    2. O ALIAS (AS morto): 
       - Define como você chamará o banco externo nas queries. 
       - Sem o ALIAS, o Rust/C++ não saberia em qual arquivo buscar a tabela.

    3. PERSISTÊNCIA: 
       - O ATTACH dura apenas enquanto a conexão (sessão) estiver aberta. 
       - Ao fechar o terminal, você precisará dar ATTACH novamente se quiser 
         cruzar os dados.

    VANTAGEM DIDÁTICA: 
    O aluno aprende que o limite de um banco de dados não é o arquivo físico, 
    permitindo arquiteturas de dados distribuídas e organizadas por tempo.
    ===============================================================
*/

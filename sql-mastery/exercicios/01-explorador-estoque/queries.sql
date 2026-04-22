/**
 * @file queries.sql
 * @brief Operações básicas de análise de inventário para a SkyStore.
 * @database SQLite 3
 * 
 * Atividade 01 - Fundamentos de Dados (Nível Iniciado).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section ExecutionPlan Análise de Desempenho
 * - Coluna 'id': PRIMARY KEY cria automaticamente um índice B-Tree. Busca O(log n).
 * - Coluna 'preco': Consultas WHERE sem índice causam Full Table Scan O(n).
 * - Armazenamento: Preço guardado como INTEGER (centavos) para evitar drifting binário.
 */

-- 1. [DDL] CRIAÇÃO DA TABELA (BLINDAGEM DE TIPOS)
CREATE TABLE IF NOT EXISTS produtos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    categoria TEXT,
    preco_centavos INTEGER NOT NULL, -- Medalha Guardião Financeiro (Centavos)
    estoque INTEGER DEFAULT 0
);

-- 2. [DML] POPULAÇÃO DE TESTE (CENÁRIO INDUSTRIAL)
-- Valores convertidos para centavos (Ex: 450.00 -> 45000)
INSERT INTO produtos (nome, categoria, preco_centavos, estoque) VALUES 
('Bateria Lipo 4S', 'Energia', 45000, 15),
('Hélice Carbono 12x4', 'Propulsão', 8550, 40),
('Sensor GPS Alfa', 'Navegação', 120000, 5),
('Câmera Térmica X1', 'Visão', 350000, 2),
('Frame em Fibra 250mm', 'Estrutura', 22000, 10);

-- 3. [DQL] CONSULTAS DE ENGENHARIA

-- [A] LISTAR NOME E PREÇO FORMATADO (FANTASMA DA PERFORMANCE)
-- Evitamos o SELECT * para reduzir o I/O de disco
SELECT nome, (preco_centavos / 100.0) AS preco_reais FROM produtos;

-- [B] FILTRAR PRODUTOS CRÍTICOS (ACIMA DE R$ 500)
-- A busca aqui é O(n) pois 'preco_centavos' não tem índice.
SELECT nome, categoria, (preco_centavos / 100.0) AS preco 
FROM produtos 
WHERE preco_centavos > 50000;

-- [C] BUSCAR O ITEM DE MAIOR VALOR PATRIMONIAL
-- O limit 1 impede o processamento de linhas desnecessárias.
SELECT nome, preco_centavos 
FROM produtos 
ORDER BY preco_centavos DESC 
LIMIT 1;

-- [D] AUDITORIA DE REPOSIÇÃO (LOW STOCK)
SELECT nome AS "Item Pendente", estoque AS "Qtd" 
FROM produtos 
WHERE estoque < 10;

/* 
    ===============================================================
    RESUMO TEÓRICO: FUNDAMENTOS DE DADOS DE ELITE
    ===============================================================

    1. INTEGRIDADE MONETÁRIA:
       - O uso de REAL/FLOAT em SQL é perigoso para dinheiro. 0.1 + 0.2
         pode resultar em 0.3000000000004. Usamos INTEGER (centavos) 
         para garantir que a contabilidade da SkyStore feche sempre.

    2. O CUSTO DO SELECT:
       - SELECT * é amador. Ele consome banda de rede e RAM do servidor 
         inutilmente. Um Engenheiro de Elite projeta apenas as colunas 
         estritamente necessárias.

    3. INDEXAÇÃO (CONCEITO):
       - A PRIMARY KEY é mais que um ID; é um índice físico. Consultar 
         por ID é instantâneo; consultar por Nome é lento (até criarmos 
         um INDEX para ele nas próximas atividades).

    ===============================================================
    ASSUNTOS CORRELATOS:
    - B-Tree Indexing: Como o banco organiza as chaves.
    - ACID Compliance: Garantindo que o INSERT não falhe pela metade.
    - SQL Injection prevention via Parameterized Queries.
    ===============================================================
*/

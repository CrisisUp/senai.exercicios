/**
 * @file queries.sql
 * @brief Atividade 11: Hierarquias Recursivas (Recursive CTEs).
 * @author Gemini CLI
 * @date 2026-04-19
 * 
 * @section ExecutionPlan
 * A consulta utiliza WITH RECURSIVE para decompor a árvore de componentes (BOM).
 * 1. Âncora: Seleciona as peças raiz (pai_id IS NULL).
 * 2. Recursão: Realiza um auto-join na tabela componentes para encontrar filhos diretos.
 * 3. Overhead: O custo de processamento cresce linearmente com a profundidade da árvore. 
 *    É fundamental que a coluna 'pai_id' possua um INDEX para otimizar os joins recursivos.
 */

-- 1. Setup da Tabela de Componentes (Auto-relacionada)
CREATE TABLE IF NOT EXISTS componentes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    pai_id INTEGER,
    preco_centavos INTEGER DEFAULT 0, -- Guardião Financeiro: Integridade Bancária
    FOREIGN KEY (pai_id) REFERENCES componentes(id)
);

-- Limpeza para demonstração
DELETE FROM componentes;

-- 2. Populando a Hierarquia (BOM - Bill of Materials) com Guardião Financeiro
INSERT INTO componentes (id, nome, pai_id, preco_centavos)
VALUES (1, 'DRONE SKY-X1', NULL, 150000), -- R$ 1.500,00
    (2, 'Chassi Carbono', 1, 45000),     -- R$ 450,00
    (3, 'Controladora de Voo', 1, 32000),
    (4, 'Braço Lateral', 2, 8500),
    (5, 'Trem de Pouso', 2, 5500),
    (6, 'Motor Brushless', 4, 12000),
    (7, 'Hélice 10x4.5', 6, 1200),
    (8, 'ESC 30A', 4, 9500),
    (9, 'Módulo GPS', 3, 18000),
    (10, 'Bateria Lipo 4S', 1, 28000);

-- 3. CONSULTA RECURSIVA (A Árvore de Peças e Soma de Custos)
WITH RECURSIVE arvore_pecas AS (
    -- [A] ÂNCORA: Seleciona o topo da hierarquia (onde pai_id é nulo)
    SELECT id,
        nome,
        pai_id,
        preco_centavos,
        0 AS nivel,
        nome AS caminho
    FROM componentes
    WHERE pai_id IS NULL
    
    UNION ALL
    
    -- [B] MEMBRO RECURSIVO: Une os filhos aos pais já encontrados
    SELECT c.id,
        c.nome,
        c.pai_id,
        c.preco_centavos,
        a.nivel + 1,
        a.caminho || ' > ' || c.nome
    FROM componentes c
    INNER JOIN arvore_pecas a ON c.pai_id = a.id
)
-- Consulta Final formatada com conversão financeira
SELECT 
    nivel,
    printf('%' || (nivel * 4) || 's', '') || nome AS "Estrutura Hierárquica",
    printf('R$ %.2f', preco_centavos / 100.0) AS "Preço Unitário",
    caminho AS "Rastreabilidade Full"
FROM arvore_pecas
ORDER BY caminho;

/* 
 ===============================================================
 RESUMO TEÓRICO: CTEs RECURSIVAS E HIERARQUIAS
 ===============================================================
 1. AUTO-RELACIONAMENTO: Permite que uma tabela referencie a si mesma para 
    armazenar árvores de profundidade arbitrária.
 2. RECURSIVIDADE SQL: O operador UNION ALL permite empilhar camadas de 
    profundidade (nível 1, nível 2, etc) até a exaustão dos registros.
 3. INTEGRIDADE FINANCEIRA: O uso de INTEGER para centavos evita erros de 
    arredondamento (floating point arithmetic errors) em transações bancárias.
 
 ASSUNTOS CORRELATOS:
 - Grafos em SQL (Busca em Largura vs Profundidade).
 - Índices em chaves estrangeiras recursivas.
 - Cláusula LIMIT na recursão para prevenção de loops infinitos.
 ===============================================================
 */

-- ==============================================================================
-- ATIVIDADE 11: HIERARQUIAS RECURSIVAS (CTE RECURSIVA)
-- OBJETIVO: Navegar em estruturas de árvore de profundidade variável.
-- ==============================================================================
-- 1. Setup da Tabela de Componentes (Auto-relacionada)
CREATE TABLE IF NOT EXISTS componentes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    pai_id INTEGER,
    FOREIGN KEY (pai_id) REFERENCES componentes(id)
);
DELETE FROM componentes;
-- 2. Populando a Hierarquia (BOM - Bill of Materials)
INSERT INTO componentes (id, nome, pai_id)
VALUES (1, 'DRONE SKY-X1', NULL),
    -- Nível 0 (Raiz)
    (2, 'Chassi Carbono', 1),
    -- Nível 1
    (3, 'Controladora de Voo', 1),
    -- Nível 1
    (4, 'Braço Lateral', 2),
    -- Nível 2
    (5, 'Trem de Pouso', 2),
    -- Nível 2
    (6, 'Motor Brushless', 4),
    -- Nível 3
    (7, 'Hélice 10x4.5', 6),
    -- Nível 4
    (8, 'ESC 30A', 4),
    -- Nível 3
    (9, 'Módulo GPS', 3),
    -- Nível 2
    (10, 'Bateria Lipo 4S', 1);
-- Nível 1
-- 3. CONSULTA RECURSIVA (A Árvore de Peças)
WITH RECURSIVE arvore_pecas AS (
    -- [A] ÂNCORA: Seleciona o topo da hierarquia (onde pai_id é nulo)
    SELECT id,
        nome,
        pai_id,
        0 AS nivel,
        nome AS caminho
    FROM componentes
    WHERE pai_id IS NULL
    UNION ALL
    -- [B] MEMBRO RECURSIVO: Une os filhos aos pais já encontrados
    SELECT c.id,
        c.nome,
        c.pai_id,
        a.nivel + 1,
        a.caminho || ' > ' || c.nome
    FROM componentes c
        INNER JOIN arvore_pecas a ON c.pai_id = a.id
) -- Consulta Final formatada
SELECT nivel,
    printf('%' || (nivel * 4) || 's', '') || nome AS "Estrutura Hierárquica",
    caminho AS "Rastreabilidade"
FROM arvore_pecas
ORDER BY caminho;
/* 
 ===============================================================
 RESUMO TEÓRICO: CTEs RECURSIVAS
 ===============================================================
 
 1. AUTO-RELACIONAMENTO: 
 - Note que 'pai_id' aponta para a própria tabela 'componentes'. 
 - Isso permite que o banco armazene árvores de qualquer tamanho.
 
 2. RECURSIVIDADE:
 - O SQL "sobe" ou "desce" a árvore executando a mesma lógica 
 até que não existam mais registros para processar.
 
 3. OPERADOR ||:
 - Usado no SQLite para concatenar strings (unir textos).
 
 4. PRINTF:
 - Usamos para adicionar espaços à esquerda baseados no nível, 
 criando o efeito visual de árvore no terminal.
 
 VANTAGEM DIDÁTICA: 
 O aluno aprende a lidar com um dos tipos de dados mais difíceis 
 e comuns na computação: Grafo e Árvores.
 ===============================================================
 */
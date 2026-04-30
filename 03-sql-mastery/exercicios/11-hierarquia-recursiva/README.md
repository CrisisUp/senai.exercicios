# 🗄️ Atividade 11: Hierarquias Complexas (Recursive CTE)

## 🎯 Estudo de Caso

Um drone não é apenas uma peça única; ele é uma montagem complexa. Por exemplo:

- O **Drone** tem um **Chassi**.
- O **Chassi** tem **Braços**.
- Cada **Braço** tem um **Motor** e um **Esc**.
- O **Motor** tem **Rolamentos** e **Bobinas**.

A "SkyCargo" precisa de um relatório que mostre a "Árvore Genealógica" de componentes (Bill of Materials - BOM). O desafio é que não sabemos quantos níveis de profundidade a montagem pode ter. Precisamos que o SQL percorra essa estrutura recursivamente.

## 🛠️ Necessidade Técnica

As **Recursive CTEs** permitem que uma consulta chame a si mesma:

* **WITH RECURSIVE:** Define o início da consulta recursiva.
* **Âncora (Anchor Member):** A consulta inicial que define o ponto de partida (ex: o Drone inteiro).
* **Membro Recursivo (Recursive Member):** A consulta que se une à anterior para buscar os "filhos" de cada item.
* **Condição de Parada:** O processo para automaticamente quando não encontra mais filhos.

## 📋 Requisitos

1. Criar a tabela `componentes` (id, nome, pai_id).
2. Inserir uma hierarquia de pelo menos 4 níveis (Drone -> Chassi -> Braço -> Motor).
3. Criar uma consulta recursiva que:
    - Mostre o nível de profundidade de cada peça.
    - Gere um "Caminho" visual (Ex: Drone > Chassi > Braço).
    - Formate o nome com espaços para simular uma árvore visual.

## ⚠️ Análise de Falha Crítica

Ao trabalhar com hierarquias recursivas, o engenheiro de dados deve estar atento aos seguintes riscos:

1.  **Recursão Infinita (Infinite Loops):** Se um componente for configurado como pai de si mesmo (direta ou indiretamente em um ciclo), a consulta `WITH RECURSIVE` entrará em um loop infinito, consumindo CPU e memória até que o banco de dados trave ou o limite de recursão seja atingido.
2.  **Orphaned Keys (Chaves Órfãs):** Componentes com `pai_id` que não existem na tabela ou que formam "ilhas" sem uma raiz (`NULL`) não aparecerão no relatório, ocultando custos e peças reais.
3.  **Explosão de Caminhos (Path Explosion):** Em hierarquias muito profundas (milhares de níveis), a concatenação de caminhos de texto pode exceder o limite de tamanho de strings do banco de dados.
4.  **Overhead de Memória:** O SQLite mantém a tabela temporária da CTE em memória. Estruturas massivas podem causar falhas de alocação se não forem limitadas.

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

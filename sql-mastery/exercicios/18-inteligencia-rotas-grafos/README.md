# 🗄️ Atividade 18: Inteligência de Rotas (Graph Pathfinding com CTE Recursiva)

## 🎯 Estudo de Caso

A "SkyCargo" opera uma rede de bases de entrega. Um drone precisa viajar do **Ponto A** ao **Ponto D**, mas não há uma rota direta. Ele deve passar por bases intermediárias para recarga. Precisamos que o banco de dados nos diga todos os caminhos possíveis, a sequência de bases e a distância total de cada rota.

## 🛠️ Necessidade Técnica

Este é o uso mais avançado das **CTEs Recursivas**, tratando tabelas como **Grafos**:

* **Grafos em SQL:** Uma tabela onde cada linha é uma "Aresta" (ligação) entre dois "Nós" (bases).
* **Acúmulo de Caminho:** Durante a recursão, vamos concatenando os nomes das bases para formar o trajeto completo.
* **Acúmulo de Custo:** Vamos somando as distâncias de cada trecho.
* **Prevenção de Ciclos:** Em redes reais, o SQL poderia entrar em loop infinito (A -> B -> A). Aprenderemos a evitar isso.

## 📋 Requisitos

1. Criar a tabela `conexoes_bases` (origem, destino, km).
2. Inserir um mapa de rotas interligadas (A para B, B para C, B para D, C para D).
3. Criar uma consulta recursiva que:

* Encontre todos os caminhos que saem de 'BASE-A'.
* Mostre a rota amigável (ex: BASE-A -> BASE-B -> BASE-D).
* Calcule a quilometragem total de cada opção.

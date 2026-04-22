# 🗄️ Atividade 21: Séries Temporais (Window Frames e Média Móvel)

## 🎯 Estudo de Caso

Um drone da "SkyCargo" envia leituras de bateria a cada minuto. Uma queda brusca isolada pode ser apenas um erro de sensor, mas se a **Média das últimas 3 leituras** estiver caindo consistentemente, o drone corre risco real de queda. Precisamos de um relatório que calcule essa "Média Móvel" (Moving Average) em tempo real para disparar alertas preventivos.

## 🛠️ Necessidade Técnica

As **Window Functions** do Nível 40 podiam olhar para o grupo inteiro. Agora, no **Nível 60**, aprenderemos a controlar o **Frame** (quadro) da janela:

* **ROWS BETWEEN:** Define exatamente quais linhas vizinhas entram no cálculo.
* **3 PRECEDING AND CURRENT ROW:** Olha para as 3 linhas anteriores e a linha atual.
* **Análise de Tendência:** Comparar o valor atual com a média móvel para detectar anomalias.

## 📋 Requisitos

1. Criar a tabela `leituras_bateria` (id, drone_id, nivel_bateria, timestamp).
2. Inserir uma série temporal de 10 leituras para um único drone, simulando uma queda de carga.
3. Criar uma consulta que utilize `AVG() OVER(...)` com `ROWS BETWEEN` para calcular a média móvel de 3 pontos.
4. Adicionar uma coluna que mostre o "Desvio da Média" (Bateria Atual - Média Móvel).

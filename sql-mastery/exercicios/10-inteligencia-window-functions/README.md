# 🗄️ Atividade 10: Inteligência Analítica (Window Functions)

## 🎯 Estudo de Caso

A "SkyCargo" quer premiar os pilotos de drones mais eficientes de cada região. O problema é que um piloto em São Paulo realiza muito mais entregas que um piloto em uma cidade pequena, mas isso não significa que ele é mais "eficiente" dentro da realidade dele. Precisamos de um ranking que compare cada piloto **dentro da sua própria categoria/região**, sem misturar os dados.

## 🛠️ Necessidade Técnica

As **Window Functions (Funções de Janela)** permitem realizar cálculos que abrangem várias linhas, mas mantendo a identidade de cada linha individual (diferente do `GROUP BY`, que "esmaga" as linhas).

* **OVER():** Define a "janela" de observação.
* **PARTITION BY:** Divide o resultado em subconjuntos (ex: por região).
* **RANK() / ROW_NUMBER():** Atribui posições baseadas em uma ordenação.
* **LAG() / LEAD():** Acessa dados da linha anterior ou seguinte (essencial para séries temporais).

## ⚠️ Análise de Falha Crítica: Impactos de Performance em Window Functions

O uso de **Window Functions** em tabelas com milhões de registros pode ser custoso. Se não houver índices que suportem a cláusula `PARTITION BY` e `ORDER BY` dentro do `OVER()`, o banco de dados precisará realizar múltiplas passagens pelos dados e criar arquivos temporários em disco.

* **Impacto:** Aumento drástico no tempo de resposta de relatórios analíticos.
* **Prevenção:** Utilizar índices compostos que cubram as colunas de partição e ordenação da janela.

## 📋 Requisitos

1. Criar a tabela `desempenho_pilotos` (id, nome, regiao, entregas_realizadas).
2. Inserir uma massa de dados com pilotos de diferentes regiões (Norte, Sul, Sudeste).
3. Realizar 3 consultas de inteligência:
    * Ranking Geral de entregas.
    * **Ranking Regional:** Onde a posição reinicia para cada nova região (PARTITION BY).
    * **Percentual do Total:** Comparar as entregas do piloto com o total da sua região.

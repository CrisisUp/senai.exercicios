# 🗄️ Atividade 29: Teste de Estresse (Simulação de Carga Massiva)

## 🎯 Estudo de Caso

A "SkyCargo" vai lançar um novo modelo de drone global. Estimamos que ele gerará **1 milhão de logs** no primeiro dia. Antes de colocar em produção, precisamos "estressar" o banco de dados atual para descobrir em que ponto ele começa a ficar lento.

## 🛠️ Necessidade Técnica

* **Data Explosion:** Usaremos uma CTE Recursiva para gerar 1.000 registros base e um **CROSS JOIN** para multiplicar esse valor por 1.000, atingindo 1.000.000 de registros.
* **Benchmarking:** Usaremos o comando `.timer on` do SQLite para medir o tempo exato de cada operação.
* **Stress Audit:** Verificaremos o tamanho físico do arquivo após o estresse.

## 📋 Requisitos

1. Criar a tabela `estresse_logs` (id, drone_id, status).
2. Gerar 1 milhão de linhas de dados via SQL puro.
3. Medir o tempo de inserção.
4. Realizar uma busca por um ID específico e verificar se o índice ainda é eficiente sob o peso de 1 milhão de registros.

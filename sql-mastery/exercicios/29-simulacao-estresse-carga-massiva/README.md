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

## ⚠️ Análise de Falha Crítica

*   **Riscos de Performance Locks:** Durante a inserção massiva (Big Bang), o banco de dados pode ficar bloqueado para leitura por outros processos, especialmente se não estiver configurado para o modo WAL (Write-Ahead Logging).
*   **Vacuum Latency:** Após realizar um teste de estresse e deletar a massa de dados gerada, a necessidade de um `VACUUM` pode travar o banco de dados por um tempo desproporcional à duração do teste em si.
*   **Heap Bloat:** Se o teste for repetido várias vezes sem manutenção, o arquivo do banco de dados crescerá exponencialmente, resultando em "buracos" de alocação que degradam a localidade de referência dos dados no disco.
*   **Transaction Log Overflow:** Inserir 1 milhão de registros em uma única transação pode estourar o limite de tamanho do arquivo journal ou sobrecarregar a memória RAM dedicada aos buffers de transação.

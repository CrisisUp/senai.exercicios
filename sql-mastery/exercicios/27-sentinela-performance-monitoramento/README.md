# 🗄️ Atividade 27: Sentinela de Performance (Monitoramento e Alertas)

## 🎯 Estudo de Caso

O sistema da "SkyCargo" processa milhares de atualizações de GPS. O gerente quer ser avisado se:

1. Uma operação de escrita levar muito tempo para ser concluída (Latência).
2. O volume de dados em uma única transação for anormalmente alto (Sobrecarga).
Precisamos de um sistema que auto-gere alertas de performance para que o Engenheiro de SRE possa agir antes que o banco trave.

## 🛠️ Necessidade Técnica

* **Performance Logging:** Criaremos uma tabela para registrar o tempo inicial e final das operações.
* **Auto-Alert Trigger:** Um gatilho que observa a latência e, se ultrapassar o limite (ex: 500ms simulados), move o registro para uma tabela de `incidentes_performance`.
* **`unixepoch('subsec')`:** Usaremos a precisão de milissegundos do SQLite para medir a velocidade real.

## 📋 Requisitos

1. Criar a tabela `operacoes_rastreio` (id, operacao_nome, tempo_ms).
2. Criar a tabela `incidentes_performance` (id, operacao_nome, latencia_ms, criticidade).
3. Criar um **TRIGGER** que monitore a tabela de operações:
    * Se `tempo_ms > 500`, inserir em incidentes como 'ALTA'.
    * Se `tempo_ms > 200`, inserir como 'MÉDIA'.
4. Simular operações lentas e rápidas para testar o radar.

## ⚠️ Análise de Falha Crítica

*   **Riscos de Performance Locks:** O uso excessivo de triggers para monitoramento pode causar contenção de escrita, aumentando o tempo de bloqueio das tabelas principais durante transações pesadas.
*   **Vacuum Latency:** Em sistemas com alta rotatividade de logs de monitoramento, o `VACUUM` pode demorar significativamente, bloqueando o acesso ao banco de dados e aumentando a latência percebida pelo usuário final.
*   **Heap Bloat:** Tabelas de incidentes que crescem indefinidamente sem políticas de expurgo (TTL) causam fragmentação do arquivo de dados, prejudicando a performance de leitura e aumentando o consumo de disco desnecessariamente.
*   **Transaction Log Overflow:** O registro massivo de eventos de performance em uma única transação pode sobrecarregar o log de transações (journal/WAL), levando a falhas de commit ou lentidão extrema no checkpoint.

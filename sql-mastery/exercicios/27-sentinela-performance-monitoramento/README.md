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

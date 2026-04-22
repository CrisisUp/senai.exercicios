# 🗄️ Atividade 17: Rastreamento de Auditoria (Shadow Tables)

## 🎯 Estudo de Caso

A "SkyCargo" exige conformidade total. Se o nível de bateria de um drone for
alterado manualmente, precisamos saber: qual era o valor antigo, qual é o novo,
e em que momento isso aconteceu. Precisamos de um sistema de "Caixa Preta" para
o banco de dados que registre todas as modificações críticas sem que a aplicação
principal precise fazer nada.

## 🛠️ Necessidade Técnica

Uma **Trilha de Auditoria (Audit Trail)** é implementada usando Gatilhos que
observam mudanças:

* **OLD vs NEW:** No gatilho de `UPDATE`, temos acesso ao dado antes (`OLD`) e
* depois (`NEW`) da mudança.
* **Shadow Table:** Uma tabela que só recebe inserções do sistema de auditoria.
* **Imutabilidade:** A tabela de auditoria deve ser configurada para que ninguém
* (nem o admin) possa apagar os registros de log.

## 📋 Requisitos

1. Criar a tabela `configuracao_drones` (id, serial, firmware_versao).
2. Criar a tabela `auditoria_logs` (id, tabela_nome, registro_id, coluna,
valor_antigo, valor_novo, data_hora).
3. Criar um **TRIGGER** que dispare em cada `UPDATE` na tabela de configurações.
4. Demonstrar o registro automático de uma mudança de firmware.

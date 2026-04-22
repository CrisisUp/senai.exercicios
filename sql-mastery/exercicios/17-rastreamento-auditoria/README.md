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

## ⚠️ Análise de Falha Crítica

Sistemas de auditoria via Triggers, embora poderosos, apresentam riscos estruturais e de performance:

1.  **Latência de Escrita (Write Amplification):** Cada `UPDATE` na tabela principal gera um `INSERT` na shadow table. Em sistemas de alta frequência, isso dobra o custo de I/O e pode causar contenção de escrita, aumentando o tempo de resposta da aplicação.
2.  **Explosão de Armazenamento:** Se não houver uma política de purga ou arquivamento (como o `ATTACH` visto na Ativ. 16), a shadow table pode crescer exponencialmente, tornando-se muito maior que o banco de produção e dificultando manutenções.
3.  **Inconsistência de Esquema:** Se a estrutura da tabela principal mudar (ex: renomear uma coluna) e o Trigger não for atualizado, a auditoria pode falhar silenciosamente ou impedir atualizações legítimas por erros de sintaxe no gatilho.
4.  **Bypass de Auditoria:** Ferramentas de importação em massa ou comandos de sistema que desabilitam triggers podem permitir alterações sem rastro. A segurança deve ser complementada por permissões de arquivo no SO.


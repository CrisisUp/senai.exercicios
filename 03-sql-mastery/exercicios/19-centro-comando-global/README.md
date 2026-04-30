# 🗄️ Atividade 19: Centro de Comando Global (Consolidação Multi-Banco)

## 🎯 Estudo de Caso

A diretoria da "SkyCargo" quer um relatório que una o **Inventário de Peças** (Ativ. 01), a **Frota de Drones** (Ativ. 12) e a **Inteligência de Rotas** (Ativ. 18). Precisamos saber se temos as peças necessárias no estoque para os drones que estão operando nas rotas mais longas.

## 🛠️ Necessidade Técnica

Usaremos a **Federação de Dados**:

* **ATTACH DATABASE:** Conectaremos múltiplos arquivos `.db` simultaneamente.
* **Cross-Database JOIN:** Realizaremos consultas que unem tabelas de arquivos físicos diferentes.
* **CTE de Consolidação:** Organizaremos o relatório final para que o usuário não precise saber de onde vem cada dado.

## 📋 Requisitos

1. Criar o banco central `comando_global.db`.
2. Anexar o banco de **Estoque** (Atividade 01).
3. Anexar o banco de **Frota** (Atividade 12).
4. Anexar o banco de **Rotas** (Atividade 18).
5. Realizar uma query que mostre: Drone (Frota) + Rota sugerida (Rotas) + Peça em estoque compatível (Estoque).

## ⚠️ Análise de Falha Crítica

A federação de dados e consolidação multi-banco (Centro de Comando) enfrenta desafios críticos de sincronização e acoplamento:

1.  **Divergência de Temporalidade:** Como os bancos de dados (Estoque, Frota, Rotas) são arquivos independentes, eles podem estar em estados temporais diferentes. Um relatório consolidado pode sugerir uma peça que acabou de ser vendida ou um drone que foi aposentado, se os processos de sincronização falharem.
2.  **Quebra de Referência (Foreign Key across DB):** O SQLite não suporta chaves estrangeiras que cruzam bancos de dados diferentes via `ATTACH`. Isso significa que a integridade referencial deve ser garantida via código ou triggers complexos, aumentando o risco de dados órfãos.
3.  **Dependência de Caminhos Relativos:** A consolidação depende de caminhos de arquivos (`../diretorio/banco.db`). Se a estrutura de pastas do servidor mudar, o "Centro de Comando" para de funcionar imediatamente, exigindo manutenção manual pesada.
4.  **Conflitos de Bloqueio (Lock Contention):** Embora os bancos sejam separados, uma transação global que anexa todos eles pode ser bloqueada se qualquer um dos arquivos estiver sofrendo um `VACUUM` ou uma escrita pesada por outro processo.


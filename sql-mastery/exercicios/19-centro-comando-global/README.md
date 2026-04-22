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

# 🗄️ Atividade 24: Engenharia ETL (Importação CSV e Exportação)

## 🎯 Estudo de Caso

A "SkyCargo" adquiriu uma pequena empresa de logística regional. Eles enviaram uma planilha de fornecedores em formato **CSV** (Comma Separated Values). Precisamos carregar esses milhares de registros para o nosso banco de dados SQLite de forma ultra-rápida. Além disso, a auditoria exigiu um **Backup em formato SQL** (Dump) que possa ser lido por qualquer outro banco de dados do mundo.

## 🛠️ Necessidade Técnica

O processo de **ETL (Extract, Transform, Load)** é a base do trabalho de um Engenheiro de Dados:

* **.import:** Comando do SQLite para ler arquivos de texto e inseri-los em uma tabela instantaneamente.
* **.mode csv:** Configura o terminal para entender o formato de planilhas.
* **.output:** Redireciona o resultado de uma query para um arquivo físico.
* **.dump:** Gera o script SQL completo para reconstruir o banco do zero (essencial para migrações e backups).

## 📋 Requisitos

1. Criar um arquivo chamado `fornecedores_externos.csv` com dados simulados.
2. Utilizar o terminal do SQLite para importar este CSV para uma nova tabela.
3. Realizar uma limpeza nos dados importados (Transformação).
4. Exportar o resultado de uma consulta de "Drones em Perigo" para um arquivo chamado `alerta_hoje.csv`.
5. Gerar um arquivo `backup_total.sql` usando o comando dump.

---

## 🛡️ ANÁLISE DE FALHA CRÍTICA (Fase 3)

1. **ETL CORRUPTION:** A importação massiva via `.import` não valida `CHECK constraints` por padrão em versões antigas ou se não houver triggers. Isso pode resultar em "Silent Data Corruption", onde dados inválidos entram no banco sem disparar erros imediatos.
2. **DELIMITER COLLISION:** Se o campo `contato` ou `nome` contiver uma vírgula (mesmo delimitador do CSV) e não estiver devidamente escapado com aspas, o motor de importação deslocará as colunas, corrompendo a integridade referencial da linha.
3. **ENCODING MISMATCH:** Arquivos CSV gerados em Windows (CP1252/ISO-8859-1) importados em sistemas Linux/Unix (UTF-8) podem causar caracteres "mojibake" (quebrados), invalidando buscas textuais e relatórios de auditoria.


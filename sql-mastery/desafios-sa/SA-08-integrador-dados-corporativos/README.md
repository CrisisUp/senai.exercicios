# 📊 SA-08: O Integrador de Dados Corporativos (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyCargo" adquiriu uma nova frota e recebeu os dados em arquivos CSV brutos. Precisamos de um processo de **Carga e Inteligência** que importe esses dados, trate conflitos de seriais duplicados e entregue um relatório mensal pivotado para a diretoria financeira.

## 🛠️ Necessidade Técnica

Este desafio integra as Atividades 22 a 24:

1. **Engenharia ETL (Ativ. 24):** Importar dados externos de uma planilha.
2. **Resolução de Conflitos (Ativ. 23):** Usar `INSERT OR REPLACE` para garantir que os dados mais novos da planilha sobrescrevam os antigos.
3. **Pivoteamento (Ativ. 22):** Transformar o faturamento mensal em colunas para comparação rápida entre tipos de drones.

## 📋 Requisitos Funcionais

1. Criar o banco `logistica_corporativa.db`.
2. Importar o arquivo `carga_externa.csv` para uma tabela temporária.
3. Mover os dados para a tabela `faturamento_frota` usando a política de resolução de conflitos `REPLACE`.
4. Gerar um relatório analítico que mostre o lucro por Categoria (Resgate, Carga) dividido em colunas por Mês.

## ⚠️ Análise de Falha Crítica (ETL & Corporate Analytics)

A integração de dados externos é o ponto mais vulnerável de um pipeline de BI corporativo:

1.  **Riscos de Performance de Window Functions:** Ao tentar calcular o crescimento percentual mês a mês usando `LAG()` sobre dados importados massivamente, a falta de índices na chave composta (categoria, mes) pode tornar a geração de relatórios de fechamento mensal extremamente lenta, atrasando decisões executivas.
2.  **Corrupção Massiva durante o Import:** O uso de `.import` sem uma transação explícita que envolva a limpeza da tabela temporária e a inserção final pode deixar o banco em estado inconsistente se o processo for interrompido, resultando em dados duplicados ou parciais que invalidam os balanços financeiros.
3.  **Data Leaks em Arquivos Temporários:** Arquivos CSV brutos usados para carga (`carga_externa.csv`) frequentemente contêm dados sensíveis. Se não forem deletados ou protegidos após o processo de ETL, representam um risco de vazamento de informações estratégicas da frota para usuários do sistema de arquivos.
4.  **Inconsistência de Backup Pós-Carga:** Realizar um backup imediatamente após uma carga massiva sem garantir que o checkpoint do WAL (Write-Ahead Log) tenha sido concluído pode resultar em um backup que não contém os dados recém-importados, levando a uma falsa sensação de segurança de dados.

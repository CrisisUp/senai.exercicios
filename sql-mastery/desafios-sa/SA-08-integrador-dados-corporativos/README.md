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

# ⚡ Atividade 05

- **DynamoDB** - Bancos NoSQL de Alta Performance
- `STATUS:` Padrão de Engenharia de Elite Aplicado

## 🎯 Estudo de Caso

A "SkyCargo" precisa rastrear a posição exata de milhares de drones em tempo
real. Um banco relacional (RDS) teria dificuldades com a altíssima frequência
de escrita simultânea. Usaremos o **Amazon DynamoDB**, um banco de dados NoSQL
chave-valor, para armazenar as coordenadas geográficas de cada drone com
latência mínima.

## 🛠️ Necessidade Técnica

O **DynamoDB** é um serviço Serverless. Você não escolhe CPU ou RAM; você define
a capacidade de leitura e escrita (ou usa o modo On-Demand).

- **Tabelas:** Diferente do SQL, não há esquemas rígidos (Schema-less).
- **Partition Key (PK):** A chave principal usada para distribuir dados.
- **Sort Key (SK):** Chave secundária para organizar itens com a mesma PK.
- **Escalabilidade:** Suporta trilhões de linhas sem perda de performance.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL ARQUITETURA NoSQL)

- RISCO DE HOT PARTITION: Se todos os drones enviarem dados para a mesma chave
  de partição ao mesmo tempo, aquele "pedaço" do banco ficará sobrecarregado,
  causando erros de `ProvisionedThroughputExceededException`.
- RISCO DE SCAN OVERHEAD: Realizar um `Scan` (ler a tabela inteira) em um banco
  NoSQL é uma falha de design grave que consome toda a performance e gera custos
  altos. Um Engenheiro de Elite projeta para usar `Query` (busca via chave).
- RISCO DE DATA INCONSISTENCY: Por padrão, o DynamoDB usa "Leitura Eventualmente
  Consistente". Em missões críticas, deve-se habilitar a "Leitura Fortemente
  Consistente" para garantir que o dado lido é a versão mais recente.

## 📋 Requisitos de Elite

1. Criação de uma tabela `DroneTelemetry` via CLI.
2. Definição de `DroneID` como Partition Key e `Timestamp` como Sort Key.
3. Inserção de itens (PutItem) simulando telemetria de voo.
4. Consulta otimizada (Query) para buscar o histórico de um drone específico.

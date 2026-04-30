# 🗄️ Atividade 15: Otimização de Espaço e Cálculo (Índices Parciais e Colunas Virtuais)

## 🎯 Estudo de Caso

A frota da "SkyCargo" possui 10.000 drones, mas apenas 5% deles estão em estado
"Crítico" no momento. O administrador do banco notou que o índice de busca está
ocupando muita memória RAM. Queremos criar um índice que aponte APENAS para os
drones em perigo. Além disso, precisamos calcular o "Score de Saúde"
(Bateria * Horas de Voo) constantemente, e queremos que esse cálculo seja
otimizado sem ocupar espaço extra em disco.

## 🛠️ Necessidade Técnica

No **Nível 40 (Lead Data Architect)**, otimizamos cada byte do servidor:

* **Índices Parciais (Partial Indexes):** Criamos um índice com uma cláusula
* `WHERE`. O índice ignora as linhas que não interessam (ex: ignora drones
* saudáveis), economizando até 90% de espaço.
* **Colunas Geradas (Generated Columns):** Colunas que são calculadas
automaticamente a partir de outras.
* **VIRTUAL:** O valor é calculado apenas no SELECT (economiza disco).
* **STORED:** O valor é calculado no INSERT e gravado (mais rápido na leitura,
ocupa disco).

## 📋 Requisitos

1. Criar a tabela `status_frota` com `id`, `serial`, `bateria` e `horas_voo`.
2. Adicionar uma **Coluna Virtual** chamada `score_saude` que faz o cálculo automático.
3. Criar um **Índice Parcial** que indexa apenas drones com `bateria < 20`.
- Realizar consultas e auditar o plano de execução para provar a otimização.

## ⚠️ Análise de Falha Crítica

A otimização extrema via índices parciais e colunas virtuais exige um equilíbrio entre CPU, RAM e Disco:

1.  **Trade-off de CPU (Virtual Columns):** Colunas do tipo `VIRTUAL` economizam espaço em disco, mas consomem ciclos de CPU em **cada leitura**. Em sistemas com alto tráfego de `SELECT`, isso pode se tornar um gargalo de processamento.
2.  **Abismo de Performance (Index Miss):** Um índice parcial é invisível para consultas que não atendem exatamente aos seus critérios de `WHERE`. Se um desenvolvedor mudar a query de `bateria < 20` para `bateria < 21`, o banco pode ignorar o índice e realizar um **Full Table Scan**, derrubando a performance.
3.  **Rigidez de Esquema:** Colunas geradas não podem ser alteradas facilmente. Se a fórmula do `score_saude` mudar, pode ser necessário recriar a tabela inteira, o que é um risco em bancos de dados em produção.
4.  **Limitação de Funções:** O SQLite não permite o uso de funções não-determinísticas (como `date('now')`) ou subconsultas em colunas geradas, limitando cálculos que dependem de fatores externos ou outras tabelas.


# 📑 Guia de Interação: SA-08 (Integrador Corporativo)

Use este guia para importar dados e gerar relatórios de Business Intelligence.

### 🛠️ 1. Configuração de Carga
```sql
.mode csv
.headers on
```

---

### 📥 2. Processo ETL e Resolução de Conflitos

#### Passo A: Importar a Planilha Externa
Execute este comando para carregar os dados brutos para uma tabela temporária de auditoria.
```sql
.import --skip 1 carga_externa.csv faturamento_temp
```

#### Passo B: Carga com Inteligência (REPLACE)
Este comando move os dados da tabela temporária para a definitiva. Se um drone já tiver um lucro registrado para aquele mês, o valor da planilha (mais novo) substituirá o antigo.
```sql
INSERT OR REPLACE INTO faturamento_frota (serial, categoria, mes, lucro)
SELECT serial, categoria, mes, lucro FROM faturamento_temp;
```

---

### 📈 3. Relatório Executivo (Pivot)

#### Desafio: Dashboard Financeiro por Setor
Agora que os dados foram limpos e carregados, veja o lucro mensal organizado por colunas.
```sql
SELECT * FROM v_dashboard_mensal;
```

---

### 🚪 4. Como Sair
```sql
.exit
```

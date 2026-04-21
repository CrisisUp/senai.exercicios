# 📑 Guia de Interação: Atividade 08 (Consultas Complexas com CTE)

Use este guia para realizar análises financeiras avançadas e modulares no terminal.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 📊 2. Consultas Analíticas (WITH / CTE)

#### Desafio: Relatório de Desempenho Mensal vs. Média Geral

Copie este bloco inteiro. Note como as subconsultas estão organizadas no topo.

```sql
WITH 
    faturamento_mensal AS (
        SELECT strftime('%m', data_venda) AS mes, SUM(valor) AS total_mes
        FROM vendas
        GROUP BY mes
    ),
    media_global AS (
        SELECT AVG(total_mes) AS media_anual
        FROM faturamento_mensal
    )
SELECT f.mes AS "Mês",
       f.total_mes AS "Faturamento (R$)",
       ROUND(m.media_anual, 2) AS "Média Geral (R$)",
       ROUND(f.total_mes - m.media_anual, 2) AS "Variação"
FROM faturamento_mensal f, media_global m;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

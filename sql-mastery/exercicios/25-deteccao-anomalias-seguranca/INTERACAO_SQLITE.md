# 📑 Guia de Interação: Atividade 25 (Radar de Segurança)

Use este guia para identificar ataques cibernéticos e fraudes no terminal.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🛡️ 2. Inteligência Forense

#### Desafio A: Detectar Ataque de Força Bruta (Delta Time)

Este comando calcula quantos segundos se passaram entre as falhas de login. Note o valor **1** no delta do hacker. Isso indica um ataque automatizado.

```sql
SELECT usuario, data_hora,
       unixepoch(data_hora) - unixepoch(LAG(data_hora) OVER(PARTITION BY usuario ORDER BY data_hora)) AS delta_seg
FROM acessos_sistema
WHERE status = 'FALHA';
```

#### Desafio B: Detectar Anomalia de Valor (Outliers)

Este comando compara cada gasto com a média geral do drone. Note o drone X-10 com um gasto de 5.000 (o alerta de fraude será disparado).

```sql
WITH stats AS (
    SELECT drone_id, valor, AVG(valor) OVER(PARTITION BY drone_id) AS media
    FROM transacoes_financeiras
)
SELECT *, 
       CASE WHEN valor > (media * 3) THEN 'ALERTA: FRAUDE' ELSE 'OK' END AS Status
FROM stats;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

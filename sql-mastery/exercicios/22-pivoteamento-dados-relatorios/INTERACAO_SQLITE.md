# 📑 Guia de Interação: Atividade 22 (Pivoteamento)

Use este guia para transformar listas longas em planilhas executivas no terminal.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 📊 2. Relatórios de Tabela Cruzada (Pivot)

#### Desafio: Dashboard Trimestral de Lucro por Categoria

Este comando reorganiza os dados para que você possa comparar o lucro de cada mês lado a lado por setor.

```sql
SELECT categoria AS "Setor",
       SUM(CASE WHEN mes = 'Jan' THEN lucro ELSE 0 END) AS "Janeiro",
       SUM(CASE WHEN mes = 'Fev' THEN lucro ELSE 0 END) AS "Fevereiro",
       SUM(CASE WHEN mes = 'Mar' THEN lucro ELSE 0 END) AS "Março",
       SUM(lucro) AS "Total_Q1"
FROM operacoes_voo
GROUP BY categoria
ORDER BY "Total_Q1" DESC;
```

#### Dica de Leitura

Observe como o setor **"Agro"** teve um salto gigantesco em Março (de 3.000 para 12.000). Em um relatório normal (por linhas), seria mais difícil notar essa explosão de crescimento comparada aos outros meses.

---

### 🚪 3. Como Sair

```sql
.exit
```

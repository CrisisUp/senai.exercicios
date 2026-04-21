# 📑 Guia de Interação: Atividade 10 (Window Functions)

Use este guia para testar as queries de inteligência analítica no terminal.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🏆 2. Rankings e Inteligência

#### Desafio A: Ranking Geral de Pilotos

Apenas numera todos os pilotos do maior para o menor número de entregas.

```sql
SELECT nome, entregas,
       ROW_NUMBER() OVER(ORDER BY entregas DESC) AS "Posição Geral"
FROM desempenho_pilotos;
```

#### Desafio B: Ranking por Região (Medalhas Locais)

Note que Ana e Roberto são ambos "1º lugar" em suas respectivas regiões.

```sql
SELECT regiao, nome, entregas,
       RANK() OVER(PARTITION BY regiao ORDER BY entregas DESC) AS "Posição na Região"
FROM desempenho_pilotos;
```

#### Desafio C: Percentual de Contribuição Regional

Calcula quanto cada piloto representa das entregas totais da sua região.

```sql
SELECT nome, regiao, entregas,
       SUM(entregas) OVER(PARTITION BY regiao) AS "Total Regional",
       ROUND(CAST(entregas AS REAL) * 100 / SUM(entregas) OVER(PARTITION BY regiao), 2) AS "% do Setor"
FROM desempenho_pilotos
ORDER BY regiao, "% do Setor" DESC;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

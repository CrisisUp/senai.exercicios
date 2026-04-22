# 📑 Guia de Interação: SA-07 (Portal de Inteligência)

Use este guia para operar o Dashboard Integrado da SkyCargo.

## 🛠️ 1. Configuração de Elite

```sql
.mode table
.headers on
ATTACH DATABASE '../../exercicios/01-explorador-estoque/database.db' AS estoque;
```

---

### 📉 2. Analítica Avançada

#### Desafio A: Relatório de Média Móvel (Detecção de Tendência)

Este comando calcula o desempenho do drone nas últimas 3 missões.

```sql
SELECT drone_id, distancia,
       ROUND(AVG(distancia) OVER(
           PARTITION BY drone_id 
           ORDER BY data_consolidacao 
           ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
       ), 2) AS "Média_Movel"
FROM consolidado_missao;
```

#### Desafio B: Tabela Cruzada de Regiões (Pivot Executivo)

```sql
SELECT 'Distância Total' AS Métrica,
       SUM(CASE WHEN regiao = 'Americas' THEN distancia ELSE 0 END) AS AMERICAS,
       SUM(CASE WHEN regiao = 'Europa' THEN distancia ELSE 0 END) AS EUROPA,
       SUM(CASE WHEN regiao = 'Asia' THEN distancia ELSE 0 END) AS ASIA
FROM consolidado_missao;
```

---

### 🛡️ 3. Teste de Segurança (Invasão)

#### Desafio C: Tentar apagar um registro consolidado

O banco deve barrar você usando o Trigger de Fortaleza que criamos.

```sql
DELETE FROM consolidado_missao WHERE drone_id = 'X-01';
```

---

### 🚪 4. Como Sair

```sql
.exit
```

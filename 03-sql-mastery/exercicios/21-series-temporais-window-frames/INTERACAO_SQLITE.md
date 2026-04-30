# 📑 Guia de Interação: Atividade 21 (Média Móvel)

Use este guia para detectar anomalias de energia no drone.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 📈 2. Análise de Séries Temporais

#### Desafio: Calcular a Média Móvel de Bateria

Este comando cria uma "janela deslizante" que olha sempre para as 3 leituras
mais recentes para detectar tendências de queda.

```sql
SELECT data_hora,
       nivel_bateria AS "Atual",
       ROUND(AVG(nivel_bateria) OVER(
           ORDER BY data_hora 
           ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
       ), 2) AS "Média_3pts",
       ROUND(nivel_bateria - AVG(nivel_bateria) OVER(
           ORDER BY data_hora 
           ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
       ), 2) AS "Variação"
FROM leituras_bateria;
```

### Dica de Ouro

Observe o resultado na linha das **10:05:00**. O desvio será um número negativo
maior, indicando que o drone está consumindo energia de forma anormal naquele
minuto específico.

---

### 🚪 3. Como Sair

```sql
.exit
```

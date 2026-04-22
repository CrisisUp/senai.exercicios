# 📑 Guia de Interação: SA-08 (O Guardião)

Use este guia para operar a fortaleza cibernética da SkyCargo.

## 🛠️ 1. Configuração de Comando

```sql
.mode table
.headers on
.timer on
```

---

### 🕵️ 2. Inteligência e Segurança

#### Desafio A: O Radar de Segurança em Tempo Real

Consulte a tabela de alertas. Veja que o banco de dados detectou o ataque do "Hacker_Bot" e a lentidão do sistema simultaneamente.

```sql
SELECT * FROM alertas_seguranca;
```

#### Desafio B: Auditoria de Manutenção (Resiliência)

Veja como as etapas de manutenção foram registradas. Note que a etapa que deu
"FALHA" sumiu da história, pois o banco voltou no tempo para o Checkpoint seguro.

```sql
SELECT * FROM manutencao_critica;
```

---

### 🌍 3. Operações Globais

#### Desafio C: Faturamento Convertido (Cross-DB)

Imagine uma entrega que custou 50 Dólares. Como converter para Reais usando a nossa tabela de câmbio?

```sql
SELECT 'SN-X10' AS Drone, 
       50.0 AS Custo_USD,
       50.0 * taxa_brl AS Total_BRL
FROM cambio WHERE moeda = 'USD';
```

---

### 🚪 4. Como Sair

```sql
.exit
```

# 📑 Guia de Interação: Atividade 26 (Câmbio e Fusos)

Use este guia para operar a logística internacional da SkyCargo no terminal.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🌐 2. Relatórios Globais

#### Desafio: Dashboard de Normalização de Tempo e Moeda

Note como os drones SN-LND e SN-SP registraram o voo no MESMO instante UTC
(12:00), mas para os pilotos locais, o horário era completamente diferente.

```sql
SELECT drone_id AS Drone,
       data_utc AS "Universal_UTC",
       datetime(data_utc, '+1 hours') AS "Londres_LND",
       datetime(data_utc, '-3 hours') AS "Sao_Paulo_BR",
       custo_local || ' ' || e.moeda AS Valor_Local,
       'R$ ' || ROUND(custo_local * t.taxa_para_brl, 2) AS Convertido_BRL
FROM entregas_globais e
JOIN taxas_cambio t ON e.moeda = t.moeda;
```

#### Dica de Engenheiro

Se você quiser saber que horas são em São Paulo **agora**, digite:

```sql
SELECT datetime('now', '-3 hours') AS "Hora_Atual_SP";
```

---

### 🚪 3. Como Sair

```sql
.exit
```

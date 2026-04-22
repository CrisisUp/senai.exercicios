# 📑 Guia de Interação: SA-03 (Manutenção Preventiva)

Use este guia para operar o sistema de manutenção automática da SkyCargo.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🤖 2. Automação e Auditoria

#### Passo A: Registrar um Voo Curto

Registre um voo de 2 horas para o drone 3 (C-Agro 12). Observe que o horímetro
dele mudará sozinho na tabela `frota_drones`.

```sql
INSERT INTO log_voos (drone_id, horas_viagem) VALUES (3, 2.0);
SELECT * FROM frota_drones;
```

#### Passo B: Disparar Alerta de Manutenção

O drone 1 (X-Resgate 01) já está com muitas horas. Registre um voo de apenas
1 hora para ele. O banco perceberá que ele passou de 100h e gerará um alerta
automático.

```sql
INSERT INTO log_voos (drone_id, horas_viagem) VALUES (1, 1.0);
SELECT * FROM alertas_manutencao;
```

#### Passo C: Auditoria de Performance

Verifique se a busca no histórico de voos está usando o índice que criamos.

```sql
EXPLAIN QUERY PLAN 
SELECT * FROM log_voos WHERE drone_id = 1;
```

---

### 📈 3. Relatórios Estratégicos (CTE)

#### Desafio: Análise de Desgaste da Frota

Este relatório usa uma tabela temporária (WITH) para calcular quem está voando
acima da média da empresa.

```sql
WITH 
    media_uso AS (
        SELECT AVG(horas_totais) as media_frota FROM frota_drones
    )
SELECT d.modelo, 
       d.horas_totais AS "Acumulado",
       ROUND(m.media_frota, 2) AS "Média Empresa",
       CASE 
          WHEN d.horas_totais > m.media_frota THEN 'ALTO DESGASTE'
          ELSE 'ESTÁVEL'
       END AS "Diagnóstico"
FROM frota_drones d, media_uso m;
```

---

### 🚪 4. Como Sair

```sql
.exit
```

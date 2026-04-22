# 📑 Guia de Interação: Atividade 29 (Explosão de Dados)

Use este guia para realizar um teste de estresse massivo no seu terminal.

## 🛠️ 1. Configuração de Benchmarking

```sql
.mode table
.headers on
.timer on      -- Ativa o cronômetro para medir milissegundos
```

---

### 💥 2. A Explosão (Simulando 1 Milhão de Linhas)

#### Passo A: Gerar a Massa de Dados

Este comando vai levar entre 2 e 5 segundos dependendo da velocidade do seu computador. Ele está criando 1 milhão de registros de uma só vez.

```sql
WITH RECURSIVE gerador(n) AS (
    SELECT 1 UNION ALL SELECT n + 1 FROM gerador WHERE n < 1000
)
INSERT INTO estresse_logs (drone_id, msg)
SELECT 'DRONE-' || a.n, 'Log_Massivo_' || b.n
FROM gerador a CROSS JOIN gerador b;
```

#### Passo B: Validar o Volume

```sql
SELECT count(*) AS "Total de Linhas no Banco" FROM estresse_logs;
```

---

### ⚡ 3. Teste de Busca (Mestria de Performance)

#### Desafio: Buscar um drone específico no meio de 1 milhão

Note o tempo que o SQLite leva para responder. Graças ao índice `idx_estresse_drone`, o tempo deve ser próximo de **0.000 segundos**.

```sql
SELECT * FROM estresse_logs WHERE drone_id = 'DRONE-777' LIMIT 10;
```

#### Comparação: Busca sem Índice (O Lento)

Tente buscar pela mensagem (que não tem índice). Note como o banco demora muito mais, pois precisa ler 1 milhão de linhas (SCAN).

```sql
SELECT * FROM estresse_logs WHERE msg = 'Log_Massivo_500' LIMIT 1;
```

---

### 🚪 4. Como Sair

```sql
.exit
```

# 📑 Guia de Interação: SA-05 (Hub IoT)

Use este guia para operar o sistema de inteligência e busca avançada.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 📡 2. Monitoramento e Busca Avançada

#### Desafio A: Busca Híbrida (Texto + JSON)

Este comando integra o motor FTS5 com a extração de dados JSON. Ele busca drones
que reportaram falhas E que estão com bateria baixa.

```sql
SELECT t.serial, 
       json_extract(t.dados_json, '$.bateria') AS "Bateria %",
       b.relatorio_texto AS "Relato"
FROM telemetria_iot t
JOIN busca_relatorios b ON t.serial = b.serial
WHERE b.relatorio_texto MATCH 'falha'
  AND json_extract(t.dados_json, '$.bateria') < 20;
```

#### Desafio B: Atualização via UPSERT

Tente "curar" o drone SN-002 enviando um novo JSON. Note como o registro é
atualizado automaticamente pelo conflito do serial.

```sql
INSERT INTO telemetria_iot (serial, dados_json) 
VALUES ('SN-002', '{"bateria": 100, "status": "reparado"}')
ON CONFLICT(serial) DO UPDATE SET dados_json = excluded.dados_json;

SELECT * FROM telemetria_iot WHERE serial = 'SN-002';
```

#### Desafio C: Auditoria de Performance

Verifique que a busca de emergência utiliza o nosso Índice Parcial.

```sql
EXPLAIN QUERY PLAN 
SELECT * FROM telemetria_iot WHERE json_extract(dados_json, '$.bateria') < 15;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

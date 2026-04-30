# 📑 Guia de Interação: SA-10 (O Monumento)

Este é o seu guia definitivo para operar o Ecossistema Global da SkyCargo.

## 🛠️ 1. Configuração de Comando

```sql
.mode table
.headers on
PRAGMA foreign_keys = ON;
```

---

### 📥 2. Engenharia ETL (Importação Massiva)

#### Passo A: Criar Tabela Temporária para o CSV

```sql
CREATE TEMP TABLE voos_temp (
    serial TEXT,
    distancia REAL,
    bateria INTEGER,
    status TEXT
);
```

#### Passo B: Importar os dados do arquivo

```sql
.import --csv --skip 1 voos_externos.csv voos_temp
```

#### Passo C: Mover para o Histórico Principal (Lógica de Produção)

Este comando converte o texto do CSV em JSON estruturado dinamicamente durante a inserção!

```sql
INSERT INTO historico_operacoes (drone_id, distancia, telemetria_json)
SELECT d.id, t.distancia, json_object('bateria', t.bateria, 'status_msg', t.status)
FROM voos_temp t
JOIN drones d ON t.serial = d.serial;
```

---

### 📉 3. Inteligência Preditiva e Rankings

#### Desafio A: Consultar o Dashboard de Elite (Window Functions)

Veja a média móvel de performance e o rank global de distância.

```sql
SELECT * FROM v_dashboard_elite;
```

#### Desafio B: Explorar Hierarquia (Recursividade)

Visualize a árvore de peças de um drone específico.

```sql
WITH RECURSIVE arvore AS (
    SELECT id, nome, 0 as nivel FROM componentes WHERE pai_id IS NULL AND drone_id = 1
    UNION ALL
    SELECT c.id, c.nome, a.nivel + 1 FROM componentes c JOIN arvore a ON c.pai_id = a.id
)
SELECT nivel, printf('%' || (nivel*3) || 's', '') || nome as Estrutura FROM arvore;
```

---

### 🛡️ 4. Teste de Blindagem (Security)

#### Desafio C: Tentar mudar status de drone em missão

O banco de dados deve barrar a alteração do drone 'SN-B22' porque o Trigger de segurança está ativo.

```sql
UPDATE drones SET status = 'OCIOSO' WHERE serial = 'SN-B22';
```

---

### 🛡️ 5. Backup e Auditoria

Gere o script completo de recuperação.

```sql
.once backup_final.sql
.dump
```

---

### 🚪 6. Como Sair

```sql
.exit
```

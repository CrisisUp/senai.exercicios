# 📑 Guia de Interação: Atividade 23 (Resolução de Conflitos)

Use este guia para ver como o banco de dados escolhe qual dado deve prevalecer.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🥊 2. Resolvendo Conflitos (Luta de Dados)

#### Desafio A: O Comando IGNORE (Preservar o Antigo)

Tente inserir um valor para um serial que já existe usando o IGNORE. Note que o
banco não dá erro, mas o valor **permanece o antigo**.

```sql
INSERT OR IGNORE INTO frota_internacional (serial, horas_voo) VALUES ('DRONE-GLOBAL-01', 500.0);
SELECT * FROM frota_internacional;
```

#### Desafio B: O Comando REPLACE (Sobrescrever tudo)

Agora use o REPLACE. Note que o valor das horas mudará para 750, mas preste atenção no **ID**: ele provavelmente mudou, pois o banco deletou a linha e criou uma nova.

```sql
INSERT OR REPLACE INTO frota_internacional (serial, horas_voo) VALUES ('DRONE-GLOBAL-01', 750.0);
SELECT * FROM frota_internacional;
```

#### Desafio C: Testando o ROLLBACK (Cancelamento Total)

Vamos tentar fazer algo errado dentro de uma transação.

```sql
BEGIN TRANSACTION;
    INSERT INTO frota_internacional (serial, horas_voo) VALUES ('DRONE-NOVO', 10.0);
    -- Este comando abaixo vai falhar (horas negativas) e cancelar a transação?
    INSERT OR ROLLBACK INTO frota_internacional (serial, horas_voo) VALUES ('DRONE-RUIM', -5.0);
-- Se você consultar agora, o 'DRONE-NOVO' não deve existir, pois o ROLLBACK desfez tudo.
SELECT * FROM frota_internacional;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

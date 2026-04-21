# 📑 Guia de Interação: Atividade 06 (Transações)

Use este guia para praticar o controle de integridade (ACID) no terminal.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🛡️ 2. Praticando Transações

#### Cenário A: Transferência com Sucesso (COMMIT)

Execute este bloco para ver como o banco processa dois comandos como se fossem um só.

```sql
BEGIN TRANSACTION;
    UPDATE estoque_geral SET quantidade = quantidade - 10 WHERE item = 'Bateria Lipo 4S';
    UPDATE carga_drone SET quantidade = quantidade + 10 WHERE item = 'Bateria Lipo 4S';
COMMIT;
```

#### Cenário B: Cancelando uma Operação com Erro (ROLLBACK)

Execute este bloco. Note que alteramos o estoque para zero, mas como damos o ROLLBACK, o valor voltará ao que era antes.

```sql
BEGIN TRANSACTION;
    UPDATE estoque_geral SET quantidade = 0 WHERE item = 'Bateria Lipo 4S';
    SELECT * FROM estoque_geral; -- Você verá o estoque zerado "no rascunho"
ROLLBACK;
```

#### Cenário C: Verificação de Integridade

Verifique que o ROLLBACK realmente funcionou e o COMMIT também.

```sql
SELECT * FROM estoque_geral;
SELECT * FROM carga_drone;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

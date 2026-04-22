# 📑 Guia de Interação: SA-02 (Faturamento e Auditoria)

Use este guia para testar o sistema de faturamento integrado.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 💰 2. Operação de Venda Blindada (Transação)

#### Passo A: Simular uma falha (ROLLBACK)

Tente registrar uma venda mas cancele no final. Note que o estoque NÃO mudará.

```sql
BEGIN TRANSACTION;
    INSERT INTO pedidos (data_faturamento) VALUES ('2026-04-21');
    INSERT INTO itens_pedido (pedido_id, produto, valor_unitario, quantidade, imposto_valor) 
    VALUES (2, 'Hélice Carbono', 85.0, 10, 8.5);
    UPDATE estoque_geral SET quantidade = quantidade - 10 WHERE item = 'Hélice Carbono';
ROLLBACK;
```

#### Passo B: Registrar Venda Real (COMMIT)

```sql
BEGIN TRANSACTION;
    INSERT INTO pedidos (data_faturamento) VALUES ('2026-04-21');
    INSERT INTO itens_pedido (pedido_id, produto, valor_unitario, quantidade, imposto_valor) 
    VALUES (2, 'Hélice Carbono', 85.0, 5, 8.5);
    UPDATE estoque_geral SET quantidade = quantidade - 5 WHERE item = 'Hélice Carbono';
COMMIT;
```

---

### 📈 3. Auditoria e Relatórios (Views)

#### Consulta: Dashboard Financeiro Consolidado

Note como a View simplifica cálculos complexos de impostos e lucros.

```sql
SELECT * FROM v_auditoria_financeira;
```

#### Consulta: Conferência de Estoque Pós-Venda

```sql
SELECT * FROM estoque_geral;
```

---

### 🚪 4. Como Sair

```sql
.exit
```

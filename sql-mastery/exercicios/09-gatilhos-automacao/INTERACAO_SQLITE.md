# 📑 Guia de Interação: Atividade 09 (Automação com Triggers)

Use este guia para ver o banco de dados agindo sozinho no seu terminal.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🤖 2. Automação em Ação

#### Passo A: Verificar o Estoque Inicial

Observe quanto temos de cada item.

```sql
SELECT * FROM produtos_estoque;
```

#### Passo B: Registrar uma Venda (Disparando o Gatilho)

Note que nós vamos apenas inserir o registro na tabela de vendas. Não vamos tocar na tabela de estoque.

```sql
INSERT INTO vendas_registro (produto_id, qtd_vendida) VALUES (1, 20);
```

#### Passo C: O Milagre da Automação

Consulte o estoque novamente. O valor mudou sozinho! O banco de dados executou a baixa para você.

```sql
SELECT * FROM produtos_estoque;
```

#### Passo D: Outro Teste (Venda de GPS)

```sql
INSERT INTO vendas_registro (produto_id, qtd_vendida) VALUES (2, 2);
SELECT * FROM produtos_estoque;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

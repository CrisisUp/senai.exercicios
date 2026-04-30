# 📑 Guia de Interação: Atividade 03

Use este guia para realizar consultas relacionadas (JOINs) no terminal.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🔗 2. Consultas Relacionadas (JOINs)

#### Desafio A: Listar Produto e o Nome do Fornecedor (Unindo Tabelas)

```sql
SELECT p.nome AS "Produto", f.nome AS "Fornecedor"
FROM produtos p
INNER JOIN fornecedores f ON p.fornecedor_id = f.id;
```

#### Desafio B: Filtrar apenas Produtos de Fornecedores de fora do Brasil

```sql
SELECT p.nome, p.preco, f.pais
FROM produtos p
INNER JOIN fornecedores f ON p.fornecedor_id = f.id
WHERE f.pais <> 'Brasil';
```

#### Desafio C: Quantos produtos cada fornecedor entrega para a SkyStore?

```sql
SELECT f.nome, COUNT(p.id) AS "Total Fornecido"
FROM fornecedores f
LEFT JOIN produtos p ON f.id = p.fornecedor_id
GROUP BY f.nome;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

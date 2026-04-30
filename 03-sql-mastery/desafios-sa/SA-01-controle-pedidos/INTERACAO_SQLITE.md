# 📑 Guia de Interação: SA-01 (Controle de Pedidos)

Este guia contém as consultas integradoras para o primeiro desafio de SQL.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 📊 2. Consultas Integradoras (O Desafio de Negócio)

#### Desafio A: Faturamento Total por Cliente (JOIN Triplo + SUM)

Este comando une as 3 tabelas para descobrir o valor total que cada cliente já
investiu na SkyCargo.

```sql
SELECT c.nome, SUM(i.valor_unitario * i.quantidade) AS "Total Gasto"
FROM clientes c
JOIN pedidos p ON c.id = p.cliente_id
JOIN itens_pedido i ON p.id = i.pedido_id
GROUP BY c.nome
ORDER BY "Total Gasto" DESC;
```

#### Desafio B: Relatório de Itens Pendentes (Filtro de Status)

Útil para a equipe de logística saber o que precisa ser empacotado agora.

```sql
SELECT p.id AS "Nº Pedido", i.produto, i.quantidade, c.nome AS "Cliente"
FROM pedidos p
JOIN itens_pedido i ON p.id = i.pedido_id
JOIN clientes c ON p.cliente_id = c.id
WHERE p.status = 'Pendente';
```

#### Desafio C: Ticket Médio dos Pedidos (Subquery Avançada)

Calcula qual o valor médio de uma venda na empresa.

```sql
SELECT ROUND(AVG(Sub.TotalPedido), 2) AS "Ticket Médio da Empresa (R$)"
FROM (
    SELECT pedido_id, SUM(valor_unitario * quantidade) AS TotalPedido
    FROM itens_pedido
    GROUP BY pedido_id
) AS Sub;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

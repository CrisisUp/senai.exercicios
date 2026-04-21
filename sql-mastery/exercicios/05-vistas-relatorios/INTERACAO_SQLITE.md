# 📑 Guia de Interação: Atividade 05 (Vistas)

Use este guia para testar como as Vistas facilitam o seu dia a dia.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🖼️ 2. Consultas sobre Vistas (Views)

#### Desafio A: Consultar o Catálogo (Abstração de JOIN)

Em vez de fazer o INNER JOIN manualmente, você usa a View que já fizemos para você.

```sql
SELECT * FROM v_catalogo_completo;
```

#### Desafio B: Consultar as Promoções (Abstração de Cálculo)

Esta View já calculou o preço final e filtrou quem tem desconto.

```sql
SELECT * FROM v_promocoes_ativas;
```

#### Desafio C: Combinando Views com Filtros Novos

Note que você pode tratar a View exatamente como uma tabela real.

```sql
SELECT Produto, Fornecedor 
FROM v_catalogo_completo 
WHERE preco > 1000;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

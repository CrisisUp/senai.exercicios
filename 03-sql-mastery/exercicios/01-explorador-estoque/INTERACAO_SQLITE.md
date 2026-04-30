# 📑 Guia de Interação: Atividade 01 (Explorador de Estoque)

Use este guia para realizar suas primeiras consultas no terminal do SQLite.

## 🛠️ 1. Configuração de Visualização

Execute estes comandos para que os resultados apareçam em tabelas organizadas.

```sql
.mode table
.headers on
```

---

### 🔍 2. Consultas Básicas (Copie um bloco por vez)

#### Desafio A: Listar Nome e Preço de todos os produtos

```sql
SELECT nome, preco FROM produtos;
```

#### Desafio B: Filtrar produtos com preço acima de R$ 500,00

```sql
SELECT * FROM produtos 
WHERE preco > 500;
```

#### Desafio C: Descobrir qual o produto mais caro da loja

```sql
SELECT nome, preco FROM produtos 
ORDER BY preco DESC 
LIMIT 1;
```

#### Desafio D: Relatório de Baixo Estoque (Usando nomes personalizados)

```sql
SELECT nome AS "Produto em Falta", estoque AS "Qtd" 
FROM produtos 
WHERE estoque < 10;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

# 📑 Guia de Interação: Atividade 02

Use este guia para copiar e colar os comandos diretamente no terminal do SQLite.

## 🛠️ 1. Configuração de Visualização

Execute estes dois comandos assim que abrir o banco para que os resultados apareçam em tabelas organizadas.

```sql
.mode table
.headers on
```

---

### 📊 2. Consultas de Desafio (Copie um bloco por vez)

#### Desafio A: Qual categoria tem mais dinheiro investido?

```sql
SELECT categoria, 
       SUM(preco * estoque) AS "Investimento Total"
FROM produtos
GROUP BY categoria
ORDER BY "Investimento Total" DESC;
```

#### Desafio B: Onde a média de itens por produto é baixa (Menos de 10)?

```sql
SELECT categoria, AVG(estoque) AS "Média de Unidades"
FROM produtos
GROUP BY categoria
HAVING "Média de Unidades" < 10;
```

#### Desafio C: Quais itens custam mais que a média de toda a loja?

```sql
SELECT nome, preco 
FROM produtos 
WHERE preco > (SELECT AVG(preco) FROM produtos);
```

#### Desafio D: Buscar todos os tipos de Baterias e Hélices

```sql
SELECT nome, estoque 
FROM produtos 
WHERE nome LIKE 'Bateria%' OR nome LIKE 'Hélice%';
```

---

### 🚪 3. Como Sair

```sql
.exit
```

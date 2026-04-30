# 📑 Guia de Interação: Atividade 04

Use este guia para modificar tabelas e atualizar dados no terminal.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🏗️ 2. Evolução e Manutenção

#### Desafio A: Adicionar novas colunas em uma tabela viva

Note como usamos o `ADD COLUMN`.

```sql
ALTER TABLE produtos ADD COLUMN avaliacao INTEGER;
ALTER TABLE produtos ADD COLUMN desconto REAL DEFAULT 0.0;
```

#### Desafio B: Atualizar dados específicos (UPDATE)

Dando 5 estrelas para um produto específico.

```sql
UPDATE produtos SET avaliacao = 5 WHERE nome = 'Sensor GPS Alfa';
```

#### Desafio C: Aplicar um desconto (Cálculo no UPDATE)

Aplicando 10% de desconto (45.0) em um produto.

```sql
UPDATE produtos SET desconto = 45.0 WHERE nome = 'Bateria Lipo 4S';
```

#### Desafio D: Consulta de Preço Final (Cálculo na Projeção)

Este comando calcula o preço com desconto sem alterar o valor base no banco.

```sql
SELECT nome, preco AS "Preço Base", desconto AS "Valor Desconto",
       (preco - desconto) AS "Preço Final"
FROM produtos;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

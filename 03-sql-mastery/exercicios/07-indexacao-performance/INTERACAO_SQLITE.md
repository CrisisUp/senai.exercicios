# 📑 Guia de Interação: Atividade 07 (Performance)

Use este guia para auditar a velocidade do seu banco de dados no terminal.

## 🛠️ 1. Configuração Inicial

```sql
.mode table
.headers on
```

---

### ⚡ 2. Auditoria de Performance

#### Passo A: Auditar a busca ANTES de otimizar

Note que o resultado dirá "SCAN TABLE". Isso significa que o banco leu tudo para achar um dado.

```sql
EXPLAIN QUERY PLAN 
SELECT * FROM historico_voo WHERE drone_id = 'DRONE-X1';
```

#### Passo B: Aplicar a Otimização (Indexação)

Este comando cria o índice remissivo.

```sql
CREATE INDEX idx_drone_id ON historico_voo(drone_id);
```

#### Passo C: Auditar a busca DEPOIS de otimizar

Note que o resultado mudará para "SEARCH TABLE". O banco agora foi direto ao ponto!

```sql
EXPLAIN QUERY PLAN 
SELECT * FROM historico_voo WHERE drone_id = 'DRONE-X1';
```

#### Passo D: Consulta Final Otimizada

```sql
SELECT * FROM historico_voo WHERE drone_id = 'DRONE-X1';
```

---

### 🚪 3. Como Sair

```sql
.exit
```

🧪 Desafio de Mestre (Para ver o banco ficando LENTO):

  Para você sentir a diferença real de performance, tente fazer o caminho inverso no seu terminal:

  1. Delete o índice (Torne o banco "burro" de novo):
   DROP INDEX idx_drone_id;

  2. Audite a busca agora:

   EXPLAIN QUERY PLAN
   SELECT * FROM historico_voo WHERE drone_id = 'DRONE-X1';
  Note que agora o resultado será SCAN TABLE. O banco vai ler todas as linhas, o que é lento.

  3. Recrie o índice (Otimize novamente):

   CREATE INDEX idx_drone_id ON historico_voo(drone_id);

  4. Audite uma última vez:

   EXPLAIN QUERY PLAN 
   SELECT * FROM historico_voo WHERE drone_id = 'DRONE-X1';
  O resultado voltará para SEARCH TABLE. Você acaba de manipular a performance do banco manualmente!

  O que achou dessa experiência de "tunar" o motor do banco de dados? 🦀🗄️⚡

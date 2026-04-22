# 📑 Guia de Interação: Atividade 20 (Fortaleza de Dados)

Use este guia para testar as defesas automáticas do seu banco de dados.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🛡️ 2. Testando as Defesas (Constraints)

#### Desafio A: Tentar burlar o formato de E-mail

Este comando deve gerar erro de `CHECK constraint`.

```sql
INSERT INTO usuarios_central (nome, email) VALUES ('Hacker', 'email_invalido_sem_arroba');
```

#### Desafio B: Tentar deixar o saldo negativo

Este comando também deve ser barrado pela Fortaleza.

```sql
INSERT INTO usuarios_central (nome, email, saldo) VALUES ('Invasor', 'i@hacker.com', -100.0);
```

---

### 🕵️ 3. Testando a Imutabilidade (Triggers Preventivos)

#### Passo 1: Verificar o log inicial na Caixa Preta

```sql
SELECT * FROM caixa_preta;
```

#### Passo 2: Tentar apagar o histórico (Tentativa de Invasão)

O banco de dados deve responder com a mensagem customizada: "ERRO DE SEGURANÇA:
Registros da Caixa Preta são IMUTÁVEIS...".

```sql
DELETE FROM caixa_preta WHERE id = 1;
```

#### Passo 3: Tentar alterar o histórico

O banco também deve barrar a alteração.

```sql
UPDATE caixa_preta SET log_msg = 'Apagado pelo invasor' WHERE id = 1;
```

---

### 🚪 4. Como Sair

```sql
.exit
```

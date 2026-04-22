# 📑 Guia de Interação: SA-09 (Monitoramento Global)

Use este guia para testar as defesas e o câmbio automatizado.

## 🛠️ 1. Configuração

```sql
.mode table
.headers on
```

---

### 📡 2. Simulação de Ataque e Performance

#### Passo A: Registrar um acesso normal

```sql
INSERT INTO operacoes (usuario, valor_local, moeda, latencia_ms, data_hora) 
VALUES ('piloto_01', 10.0, 'USD', 25.0, '2026-04-21 10:00:00');
```

#### Passo B: Simular Ataque de Brute Force (Acessos Rápidos)

Execute os dois comandos abaixo em menos de 2 segundos.

```sql
INSERT INTO operacoes (usuario, valor_local, moeda, latencia_ms, data_hora) 
VALUES ('piloto_01', 10.0, 'USD', 25.0, '2026-04-21 10:00:01');

INSERT INTO operacoes (usuario, valor_local, moeda, latencia_ms, data_hora) 
VALUES ('piloto_01', 10.0, 'USD', 25.0, '2026-04-21 10:00:02');
```

#### Passo C: Verificar os alertas gerados pelo Radar

```sql
SELECT * FROM alertas;
```

---

### 📈 3. Relatórios Financeiros

```sql
SELECT * FROM v_financeiro_global;
```

---

### 🚪 4. Como Sair

```sql
.exit
```

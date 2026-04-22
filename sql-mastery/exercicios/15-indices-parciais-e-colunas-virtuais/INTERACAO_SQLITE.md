# 📑 Guia de Interação: Atividade 15 (Otimização de Espaço)

Use este guia para testar as estratégias de economia de disco e aceleração de busca.

### 🛠️ 1. Configuração de Visualização
```sql
.mode table
.headers on
```

---

### ⚡ 2. Performance e Otimização

#### Desafio A: Consultar o Score de Saúde Automático
Note que você não digitou o cálculo na query. A **Coluna Virtual** fez isso nos bastidores.
```sql
SELECT serial, bateria, horas_voo, score_saude 
FROM status_frota;
```

#### Desafio B: Auditar a Busca de Emergência (Índice Parcial)
Note que o resultado dirá "SEARCH ... USING INDEX idx_emergencia". O banco usou o índice otimizado.
```sql
EXPLAIN QUERY PLAN 
SELECT * FROM status_frota WHERE bateria < 15.0;
```

#### Desafio C: Auditar a Busca Normal (Ignora o Índice)
Note que como a bateria é > 50, o índice parcial (que só olha para < 20) é ignorado e o banco faz um "SCAN". Isso economiza RAM, pois o índice não precisa carregar dados inúteis.
```sql
EXPLAIN QUERY PLAN 
SELECT * FROM status_frota WHERE bateria > 70.0;
```

---

### 🚪 3. Como Sair
```sql
.exit
```

# 📑 Guia de Interação: Atividade 14 (FTS5)

Use este guia para testar o seu motor de busca de alta velocidade.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🔍 2. Consultas de Busca (MATCH)

#### Desafio A: Buscar pela palavra exata "fumaça"

Diferente do LIKE, o MATCH é instantâneo.

```sql
SELECT drone_id, relatorio_piloto 
FROM busca_logs 
WHERE relatorio_piloto MATCH 'fumaça';
```

#### Desafio B: Busca por prefixo (Começa com...)

Ache qualquer registro que tenha palavras começando com "vibr" (ex: vibração, vibrou).

```sql
SELECT * FROM busca_logs 
WHERE relatorio_piloto MATCH 'vibr*';
```

#### Desafio C: Busca combinada (AND)

Ache logs que falem de "bateria" E "aquecimento" ao mesmo tempo.

```sql
SELECT * FROM busca_logs 
WHERE relatorio_piloto MATCH 'bateria AND aquecimento';
```

#### Desafio D: Busca por Proximidade (Avançado)

Ache registros onde "motor" e "vibração" aparecem com no máximo 5 palavras de
distância um do outro.

```sql
SELECT * FROM busca_logs 
WHERE relatorio_piloto MATCH 'NEAR(motor vibração, 5)';
```

---

### 🚪 3. Como Sair

```sql
.exit
```

# 📑 Guia de Interação: Atividade 11 (Hierarquias Recursivas)

Use este guia para visualizar a árvore de componentes (BOM) no terminal.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🌳 2. Exploração Recursiva

#### Desafio: Gerar a Árvore de Peças do Drone

Copie este bloco inteiro. Ele percorre todos os níveis de montagem, do drone 
completo até o menor parafuso/hélice.

```sql
WITH RECURSIVE arvore_pecas AS (
    SELECT id, nome, pai_id, 0 AS nivel, nome AS caminho
    FROM componentes
    WHERE pai_id IS NULL
    UNION ALL
    SELECT c.id, c.nome, c.pai_id, a.nivel + 1, a.caminho || ' > ' || c.nome
    FROM componentes c
    INNER JOIN arvore_pecas a ON c.pai_id = a.id
)
SELECT nivel,
       printf('%' || (nivel * 4) || 's', '') || nome AS "Estrutura Hierárquica",
       caminho AS "Rastreabilidade"
FROM arvore_pecas
ORDER BY caminho;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

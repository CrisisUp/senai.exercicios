# 📑 Guia de Interação: Atividade 18 (Navegação de Rotas)

Use este guia para ver o SQL resolvendo problemas de logística complexa.

### 🛠️ 1. Configuração de Visualização
```sql
.mode table
.headers on
```

---

### 🗺️ 2. Navegação em Grafos

#### Desafio: Encontrar todos os caminhos para a BASE-D
Este comando faz o banco de dados "caminhar" por todas as conexões possíveis saindo da BASE-A. Note como ele calcula a distância acumulada de cada opção.
```sql
WITH RECURSIVE navegador_rotas AS (
    SELECT destino, 
           distancia AS km_total, 
           origem || ' -> ' || destino AS trajeto,
           1 AS paradas
    FROM conexoes_bases
    WHERE origem = 'BASE-A'
    UNION ALL
    SELECT c.destino, 
           n.km_total + c.distancia, 
           n.trajeto || ' -> ' || c.destino,
           n.paradas + 1
    FROM conexoes_bases c
    JOIN navegador_rotas n ON c.origem = n.destino
    WHERE n.trajeto NOT LIKE '%' || c.destino || '%'
)
SELECT trajeto AS "Rota Completa",
       km_total AS "Distância Total",
       paradas AS "Saltos"
FROM navegador_rotas
WHERE destino = 'BASE-D'
ORDER BY km_total ASC;
```

---

### 🚪 3. Como Sair
```sql
.exit
```

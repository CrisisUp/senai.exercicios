# 📑 Guia de Interação: Atividade 19 (Comando Global)

Use este guia para operar a central de comando que une 3 bancos de dados.

## 🛠️ 1. Configuração da Federação (Crucial!)

Você deve anexar os arquivos antes de qualquer consulta.

```sql
.mode table
.headers on

-- Anexando bancos de outros exercícios
ATTACH DATABASE '../01-explorador-estoque/database.db' AS estoque;
ATTACH DATABASE '../12-integridade-cascata/database.db' AS frota;
ATTACH DATABASE '../18-inteligencia-rotas-grafos/database.db' AS rotas;
```

---

### 🌐 2. Consultas Multi-Banco (Cross-DB)

#### Desafio A: O Relatório da Diretoria (Unindo tudo)

Este comando busca dados de 3 arquivos diferentes e entrega um plano de missão consolidado.

```sql
WITH 
    drone AS (SELECT serial FROM frota.drones_frota LIMIT 1),
    rota AS (SELECT origem || ' -> ' || destino AS trajeto FROM rotas.conexoes_bases LIMIT 1),
    peca AS (SELECT nome FROM estoque.produtos LIMIT 1)
SELECT d.serial AS Drone, r.trajeto AS Rota, p.nome AS Pecas_Prontos
FROM drone d, rota r, peca p;
```

#### Desafio B: Conferência de Consistência

Verifique se algum serial de drone da frota (Ativ 12) aparece por engano no estoque de peças (Ativ 01).

```sql
SELECT f.serial 
FROM frota.drones_frota f
INNER JOIN estoque.produtos e ON f.serial = e.nome;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

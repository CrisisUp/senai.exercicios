# 📑 Guia de Interação: SA-04 (Data Warehouse Logístico)

Este é o seu guia final para operar como um Lead Data Architect.

## 🛠️ 1. Configuração de Segurança Industrial

```sql
PRAGMA foreign_keys = ON;
.mode table
.headers on
```

---

### 🏆 2. Dashboard de Performance (Nível Executivo)

#### Consulta: Ranking de Drones por Região

Note como o banco separa as Américas da Europa e dá medalhas de 1º e 2º lugar
para cada uma, comparando-os com a média local.

```sql
SELECT * FROM v_ranking_produtividade;
```

---

### 🌳 3. Engenharia de Manutenção (Nível Técnico)

#### Consulta: Árvore de Peças do Drone SN-X10 (Recursivo)

Veja a estrutura de montagem completa, do Chassi até a Hélice.

```sql
WITH RECURSIVE bom_drone AS (
    SELECT id, nome, pai_id, 0 AS nivel
    FROM componentes
    WHERE pai_id IS NULL AND drone_id = 1
    UNION ALL
    SELECT c.id, c.nome, c.pai_id, b.nivel + 1
    FROM componentes c
    JOIN bom_drone b ON c.pai_id = b.id
)
SELECT nivel AS Profundidade, 
       printf('%' || (nivel * 3) || 's', '') || nome AS "Estrutura de Montagem"
FROM bom_drone;
```

---

### 🌊 4. Teste de Aposentadoria (Integridade e Cascata)

#### Passo 1: Verificar dados do Drone SN-X10

Veja que ele tem viagens registradas e 5 peças cadastradas.

```sql
SELECT 'Total Peças' AS Info, COUNT(*) FROM componentes WHERE drone_id = 1;
SELECT 'Total Viagens' AS Info, COUNT(*) FROM historico_viagens WHERE drone_id = 1;
```

#### Passo 2: Deletar o Drone

```sql
DELETE FROM frota WHERE serial = 'SN-X10';
```

#### Passo 3: Auditoria de Limpeza Automática

Note que tanto o histórico quanto as peças sumiram do banco. O sistema está limpo!

```sql
SELECT 'Peças Restantes' AS Info, COUNT(*) FROM componentes WHERE drone_id = 1;
SELECT 'Viagens Restantes' AS Info, COUNT(*) FROM historico_viagens WHERE drone_id = 1;
```

---

### 🚪 5. Como Sair

```sql
.exit
```

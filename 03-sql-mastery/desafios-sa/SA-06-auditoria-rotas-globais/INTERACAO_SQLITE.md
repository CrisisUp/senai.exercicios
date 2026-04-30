# 📑 Guia de Interação: SA-06 (Central de Auditoria e Rotas)

Use este guia para operar a inteligência de rede da SkyCargo.

## 🛠️ 1. Configuração da Federação

```sql
.mode table
.headers on
ATTACH DATABASE '../../exercicios/16-multi-banco-attach/arquivo_morto.db' AS backup;
```

---

### 🗺️ 2. Navegação Global

#### Desafio: Encontrar Rota Londres -> Berlim

Note como o banco cruza os arquivos físicos para informar quantos drones estão indisponíveis enquanto calcula o trajeto.

```sql
WITH RECURSIVE navegador AS (
    SELECT destino, distancia AS km, origem || ' -> ' || destino AS caminho
    FROM rotas_globais WHERE origem = 'LONDRES'
    UNION ALL
    SELECT r.destino, n.km + r.distancia, n.caminho || ' -> ' || r.destino
    FROM rotas_globais r
    JOIN navegador n ON r.origem = n.destino
)
SELECT caminho AS Rota, km AS Distancia,
       (SELECT COUNT(*) FROM backup.drones_velhos) AS Indisponiveis
FROM navegador n
WHERE n.destino = 'BERLIM';
```

---

### 🕵️ 3. Auditoria de Rotas

#### Passo A: Mudar a quilometragem de uma rota

Mude a distância de LONDRES -> MADRI para 1500.0.

```sql
UPDATE rotas_globais SET distancia = 1500.0 WHERE destino = 'MADRI';
```

#### Passo B: Consultar a "Caixa Preta" de auditoria

Verifique se o banco registrou o valor antigo e o novo sozinho.

```sql
SELECT * FROM log_auditoria_rotas;
```

---

### 🚪 4. Como Sair

```sql
.exit
```

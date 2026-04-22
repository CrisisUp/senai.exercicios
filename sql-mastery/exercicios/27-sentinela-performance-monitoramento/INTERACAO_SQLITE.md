# 📑 Guia de Interação: Atividade 27 (Sentinela de Performance)

Use este guia para testar como o banco de dados monitora a própria velocidade.

## 🛠️ 1. Configuração de Monitoramento

```sql
.mode table
.headers on
```

---

### ⚡ 2. Testando a Automação de Alertas

#### Passo A: Simular uma operação Rápida

Esta operação leva 15ms. Ela não deve gerar nenhum alerta.

```sql
INSERT INTO operacoes_rastreio (operacao_nome, tempo_ms) VALUES ('Leitura Sensor A', 15.0);
SELECT * FROM incidentes_performance;
```

#### Passo B: Simular uma operação Lenta (Nível Médio)

Esta operação leva 300ms. O Sentinela deve capturá-la.

```sql
INSERT INTO operacoes_rastreio (operacao_nome, tempo_ms) VALUES ('Calculo Rota Europa', 300.0);
SELECT * FROM incidentes_performance;
```

#### Passo C: Simular uma operação Crítica (Nível Alto)

Esta operação de 1200ms é perigosa para o sistema em tempo real.

```sql
INSERT INTO operacoes_rastreio (operacao_nome, tempo_ms) VALUES ('Processamento Batch Histórico', 1200.0);
SELECT * FROM incidentes_performance;
```

---

### 🕵️ 3. Auditoria do SRE

Veja o relatório final de incidentes que o próprio banco de dados gerou para você.

```sql
SELECT operacao_nome, latencia_ms, criticidade 
FROM incidentes_performance 
ORDER BY latencia_ms DESC;
```

---

### 🚪 4. Como Sair

```sql
.exit
```

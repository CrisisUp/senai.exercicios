# 📑 Guia de Interação: Atividade 30 (Savepoints)

Use este guia para praticar a "Viagem no Tempo Parcial" dentro do terminal.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🛡️ 2. Gerenciando Checkpoints (SAVEPOINT)

#### Passo A: Iniciar o processo

```sql
BEGIN TRANSACTION;
INSERT INTO manutencao_progresso (drone_id, etapa, status) VALUES ('DRONE-777', 'Limpeza', 'OK');
SAVEPOINT sp_limpeza;
```

#### Passo B: Executar segunda etapa

```sql
INSERT INTO manutencao_progresso (drone_id, etapa, status) VALUES ('DRONE-777', 'Bateria', 'OK');
SAVEPOINT sp_bateria;
```

#### Passo C: Simular Erro Grave

```sql
INSERT INTO manutencao_progresso (drone_id, etapa, status) VALUES ('DRONE-777', 'Firmware', 'ERRO');
SELECT * FROM manutencao_progresso; -- Você verá o erro aqui no rascunho
```

#### Passo D: Voltar ao Checkpoint da Bateria

Este comando apaga a etapa de Firmware mas PRESERVA a Limpeza e a Bateria.

```sql
ROLLBACK TO sp_bateria;
SELECT * FROM manutencao_progresso; -- O erro de Firmware sumiu!
```

#### Passo E: Finalizar com Sucesso

```sql
INSERT INTO manutencao_progresso (drone_id, etapa, status) VALUES ('DRONE-777', 'Firmware-Recuperado', 'OK');
COMMIT;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

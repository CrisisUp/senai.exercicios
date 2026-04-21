# 📑 Guia de Interação: Atividade 12 (Integridade de Ferro)

Use este guia para testar as restrições e a automação de limpeza no terminal.

## 🛠️ 1. Configuração de Segurança

**IMPORTANTE:** No SQLite, o suporte a chaves estrangeiras vem desativado por
padrão em cada sessão. Execute este comando primeiro!

```sql
PRAGMA foreign_keys = ON;
.mode table
.headers on
```

---

### 🛡️ 2. Testando a Blindagem (Constraints)

#### Desafio A: Tentar inserir serial repetido

Este comando deve gerar um erro: `UNIQUE constraint failed`.

```sql
INSERT INTO drones_frota (serial, modelo, horas_voo) VALUES ('SN-001', 'Falcon-X', 10.0);
INSERT INTO drones_frota (serial, modelo, horas_voo) VALUES ('SN-001', 'Duplicata', 5.0);
```

#### Desafio B: Tentar inserir horas negativas

Este comando deve gerar um erro: `CHECK constraint failed`.

```sql
INSERT INTO drones_frota (serial, modelo, horas_voo) VALUES ('SN-999', 'Bug', -5.0);
```

---

### 🌊 3. Testando a Cascata (Limpeza Automática)

#### Passo 1: Verificar se há logs órfãos

Primeiro, vamos ver quantos logs existem para o drone principal.

```sql
SELECT 'Total de Logs' AS Info, COUNT(*) FROM telemetria_historico;
```

#### Passo 2: Deletar o Drone (O "Pai")

```sql
DELETE FROM drones_frota WHERE serial = 'SN-001';
```

#### Passo 3: O Milagre da Cascata

Consulte os logs novamente. Note que eles SUMIRAM sozinhos, pois o banco de dados limpou o "lixo" para você.

```sql
SELECT 'Logs após a deleção' AS Info, COUNT(*) FROM telemetria_historico;
```

---

### 🚪 4. Como Sair

```sql
.exit
```

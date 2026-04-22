# 📑 Guia de Interação: Atividade 17 (Rastreamento de Auditoria)

Use este guia para ver o seu banco de dados agindo como uma "Caixa Preta".

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🕵️ 2. Investigação de Mudanças

#### Passo A: Verificar o drone inicial

Note a versão do firmware.

```sql
SELECT * FROM configuracao_drones;
```

#### Passo B: Atualizar a Versão (Disparando Auditoria)

Mude a versão para v2.0.0.

```sql
UPDATE configuracao_drones 
SET firmware_versao = 'v2.0.0' 
WHERE serial = 'SN-ALPHA';
```

#### Passo C: Consultar a Tabela de Sombras (Auditoria)

Veja como o banco registrou o valor que existia antes e o valor que você acabou de colocar!

```sql
SELECT * FROM auditoria_logs;
```

#### Passo D: Outra mudança para testar o histórico

Mude novamente o firmware e veja o log crescer.

```sql
UPDATE configuracao_drones 
SET firmware_versao = 'v2.1.0-beta' 
WHERE serial = 'SN-ALPHA';

SELECT * FROM auditoria_logs;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

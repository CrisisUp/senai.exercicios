# 📑 Guia de Interação: Atividade 16 (Multi-Banco / ATTACH)

Use este guia para aprender a cruzar dados de dois arquivos diferentes.

### 🛠️ 1. Configuração Inicial
```sql
.mode table
.headers on
```

---

### 📂 2. Operações Multi-Arquivo

#### Passo A: Anexar o Banco de Arquivo Morto
Este comando "linka" o outro arquivo de banco à sua sessão atual sob o nome `morto`.
```sql
ATTACH DATABASE 'arquivo_morto.db' AS morto;
```

#### Passo B: Verificar os bancos conectados
Este comando lista todos os arquivos físicos que você está acessando no momento.
```sql
.databases
```

#### Passo C: Consulta Unificada (UNION ALL)
Consolida os drones de ambos os arquivos em uma única lista para auditoria.
```sql
SELECT serial, 'ATIVO' AS situacao FROM drones_ativos
UNION ALL
SELECT serial, 'APOSENTADO' AS situacao FROM morto.drones_velhos;
```

#### Passo D: Cruzamento de Dados (JOIN Cross-DB)
Imagine que você queira saber se algum drone ativo tem o mesmo serial de um antigo (erro de cadastro).
```sql
SELECT a.serial 
FROM drones_ativos a
INNER JOIN morto.drones_velhos m ON a.serial = m.serial;
```

---

### 🚪 3. Como Sair
```sql
.exit
```

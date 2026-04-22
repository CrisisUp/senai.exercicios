# 🕵️ MANUAL DO DETETIVE SQL: Comandos de Exploração

Este guia contém os comandos essenciais para você "interrogar" qualquer banco de dados SQLite e descobrir sua estrutura, segredos e automações.

---

## 🛠️ 1. Configuração de Visualização (Obrigatório)

Sempre execute estes comandos ao abrir o banco para que os dados fiquem legíveis.

```sql
.mode table    -- Ativa o modo de tabela com bordas
.headers on    -- Exibe o nome das colunas no topo
```

---

### 🔍 2. Comandos de "Raio-X" da Estrutura

#### Ver como o banco foi construído (O Melhor!)

Mostra o código de criação de todas as tabelas, índices e gatilhos.

```sql
.fullschema
```

#### Ver a estrutura de uma tabela específica

Mostra as colunas, tipos de dados e quais campos são obrigatórios (RG da tabela).

```sql
PRAGMA table_info('nome_da_tabela');
```

#### Listar todas as tabelas do banco

```sql
.tables
```

---

### 🔗 3. Investigando Relacionamentos

#### Listar Chaves Estrangeiras (Conexões)

Revela para qual tabela a tabela atual está apontando.

```sql
PRAGMA foreign_key_list('nome_da_tabela');
```

#### Ativar a Inteligência de Chaves (Importante!)

O SQLite exige este comando para que a exclusão em CASCATA funcione na sessão atual.

```sql
PRAGMA foreign_keys = ON;
```

---

### 🤖 4. Descobrindo Automações Ocultas

#### Listar todos os Gatilhos (Triggers)

Descubra se o banco toma ações "sozinho" nos bastidores.

```sql
SELECT name, event, action_timing FROM sqlite_master WHERE type = 'trigger';
```

#### Listar Vistas (Views)

Veja quais "tabelas virtuais" foram criadas para simplificar relatórios.

```sql
SELECT name FROM sqlite_master WHERE type = 'view';
```

---

### ⚡ 5. Auditoria de Performance

#### Analisar o Plano de Busca

Descubra se o banco fará um SCAN (Lento) ou um SEARCH (Rápido) na sua query.

```sql
EXPLAIN QUERY PLAN SEU_COMANDO_SELECT_AQUI;
```

#### Listar Índices de Performance

```sql
.indices nome_da_tabela
```

---

### 🚪 6. Comandos de Sistema

- `.databases`: Mostra onde o arquivo físico do banco está no computador.
- `.help`: Lista todos os comandos do SQLite.
- `.exit`: Sai do banco e volta para o terminal normal.

---
*Manual gerado pelo mentor Gemini CLI para o nível Lead Data Architect.*

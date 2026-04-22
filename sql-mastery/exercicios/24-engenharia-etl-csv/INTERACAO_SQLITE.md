# 📑 Guia de Interação: Atividade 24 (Engenharia ETL)

Use este guia para importar planilhas e gerar backups de segurança no terminal.

### 🛠️ 1. Configuração de Modo
Sempre comece preparando o terminal para o formato de planilhas.
```sql
.mode csv
.headers on
```

---

### 📥 2. Importação Massiva (LOAD)

#### Passo A: Criar a Tabela de Destino
```sql
CREATE TABLE IF NOT EXISTS fornecedores_importados (
    id INTEGER PRIMARY KEY,
    nome TEXT,
    regiao TEXT,
    contato TEXT
);
```

#### Passo B: Importar o arquivo CSV
Este comando lê o arquivo `fornecedores_externos.csv` e insere os dados na tabela. O `--skip 1` pula o cabeçalho do arquivo.
```sql
.import --skip 1 fornecedores_externos.csv fornecedores_importados
```

#### Passo C: Validar a Importação
```sql
SELECT * FROM fornecedores_importados;
```

---

### 📤 3. Exportação de Relatórios

#### Desafio: Salvar apenas fornecedores do Norte em um novo arquivo
Execute este bloco. O resultado da query não aparecerá na tela, ele será gravado no arquivo `contatos_norte.csv`.
```sql
.output contatos_norte.csv
SELECT nome, contato FROM fornecedores_importados WHERE regiao = 'Norte';
.output stdout    -- Volta a mostrar resultados no terminal
```

---

### 🛡️ 4. Backup Total (DUMP)

#### Desafio: Gerar o script SQL de backup do banco inteiro
Este comando cria o arquivo `backup_sistema.sql` com todos os comandos necessários para reconstruir este banco em qualquer outro computador.
```sql
.once backup_sistema.sql
.dump
```

---

### 🚪 5. Como Sair
```sql
.exit
```

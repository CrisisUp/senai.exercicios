# 📑 Guia de Interação: Atividade 28 (Manutenção de Banco)

Use este guia para aprender a reduzir o tamanho do banco e otimizar a performance.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🧹 2. Manutenção e Limpeza

#### Passo A: Verificar o tamanho atual (em páginas)

```sql
SELECT page_count AS "Páginas Atuais" FROM pragma_page_count();
```

#### Passo B: Deletar todos os dados (Sem limpar o arquivo)

Execute o delete. Note que se você olhar o tamanho do arquivo no seu explorador de arquivos, ele continuará o mesmo!

```sql
DELETE FROM logs_temporarios;
SELECT page_count AS "Páginas após DELETE" FROM pragma_page_count();
```

#### Passo C: A Limpeza Real (VACUUM)

Note a redução drástica no número de páginas. O banco devolveu o espaço vazio para o sistema operacional.

```sql
VACUUM;
SELECT page_count AS "Páginas após VACUUM" FROM pragma_page_count();
```

#### Passo D: Atualizar o Planejador (ANALYZE)

Use sempre após grandes limpezas ou importações massivas para manter as buscas rápidas.

```sql
ANALYZE;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

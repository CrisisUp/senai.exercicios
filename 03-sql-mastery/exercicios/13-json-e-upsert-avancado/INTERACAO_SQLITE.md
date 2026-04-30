# 📑 Guia de Interação: Atividade Bônus 13 (JSON e UPSERT)

Este manual apresenta os comandos modernos do SQLite para lidar com dados flexíveis.

## 🛠️ 1. Configuração de Visualização

```sql
.mode table
.headers on
```

---

### 🚀 2. Recursos Modernos em Ação

#### Desafio A: O Comando UPSERT (Inserir ou Atualizar)

Tente inserir o mesmo drone duas vezes com dados diferentes. Note como o banco
não dá erro, ele apenas atualiza o registro existente.

```sql
INSERT INTO telemetria_avancada (drone_serial, dados_json)
VALUES ('SN-100', '{"temp": 30.5, "status": "alerta"}')
ON CONFLICT(drone_serial) DO UPDATE SET
    dados_json = excluded.dados_json,
    ultima_atualizacao = CURRENT_TIMESTAMP;
```

#### Desafio B: Consultando "Dentro" do JSON

Note como extraímos apenas a temperatura (`$.temp`) de uma coluna de texto.

```sql
SELECT drone_serial, 
       json_extract(dados_json, '$.temp') AS Temperatura
FROM telemetria_avancada;
```

#### Desafio C: Filtrando por Campo JSON

O banco de dados consegue filtrar linhas baseado em valores que estão escondidos
dentro do JSON!

```sql
SELECT * FROM telemetria_avancada 
WHERE json_extract(dados_json, '$.temp') > 25;
```

---

### 🚪 3. Como Sair

```sql
.exit
```

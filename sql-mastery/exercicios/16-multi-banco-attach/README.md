# 🗄️ Atividade 16: Multi-Banco e Arquivamento (ATTACH DATABASE)

## 🎯 Estudo de Caso

A "SkyCargo" opera há muitos anos. O banco de dados principal está ficando lento
devido ao excesso de dados históricos (drones que já foram aposentados e não
voam mais). Para manter a performance, decidimos mover os drones inativos para
um arquivo separado chamado `arquivo_morto.db`. No entanto, o departamento de
auditoria ocasionalmente precisa de um relatório que mostre **toda a frota**
(ativos + inativos).

## 🛠️ Necessidade Técnica

O comando **`ATTACH DATABASE`** permite conectar múltiplos arquivos de banco de
dados à mesma sessão:

* **Segregação de Dados:** Mantém o banco de produção leve e pequeno.
* **Arquivamento:** Permite mover dados antigos para discos mais baratos ou mídias externas.
* **Interoperabilidade:** Você pode realizar `JOIN` e `UNION` entre tabelas que
* estão em arquivos físicos diferentes.
* **Namespace:** Cada banco anexado ganha um prefixo (ex: `backup.tabela`).

## 📋 Requisitos

1. Criar um banco de dados secundário `arquivo_morto.db` com drones inativos.
2. Criar o banco de dados principal `frota_ativa.db` com drones em operação.
3. Usar o comando `ATTACH` para conectar o arquivo morto ao principal.
4. Realizar uma consulta usando **`UNION ALL`** para consolidar a frota completa
5. em um único relatório.

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

## ⚠️ Análise de Falha Crítica

A utilização de múltiplos bancos de dados via `ATTACH` introduz riscos complexos de integridade e performance:

1.  **Corrupção de Cross-DB:** Se a conexão for interrompida durante uma transação que envolve múltiplos bancos (`BEGIN IMMEDIATE`), o risco de inconsistência aumenta. Embora o SQLite suporte transações atômicas multi-banco, uma falha de hardware pode deixar um banco atualizado e outro não, se o journal de um deles falhar.
2.  **Gargalo de I/O:** Consultas que cruzam bancos em discos físicos diferentes podem sofrer latência imprevisível. O planejador de consultas tem menos informações estatísticas consolidadas para otimizar `JOINs` globais.
3.  **Conflitos de Namespace:** Tabelas com o mesmo nome em bancos diferentes podem causar erros catastróficos se o desenvolvedor esquecer o prefixo (ex: `morto.drones` vs `drones`). O banco `main` sempre tem precedência, o que pode levar à leitura de dados errados.
4.  **Complexidade de Backup:** Backups a quente (`VACUUM INTO`) tornam-se mais difíceis de coordenar quando os dados estão espalhados por múltiplos arquivos, exigindo uma orquestração externa para garantir que todos os arquivos reflitam o mesmo ponto no tempo.


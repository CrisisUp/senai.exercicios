# 📊 SA-07: Portal de Inteligência Global (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyCargo" precisa de uma central única de decisão. O CEO quer um painel que mostre não apenas onde os drones estão, mas o quão seguros eles estão operando. O sistema deve unir dados de múltiplos bancos, garantir que ninguém altere os dados de segurança e apresentar médias móveis de performance em um formato de tabela executiva (Pivot).

## 🛠️ Necessidade Técnica

Este desafio integra os conhecimentos do Nível 50-60 (Atividades 19 a 22):

1. **ATTACH DATABASE (Atividade 19):** Unir o banco de Produção com o banco de Telemetria Histórica.
2. **Segurança de Fortaleza (Atividade 20):** Implementar gatilhos que impeçam a alteração de registros de telemetria consolidados.
3. **Window Frames (Atividade 21):** Calcular a média móvel de distância percorrida para identificar cansaço da frota.
4. **Pivoteamento (Atividade 22):** Gerar um relatório trimestral de desempenho por região em formato de colunas.

## 📋 Requisitos Funcionais

1. Criar o banco `portal_inteligencia.db`.
2. Anexar o banco de `01-explorador-estoque` para verificar disponibilidade de peças.
3. Implementar um Trigger que proteja a tabela de `consolidado_missao` contra exclusões.
4. Realizar uma query que calcule a média móvel de 3 missões por drone.
5. Gerar um Pivot que mostre o total de quilômetros por Região (Americas, Europa, Asia) como colunas.

## ⚠️ Análise de Falha Crítica (Elite Analytics)

O Portal de Inteligência Global centraliza dados estratégicos, o que amplia os riscos de falhas estruturais:

1.  **Riscos de Performance de Window Functions:** O uso extensivo de `OVER(PARTITION BY...)` em grandes volumes de dados sem índices adequados nas colunas de partição e ordenação pode causar *full table scans* repetitivos, levando a uma degradação exponencial da performance do dashboard.
2.  **Corrupção Massiva (Multi-Database):** Ao utilizar `ATTACH DATABASE`, uma falha de energia ou interrupção de transação durante operações que envolvam múltiplos bancos pode levar a estados de inconsistência onde um banco reflete a alteração e o outro não, dificultando a recuperação de desastres.
3.  **Data Leaks via Cross-Database Join:** A facilidade de unir bancos externos (`ATTACH`) aumenta o risco de vazamento de dados sensíveis de produção para ambientes de relatório se as permissões de arquivo do sistema operacional não forem rigorosamente controladas, permitindo que usuários de analytics acessem tabelas restritas.
4.  **Inconsistência de Backup:** Backups realizados via simples cópia de arquivo em bancos anexados podem resultar em instantâneos (snapshots) inconsistentes entre si, já que o SQLite não garante atomicidade de backup entre múltiplos arquivos de banco de dados distintos simultaneamente.

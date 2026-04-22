# 🛡️ SA-08: O Guardião de Missões Críticas (Desafio Final de Elite)

## 🎯 Estudo de Caso: Operação SkyShield

A "SkyCargo" agora opera em zonas de alto risco e sob ataques cibernéticos constantes. O banco de dados deve ser capaz de:

1. Detectar automaticamente bots tentando acessos rápidos (Brute Force).
2. Gerenciar manutenções em múltiplos estágios, garantindo que o progresso não
seja perdido em caso de falha parcial.
3. Monitorar a própria latência e gerar alertas de SRE.
4. Realizar conversões de câmbio para faturamento internacional.
5. Suportar cargas massivas de telemetria sem degradar a busca.

## 🛠️ Necessidade Técnica

Este desafio integra as Atividades 25 a 30:

* **Cibersegurança (Ativ. 25):** Detecção de anomalias temporais via `LAG()`.
* **Gestão Global (Ativ. 26):** Normalização de moedas e fuso UTC.
* **Observabilidade SRE (Ativ. 27):** Gatilhos que monitoram latência.
* **Escala e Estresse (Ativ. 29):** Manipulação de grandes volumes de dados.
* **Resiliência (Ativ. 30):** Uso de `SAVEPOINT` para recuperação granular.

## 📋 Requisitos Funcionais

1. Implementar o **Radar de Segurança** para detectar logins suspeitos.
2. Criar o **Módulo de Faturamento Global** com taxas de câmbio dinâmicas.
3. Desenvolver o **Fluxo de Manutenção Blindada** usando 3 checkpoints (Savepoints).
4. Garantir que o sistema dispare alertas se qualquer operação levar mais de 500ms.
5. Simular uma carga de 100.000 registros para validar o ambiente sob pressão.

## 🏗️ Estrutura de Arquivos Obrigatória

* `README.md`: Este guia mestre.
* `queries.sql`: O motor da fortaleza de dados.
* `INTERACAO_SQLITE.md`: Manual do Arquiteto de Operações Críticas.

# 🛡️ SA-06: Central de Auditoria e Rotas Globais (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyCargo" unificou suas bases internacionais. Precisamos de um sistema que:

1. Busque rotas entre cidades (Ativ. 18).
2. Cruze esses dados com o banco de "Drones Aposentados" (Ativ. 16) para garantir que nenhuma rota perigosa use drones velhos.
3. Registre em uma tabela de auditoria (Ativ. 17) toda vez que uma nova rota for inserida ou modificada no mapa global.

## 🛠️ Necessidade Técnica

Este desafio integra:

* **ATTACH DATABASE:** Para conectar o banco de drones aposentados.
* **RECURSIVE CTE:** Para navegar no mapa de cidades.
* **TRIGGERS:** Para auditoria automática de mudanças no mapa.
* **JOIN CROSS-DB:** Para validar a segurança da frota.

## 📋 Requisitos Funcionais

1. Criar o mapa de rotas (tabela `rotas_globais`).
2. Criar a tabela de auditoria `log_rotas`.
3. Anexar o banco `arquivo_morto.db` (da Atividade 16).
4. Implementar um Trigger que grave o log de auditoria ao mudar a quilometragem de uma rota.
5. Realizar uma query que busque o caminho entre Cidade A e Cidade C e mostre se há algum drone inativo associado por erro.

## 🏗️ Estrutura de Arquivos Obrigatória

* `README.md`: Este guia.
* `queries.sql`: A arquitetura e transações.
* `INTERACAO_SQLITE.md`: Guia operacional.

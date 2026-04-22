# 🛠️ SA-03: Sistema de Manutenção Preventiva (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyCargo" atingiu um nível de operação onde a segurança não pode depender de verificações manuais. Cada drone tem um limite de **100 horas de voo** antes de precisar de uma revisão completa. O sistema deve ser capaz de:

1. Registrar voos e atualizar automaticamente o horímetro do drone.
2. Gerar alertas de manutenção assim que o limite for atingido.
3. Permitir consultas rápidas ao histórico de voo (performance).
4. Gerar relatórios comparativos de uso da frota.

## 🛠️ Necessidade Técnica

Este desafio final integra os conhecimentos do Nível 31 (Atividades 07 a 09):

1. **Indexação (Atividade 07):** Otimizar a busca no histórico de voos, que cresce exponencialmente.
2. **CTEs e Relatórios (Atividade 08):** Criar uma análise de "Uso de Frota" que compare as horas de cada drone com a média da empresa.
3. **Triggers e Automação (Atividade 09):** Criar gatilhos que atualizam o horímetro e disparam alertas de manutenção sem intervenção humana.

## 📋 Requisitos Funcionais

1. Criar a tabela `frota_drones` (id, modelo, horas_totais).
2. Criar a tabela `log_voos` (id, drone_id, horas_viagem).
3. Criar a tabela `alertas_manutencao` (id, drone_id, mensagem).
4. Criar um **INDEX** na coluna `drone_id` da tabela `log_voos`.
5. Criar um **TRIGGER** que, após um voo:
    - Adicione as horas da viagem às `horas_totais` do drone.
    - Se o drone ultrapassar 100 horas, insira um registro em `alertas_manutencao`.
6. Criar uma consulta complexa usando **WITH** para mostrar drones "estressados" (acima da média de voo da frota).

## 🏗️ Estrutura de Arquivos Obrigatória

- `README.md`: Contexto e requisitos (Este arquivo).
- `queries.sql`: Arquitetura, automação e população.
- `INTERACAO_SQLITE.md`: Guia de simulação operacional.

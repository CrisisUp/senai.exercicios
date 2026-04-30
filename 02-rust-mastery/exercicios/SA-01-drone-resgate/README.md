# 🚁 SA-01: Sistema de Rastreamento de Drones de Resgate (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyRescue" é uma organização humanitária que utiliza drones para entregar suprimentos médicos em áreas de difícil acesso. Eles precisam de um sistema de controle de missão que seja **extremamente confiável**. Falhas no software podem significar perda de equipamentos ou, pior, falha na entrega de remédios vitais.

## 🛠️ Necessidade Técnica

Este desafio integra os conhecimentos das Atividades 01 a 03:

1. **Enums e Pattern Matching:** Para gerenciar o estado dos drones e os níveis de prioridade dos suprimentos.
2. **Ownership (Posse):** Para garantir que cada relatório de missão tenha um dono único e seja processado corretamente pela central de comando.
3. **Imutabilidade e Tipagem:** Para cálculos de autonomia e carga.
4. **Testes Unitários:** Para validar a segurança da decolagem e o processamento de riscos.

## 📋 Requisitos Funcionais

1. Definir um enum `StatusDrone` (Disponivel, EmMissao, Manutencao).
2. Definir um enum `PrioridadeCarga` (Baixa, Media, Alta).
3. Implementar uma função `analisar_risco(carga: PrioridadeCarga, clima_ruim: bool) -> bool` que retorna se a missão é arriscada.
4. Criar uma função `processar_missao(log: String)` que toma a posse do log da missão e o "arquiva" (imprime no console).
5. O programa deve simular o ciclo de vida de uma missão, da triagem do drone ao arquivamento do log.

## ⚠️ Análise de Falha Crítica

Nesta missão crítica, identificamos os seguintes riscos técnicos:
1. **Riscos de Panics em Missão Crítica:** O uso de `.unwrap()` ou indexação direta em vetores de telemetria sem verificação pode causar um crash instantâneo do drone no campo. Deve-se priorizar o uso de `match` ou `if let`.
2. **Esgotamento de Memória (OOM):** Logs de missão gerados em loops infinitos sem limpeza (Ownership properly handled) podem travar o hardware embarcado.
3. **Corrupção de Estado:** Falhas na transição entre `StatusDrone` podem autorizar decolagens de drones em manutenção.

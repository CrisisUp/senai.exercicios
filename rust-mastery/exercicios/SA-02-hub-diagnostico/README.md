# 🛰️ SA-02: Hub de Diagnóstico de Frota (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyCargo" centralizou o monitoramento de seus drones em um **Hub de Diagnóstico**. O sistema recebe referências de telemetria de vários drones e deve identificar qual drone apresenta o erro mais crítico. O desafio é que o sistema não pode "possuir" (own) os dados dos drones (pois eles pertencem ao sistema de voo), apenas "pedir emprestado" (borrow) para análise rápida.

## 🛠️ Necessidade Técnica

Este desafio integra os conhecimentos das Atividades 04 a 06:

1. **Borrowing:** Passar referências de telemetria para o Hub sem duplicar dados na memória.
2. **Option e Result:** Tratar casos onde drones estão offline ou onde a leitura está fora dos limites.
3. **Lifetimes:** Garantir que o alerta retornado pelo Hub seja uma referência válida para a string original do erro.

## 📋 Requisitos Funcionais

1. Criar uma struct `Drone` com ID e nível de bateria.
2. Implementar uma função `verificar_bateria(d: &Drone) -> Result<(), &'static str>` que valida se a bateria está acima de 15%.
3. Implementar uma função `comparar_alertas<'a>(msg1: &'a str, msg2: &'a str) -> &'a str` que seleciona a mensagem de erro mais longa (mais detalhada).
4. Simular o diagnóstico de uma frota no `main`, exibindo o relatório final.

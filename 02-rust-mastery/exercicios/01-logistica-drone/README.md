# 🦀 Atividade 01: Logística de Drone (Imutabilidade e Tipos)

STATUS: Padrão de Engenharia de Elite Aplicado

## 🎯 Estudo de Caso

A startup "SkyCargo" entrega pacotes via drone. O sistema precisa calcular se um drone pode decolar com base no peso da carga e na carga da bateria.

## 🛠️ Necessidade Técnica

Em Rust, a segurança começa na variável. A linguagem garante que dados não sejam alterados acidentalmente e que tipos sejam consistentes desde o "nascimento" na memória.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL SEGURANÇA DE MEMÓRIA)

- RISCO DE ARITHMETIC OVERFLOW: Se realizássemos cálculos complexos de empuxo, um estouro de valor causaria um `panic` no Rust (travamento seguro), prevenindo cálculos errados que derrubariam o drone físico.
- RISCO DE FLOATING POINT PRECISION: O uso de `f64` é adequado para física, mas seria proibido para faturamento de frete. Para dinheiro, usaríamos a medalha **Guardião Financeiro** (Cents as Integers).
- RISCO DE DATA RACE: Como as variáveis são imutáveis por padrão, o Rust garante que múltiplos sensores possam ler o peso sem risco de corrupção de dados.

## 📋 Requisitos de Elite

1. Implementação de lógica booleana resiliente.
2. Uso de imutabilidade estrita para constantes de voo.
3. Cobertura de Testes Unitários de 100% para cenários de borda.

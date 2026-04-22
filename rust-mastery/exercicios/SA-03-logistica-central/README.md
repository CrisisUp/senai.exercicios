# 📦 SA-03: Sistema de Logística de Armazém Central (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyCargo" expandiu suas operações e agora possui um **Armazém Central**. Este armazém precisa gerenciar milhares de pacotes e centenas de rotas de entrega. O sistema anterior era manual e lento. O novo sistema deve permitir o rastreamento instantâneo de pacotes, o cálculo de carga por drone e a gestão de clientes prioritários.

## 🛠️ Necessidade Técnica

Este desafio integra os conhecimentos das Atividades 07 a 09:

1. **Structs e Métodos:** Para modelar o `Pacote` e o próprio `Armazem`.
2. **Vetores e Iteradores:** Para gerenciar a lista física de pacotes no estoque e realizar cálculos de peso total de forma eficiente.
3. **HashMap:** Para criar um índice de rastreio que permite encontrar a localização/status de um pacote via ID em tempo recorde.

## 📋 Requisitos Funcionais

1. Criar uma struct `Pacote` com ID único, descrição, peso e destinatário.
2. Criar uma struct `Armazem` que contém:
    - Um `Vec<Pacote>` para o estoque físico.
    - Um `HashMap<String, usize>` que mapeia o ID do pacote para sua posição no vetor (índice).
3. Implementar métodos no `Armazem`:
    - `registrar_entrada(&mut self, p: Pacote)`: Adiciona ao vetor e atualiza o mapa de índices.
    - `buscar_pacote(&self, id: &str) -> Option<&Pacote>`: Localiza o pacote usando o mapa.
    - `calcular_carga_total(&self) -> f64`: Soma o peso de todo o estoque usando iteradores.
4. Simular uma operação de pico no `main`, demonstrando a eficiência da busca e do processamento de carga.

## ⚠️ Análise de Falha Crítica

Neste sistema de logística, identificamos os seguintes gargalos de performance e riscos:
1. **Performance Bottlenecks em Logística:** O crescimento desordenado do `Vec` de estantes causa realocações massivas na memória. Usar `Vec::with_capacity()` é essencial para operações de larga escala.
2. **Inconsistência de Índice:** Se um pacote for removido do `Vec` sem atualizar o `HashMap`, teremos uma falha catastrófica de busca (Dangling Index).
3. **Custo de Clonagem:** O uso de `.clone()` no ID para o HashMap duplica o uso de memória por ID. Em sistemas com milhões de pacotes, isso pode levar ao transbordamento da RAM.

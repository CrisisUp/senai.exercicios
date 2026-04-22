# 🦀 Atividade 11: Transmissão Genérica (Generics e Trait Bounds)

## 🎯 Estudo de Caso

O sistema da "SkyCargo" precisa enviar dados do drone para a base. No entanto, os dados podem ser de diversos tipos: coordenadas de GPS (`Telemetria`), mensagens de texto (`String`), ou níveis de carga (`u32`). Em vez de criar uma função de envio para cada tipo, queremos uma única função genérica que saiba transmitir QUALQUER dado, desde que ele saiba como se formatar para o rádio.

## 🛠️ Necessidade Técnica

Em Rust, os **Generics** permitem escrever código que funciona com múltiplos tipos, mantendo a performance do código estático (monomorfização):

* **Generics (`<T>`):** Define um tipo coringa.
* **Trait Bounds (`T: Trait`):** Restringe o tipo `T` a apenas aqueles que implementam uma funcionalidade específica.
* **Static Dispatch:** O compilador gera uma versão da função para cada tipo usado, resultando em execução ultra-rápida (sem vtable).

## 📋 Requisitos

1. Definir a trait `Transmissivel` com o método `formatar_pacote(&self) -> String`.
2. Criar a struct `MensagemVoo` que implementa `Transmissivel`.
3. Criar a struct `DadosGPS` que implementa `Transmissivel`.
4. Implementar a função genérica `transmitir_via_radio<T: Transmissivel>(dado: T)` que simula o envio.
5. Demonstrar o uso da sintaxe `where` para organizar os bounds (limites) de tipos genéricos complexos.

## ⚠️ Análise de Falha Crítica

Nesta atividade, exploramos o poder dos **Generics**, mas é vital entender os riscos associados à infraestrutura de baixo nível:

1.  **Monomorfização e Code Bloat:** Embora o Static Dispatch seja extremamente rápido, o compilador gera uma cópia da função para cada tipo `T`. Em sistemas com restrição de memória (embarcados), o uso excessivo de generics pode inflar o binário (Code Bloat).
2.  **Custo de Dynamic Dispatch:** Se trocássemos `transmitir_via_radio<T: Transmissivel>` por `transmitir_via_radio(dado: &dyn Transmissivel)`, estaríamos usando **Dynamic Dispatch**. Isso economiza espaço no binário, mas introduz um custo de runtime devido à busca na `vtable` e impede algumas otimizações de inline do compilador.
3.  **Heap Fragmentation:** Embora os generics em si não causem fragmentação, o uso de `String` (como em `formatar_pacote`) envolve alocações na Heap. Em sistemas de tempo real, preferimos `&str` ou buffers fixos para evitar que a heap fique fragmentada ao longo do tempo.
4.  **Riscos de Deadlock:** Embora não tenhamos concorrência aqui, o uso de tipos genéricos dentro de `Arc<Mutex<T>>` exige cuidado redobrado para garantir que a ordem de aquisição dos locks seja consistente, evitando travamentos fatais no sistema de telemetria.

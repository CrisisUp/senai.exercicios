# 🤖 SA-06: Simulador de Fábrica Automata (Desafio Integrador)

## 🎯 Estudo de Caso

A "SkyCargo" inaugurou sua primeira fábrica automatizada de drones. O sistema de controle da fábrica é composto por robôs montadores que seguem um fluxo rigoroso de estados. As peças montadas são empilhadas em uma estrutura de dados customizada e o peso final das remessas é calculado automaticamente. Para garantir a performance, um módulo legado em C realiza o "stress test" das juntas dos robôs.

## 🛠️ Necessidade Técnica

Este desafio integra os conhecimentos avançados do Nível 32 (Atividades 17 a 20):

1. **Type States:** Para garantir que um robô não tente montar uma peça antes de estar devidamente carregado.
2. **Lista Ligada (Custom Stack):** Para armazenar o histórico de peças produzidas na linha de montagem.
3. **Sobrecarga de Operadores:** Para somar a massa das peças produzidas (`Peça + Peça`).
4. **Ponteiros Crus / FFI:** Para integrar com o sistema de log de performance em C (simulado ou real).
5. **Interatividade:** Um menu completo para operar a fábrica.

## 📋 Requisitos Funcionais

1. Definir estados para o robô: `Ocioso`, `Carregado`, `Montando`.
2. Implementar a transição segura entre esses estados usando Ownership.
3. Criar a struct `Peca` com massa e implementar o trait `Add`.
4. Utilizar uma `ListaLigada` manual (baseada em `Box`) para o estoque de saída.
5. Criar uma interface onde o usuário possa:
    - Comandar o robô para pegar uma peça (Ocioso -> Carregado).
    - Comandar a montagem (Carregado -> Montando -> Ocioso).
    - Ver a pilha de produção.
    - Calcular a massa total da pilha.

---

## ⚠️ Análise de Falha Crítica (Engenharia de Confiabilidade)

Em uma fábrica automatizada, a integração entre software de alto nível e hardware legado (C) exige vigilância:

1. **Riscos de Race Conditions:** Se múltiplos robôs compartilhassem a mesma `LinhaProducao` sem proteção de exclusão mútua (`Arc<Mutex<T>>`), a estrutura da lista ligada (ponteiros `Box`) poderia ser corrompida durante um `empilhar` simultâneo, resultando em "Dangling Pointers" ou segfaults no momento da leitura.
2. **Transactional Inconsistency:** A transição de estado do robô (`Carregado -> Montando`) deve ser atômica com o consumo da peça. No Rust, o uso de `Type States` garante que, se a função `iniciar_montagem` falhar ou o programa crashar, a peça não "desaparece" nem "duplica", pois a posse (Ownership) é transferida de forma unívoca.
3. **Buffer Overflows em Sockets:** Na comunicação entre o controlador Rust e os sensores da fábrica via rede, pacotes malformados poderiam tentar injetar dados além da capacidade do buffer de recepção. O Rust previne isso nativamente, mas o perigo aumenta na fronteira FFI com o C. O desenvolvedor deve garantir que os dados passados para o `stress_test_c` estejam sanitizados para evitar estouros de pilha no módulo legado.

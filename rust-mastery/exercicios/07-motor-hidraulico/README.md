# 🦀 Atividade 07: Controle de Motor (Structs e Métodos)

## 🎯 Estudo de Caso

A "SkyCargo" está desenvolvendo motores hidráulicos para drones de carga pesada. Cada motor possui um estado interno (pressão, temperatura e se está ligado). Precisamos encapsular esse comportamento em uma estrutura que saiba se auto-gerenciar, permitindo ligar, desligar e ajustar a potência com segurança.

## 🛠️ Necessidade Técnica

Em Rust, usamos **Structs** para armazenar dados e blocos **`impl`** para definir comportamentos (métodos):

* **Structs de Dados:** Agrupam campos relacionados.
* **Métodos (`self`):** Funções que operam sobre uma instância da struct.
  * `&self`: Acesso de leitura.
  * `&mut self`: Acesso de escrita (alteração do estado).
* **Funções Associadas:** Como o `new()`, usadas para criar novas instâncias (semelhante a construtores).

## 📋 Requisitos

1. Criar a struct `MotorHidraulico`.
2. Implementar uma função associada `new(id: u32)` que inicializa o motor desligado e com pressão zero.
3. Implementar o método `ligar(&mut self)` que altera o estado.
4. Implementar o método `ajustar_pressao(&mut self, psi: f64)` com validação de segurança (não permitir pressão negativa ou acima de 5000 PSI).
4. Implementar o método `status(&self)` para exibir as informações atuais.

## ⚠️ Análise de Falha Crítica

*   **Riscos de Panic:** O uso de `unwrap()` em operações de entrada de dados ou em cálculos sem verificação pode levar ao encerramento abrupto do programa. Sempre prefira `Result` ou `Option`.
*   **Heap Exhaustion:** Embora structs simples fiquem na stack, o uso excessivo de `String` ou `Vec` dentro de structs em loops infinitos sem limpeza pode esgotar a memória heap em sistemas embarcados.
*   **Trait Misuse:** Implementar traits como `Copy` em structs que gerenciam recursos externos (como handles de arquivos ou conexões) pode causar inconsistências de estado e bugs difíceis de rastrear.


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
5. Implementar o método `status(&self)` para exibir as informações atuais.

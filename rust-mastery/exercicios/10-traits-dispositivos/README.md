# 🦀 Atividade 10: Protocolos de Hardware (Traits e Interfaces)

## 🎯 Estudo de Caso

Um drone de resgate é composto por diversos componentes de hardware: Câmeras Térmicas, Módulos GPS e Motores de Propulsão. Embora cada um funcione de forma diferente, todos precisam responder a comandos básicos do sistema central, como "verificar status" e "reiniciar". Em vez de tratar cada hardware como um tipo isolado, queremos tratá-los de forma **Polimórfica**.

## 🛠️ Necessidade Técnica

Em Rust, não existe herança de classes como no C++. Usamos **Traits** para definir interfaces:

* **Traits:** Definem um conjunto de métodos que um tipo deve implementar. É o equivalente a uma interface em Java ou uma classe puramente abstrata em C++.
* **Polimorfismo (Static Dispatch):** Usando Generics com limites de Trait (`T: MyTrait`).
* **Polimorfismo (Dynamic Dispatch):** Usando Objetos de Trait (`Box<dyn MyTrait>`), permitindo armazenar diferentes tipos em uma mesma coleção.

## 📋 Requisitos

1. Definir a trait `Dispositivo` com os métodos `status(&self) -> String` e `reiniciar(&mut self)`.
2. Criar a struct `SensorGPS` que implementa `Dispositivo`.
3. Criar a struct `Motor` que implementa `Dispositivo`.
4. Implementar uma função `diagnostico_geral` que recebe uma lista de diferentes dispositivos e executa o status de cada um.
5. Usar `Box<dyn Dispositivo>` para demonstrar o polimorfismo em coleções.

## 🛡️ Análise de Falha Crítica

Nesta atividade, exploramos o polimorfismo e seus riscos:

1.  **Riscos de Hash Collision:** Embora menos relevante aqui, se usássemos Traits como chaves de um HashMap, a implementação de `Hash` precisaria ser consistente.
2.  **Panic em Option/Result:** O uso de `Box<dyn Trait>` pode levar a tentativas de downcasting manual (`downcast_ref`), que retornam `Option`. Ignorar o `None` resultaria em falhas.
3.  **Trait Bounds Complexity:** O uso excessivo de múltiplos bounds (`T: A + B + C`) pode tornar a assinatura de funções ilegível e difícil de implementar para novos tipos, um fenômeno conhecido como "Trait Soup".

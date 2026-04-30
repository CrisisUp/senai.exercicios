# 🦀 Atividade 20: Estados por Tipo (Type States e Segurança de Máquina de Estados)

## 🎯 Estudo de Caso

A "SkyCargo" quer garantir que um drone nunca tente decolar se estiver em **Manutenção** ou se já estiver **Em Voo**. Usar apenas um `enum` com `match` em tempo de execução funciona, mas erros de lógica ainda podem passar despercebidos pelo programador. O desafio é usar o **Sistema de Tipos do Rust** para tornar esses erros impossíveis de compilar. Se o programador tentar chamar `.decolar()` em um drone em manutenção, o código nem gera o executável.

## 🛠️ Necessidade Técnica

O padrão **Type State** utiliza o sistema de tipos para representar os estados de um objeto:

* **Zero-Sized Structs (Marcadores):** Structs vazias que servem apenas para diferenciar tipos em tempo de compilação.
* **Generics:** A struct principal (Drone) é genérica sobre o seu estado.
* **Ownership (`self`):** Métodos de transição de estado consomem o objeto atual e retornam um novo objeto com um novo tipo de estado.
* **Implementações Específicas:** Definimos métodos que existem apenas para determinados estados (ex: `.decolar()` existe para `Drone<Terra>`, mas não para `Drone<Voo>`).

## 📋 Requisitos

1. Criar structs marcadoras: `Terra`, `Voo` e `Manutencao`.
2. Criar a struct `Drone<S>` onde `S` representa o estado.
3. Implementar o método `preparar_para_voo()` que move o drone de `Manutencao` para `Terra`.
4. Implementar o método `decolar()` que move o drone de `Terra` para `Voo`.
5. Implementar o método `pousar()` que move o drone de `Voo` para `Terra`.
6. Criar uma interface interativa onde o usuário tenta mover o drone entre estados.

## 🛡️ Análise de Falha Crítica: Illegal State Transitions

A maioria dos bugs de segurança em drones ocorre por comandos enviados em estados inválidos (ex: desligar motor em voo). Sistemas baseados em `if` ou `switch` são frágeis porque dependem da atenção do programador.

*   **Risco Crítico:** Tentar decolar sem passar pela calibração (Manutenção -> Terra).
*   **A Abordagem Elite:** Type States bloqueiam o erro no nascimento. Como o método `.decolar()` só existe na implementação `impl Drone<Terra>`, se você tentar chamá-lo num `Drone<Manutencao>`, o compilador emite um erro de "método não encontrado".
*   **Segurança de Propriedade:** Ao usar o consumo do `self` (`fn decolar(self)`), garantimos que o drone antigo (em Terra) não possa mais ser usado após a transição para o drone novo (em Voo). O estado "zumbi" (usar o drone em dois estados ao mesmo tempo) é impossível.

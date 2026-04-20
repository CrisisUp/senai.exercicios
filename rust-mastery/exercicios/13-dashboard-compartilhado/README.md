# 🦀 Atividade 13: Dashboard Compartilhado (Rc e Entrada de Dados)

## 🎯 Estudo de Caso

O sistema da "SkyCargo" agora possui um **Dashboard de Telemetria**. Este dashboard precisa ser acessado simultaneamente por:

1. O Sistema de Voo (Escrita).
2. O Painel do Piloto (Leitura).
3. O Gravador de Caixa Preta (Leitura).

Para que o dado de telemetria não seja destruído enquanto um deles ainda o usa, precisamos de um ponteiro **`Rc`**. Além disso, o usuário poderá decidir via teclado quantos observadores deseja conectar ao sistema.

## 🛠️ Necessidade Técnica

* **`std::rc::Rc<T>` (Reference Counting):** Permite que um valor tenha múltiplos donos no mesmo thread. Cada vez que você dá um `.clone()` no `Rc`, ele incrementa um contador interno em vez de copiar o dado.
* **`std::io::stdin()`:** Canal para ler o que o usuário digita.
* **`trim()` e `parse()`:** Essenciais para limpar o "Enter" da entrada do usuário e converter texto em números.

## 📋 Requisitos

1. Criar a struct `Telemetria` com os dados do drone.
2. Usar `Rc<Telemetria>` para compartilhar o estado entre diferentes variáveis.
3. Solicitar ao usuário, via terminal, o nome do Drone e o número de sistemas de monitoramento a serem ativados.
4. Exibir o **Contador de Referências** (`Rc::strong_count`) para provar que o Rust está rastreando os donos corretamente.

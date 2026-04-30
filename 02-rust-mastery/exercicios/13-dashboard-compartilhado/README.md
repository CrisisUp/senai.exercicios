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

## ⚠️ Análise de Falha Crítica

O uso de `Rc<T>` é uma ferramenta de flexibilidade, mas introduz riscos que o engenheiro de elite deve prever:

1.  **Vazamento de Memória (Reference Cycles):** Se dois `Rc` apontarem um para o outro (ex: A -> B e B -> A), o contador nunca chegará a zero, causando um memory leak silencioso. O uso de `Weak<T>` é a cura para este problema.
2.  **Incompatibilidade com Threads:** O `Rc` **não é Thread-Safe**. Tentar movê-lo para outra thread causará erro de compilação. Para concorrência, o `Arc` (Atomic Reference Counting) é obrigatório, embora tenha um custo maior de performance.
3.  **Heap Fragmentation:** Cada `Rc::new()` aloca o dado E o contador de referências na Heap. Milhares de pequenas alocações de `Rc` podem fragmentar a memória em sistemas de longa duração.
4.  **Imutabilidade por Padrão:** O `Rc` permite múltiplos donos, mas apenas para **leitura**. Para permitir escrita compartilhada, ele deve ser combinado com `RefCell<T>` (Interior Mutability), o que introduz verificações de empréstimo em tempo de execução e risco de panic se violadas.

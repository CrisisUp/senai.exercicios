# 🦀 Atividade 05: Diagnóstico de Sensores (Option e Result)

## 🎯 Estudo de Caso
A "SkyCargo" precisa de um sistema de diagnóstico para os sensores dos drones. Dois problemas são comuns:
1.  **Sensor Ausente:** Um sensor pode não estar instalado ou não ser detectado.
2.  **Erro de Leitura:** O sensor está lá, mas enviou um dado corrompido ou inválido.

Antigamente (em C ou C++ antigo), usávamos `-1` ou `NULL` para indicar erro, o que causava muitos crashes. O Rust resolve isso com os tipos `Option` e `Result`.

## 🛠️ Necessidade Técnica
*   **`Option<T>`:** Usado quando um valor pode ou não existir.
    *   `Some(v)`: O valor existe.
    *   `None`: O valor não existe (sem riscos de ponteiro nulo).
*   **`Result<T, E>`:** Usado quando uma operação pode falhar.
    *   `Ok(v)`: A operação deu certo.
    *   `Err(e)`: A operação falhou com um erro específico.
*   **O Operador `?`:** Facilita a propagação de erros de forma elegante.

## 📋 Requisitos
1. Criar uma função `ler_temperatura_sensor(id: i32) -> Option<f64>` (Simula sensor presente/ausente).
2. Criar uma função `validar_leitura(temp: f64) -> Result<f64, String>` (Valida se a temperatura está na faixa segura).
3. Criar uma função `gerar_diagnostico(id: i32) -> Result<String, String>` que une as duas anteriores usando o operador `?` ou `match`.
### 4. Implementar testes unitários para todos os casos de sucesso e falha.

## 🛡️ Análise de Falha Crítica (Refatoração de Elite)

*   **Riscos de Panic:** O uso de `.unwrap()` em `Option` ou `Result` é um risco de Panic se o valor for `None` ou `Err`. A refatoração utiliza o operador `?` e `match` para garantir que o programa nunca sofra um crash inesperado.
*   **Use-after-move:** Ao retornar `Result<String, String>`, a posse da string de erro ou sucesso é transferida para o chamador, garantindo que a memória seja limpa após o uso no loop `main`.
*   **Borrow Checker Errors:** O uso de `format!` cria novas `Strings` no Heap. Em sistemas de alta performance, poderíamos usar `&'static str` para erros constantes para evitar alocações desnecessárias.
*   **Memory Overheads:** `Option<f64>` ocupa apenas o espaço de um `f64` mais um byte de tag (com otimização de nicho em alguns tipos). É uma abstração de custo zero comparada ao uso de códigos de erro mágicos.


# 🦀 Atividade 16: Cálculos Legados (Unsafe e FFI)

## 🎯 Estudo de Caso

Para economizar bateria, os drones da "SkyCargo" usam um chip matemático antigo, cuja biblioteca de controle foi escrita em **C** há 20 anos. O Rust deve enviar o valor da aceleração para essa biblioteca e receber o cálculo de torque necessário. Como o chip não tem as garantias de segurança do Rust, precisamos usar o modo `unsafe`.

## 🛠️ Necessidade Técnica

* **FFI (Foreign Function Interface):** Permite que o Rust "fale" com outras linguagens.
* **`extern "C"`:** Define a convenção de chamada de funções compatível com o C.
* **Unsafe:** O Rust não pode garantir que o código C não vá corromper a memória ou ter ponteiros nulos. Por isso, toda chamada FFI é obrigatoriamente `unsafe`.
* **Ponteiros Crus (`*const i32`):** Passagem de dados por endereço de memória, sem Borrow Checker.

## 📋 Requisitos

1. Criar um arquivo `math_motor.c` com a função `calcular_torque_c`.
2. Criar um `build.rs` para compilar o código C automaticamente.
3. Declarar a interface externa no Rust.
4. Solicitar ao usuário o valor da aceleração via terminal.
5. Chamar a função C dentro de um bloco `unsafe` e exibir o resultado.

## ⚠️ Análise de Falha Crítica

* **Deadlocks:** Não se aplica diretamente ao FFI simples, mas se o código C usar mutexes internos, o Rust não terá visibilidade sobre eles, podendo causar deadlocks invisíveis ao Borrow Checker.
* **Send/Sync Violations:** Ponteiros crus (`*const T`, `*mut T`) não implementam `Send` nem `Sync`. Passar ponteiros vindos do C entre threads Rust exige cautela extrema e wrappers seguros (Newtype pattern).
* **Stack vs Heap:** O Rust passa argumentos pela **Stack** (seguindo a ABI do C). Se o C alocar memória no Heap dele, o Rust **NÃO** pode liberá-la usando `drop()`; é necessário uma função C correspondente para desalocação (evitando memory leaks).

# 🦀 Atividade 15: Concorrência Segura (Arc, Mutex e Threads)

## 🎯 Estudo de Caso

A frota da "SkyCargo" cresceu tanto que a central de comando não consegue mais processar todos os logs de voo em uma única CPU de forma sequencial. Precisamos processar os dados de múltiplos drones em **paralelo** (usando Threads). O desafio: todos os processos precisam atualizar um **Contador Global de Quilometragem** sem causar conflitos de memória (*race conditions*).

## 🛠️ Necessidade Técnica

Em Rust, a concorrência é "destemida" (*fearless concurrency*). O compilador garante que você não acesse dados de forma insegura entre threads:

* **`std::thread::spawn`:** Cria uma nova linha de execução (Thread).
* **`std::sync::Arc<T>` (Atomic Reference Counting):** É a versão do `Rc` que pode ser compartilhada com segurança entre múltiplas threads.
* **`std::sync::Mutex<T>` (Mutual Exclusion):** Garante que apenas uma thread por vez possa alterar o dado interno.
* **`lock().unwrap()`:** Solicita acesso ao dado. Se outra thread estiver usando, a atual espera sua vez.

## 📋 Requisitos

1. Criar uma variável global `quilometragem_total` protegida por um `Arc<Mutex<f64>>`.
2. Solicitar ao usuário o número de drones que estão em voo (número de threads).
3. Cada thread deve simular uma viagem de drone e somar um valor aleatório (ou fixo) à quilometragem total.
4. Usar `join()` para garantir que o programa principal espere todas as threads terminarem antes de exibir o resultado final.

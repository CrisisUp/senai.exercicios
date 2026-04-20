# 🦀 Atividade 17: Buffer Compartilhado (Ponteiros Crus e FFI)

## 🎯 Estudo de Caso

A "SkyCargo" precisa processar grandes volumes de dados de imagem dos drones em tempo real. O processamento pesado de pixels é feito por um algoritmo legado em **C**, mas a gestão de memória e a interface com o usuário devem ser feitas em **Rust**. Precisamos alocar um buffer de memória no Rust, passar o ponteiro para o C para que ele preencha com dados simulados, e então ler o resultado de volta no Rust usando aritmética de ponteiros.

## 🛠️ Necessidade Técnica

No **Nível 32 (Engenheiro de Performance)**, exploramos a manipulação direta de memória:

* **Ponteiros Crus (`*mut T` e `*const T`):** Diferente das referências, eles não têm tempos de vida (lifetimes) rastreados pelo compilador e podem ser nulos.
* **Aritmética de Ponteiros:** Avançar ou recuar endereços de memória manualmente.
* **Alocação Manual:** Garantir que o buffer passado para o C seja válido durante toda a execução da função externa.

## 📋 Requisitos

1. Criar um arquivo `buffer_handler.c` com a função `processar_buffer_c(int* buffer, int tamanho)`.
2. Criar um `build.rs` para compilar o código C.
3. No Rust, solicitar ao usuário o número de elementos para o buffer.
4. Alocar um `Vec<i32>` e converter seu ponteiro para um ponteiro cru mutável.
5. Chamar a função C dentro de um bloco `unsafe`.
6. Exibir os dados processados pelo C no terminal Rust.

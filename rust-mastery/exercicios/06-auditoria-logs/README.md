# 🦀 Atividade 06: Auditoria de Logs (Lifetimes / Tempos de Vida)

## 🎯 Estudo de Caso

A "SkyCargo" armazena centenas de logs de voo. O sistema de auditoria precisa comparar dois logs e extrair uma referência para o log mais longo ou mais importante. Em linguagens como C++, retornar uma referência para algo recebido por parâmetro é perigoso (o dado original pode morrer e a referência virar um "ponteiro fantasma"). O Rust resolve isso com **Lifetimes**.

## 🛠️ Necessidade Técnica

**Lifetimes (Anotações de Tempo de Vida):**

* São metadados para o compilador (`'a`).
* Eles não mudam quanto tempo um objeto vive, eles apenas **descrevem** a relação entre os tempos de vida de diferentes referências.
* **Regra:** O compilador deve garantir que quem recebe a referência (retorno da função) não viva mais do que quem deu a referência (parâmetros).

## 📋 Requisitos

1. Criar uma função `comparar_logs<'a>(log1: &'a str, log2: &'a str) -> &'a str` que retorna a string mais longa.
2. Explicar por que a anotação `'a` é necessária (ajuda o compilador a entender que o retorno é válido enquanto AMBOS os parâmetros forem válidos).
3. Demonstrar no `main` um caso onde o tempo de vida é respeitado.
4. Demonstrar (em comentário) o erro que ocorreria se tentássemos usar uma referência após o objeto original sair de escopo.

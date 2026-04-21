# 🦀 Atividade 19: Gestão de Energia Modular (Sobrecarga de Operadores)

## 🎯 Estudo de Caso

A "SkyCargo" utiliza packs de bateria modulares em seus drones. Para facilitar o trabalho dos engenheiros, o sistema deve permitir que dois packs de bateria sejam "somados" para obter a capacidade total disponível, ou que um valor de consumo seja "subtraído" diretamente do pack usando operadores matemáticos padrão (`+`, `-`).

## 🛠️ Necessidade Técnica

Em Rust, a **Sobrecarga de Operadores (Operator Overloading)** não é feita de forma arbitrária como no C++. Ela é feita através da implementação de **Traits Específicas** da biblioteca padrão (`std::ops`):

* **`Add`:** Para o operador `+`.
* **`Sub`:** Para o operador `-`.
* **`Display`:** Para personalizar como o objeto é impresso (equivalente ao `<<` do C++).
* **Benefício:** Torna o código muito mais legível e expressivo, mantendo a segurança de tipos.

## 📋 Requisitos

1. Criar a struct `PackBateria` com o campo `capacidade_mah` (f64).
2. Implementar o Trait `std::ops::Add` para somar dois packs.
3. Implementar o Trait `std::ops::Sub` para subtrair consumo de um pack.
4. Implementar o Trait `std::fmt::Display` para exibir o pack de forma amigável.
5. Criar uma interface interativa onde o usuário insere as capacidades de dois packs e vê a soma em tempo real.

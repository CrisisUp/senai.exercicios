# 🦀 Atividade 01: Logística de Drone (Imutabilidade e Tipos)

## 🎯 Estudo de Caso

A startup "SkyCargo" entrega pacotes via drone. O sistema precisa calcular se um drone pode decolar com base no peso da carga e na carga da bateria.

## 🛠️ Necessidade Técnica

Em Rust, a segurança começa na variável:

* **Imutabilidade:** Variáveis são `let x = 5` (não mudam). Para mudar, use `let mut x = 5`.
* **Shadowing:** Podemos "esconder" uma variável criando uma nova com o mesmo nome (útil para transformações de dados).
* **Funções:** Devem ter tipos de retorno e parâmetros definidos explicitamente.

## 📋 Requisitos

1. Criar uma função `pode_decolar(peso: f64, bateria: f64) -> bool`.
2. O drone só decola se o peso for menor que 5.0kg e a bateria maior que 20.0%.
3. Criar testes unitários usando `#[cfg(test)]` para validar a lógica.

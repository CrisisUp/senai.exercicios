# 🦀 Atividade 14: Calibração Dinâmica (RefCell e Mutabilidade Interior)

## 🎯 Estudo de Caso

O sistema de telemetria da "SkyCargo" (SA-02) agora permite a calibração de sensores em pleno voo. O problema: o objeto de hardware está envolto em um `Rc` para ser compartilhado por vários sistemas, e o `Rc` não permite mutação por padrão. Precisamos de uma forma de "burlar" essa imutabilidade externa para ajustar os valores internos do sensor, mantendo a segurança do Rust.

## 🛠️ Necessidade Técnica

Em Rust, quando um dado é compartilhado (via `&` ou `Rc`), ele torna-se imutável. Para alterar dados compartilhados, usamos a **Mutabilidade Interior (Interior Mutability)**:

* **`std::cell::RefCell<T>`:** Permite alterar dados mesmo através de referências imutáveis.
* **Borrowing em Runtime:** Diferente do Rust normal, o `RefCell` verifica as regras de empréstimo (um escritor ou muitos leitores) em **tempo de execução**. Se você tentar violar as regras, o programa entrará em pânico (*panic*).
* **Padrão Comum:** `Rc<RefCell<T>>` é a combinação clássica para ter múltiplos donos que podem todos alterar o mesmo dado.

## 📋 Requisitos

1. Criar a struct `SensorCalibragem` com o campo `fator_correcao` (f64).
2. Envolver a struct em um `Rc<RefCell<SensorCalibragem>>`.
3. Criar uma função que simula um sistema de monitoramento (leitura).
4. Criar uma função que solicita ao usuário um novo valor de calibração (escrita).
5. Demonstrar que todos os sistemas enxergam a mudança instantaneamente.

## ⚠️ Análise de Falha Crítica
- **Deadlocks:** Embora o `RefCell` não cause deadlocks tradicionais de threads (pois opera em thread única), ele causa **Panic em Runtime** se houver violação de empréstimo (ex: tentar `borrow_mut()` enquanto um `borrow()` ainda está ativo).
- **Send/Sync Violations:** `Rc<T>` e `RefCell<T>` **NÃO** implementam `Send` nem `Sync`. Isso significa que eles não podem ser transferidos ou compartilhados entre threads. Tentar usá-los com `std::thread::spawn` resultará em erro de compilação.
- **Stack vs Heap:** O `Rc` aloca o contador de referências e o dado no **Heap**. O `RefCell` adiciona um pequeno overhead de um `isize` (contador de borrows) também no Heap (dentro do Rc).

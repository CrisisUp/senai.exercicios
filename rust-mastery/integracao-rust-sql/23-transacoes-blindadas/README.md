# 🦀🗄️ Atividade Integradora 23: Transações Blindadas

## 🎯 Estudo de Caso

A "SkyCargo" realiza transferências de baterias do armazém para os drones. Se o Rust conseguir retirar a bateria do armazém, mas falhar ao registrá-la no drone (por um erro de rede ou lógica), o sistema deve desfazer tudo automaticamente.

## 🛠️ Necessidade Técnica

Em Rust, usamos o objeto `Transaction`:

* **Atomicidade Automática:** O Rust abre a transação e, se o programa entrar em pânico ou retornar um erro antes do `commit()`, o banco de dados desfaz tudo sozinho.
* **Gestão de Erros:** Unimos o `Result<T>` do Rust com o `ROLLBACK` do SQL.

## 📋 Requisitos

1. Conectar ao banco da Atividade 06 de SQL.
2. Iniciar uma transação via Rust.
3. Diminuir a quantidade em `estoque_geral`.
4. Aumentar a quantidade em `carga_drone`.
5. Demonstrar o cancelamento (Rollback) simulando um erro no meio do processo.

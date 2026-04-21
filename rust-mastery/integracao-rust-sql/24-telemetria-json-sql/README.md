# 🦀🗄️ Atividade Integradora 24: Telemetria IoT com JSON

## 🎯 Estudo de Caso

A "SkyCargo" utiliza sensores experimentais que geram dados muito variados. Em
vez de mudar a estrutura do banco de dados toda vez que um sensor novo é
adicionado, decidimos usar uma coluna de texto JSON. O Rust deve ser capaz de
transformar suas structs internas em JSON para salvar no banco e vice-versa.

## 🛠️ Necessidade Técnica

Este exercício demonstra a integração de serialização com banco de dados:

* **Serde:** O framework definitivo do Rust para converter dados (`Serialize` e `Deserialize`).
* **JSON no SQLite:** Usando as funções que aprendemos na trilha SQL para validar e extrair dados.
* **Tipagem Flexível:** O Rust garante que o JSON tenha os campos certos antes de enviá-lo ao banco.

## 📋 Requisitos

1. Conectar ao banco da Atividade 13 de SQL (`telemetria_avancada`).
2. Definir a struct `DadosSensores` no Rust com campos como `temp` e `bateria`.
3. Serializar a struct para uma String JSON.
4. Salvar no banco usando o comando **UPSERT** (Atividade 13 SQL).
5. Ler os dados do banco e deserializar de volta para a struct Rust.

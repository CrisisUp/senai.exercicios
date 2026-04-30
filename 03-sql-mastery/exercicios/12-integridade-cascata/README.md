# 🗄️ Atividade 12: Integridade de Ferro (Constraints e Cascatas)

## 🎯 Estudo de Caso

A "SkyCargo" precisa garantir que seus dados sejam impecáveis. Tivemos problemas no passado: usuários cadastrando drones com horas negativas, ou deletando um drone e deixando seus registros de voo "órfãos" no banco, ocupando espaço à toa. Precisamos de uma blindagem que impeça dados inválidos de entrarem e que limpe o lixo automaticamente quando um drone for removido da frota.

## 🛠️ Necessidade Técnica

As **Constraints (Restrições)** são as leis do banco de dados:

* **UNIQUE:** Garante que um valor não se repita (ex: o número de série do drone).
* **CHECK:** Valida o valor antes de aceitá-lo (ex: `horas >= 0`).
* **NOT NULL:** Proíbe campos vazios.
* **ON DELETE CASCADE:** Se o registro "Pai" (Drone) for deletado, o banco deleta automaticamente todos os registros "Filhos" (Logs de Voo).

## 📋 Requisitos

1. Criar a tabela `drones_frota` com `id`, `serial` (UNIQUE) e `horas_voo` (CHECK >= 0).
2. Criar a tabela `telemetria_historico` com um relacionamento via `FOREIGN KEY` configurado com `ON DELETE CASCADE`.
3. Demonstrar que o banco rejeita horas negativas ou seriais repetidos.
- Demonstrar a exclusão automática dos logs ao remover um drone.

## ⚠️ Análise de Falha Crítica

A integridade referencial é o pilar de um banco de dados confiável, mas sua implementação exige cautela:

1.  **Silêncio do SQLite:** Por padrão, o SQLite mantém o suporte a `FOREIGN KEYS` desligado por compatibilidade com versões antigas. Se o `PRAGMA foreign_keys = ON` for omitido, as cascatas serão ignoradas, gerando **registros órfãos** que corrompem a lógica do sistema.
2.  **Cascata Destrutiva (Mass Delete):** O `ON DELETE CASCADE` é uma faca de dois gumes. Um erro simples em um `DELETE` no topo da hierarquia pode apagar milhões de registros históricos de telemetria de forma irreversível.
3.  **Locks e Performance:** A exclusão em cascata de grandes volumes de dados pode causar um "Lock" prolongado no banco de dados, impedindo inserções e leituras de outros usuários durante o processo.
4.  **Violação de CHECK Silenciosa:** Se as regras de `CHECK` forem alteradas após a inserção de dados, os dados antigos (agora inválidos) permanecerão no banco a menos que uma validação manual seja executada.


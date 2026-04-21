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
4. Demonstrar a exclusão automática dos logs ao remover um drone.

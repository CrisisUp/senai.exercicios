# 🗄️ Atividade 30: Checkpoints em Transações (SAVEPOINT e ROLLBACK TO)

## 🎯 Estudo de Caso

A "SkyCargo" realiza manutenções complexas em drones que envolvem várias etapas:

1. Limpeza Física.
2. Calibragem de Sensores.
3. Atualização de Firmware.

Se a Atualização de Firmware (etapa 3) falhar, não queremos cancelar todo o trabalho e "deslimpar" o drone. Queremos apenas voltar para o estado logo após a Calibragem. Precisamos de **Checkpoints** dentro de uma transação longa.

## 🛠️ Necessidade Técnica

As transações básicas (`BEGIN/COMMIT`) são "Tudo ou Nada". Os **SAVEPOINTS** trazem granularidade:

* **SAVEPOINT nome:** Cria um ponto de restauração dentro da transação ativa.
* **ROLLBACK TO nome:** Volta o banco de dados para aquele ponto específico, mantendo o que foi feito antes.
* **RELEASE nome:** Confirma aquele ponto e libera os recursos.
* **Benefício:** Permite gerenciar processos de negócio complexos e propensos a falhas parciais sem perder o progresso total.

## 📋 Requisitos

1. Criar a tabela `manutencao_progresso` (id, drone_id, etapa, status).
2. Iniciar uma transação e realizar a Etapa 1 (Limpeza).
3. Criar um `SAVEPOINT` chamado `limpeza_ok`.
4. Realizar a Etapa 2 (Calibragem).
5. Criar um `SAVEPOINT` chamado `calibragem_ok`.
6. Simular uma falha na Etapa 3 e usar `ROLLBACK TO` para voltar ao checkpoint da calibragem.
7. Confirmar a transação final.

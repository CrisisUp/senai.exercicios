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

## ⚠️ Análise de Falha Crítica

*   **Riscos de Performance Locks:** Manter transações abertas com múltiplos `SAVEPOINTS` por longos períodos impede que outros processos realizem manutenção no banco e pode segurar locks de escrita em linhas cruciais, causando filas de espera (lock contention).
*   **Vacuum Latency:** Transações longas impedem que o banco limpe páginas antigas. No SQLite, isso atrasa o reaproveitamento de espaço; em outros bancos (como Postgres), isso impede o avanço do `FREEZE` e do `VACUUM`, causando lentidão sistêmica.
*   **Heap Bloat:** O uso excessivo de `SAVEPOINTS` dentro de loops massivos pode aumentar significativamente o uso de memória temporária e criar fragmentação no arquivo de journal, pois cada ponto de salvamento precisa ser rastreado individualmente.
*   **Transaction Log Overflow:** Se uma transação com muitos checkpoints envolver um grande volume de modificações de dados, o log de transações (UNDO/REDO log) pode crescer até atingir o limite físico do disco, forçando um rollback automático de todo o trabalho.

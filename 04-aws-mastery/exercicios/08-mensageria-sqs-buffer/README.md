# 📩 Atividade 08

- **Amazon SQS** - Mensageria Assíncrona e Buffering
- `STATUS:` Padrão de Engenharia de Elite Aplicado (Nível Arquiteto)

## 🎯 Estudo de Caso

Imagine que 10.000 drones da "SkyCargo" entrem em uma zona de tempestade e todos
decidam enviar alertas de segurança ao mesmo tempo. Se o nosso sistema
processar um por um (Síncrono), o servidor travará. Usaremos o **Amazon SQS**
(Simple Queue Service) para que os drones "depositem" seus alertas em uma fila.
O sistema de processamento então lê as mensagens no seu próprio ritmo, sem nunca
perder um alerta.

## 🛠️ Necessidade Técnica

O **SQS** é o serviço de mensageria gerenciado da AWS:

- **Standard Queues:** Alta vazão e entrega "pelo menos uma vez".
- **FIFO Queues:** Garante a ordem exata das mensagens e entrega única.
- **Visibility Timeout:** Tempo que uma mensagem fica "escondida" enquanto é
  processada.
- **DLQ (Dead Letter Queue):** Fila de "lixo" para mensagens que falharam
  repetidamente.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL RESILIÊNCIA DE SISTEMAS)

- `RISCO DE QUEUE POISONING:` Uma mensagem corrompida que faz o consumidor dar
  Crash toda vez que tenta lê-la. Sem uma **DLQ**, essa mensagem travará o
  sistema em um loop infinito de falhas.
- `RISCO DE DUPLICATE PROCESSING:` Em filas Standard, a mesma mensagem pode ser
  entregue duas vezes. O código consumidor (Lambda/EC2) deve ser **Idempotente**
  (processar a mesma coisa duas vezes não causa erro).
- `RISCO DE BACKLOG EXPLOSION:` Se os drones produzem 1000 msgs/s e o consumidor
  só processa 100 msgs/s, a fila crescerá infinitamente até o timeout. Solução:
  Auto-scaling baseado na profundidade da fila.

## 📋 Requisitos de Elite

1. Provisionamento de uma Fila SQS Standard via CLI.
2. Configuração de tempo de retenção e tempo de visibilidade.
3. Script de envio de mensagens de telemetria simulada.
4. Demonstração de leitura (Receive) e deleção segura de mensagens.

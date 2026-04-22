# 🏛️ Desafio Integrador SA-01

- **SkyCargo Global Ops** (Sinfonia na Nuvem)
- `STATUS:` Padrão de Engenharia de Elite Aplicado (Nível Arquiteto)

## 🎯 Estudo de Caso

A "SkyCargo" precisa de uma infraestrutura robusta para sua expansão mundial. O
sistema deve receber telemetria dos drones (API Gateway), processar alertas de
segurança (Lambda), enfileirar missões de manutenção (SQS), notificar os técnicos
(SNS) e armazenar o histórico de voo (DynamoDB/RDS). Toda a operação deve ser
vigiada por alarmes de performance (CloudWatch) e protegida por identidades
estritas (IAM).

## 🛠️ Necessidade Técnica (A Grande Integração)

Este projeto consolida os pilares da Cloud Computing moderna:

- **INGESTÃO:** API Gateway -> Lambda -> DynamoDB.
- **RESILIÊNCIA:** Lambda -> SQS (Buffer de Manutenção).
- **COMUNICAÇÃO:** SQS -> Lambda -> SNS (Notificação Multicanal).
- **STORAGE:** S3 (Logs Brutos) e RDS (Relatórios de Faturamento).
- **OBSERVABILIDADE:** CloudWatch Dashboards e Alertas de Erro.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL ARQUITETURA GLOBAL)

- RISCO DE CASCADE FAILURE: Se o DynamoDB atingir o limite de escrita, o Lambda
  falhará, o que pode travar o API Gateway. Solução: Inserção Assíncrona via SQS.
- RISCO DE OVERBILLING: Sem limites de faturamento e limpeza automática de
  versões antigas no S3, o custo de armazenamento de milhões de drones pode
  inviabilizar o negócio.
- RISCO DE DATA LEAK EM TRÂNSITO: Dados de localização de drones interceptados
  podem permitir o roubo físico de cargas. Solução: HTTPS mandatório (Gateway) e
  Encryption at Rest (KMS).

## 📋 Requisitos de Elite

1. Desenhar a topologia lógica conectando os 8 serviços AWS aprendidos.
2. Criar um script de "Deploy Total" que valida requisitos e orquestra a criação.
3. Implementar a lógica de "Guardião Financeiro" nos cálculos do RDS.
4. Configurar uma DLQ (Dead Letter Queue) para alertas que não puderam ser
   processados.

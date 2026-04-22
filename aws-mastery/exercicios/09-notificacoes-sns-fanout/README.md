# 🔔 Atividade 09

- **Amazon SNS** - Notificações Fan-out e Pub/Sub
- `STATUS:` Padrão de Engenharia de Elite Aplicado (Nível Arquiteto)

## 🎯 Estudo de Caso

A "SkyCargo" precisa disparar um alerta multicanal quando um drone entra em rota
de colisão. O alerta deve chegar instantaneamente no e-mail do técnico de campo,
no SMS do supervisor de voo e ser gravado em uma fila de auditoria (SQS). Em vez
de fazer três chamadas separadas no código, usaremos o **Amazon SNS** (Simple
Notification Service) para distribuir a mensagem (Fan-out).

## 🛠️ Necessidade Técnica

O **SNS** é um serviço de publicação/assinatura (Pub/Sub) de alta disponibilidade:

- **Topics:** O canal central onde as mensagens são publicadas.
- **Subscriptions:** Os interessados que "assinam" o tópico (Email, SMS, Lambda).
- **Fan-out Pattern:** Uma única publicação no tópico é replicada para todos os
  assinantes automaticamente pela AWS.
- **Message Filtering:** Capacidade de enviar a mensagem apenas para assinantes
  que atendam a critérios específicos (ex: apenas drones modelo X).

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL ARQUITETURA DE EVENTOS)

- `RISCO DE NOTIFICATION STORM:` Se um sensor falhar e enviar 1000 alertas por
  segundo, o SNS tentará notificar todos os assinantes, podendo gerar custos
  altos e "inundar" a caixa de entrada dos humanos.
- `RISCO DE DATA EXPOSURE:` Mensagens SNS não são criptografadas por padrão. Dados
  de telemetria sigilosos devem ser protegidos via **KMS (Key Management
  Service)**.
- `RISCO DE ORPHANED SUBSCRIPTIONS:` Assinantes que não existem mais (ex: e-mails
  desativados) podem fazer a AWS tentar re-entregar a mensagem por dias, poluindo
  os logs de auditoria.

## 📋 Requisitos de Elite

1. Provisionamento de um Tópico SNS Standard via CLI.
2. Criação de uma assinatura (simulando e-mail ou SMS).
3. Publicação de uma mensagem de alerta com atributos de prioridade.
4. Demonstração de listagem de assinaturas ativas para auditoria.

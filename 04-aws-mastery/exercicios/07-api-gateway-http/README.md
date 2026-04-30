# 🌐 Atividade 07

- **API Gateway** - Endpoints HTTP para Telemetria
- `STATUS:` Padrão de Engenharia de Elite Aplicado (Nível Arquiteto)

## 🎯 Estudo de Caso

A "SkyCargo" precisa que os drones enviem alertas de bateria via internet de
qualquer lugar do mundo. Atualmente, nossa função Lambda só pode ser invocada
internamente via CLI. Usaremos o **Amazon API Gateway** para criar uma URL
pública (Endpoint) que receberá requisições POST dos drones e as encaminhará
automaticamente para o nosso processador serverless.

## 🛠️ Necessidade Técnica

O **API Gateway** atua como o "porteiro" da sua arquitetura:

- **HTTP APIs:** Versão moderna, rápida e barata do serviço.
- **Routes:** Define os caminhos da URL (ex: `/alerta`).
- **Integrations:** Conecta a rota ao serviço de destino (Lambda).
- **Throttling:** Controle de quantas requisições por segundo a API aceita.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL SEGURANÇA E PERFORMANCE)

- `RISCO DE DDOS ATTACK:` Uma API pública sem limites de taxa (Throttling) pode ser
  inundada por milhões de requisições, derrubando o sistema e gerando custos
  astronômicos.
- `RISCO DE AUTHENTICATION BYPASS:` Expor lógica de negócio sem chaves de API ou
tokens (JWT) permite que qualquer pessoa injete alertas falsos no sistema.
- `RISCO DE LATE BINDING LATENCY:` A soma da latência da rede + latência do
Gateway + Cold Start do Lambda pode fazer o drone esperar segundos por uma
resposta, o que é inaceitável em controle de voo.

## 📋 Requisitos de Elite

1. Provisionamento de uma HTTP API via CLI.
2. Criação de uma Integração do tipo 'AWS_PROXY' com o Lambda da Atividade 06.
3. Configuração de uma Rota POST `/telemetria`.
4. Deploy automático e captura da URL de produção.

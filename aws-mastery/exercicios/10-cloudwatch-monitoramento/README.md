# 👁️ Atividade 10

- **Amazon CloudWatch** - Monitoramento e Alarmes de Elite
- `STATUS:` Padrão de Engenharia de Elite Aplicado (Nível Arquiteto)

## 🎯 Estudo de Caso

A "SkyCargo" agora opera em escala global. O problema é: como saber se um drone
caiu ou se o banco de dados está lento às 3 da manhã? Precisamos de um "Vigia
Eterno". Usaremos o **Amazon CloudWatch** para centralizar os logs de todas as
nossas funções Lambda e configurar alarmes automáticos que nos avisem antes que
o sistema entre em colapso.

## 🛠️ Necessidade Técnica

O **CloudWatch** é o sistema nervoso de monitoramento da AWS:

- **Log Groups:** Containers para logs de diferentes serviços.
- **Metrics:** Dados numéricos sobre o sistema (CPU, Erros, Latência).
- **Alarms:** Gatilhos que disparam ações (SNS) quando um limite é ultrapassado.
- **Dashboards:** Painéis visuais para telemetria em tempo real.

## 🧪 ANÁLISE DE FALHA CRÍTICA (NÍVEL OBSERVABILIDADE)

- `RISCO DE LOG OVERFLOW:` Gravar logs em excesso (ex: "Debug Mode" ligado em
  produção) pode gerar custos de milhares de dólares em armazenamento e ingestão.
  Solução: Políticas de Retenção (Retention Policies).
- `RISCO DE SILENT FAILURE:` Um erro que não gera log ou não tem alarme é uma
  "Falha Silenciosa". O sistema parece estar bem, mas está perdendo dados no
  fundo.
- `RISCO DE PII LEAK EM LOGS:` Gravar dados sensíveis de clientes (Senhas, Cartões)
  em texto puro nos logs do CloudWatch viola leis de privacidade (LGPD).

## 📋 Requisitos de Elite

1. Criação de um Log Group dedicado via CLI.
2. Configuração de uma Política de Retenção de 7 dias (Economia de Elite).
3. Criação de um Alarme de Métrica simulado para detectar falhas.
4. Demonstração de busca de eventos de log (Insights).

/**
 * @file event_bus.tf
 * @brief Definição do Barramento de Eventos e Regras de Negócio (IaC).
 */

# 1. Criação do Barramento de Eventos Customizado
resource "aws_cloudwatch_event_bus" "nexus_bus" {
  name = "Nexus-Global-Events"

  tags = {
    Name = "Nexus-Bus"
  }
}

# 2. Regra de Elite: Detecção de Excesso de Velocidade
# Esta regra usa um 'Event Pattern' (JSON) para filtrar eventos.
resource "aws_cloudwatch_event_rule" "speed_alert_rule" {
  name           = "Nexus-HighSpeed-Alert"
  description    = "Detecta drones voando acima do limite de segurança"
  event_bus_name = aws_cloudwatch_event_bus.nexus_bus.name

  event_pattern = jsonencode({
    "source": ["nexus.telemetria"],
    "detail-type": ["TelemetriaProcessada"],
    "detail": {
      "velocidade": [{ "numeric": [">", 110] }]
    }
  })
}

# 3. Target da Regra (Exemplo: Enviar para um log de auditoria)
resource "aws_cloudwatch_event_target" "log_target" {
  rule           = aws_cloudwatch_event_rule.speed_alert_rule.name
  event_bus_name = aws_cloudwatch_event_bus.nexus_bus.name
  arn            = "arn:aws:logs:us-east-1:123456789012:log-group:Nexus-Alerts"
}

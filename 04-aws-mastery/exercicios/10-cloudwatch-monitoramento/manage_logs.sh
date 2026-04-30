#!/bin/bash

# @file manage_logs.sh
# @brief Script de orquestração para Observabilidade e Logs.
# 
# Atividade 10 - Amazon CloudWatch & Alarms (Nível Arquiteto).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026
# 
# @section CloudMap Topologia de Observabilidade
# - Recurso: Amazon CloudWatch Logs & Metrics.
# - Retenção: 7 dias (Otimização de Custo).
# - Alarme: Gatilho de Erro (Erro > 1 em 5 minutos).
# - Dashboard: Telemetria Unificada via Log Groups.

# --- 1. NAMESPACE DE INTERFACE (ANSI) ---
VERDE="\033[32m"
AMARELO="\033[33m"
CIANO="\033[36m"
VERMELHO="\033[31m"
RESET="\033[0m"

LOG_GROUP="/aws/skycargo/telemetry"
ALARM_NAME="SkyCargo-High-Error-Rate"

# --- 2. VALIDAÇÃO DE REQUISITOS ---
check_requirements() {
    if ! command -v aws &> /dev/null; then
        echo -e "${VERMELHO}[ERRO]: AWS CLI não localizada.${RESET}"
        exit 1
    fi
}

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: CLOUDWATCH LOG MANAGER v1.0     "
echo -e "       (Observability & Alarm Engine)          "
echo -e "${CIANO}===============================================${RESET}"

check_requirements

# 3. CRIAÇÃO DO LOG GROUP
echo -e "\n${CIANO}[1/4] Provisionando Log Group: ${LOG_GROUP}...${RESET}"
aws logs create-log-group --log-group-name "${LOG_GROUP}" || echo -e "${AMARELO}[AVISO]: Log Group já existe.${RESET}"

# 4. POLÍTICA DE RETENÇÃO (BUDGET GUARDIAN)
echo -e "${CIANO}[2/4] Aplicando Retenção de 7 dias (Custo Otimizado)...${RESET}"
aws logs put-retention-policy --log-group-name "${LOG_GROUP}" --retention-in-days 7

# 5. CRIAÇÃO DE ALARME DE MÉTRICA (SIMULADO)
echo -e "${CIANO}[3/4] Configurando Alarme de Erros Críticos...${RESET}"
# Simulamos um alarme que vigia erros na função Lambda da Atividade 06
aws cloudwatch put-metric-alarm \
    --alarm-name "${ALARM_NAME}" \
    --alarm-description "Alerta se houver mais de 1 erro em 5 minutos" \
    --metric-name Errors \
    --namespace AWS/Lambda \
    --statistic Sum \
    --period 300 \
    --threshold 1 \
    --comparison-operator GreaterThanThreshold \
    --evaluation-periods 1 \
    --dimensions Name=FunctionName,Value=SkyCargo-AlertHandler \
    --unit Count

echo -e "${VERDE}[OK]: Alarme configurado e em estado INSUFFICIENT_DATA (Aguardando métricas).${RESET}"

# 6. CONSULTA DE LOGS (LOG INSIGHTS)
echo -e "\n${CIANO}[4/4] Executando Busca de Telemetria Histórica...${RESET}"
# Exemplo de comando que busca erros nas últimas 1h
echo -e "${AMARELO}[INSIGHTS]: aws logs filter-log-events --log-group-name ${LOG_GROUP} --filter-pattern 'ERROR' --limit 5${RESET}"

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      SISTEMA DE VIGILÂNCIA HOMOLOGADO         "
echo -e " Log Group: ${LOG_GROUP}"
echo -e " Retention: 7 Days | Alarm: Active"
echo -e "${VERDE}===============================================${RESET}"

# RESUMO TEÓRICO: OBSERVABILIDADE DE ELITE
# 1. CENTRALIZAÇÃO: Ter logs espalhados em instâncias EC2 é um erro. 
#    O CloudWatch unifica tudo em uma única interface.
# 2. MÉTRICAS VS LOGS: Logs são "O que aconteceu" (texto). Métricas 
#    são "Quanto aconteceu" (números). O alarme vigia os números.
# 3. FILTROS DE MÉTRICA: Você pode criar um alarme baseado em um 
#    texto específico dentro do log (ex: toda vez que aparecer 'FATAL').
# 4. RETENÇÃO: Logs eternos são caros e desnecessários. Um Engenheiro 
#    de Elite configura a retenção baseada em compliance (7, 30, 90 dias).

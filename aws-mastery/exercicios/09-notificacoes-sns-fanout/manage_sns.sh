#!/bin/bash

# @file manage_sns.sh
# @brief Script de orquestração para Notificações e Distribuição Fan-out.
# 
# Atividade 09 - Amazon SNS & Pub-Sub (Nível Arquiteto).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026
# 
# @section CloudMap Topologia de Notificação
# - Recurso: Amazon SNS Topic Standard.
# - Padrão: Fan-out (Uma publicação para N assinantes).
# - Protocolos: E-mail (Simulado) e CLI Dispatch.
# - Escalabilidade: Escala global sem necessidade de gestão de servidores SMTP.

# --- 1. NAMESPACE DE INTERFACE (ANSI) ---
VERDE="\033[32m"
AMARELO="\033[33m"
CIANO="\033[36m"
VERMELHO="\033[31m"
RESET="\033[0m"

TOPIC_NAME="SkyCargo-Critical-Alerts"

# --- 2. VALIDAÇÃO DE REQUISITOS ---
check_requirements() {
    if ! command -v aws &> /dev/null; then
        echo -e "${VERMELHO}[ERRO]: AWS CLI não localizada.${RESET}"
        exit 1
    fi
}

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: SNS NOTIFICATION MANAGER v1.0   "
echo -e "       (Pub/Sub & Fan-out Architecture)        "
echo -e "${CIANO}===============================================${RESET}"

check_requirements

# 3. CRIAÇÃO DO TÓPICO
echo -e "\n${CIANO}[1/4] Provisionando Tópico SNS...${RESET}"
TOPIC_ARN=$(aws sns create-topic \
    --name "${TOPIC_NAME}" \
    --query 'TopicArn' --output text)

echo -e "ARN do Tópico: ${VERDE}${TOPIC_ARN}${RESET}"

# 4. CRIAÇÃO DE ASSINATURA (EMAIL SIMULADO)
EMAIL_MOCK="tecnico-elite@skycargo.com"
echo -e "${CIANO}[2/4] Inscrevendo Técnico no canal de Alerta...${RESET}"
aws sns subscribe \
    --topic-arn "${TOPIC_ARN}" \
    --protocol email \
    --notification-endpoint "${EMAIL_MOCK}"

echo -e "${AMARELO}[INFO]: A AWS enviará um e-mail de confirmação para ${EMAIL_MOCK}.${RESET}"

# 5. PUBLICAÇÃO DE ALERTA (BROADCAST)
echo -e "${CIANO}[3/4] Disparando Alerta Global (Fan-out Active)...${RESET}"
SUBJECT="URGENTE: Drone em Rota de Colisão"
MESSAGE="ALERTA: Drone SKY-X detectou obstáculo a 200m. Iniciando manobra evasiva automática."

aws sns publish \
    --topic-arn "${TOPIC_ARN}" \
    --subject "${SUBJECT}" \
    --message "${MESSAGE}" \
    --message-attributes '{ "Prioridade": {"DataType": "String", "StringValue": "ALTA"} }'

# 6. AUDITORIA DE REDE
echo -e "\n${CIANO}[4/4] Listando Assinaturas Ativas para Auditoria...${RESET}"
aws sns list-subscriptions-by-topic --topic-arn "${TOPIC_ARN}" --output table

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      SISTEMA DE NOTIFICAÇÃO OPERACIONAL       "
echo -e " Modo: Publish/Subscribe | Protocol: Multi-Stack"
echo -e "${VERDE}===============================================${RESET}"

# RESUMO TEÓRICO: O PODER DO SNS
# 1. FAN-OUT: Permite que um único evento dispare e-mails para humanos 
#    e mensagens SQS para máquinas simultaneamente.
# 2. ALTA DISPONIBILIDADE: O SNS é redundante em todas as zonas de 
#    disponibilidade. Sua notificação não se perde por falha de infra local.
# 3. FILTRAGEM (FILTER POLICIES): Você pode configurar para que o 
#    técnico só receba mensagens onde 'Prioridade' == 'ALTA'.
# 4. DESACOPLAMENTO TOTAL: O drone não precisa saber quantos e-mails 
#    serão enviados. Ele só avisa ao SNS "houve um alerta" e segue voando.

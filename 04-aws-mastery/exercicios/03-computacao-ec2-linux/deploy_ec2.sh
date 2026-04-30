#!/bin/bash

# @file deploy_ec2.sh
# @brief Orquestrador de Computação via CloudFormation.
# 
# Atividade 03 - IaC Deployment (Nível Arquiteto).

# --- NAMESPACE DE INTERFACE ---
VERDE="\033[32m"
CIANO="\033[36m"
AMARELO="\033[33m"
VERMELHO="\033[31m"
RESET="\033[0m"

STACK_NAME="SkyCargo-EC2-Stack"

# Captura diretório e IP dinamicamente
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
MY_IP=$(curl -s http://checkip.amazonaws.com)

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: EC2 ORCHESTRATOR v1.0           "
echo -e "       (IP Detectado: $MY_IP)                 "
echo -e "${CIANO}===============================================${RESET}"

cd "$SCRIPT_DIR"

# 1. VALIDAÇÃO DE PRÉ-REQUISITOS
if ! aws sts get-caller-identity &> /dev/null; then
    echo -e "${VERMELHO}[FALHA]: Credenciais não detectadas.${RESET}"
    exit 1
fi

# 2. DISPARO DA ORQUESTRAÇÃO
echo -e "\n${CIANO}[1/1] Provisionando Instância Linux Protegida...${RESET}"

aws cloudformation deploy \
    --template-file ec2-setup.yaml \
    --stack-name "${STACK_NAME}" \
    --parameter-overrides OperatorIP="${MY_IP}/32" \
    --capabilities CAPABILITY_IAM

# 3. CAPTURA DO ENDEREÇO DE ACESSO
echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      NÓ DE COMPUTAÇÃO ATIVO                   "
echo -e "===============================================${RESET}"
aws cloudformation describe-stacks \
    --stack-name "${STACK_NAME}" \
    --query 'Stacks[0].Outputs' \
    --output table
echo -e "${VERDE}===============================================${RESET}"

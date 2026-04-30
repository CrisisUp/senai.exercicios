#!/bin/bash

# @file deploy_rds.sh
# @brief Orquestrador de Banco de Dados Gerenciado via CloudFormation.

# --- NAMESPACE DE INTERFACE ---
VERDE="\033[32m"
CIANO="\033[36m"
AMARELO="\033[33m"
VERMELHO="\033[31m"
RESET="\033[0m"

STACK_NAME="SkyCargo-RDS-Stack"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: RDS ORCHESTRATOR v1.0           "
echo -e "${CIANO}===============================================${RESET}"

cd "$SCRIPT_DIR"

# 1. VALIDAÇÃO DE PRÉ-REQUISITOS
if ! aws sts get-caller-identity &> /dev/null; then
    echo -e "${VERMELHO}[FALHA]: Credenciais não detectadas.${RESET}"
    exit 1
fi

# 2. DISPARO DA ORQUESTRAÇÃO
echo -e "\n${CIANO}[1/1] Provisionando Engine de Dados Resiliente...${RESET}"
echo -e "${AMARELO}[INFO]: O RDS pode levar até 10 minutos para inicializar.${RESET}"

read -s -p "Defina a senha mestre do Banco: " MY_PASS
echo ""

aws cloudformation deploy \
    --template-file rds-setup.yaml \
    --stack-name "${STACK_NAME}" \
    --parameter-overrides DBPass="${MY_PASS}" \
    --capabilities CAPABILITY_IAM

# 3. CAPTURA DO ENDEREÇO
echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      BANCO DE DADOS ATIVO E PROTEGIDO         "
echo -e "===============================================${RESET}"
aws cloudformation describe-stacks \
    --stack-name "${STACK_NAME}" \
    --query 'Stacks[0].Outputs' \
    --output table
echo -e "${VERDE}===============================================${RESET}"

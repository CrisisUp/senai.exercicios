#!/bin/bash

# @file deploy_dynamo.sh
# @brief Orquestrador de Tabelas NoSQL via CloudFormation.

# --- NAMESPACE DE INTERFACE ---
VERDE="\033[32m"
CIANO="\033[36m"
VERMELHO="\033[31m"
RESET="\033[0m"

STACK_NAME="SkyCargo-Dynamo-Stack"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: DYNAMODB ORCHESTRATOR v1.0      "
echo -e "${CIANO}===============================================${RESET}"

cd "$SCRIPT_DIR"

# 1. VALIDAÇÃO DE PRÉ-REQUISITOS
if ! aws sts get-caller-identity &> /dev/null; then
    echo -e "${VERMELHO}[FALHA]: Credenciais não detectadas.${RESET}"
    exit 1
fi

# 2. DISPARO DA ORQUESTRAÇÃO
echo -e "\n${CIANO}[1/1] Provisionando Tabela NoSQL Escalável...${RESET}"

aws cloudformation deploy \
    --template-file dynamo-setup.yaml \
    --stack-name "${STACK_NAME}" \
    --capabilities CAPABILITY_IAM

# 3. CAPTURA DO NOME DA TABELA
echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      CORE DE DADOS NoSQL ATIVO                 "
echo -e "===============================================${RESET}"
aws cloudformation describe-stacks \
    --stack-name "${STACK_NAME}" \
    --query 'Stacks[0].Outputs' \
    --output table
echo -e "${VERDE}===============================================${RESET}"

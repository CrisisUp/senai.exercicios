#!/bin/bash

# @file deploy_iam.sh
# @brief Orquestrador de Identidades via AWS CloudFormation.
# 
# Atividade 01 - IaC Identity Deployment (Nível Arquiteto).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026

# --- NAMESPACE DE INTERFACE ---
VERDE="\033[32m"
CIANO="\033[36m"
AMARELO="\033[33m"
VERMELHO="\033[31m"
RESET="\033[0m"

STACK_NAME="SkyCargo-IAM-Stack"
REGION=${1:-"us-east-1"} # Padrão us-east-1 se não informado

# Navega para o diretório do script (Engenharia de Caminhos Absolutos)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: IAM ORCHESTRATOR v1.1           "
echo -e "       (Location: $SCRIPT_DIR)                 "
echo -e "${CIANO}===============================================${RESET}"

# 1. VALIDAÇÃO DE PRÉ-REQUISITOS
if ! aws sts get-caller-identity &> /dev/null; then
    echo -e "${VERMELHO}[FALHA]: AWS CLI não configurada ou sem permissão.${RESET}"
    echo -e "Rode 'aws configure' antes de tentar o deploy."
    exit 1
fi

# 2. VALIDAÇÃO DO TEMPLATE
echo -e "\n${CIANO}[1/2] Verificando integridade do Contrato YAML...${RESET}"
aws cloudformation validate-template --template-body "file://iam-setup.yaml" --region "$REGION"

# 3. DISPARO DA ORQUESTRAÇÃO
echo -e "${CIANO}[2/2] Enviando Stack para a região $REGION...${RESET}"

aws cloudformation deploy \
    --template-file "iam-setup.yaml" \
    --stack-name "${STACK_NAME}" \
    --capabilities CAPABILITY_NAMED_IAM \
    --region "$REGION"

# 4. CAPTURA DOS OUTPUTS
echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      INFRAESTRUTURA DE IDENTIDADE ATIVA       "
echo -e "===============================================${RESET}"

aws cloudformation describe-stacks \
    --stack-name "${STACK_NAME}" \
    --region "$REGION" \
    --query 'Stacks[0].Outputs' \
    --output table

echo -e "\n${AMARELO}AVISO: Guarde as chaves geradas em local seguro.${RESET}"
echo -e "${VERDE}===============================================${RESET}"

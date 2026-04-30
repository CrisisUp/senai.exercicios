#!/bin/bash

# @file deploy_stack.sh
# @brief Script de orquestração para templates CloudFormation.
# 
# Atividade 11 - IaC Deployment (Nível Arquiteto).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026

# --- NAMESPACE DE INTERFACE ---
VERDE="\033[32m"
CIANO="\033[36m"
RESET="\033[0m"

STACK_NAME="SkyCargo-Telemetry-Stack"

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: CLOUDFORMATION DEPLOYER v1.0    "
echo -e "       (Infrastructure as Code Core)           "
echo -e "${CIANO}===============================================${RESET}"

# 1. VALIDAÇÃO DO TEMPLATE (LINTING)
echo -e "\n${CIANO}[1/2] Validando sintaxe do Template YAML...${RESET}"
aws cloudformation validate-template --template-body file://template.yaml

# 2. EXECUÇÃO DO DEPLOY (CREATE/UPDATE)
echo -e "${CIANO}[2/2] Sincronizando Stack: ${STACK_NAME}...${RESET}"
aws cloudformation deploy \
    --template-file template.yaml \
    --stack-name "${STACK_NAME}" \
    --parameter-overrides ProjectName="skycargo-fleet" \
    --capabilities CAPABILITY_IAM

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      STACK SINCRONIZADA COM SUCESSO           "
echo -e " Use 'aws cloudformation describe-stacks' para ver outputs."
echo -e "${VERDE}===============================================${RESET}"

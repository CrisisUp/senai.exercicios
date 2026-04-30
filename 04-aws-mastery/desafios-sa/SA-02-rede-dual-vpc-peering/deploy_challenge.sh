#!/bin/bash

# @file deploy_challenge.sh
# @brief Orquestrador de Infraestrutura para o Desafio SA-02 (Rede Dual VPC).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026

# --- CORES ---
VERDE="\033[32m"
CIANO="\033[36m"
AMARELO="\033[33m"
RESET="\033[0m"

STACK_NAME="SA-02-DualVPC-Challenge"
REGION="us-east-1"

echo -e "${CIANO}===============================================${RESET}"
echo -e "      SA-02: DUAL-VPC NETWORKING CHALLENGE     "
echo -e "       (Infrastructure as Code Orchestrator)   "
echo -e "${CIANO}===============================================${RESET}"

# 1. VALIDAÇÃO
echo -e "\n${CIANO}[1/2] Auditando topologia declarada...${RESET}"
aws cloudformation validate-template --template-body file://infrastructure.yaml

# 2. DEPLOY
echo -e "${CIANO}[2/2] Provisionando Malha de Rede e Servidores...${RESET}"
echo -e "${AMARELO}[INFO]: O RDS e o Peering podem levar alguns minutos.${RESET}"

aws cloudformation deploy \
    --template-file infrastructure.yaml \
    --stack-name "${STACK_NAME}" \
    --capabilities CAPABILITY_IAM \
    --region "${REGION}"

# 3. RESULTADOS
echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      INFRAESTRUTURA ENTREGUE COM SUCESSO      "
echo -e "===============================================${RESET}"
aws cloudformation describe-stacks \
    --stack-name "${STACK_NAME}" \
    --query 'Stacks[0].Outputs' \
    --output table
echo -e "${VERDE}===============================================${RESET}"

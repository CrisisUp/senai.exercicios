#!/bin/bash

# @file deploy_sqs.sh
# @brief Orquestrador de Mensageria via CloudFormation.

VERDE="\033[32m"
CIANO="\033[36m"
RESET="\033[0m"

STACK_NAME="SkyCargo-SQS-Stack"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: SQS PROVISIONER v1.1            "
echo -e "       (Resilient Messaging Infrastructure)    "
echo -e "${CIANO}===============================================${RESET}"

cd "$SCRIPT_DIR"

aws cloudformation deploy \
    --template-file sqs-setup.yaml \
    --stack-name "${STACK_NAME}" \
    --capabilities CAPABILITY_IAM

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      CANAL DE MENSAGENS ATIVO                 "
echo -e "===============================================${RESET}"
aws cloudformation describe-stacks --stack-name "${STACK_NAME}" --query 'Stacks[0].Outputs' --output table
echo -e "${VERDE}===============================================${RESET}"

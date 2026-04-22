#!/bin/bash

# @file deploy_api.sh
# @brief Orquestrador de API Gateway via CloudFormation.

VERDE="\033[32m"
CIANO="\033[36m"
RESET="\033[0m"

STACK_NAME="SkyCargo-API-Stack"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Precisamos do ARN do Lambda da Atividade 06
LAMBDA_ARN=$(aws cloudformation describe-stacks --stack-name SkyCargo-Lambda-Stack --query 'Stacks[0].Outputs[?OutputKey==`FunctionArn`].OutputValue' --output text)

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: API GATEWAY DEPLOYER v1.1       "
echo -e "       (Linking to Lambda Processors)          "
echo -e "${CIANO}===============================================${RESET}"

cd "$SCRIPT_DIR"

aws cloudformation deploy \
    --template-file api-setup.yaml \
    --stack-name "${STACK_NAME}" \
    --parameter-overrides TargetLambdaArn="${LAMBDA_ARN}" \
    --capabilities CAPABILITY_IAM

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      ENDPOINT PÚBLICO OPERACIONAL             "
echo -e "===============================================${RESET}"
aws cloudformation describe-stacks --stack-name "${STACK_NAME}" --query 'Stacks[0].Outputs' --output table
echo -e "${VERDE}===============================================${RESET}"

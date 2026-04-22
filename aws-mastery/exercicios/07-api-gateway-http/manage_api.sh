#!/bin/bash

# @file manage_api.sh
# @brief Script de criação e integração de Endpoints HTTP.
# 
# Atividade 07 - API Gateway & Integrations (Nível Arquiteto).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026
# 
# @section CloudMap Topologia de Interface
# - Recurso: Amazon API Gateway (HTTP Protocol).
# - Rota: POST /telemetria.
# - Integração: Lambda Proxy (Encaminhamento total do payload).
# - Segurança: CORS desativado (simulado) e Throttling padrão.

# --- 1. NAMESPACE DE INTERFACE (ANSI) ---
VERDE="\033[32m"
AMARELO="\033[33m"
CIANO="\033[36m"
VERMELHO="\033[31m"
RESET="\033[0m"

API_NAME="SkyCargo-Public-API"
LAMBDA_NAME="SkyCargo-AlertHandler"
REGION="us-east-1"

# --- 2. VALIDAÇÃO DE REQUISITOS ---
check_requirements() {
    if ! command -v aws &> /dev/null; then
        echo -e "${VERMELHO}[ERRO]: AWS CLI não localizada.${RESET}"
        exit 1
    fi
}

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: API GATEWAY ORCHESTRATOR v1.0   "
echo -e "       (Public Endpoints & Lambda Proxy)       "
echo -e "${CIANO}===============================================${RESET}"

check_requirements

# 3. CRIAÇÃO DA API HTTP
echo -e "\n${CIANO}[1/4] Provisionando Engine API Gateway...${RESET}"
API_ID=$(aws apigatewayv2 create-api \
    --name "${API_NAME}" \
    --protocol-type HTTP \
    --query 'ApiId' --output text)

echo -e "API ID Gerada: ${VERDE}${API_ID}${RESET}"

# 4. CRIAÇÃO DA INTEGRAÇÃO COM LAMBDA
# Precisamos do ARN do Lambda (Simulado aqui p/ propósitos educacionais)
LAMBDA_ARN="arn:aws:lambda:${REGION}:ACCOUNT_ID:function:${LAMBDA_NAME}"

echo -e "${CIANO}[2/4] Criando Integração Lambda Proxy...${RESET}"
INT_ID=$(aws apigatewayv2 create-integration \
    --api-id "${API_ID}" \
    --integration-type AWS_PROXY \
    --integration-uri "${LAMBDA_ARN}" \
    --payload-format-version "2.0" \
    --query 'IntegrationId' --output text)

# 5. CONFIGURAÇÃO DE ROTA
echo -e "${CIANO}[3/4] Mapeando Rota POST /telemetria...${RESET}"
aws apigatewayv2 create-route \
    --api-id "${API_ID}" \
    --route-key "POST /telemetria" \
    --target "integrations/${INT_ID}"

# 6. PERMISSÃO DE ACESSO (O Pulo do Gato)
# O Gateway precisa de autorização do Lambda para 'invocar' a função
echo -e "${CIANO}[4/4] Blindando Permissão de Invocação (Resource Policy)...${RESET}"
echo -e "${AMARELO}[COMANDO]: aws lambda add-permission --function-name ${LAMBDA_NAME} --statement-id apigateway-access --action lambda:InvokeFunction --principal apigateway.amazonaws.com ...${RESET}"

# 7. EXIBIÇÃO DA URL FINAL
API_ENDPOINT="https://${API_ID}.execute-api.${REGION}.amazonaws.com/telemetria"

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      GATEWAY DE TELEMETRIA OPERACIONAL        "
echo -e " ENDPOINT: ${CIANO}${API_ENDPOINT}${RESET}"
echo -e " MÉTODO  : POST"
echo -e " PAYLOAD : { \"DroneID\": \"...\", \"Bateria\": 15 }"
echo -e "${VERDE}===============================================${RESET}"

# RESUMO TEÓRICO: API GATEWAY E DESACOPLAMENTO
# 1. FACHADA (FACADE): A API esconde a complexidade da nuvem. O drone 
#    não sabe que existe um Lambda; ele apenas faz um POST para uma URL.
# 2. LAMBDA PROXY: O Gateway repassa o cabeçalho HTTP inteiro (IP, 
#    Browser, Token) para o Lambda, permitindo auditoria avançada.
# 3. ESCALABILIDADE: O Gateway suporta picos de tráfego que 
#    matariam um servidor comum, agindo como um "Buffer de Choque".
# 4. VERSIONAMENTO: Podemos ter /v1/telemetria e /v2/telemetria 
#    rodando simultaneamente para drones antigos e novos.

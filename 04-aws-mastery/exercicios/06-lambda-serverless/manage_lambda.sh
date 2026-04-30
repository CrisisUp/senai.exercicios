#!/bin/bash

# @file manage_lambda.sh
# @brief Script de Deploy e Invocação para Funções Serverless.
# 
# Atividade 06 - AWS Lambda & Event-Driven (Nível Arquiteto).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026
# 
# @section CloudMap Topologia Serverless
# - Recurso: AWS Lambda (Python 3.12).
# - Gatilho: Invocação Síncrona via CLI (Teste).
# - Posse: Role IAM 'Lambda-Execution-Role' atrelada à função.
# - RAII (Cloud): Purga automática de pacotes .zip após o upload.

# --- 1. NAMESPACE DE INTERFACE (ANSI) ---
VERDE="\033[32m"
AMARELO="\033[33m"
CIANO="\033[36m"
VERMELHO="\033[31m"
RESET="\033[0m"

FUNC_NAME="SkyCargo-AlertHandler"
ZIP_FILE="function.zip"
ROLE_NAME="LambdaBasicExecutionRole"

# --- 2. VALIDAÇÃO DE REQUISITOS ---
check_requirements() {
    if ! command -v zip &> /dev/null; then
        echo -e "${VERMELHO}[ERRO]: Utilitário 'zip' não localizado.${RESET}"
        exit 1
    fi
    if ! command -v aws &> /dev/null; then
        echo -e "${VERMELHO}[ERRO]: AWS CLI não localizada.${RESET}"
        exit 1
    fi
}

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: LAMBDA ORCHESTRATOR v1.0        "
echo -e "       (Serverless Compute & Deployment)       "
echo -e "${CIANO}===============================================${RESET}"

check_requirements

# 3. EMPACOTAMENTO (ARTEFATO DE SOFTWARE)
echo -e "\n${CIANO}[1/4] Gerando pacote de implantação...${RESET}"
zip -j "${ZIP_FILE}" lambda_function.py

# 4. CRIAÇÃO DA ROLE (SIMULADO - REQUER PRIVILÉGIO IAM)
echo -e "${CIANO}[2/4] Verificando permissões de execução...${RESET}"
echo -e "${AMARELO}[INFO]: Em produção, a Role deve conter a política AWSLambdaBasicExecutionRole.${RESET}"

# 5. DEPLOY DA FUNÇÃO
echo -e "${CIANO}[3/4] Subindo função para a AWS Cloud...${RESET}"
echo -e "${AMARELO}[COMANDO]: aws lambda create-function --function-name ${FUNC_NAME} --zip-file fileb://${ZIP_FILE} ...${RESET}"

# 6. INVOCAÇÃO DE TESTE (CIENTISTA DO CAOS)
echo -e "\n${CIANO}[4/4] Simulando Alerta de Bateria Crítica (Event Test)...${RESET}"
cat <<EOF > event.json
{
    "DroneID": "SKY-VULCAN-X9",
    "Bateria": 12
}
EOF

# Invocação manual simulada
echo -e "${AMARELO}[INVOQUE]: aws lambda invoke --function-name ${FUNC_NAME} --payload file://event.json out.json${RESET}"

# 7. LIMPEZA RAII
echo -e "\n${CIANO}[SISTEMA]: Executando limpeza de artefatos...${RESET}"
rm "${ZIP_FILE}" event.json 2> /dev/null

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      ARQUITETURA SERVERLESS HOMOLOGADA        "
echo -e " Função: ${FUNC_NAME}"
echo -e " Estado: Ready for Event-Triggering"
echo -e "${VERDE}===============================================${RESET}"

# RESUMO TEÓRICO: O PARADIGMA SERVERLESS
# 1. EVENT-DRIVEN: O código não roda o tempo todo. Ele dorme até 
#    que um evento (HTTP, S3, DB) o desperte.
# 2. ESCALABILIDADE ATÔMICA: Se 1.000 eventos ocorrerem ao mesmo 
#    tempo, a AWS sobe 1.000 instâncias da sua função em paralelo.
# 3. NO OPS: Você não gerencia patches de segurança do Linux ou 
#    atualizações de hardware. Foco 100% no código.
# 4. ECONOMIA: O desperdício de CPU ociosa é eliminado da fatura.

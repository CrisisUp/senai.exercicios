#!/bin/bash

# @file deploy_s3.sh
# @brief Orquestrador de Storage via CloudFormation.

# --- NAMESPACE DE INTERFACE ---
VERDE="\033[32m"
CIANO="\033[36m"
AMARELO="\033[33m"
VERMELHO="\033[31m"
RESET="\033[0m"

STACK_NAME="SkyCargo-S3-Stack"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: S3 ORCHESTRATOR v1.0           "
echo -e "${CIANO}===============================================${RESET}"

cd "$SCRIPT_DIR"

# 1. VALIDAÇÃO DE PRÉ-REQUISITOS
if ! aws sts get-caller-identity &> /dev/null; then
    echo -e "${VERMELHO}[FALHA]: Credenciais não detectadas.${RESET}"
    exit 1
fi

# 2. DISPARO DA ORQUESTRAÇÃO
echo -e "\n${CIANO}[1/2] Provisionando Infraestrutura de Storage...${RESET}"

aws cloudformation deploy \
    --template-file s3-setup.yaml \
    --stack-name "${STACK_NAME}" \
    --capabilities CAPABILITY_IAM

# 3. DEPLOY DO CONTEÚDO (Data Plane)
echo -e "${CIANO}[2/2] Enviando Arquivos de Telemetria...${RESET}"
BUCKET_NAME=$(aws cloudformation describe-stacks --stack-name "${STACK_NAME}" --query 'Stacks[0].Outputs[?OutputKey==`BucketName`].OutputValue' --output text)

cat <<EOF > index.html
<!DOCTYPE html>
<html>
<head><title>SkyCargo Elite</title></head>
<body style="background: #000; color: #0f0; text-align: center;">
    <h1>🛰️ SKYCARGO CLOUD NODE</h1>
    <p>Status: ONLINE via CloudFormation</p>
    <p>Deploy: $(date)</p>
</body>
</html>
EOF

aws s3 cp index.html "s3://${BUCKET_NAME}/index.html"
rm index.html

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      SISTEMA DE ARMAZENAMENTO ATIVO           "
echo -e "===============================================${RESET}"
aws cloudformation describe-stacks \
    --stack-name "${STACK_NAME}" \
    --query 'Stacks[0].Outputs' \
    --output table
echo -e "${VERDE}===============================================${RESET}"

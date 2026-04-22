#!/bin/bash

# @file manage_s3.sh
# @brief Script de automação para provisionamento de Storage e Site Estático.
# 
# Atividade 02 - S3 & Static Hosting (Nível Iniciado).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026
# 
# @section CloudMap Topologia de Storage
# - Recurso: AWS S3 Bucket com Blindagem de Acesso Público Gerenciada.
# - Segurança: s3:GetObject liberado apenas via Bucket Policy específica.
# - Endpoint: http://<bucket-name>.s3-website-<region>.amazonaws.com
# - RAII (Cloud): Limpeza automática de artefatos locais após o deploy.

# --- 1. NAMESPACE DE INTERFACE (ANSI) ---
VERDE="\033[32m"
AMARELO="\033[33m"
CIANO="\033[36m"
VERMELHO="\033[31m"
RESET="\033[0m"

# Variáveis de Configuração
BUCKET_NAME="skycargo-status-cristiano-$(date +%s)"
REGION="us-east-1"

# --- 2. FUNÇÕES DE VALIDAÇÃO (ELITE CHECK) ---
check_requirements() {
    if ! command -v aws &> /dev/null; then
        echo -e "${VERMELHO}[FALHA CRÍTICA]: AWS CLI não instalada.${RESET}"
        exit 1
    fi
}

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: S3 STORAGE PROVISIONER v1.1     "
echo -e "       (Secure Object Storage & Web)           "
echo -e "${CIANO}===============================================${RESET}"

check_requirements

# 3. CRIAÇÃO E VERSIONAMENTO
echo -e "\n${CIANO}[1/6] Provisionando Bucket: ${BUCKET_NAME}...${RESET}"
aws s3 mb "s3://${BUCKET_NAME}" --region "${REGION}"
aws s3api put-bucket-versioning --bucket "${BUCKET_NAME}" --versioning-configuration Status=Enabled

# 4. QUEBRA DO BLOQUEIO PÚBLICO (NECESSÁRIO PARA HOSTING)
echo -e "${CIANO}[2/6] Desabilitando Block Public Access (BPA)...${RESET}"
aws s3api delete-public-access-block --bucket "${BUCKET_NAME}"

# 5. APLICAÇÃO DE BUCKET POLICY (PRINCÍPIO DO MENOR PRIVILÉGIO)
echo -e "${CIANO}[3/6] Injetando Política de Leitura Pública...${RESET}"
cat <<EOF > policy.json
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "PublicReadGetObject",
            "Effect": "Allow",
            "Principal": "*",
            "Action": "s3:GetObject",
            "Resource": "arn:aws:s3:::${BUCKET_NAME}/*"
        }
    ]
}
EOF
aws s3api put-bucket-policy --bucket "${BUCKET_NAME}" --policy file://policy.json

# 6. CONFIGURAÇÃO DE HOSTING E DEPLOY
echo -e "${CIANO}[4/6] Ativando Static Web Engine...${RESET}"
aws s3 website "s3://${BUCKET_NAME}/" --index-document index.html

echo -e "${CIANO}[5/6] Enviando Telemetria Dashboard...${RESET}"
cat <<EOF > index.html
<!DOCTYPE html>
<html>
<head>
    <title>SkyCargo | Cloud Dashboard</title>
    <style>
        body { font-family: 'Courier New', monospace; background: #0d1117; color: #58a6ff; text-align: center; padding: 50px; }
        .box { border: 1px solid #30363d; padding: 30px; border-radius: 6px; background: #161b22; display: inline-block; }
        .live { color: #3fb950; font-weight: bold; }
    </style>
</head>
<body>
    <div class="box">
        <h1>🛰️ SKYCARGO CLOUD NODE</h1>
        <hr style="border-color: #30363d;">
        <p>STATUS: <span class="live">PROVISIONADO VIA SCRIPT</span></p>
        <p>DEPLOY TIME: $(date)</p>
        <p style="font-size: 0.8em; color: #8b949e;">Security: Bucket Policy Enabled | BPA Disabled</p>
    </div>
</body>
</html>
EOF
aws s3 cp index.html "s3://${BUCKET_NAME}/index.html"

# 7. LIMPEZA RAII (ARTEFATOS LOCAIS)
echo -e "${CIANO}[6/6] Executando Purga de Artefatos Locais...${RESET}"
rm policy.json index.html

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      INFRAESTRUTURA WEB ESTÁ ATIVA            "
echo -e " URL: http://${BUCKET_NAME}.s3-website-${REGION}.amazonaws.com"
echo -e "${VERDE}===============================================${RESET}"

# RESUMO TEÓRICO: SEGURANÇA POR POLÍTICA
# 1. BPA (Block Public Access): Atua como um firewall mestre da conta.
# 2. BUCKET POLICY: É um documento JSON de permissões granulares.
# 3. PRINCÍPIO DO MENOR PRIVILÉGIO: Liberamos apenas s3:GetObject, 
#    impedindo que o público liste (ListBucket) ou apague arquivos.
# 4. CLEANUP: Um script de elite não deixa lixo no diretório do projeto.

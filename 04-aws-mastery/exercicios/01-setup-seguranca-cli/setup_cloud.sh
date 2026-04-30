#!/bin/bash

# @file setup_cloud.sh
# @brief Script de auditoria e configuração inicial de segurança AWS.
# 
# Atividade 01 - Fundação Cloud (Nível Iniciado).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026
# 
# @section CloudMap Topologia de Identidade
# - Entidade: Usuário IAM 'Dev-Elite'.
# - Permissão: Policy 'PowerUserAccess'.
# - Segurança: Credenciais armazenadas em ~/.aws/credentials.

# --- 1. NAMESPACE DE INTERFACE (ANSI) ---
VERDE="\033[32m"
AMARELO="\033[33m"
CIANO="\033[36m"
RESET="\033[0m"

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: AUDITORIA DE SEGURANÇA v1.0     "
echo -e "       (Foundation & Identity Shield)          "
echo -e "${CIANO}===============================================${RESET}"

# Verificação de Instalação da CLI
if ! command -v aws &> /dev/null; then
    echo -e "${AMARELO}[ERRO]: AWS CLI não localizada. Instale antes de prosseguir.${RESET}"
    exit 1
fi

# 2. AUDITORIA DE IDENTIDADE ATIVA
echo -e "\n${CIANO}[1/3] Verificando Identidade Ativa...${RESET}"
aws sts get-caller-identity --output table

# 3. STATUS DE SAÚDE DA CONTA
echo -e "\n${CIANO}[2/3] Checando Região Padrão...${RESET}"
REGION=$(aws configure get region)
echo -e "Região de Operação: ${VERDE}${REGION:-'Não configurada'}${RESET}"

# 4. RESUMO TEÓRICO: SEGURANÇA E CLI NA AWS
# 1. O PERIGO DA ACCESS KEY: NUNCA versionar arquivos de credenciais.
# 2. AWS CLI: Ferramenta de elite para automação em escala.
# 3. MENOR PRIVILÉGIO: Dê apenas a permissão necessária.
# 4. MFA: Obrigatório para proteção contra vazamento de senhas físicas.

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      AMBINETE HOMOLOGADO PELO PEC (AWS ELITE) "
echo -e "${VERDE}===============================================${RESET}"

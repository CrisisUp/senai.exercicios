#!/bin/bash

# @file manage_ec2.sh
# @brief Script de orquestração para instâncias Linux e Firewalls Virtuais.
# 
# Atividade 03 - Computação & Network Security (Nível Iniciado).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026
# 
# @section CloudMap Topologia de Computação
# - Recurso: AWS EC2 (t3.micro).
# - Rede: VPC Default com Security Group dedicado.
# - Firewall: Porta 22 (SSH) limitada ao CIDR do operador via checkip.
# - Ciclo de Vida: Provisionamento On-Demand com tag de monitoramento.

# --- 1. NAMESPACE DE INTERFACE (ANSI) ---
VERDE="\033[32m"
AMARELO="\033[33m"
CIANO="\033[36m"
VERMELHO="\033[31m"
RESET="\033[0m"

# Configurações de Hardware
SG_NAME="skycargo-sec-group-$(date +%s)"
INSTANCE_TYPE="t3.micro"
AMI_ID="ami-051f8b2130e2831f5" 

# --- 2. FUNÇÕES DE VALIDAÇÃO ---
check_requirements() {
    if ! command -v aws &> /dev/null; then
        echo -e "${VERMELHO}[FALHA CRÍTICA]: AWS CLI não localizada.${RESET}"
        exit 1
    fi
}

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: EC2 COMPUTE ORCHESTRATOR v1.1   "
echo -e "       (Virtual Servers & Network Firewall)    "
echo -e "${CIANO}===============================================${RESET}"

check_requirements

# 3. PROVISIONAMENTO DO SECURITY GROUP
echo -e "\n${CIANO}[1/4] Criando Security Group: ${SG_NAME}...${RESET}"
SG_ID=$(aws ec2 create-security-group \
    --group-name "${SG_NAME}" \
    --description "SG para Processamento de Telemetria" \
    --query 'GroupId' --output text)

# 4. BLINDAGEM DE REDE (DINÂMICA)
MY_IP=$(curl -s http://checkip.amazonaws.com)
echo -e "${CIANO}[2/4] Blindando Porta 22 (SSH) para o IP: ${MY_IP}/32...${RESET}"
aws ec2 authorize-security-group-ingress \
    --group-id "${SG_ID}" \
    --protocol tcp --port 22 --cidr "${MY_IP}/32"

# 5. LANÇAMENTO DA INSTÂNCIA
echo -e "${CIANO}[3/4] Lançando Instância ${INSTANCE_TYPE}...${RESET}"
INSTANCE_ID=$(aws ec2 run-instances \
    --image-id "${AMI_ID}" \
    --count 1 \
    --instance-type "${INSTANCE_TYPE}" \
    --security-group-ids "${SG_ID}" \
    --tag-specifications "ResourceType=instance,Tags=[{Key=Name,Value=SkyCargo-Node},{Key=Project,Value=Elite}]" \
    --query 'Instances[0].InstanceId' --output text)

# 6. MONITORAMENTO DE BOOT
echo -e "${CIANO}[4/4] Aguardando Hardware Provisioning...${RESET}"
aws ec2 wait instance-running --instance-ids "${INSTANCE_ID}"
PUBLIC_IP=$(aws ec2 describe-instances --instance-ids "${INSTANCE_ID}" --query 'Reservations[0].Instances[0].PublicIpAddress' --output text)

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      PROVISIONAMENTO EC2 CONCLUÍDO            "
echo -e " IP PÚBLICO: ${VERDE}${PUBLIC_IP}${RESET}"
echo -e " COMANDO SSH: ssh -i \"sua-chave.pem\" ec2-user@${PUBLIC_IP}"
echo -e "${AMARELO} AVISO: Finalize com 'aws ec2 terminate-instances' após o uso!${RESET}"
echo -e "${VERDE}===============================================${RESET}"

# RESUMO TEÓRICO: EC2 E VIRTUALIZAÇÃO
# 1. IaC (Infra as Code): Automação evita erro humano e drift de config.
# 2. STATEFUL FIREWALL: O SG gerencia o estado da conexão automaticamente.
# 3. TAGGING STRATEGY: Vital para controle de custos e governança FinOps.
# 4. ELASTICIDADE: Capacidade de mudar o hardware sem reinstalar o software.

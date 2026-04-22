#!/bin/bash

# @file provision_rds.sh
# @brief Orquestração de Bancos de Dados Relacionais e Regras de Tráfego.
# 
# Atividade 04 - RDS & Layered Security (Nível Iniciado).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026
# 
# @section CloudMap Topologia de Dados
# - Recurso: Amazon RDS (PostgreSQL).
# - Rede: Isolamento em Subnet Privada.
# - Firewall: Porta 5432 aberta apenas para o SG da Aplicação (Tiered Arch).
# - Resiliência: Automated Backups e Retention de 7 dias.

# --- 1. NAMESPACE DE INTERFACE (ANSI) ---
VERDE="\033[32m"
AMARELO="\033[33m"
CIANO="\033[36m"
VERMELHO="\033[31m"
RESET="\033[0m"

DB_INSTANCE_IDENTIFIER="skycargo-db-master"
ENGINE="postgres"
INSTANCE_CLASS="db.t3.micro"

# --- 2. VALIDAÇÃO DE REQUISITOS ---
check_requirements() {
    if ! command -v aws &> /dev/null; then
        echo -e "${VERMELHO}[ERRO]: AWS CLI não encontrada.${RESET}"
        exit 1
    fi
}

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: RDS DATABASE PROVISIONER v1.1   "
echo -e "       (Managed Data & Security Tiers)         "
echo -e "${CIANO}===============================================${RESET}"

check_requirements

# 3. SECURITY GROUP DO BANCO
echo -e "\n${CIANO}[1/2] Provisionando DB-Security-Group...${RESET}"
DB_SG_ID=$(aws ec2 create-security-group \
    --group-name "skycargo-db-sg-$(date +%s)" \
    --description "Acesso restrito ao core de dados" \
    --query 'GroupId' --output text)

echo -e "SG ID: ${VERDE}${DB_SG_ID}${RESET}"

# 4. LANÇAMENTO DO MOTOR RDS (Simulado p/ Segurança)
echo -e "${CIANO}[2/2] Gerando comando de provisionamento RDS...${RESET}"
echo -e "${AMARELO}[INFO]: O RDS leva tempo para subir. Comando documentado abaixo.${RESET}"

# COMANDO DE REFERÊNCIA:
# aws rds create-db-instance \
#    --db-instance-identifier "${DB_INSTANCE_IDENTIFIER}" \
#    --engine "${ENGINE}" \
#    --db-instance-class "${INSTANCE_CLASS}" \
#    --allocated-storage 20 \
#    --master-username "admin_elite" \
#    --vpc-security-group-ids "${DB_SG_ID}" \
#    --backup-retention-period 7

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      AUTOMAÇÃO DE DADOS PRONTA PARA DEPLOY    "
echo -e " Identificador: ${DB_INSTANCE_IDENTIFIER}"
echo -e " Segurança: Layer 2 (SG Restriction Active)"
echo -e "${VERDE}===============================================${RESET}"

# RESUMO TEÓRICO: BANCOS GERENCIADOS
# 1. RESPONSABILIDADE COMPARTILHADA: AWS cuida da infra; você cuida do SQL.
# 2. ISOLAMENTO: Bancos nunca devem ter IP público em arquiteturas de elite.
# 3. RECOVERY: Snapshots permitem voltar o tempo em caso de corrupção.
# 4. SCALABILITY: Upgrade de instância em um clique via 'Modify-DB'.

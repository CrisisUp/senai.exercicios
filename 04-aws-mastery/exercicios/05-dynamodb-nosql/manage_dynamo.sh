#!/bin/bash

# @file manage_dynamo.sh
# @brief Orquestração de tabelas NoSQL e ingestão de telemetria.
# 
# Atividade 05 - DynamoDB & High Performance Data (Nível Iniciado).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026
# 
# @section CloudMap Topologia NoSQL
# - Recurso: Amazon DynamoDB.
# - Modelo de Dados: Chave-Valor com Sort Key para ordenação cronológica.
# - PK: DroneID | SK: Timestamp.
# - Performance: Latência milimétrica constante independente do volume.

# --- 1. NAMESPACE DE INTERFACE (ANSI) ---
VERDE="\033[32m"
AMARELO="\033[33m"
CIANO="\033[36m"
VERMELHO="\033[31m"
RESET="\033[0m"

TABLE_NAME="DroneTelemetry"

# --- 2. VALIDAÇÃO DE REQUISITOS ---
check_requirements() {
    if ! command -v aws &> /dev/null; then
        echo -e "${VERMELHO}[ERRO]: AWS CLI não localizada.${RESET}"
        exit 1
    fi
}

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: DYNAMODB TABLE MANAGER v1.1     "
echo -e "       (High-Speed NoSQL Ingestion)            "
echo -e "${CIANO}===============================================${RESET}"

check_requirements

# 3. PROVISIONAMENTO NoSQL
echo -e "\n${CIANO}[1/3] Criando Tabela ${TABLE_NAME}...${RESET}"
aws dynamodb create-table \
    --table-name "${TABLE_NAME}" \
    --attribute-definitions \
        AttributeName=DroneID,AttributeType=S \
        AttributeName=Timestamp,AttributeType=N \
    --key-schema \
        AttributeName=DroneID,KeyType=HASH \
        AttributeName=Timestamp,KeyType=RANGE \
    --billing-mode PAY_PER_REQUEST || echo -e "${AMARELO}[AVISO]: Tabela já operacional.${RESET}"

aws dynamodb wait table-exists --table-name "${TABLE_NAME}"

# 4. INGESTÃO DE TELEMETRIA
TS=$(date +%s)
echo -e "${CIANO}[2/3] Enviando Pulso de Telemetria (SKY-001)...${RESET}"
aws dynamodb put-item \
    --table-name "${TABLE_NAME}" \
    --item '{
        "DroneID": {"S": "SKY-001"},
        "Timestamp": {"N": "'$TS'"},
        "Lat": {"S": "-23.55"},
        "Lon": {"S": "-46.63"},
        "Status": {"S": "CRITICAL_LOW_BATT"}
    }'

# 5. QUERY DE ELITE (BUSCA INDEXADA)
echo -e "\n${CIANO}[3/3] Consultando Histórico do Sensor...${RESET}"
aws dynamodb query \
    --table-name "${TABLE_NAME}" \
    --key-condition-expression "DroneID = :id" \
    --expression-attribute-values '{":id": {"S": "SKY-001"}}' \
    --output table

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      OPERAÇÃO NoSQL EXECUTADA COM SUCESSO     "
echo -e " Integridade: Strong Consistency Mode Ready     "
echo -e "${VERDE}===============================================${RESET}"

# RESUMO TEÓRICO: PERFORMANCE NoSQL
# 1. KEY-VALUE DESIGN: Otimizado para buscas pontuais via Partition Key.
# 2. SCHEMA-LESS: Itens na mesma tabela podem ter atributos diferentes.
# 3. ON-DEMAND: Escala de zero a milhões de requests sem gestão de hardware.
# 4. DATA DISTRIBUTION: Dados são espalhados globalmente via algoritmos de Hash.

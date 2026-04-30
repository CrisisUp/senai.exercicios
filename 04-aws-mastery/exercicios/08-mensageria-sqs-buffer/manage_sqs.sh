#!/bin/bash

# @file manage_sqs.sh
# @brief Script de orquestração para Filas de Mensagens Assíncronas.
# 
# Atividade 08 - Amazon SQS & Resilient Buffering (Nível Arquiteto).
# 
# @author SENAI - Cristiano Batista Pessoa
# @date 22/04/2026
# 
# @section CloudMap Topologia de Mensageria
# - Recurso: Amazon SQS Standard.
# - Produtor: Script CLI (simulando Drone).
# - Consumidor: Script CLI (simulando Sistema de Manutenção).
# - Fluxo: Enviar -> Ocultar (Visibility) -> Processar -> Deletar.

# --- 1. NAMESPACE DE INTERFACE (ANSI) ---
VERDE="\033[32m"
AMARELO="\033[33m"
CIANO="\033[36m"
VERMELHO="\033[31m"
RESET="\033[0m"

QUEUE_NAME="SkyCargo-Maintenance-Queue"

# --- 2. VALIDAÇÃO DE REQUISITOS ---
check_requirements() {
    if ! command -v aws &> /dev/null; then
        echo -e "${VERMELHO}[ERRO]: AWS CLI não localizada.${RESET}"
        exit 1
    fi
}

echo -e "${CIANO}===============================================${RESET}"
echo -e "      G-CLOUD: SQS MESSAGE ORCHESTRATOR v1.0   "
echo -e "       (Async Buffering & Resilience)          "
echo -e "${CIANO}===============================================${RESET}"

check_requirements

# 3. CRIAÇÃO DA FILA
echo -e "\n${CIANO}[1/4] Provisionando Fila SQS...${RESET}"
QUEUE_URL=$(aws sqs create-queue \
    --queue-name "${QUEUE_NAME}" \
    --attributes VisibilityTimeout=30,MessageRetentionPeriod=86400 \
    --query 'QueueUrl' --output text)

echo -e "Fila Operacional: ${VERDE}${QUEUE_URL}${RESET}"

# 4. ENVIO DE MENSAGEM (PRODUTOR)
echo -e "${CIANO}[2/4] Enviando Alerta de Manutenção (Drone SKY-X)...${RESET}"
PAYLOAD='{"DroneID": "SKY-VULCAN-X9", "Evento": "MANUTENCAO_PREVENTIVA", "HorasVoo": 450}'

aws sqs send-message \
    --queue-url "${QUEUE_URL}" \
    --message-body "${PAYLOAD}" \
    --query 'MessageId' --output text

# 5. RECEBIMENTO DE MENSAGEM (CONSUMIDOR)
echo -e "${CIANO}[3/4] Capturando Mensagem para Processamento...${RESET}"
RECEIVE_OUT=$(aws sqs receive-message \
    --queue-url "${QUEUE_URL}" \
    --max-number-of-messages 1 \
    --query 'Messages[0].[Body,ReceiptHandle]' --output text)

# Separa o corpo e o identificador de deleção (ReceiptHandle)
BODY=$(echo "${RECEIVE_OUT}" | head -n 1)
HANDLE=$(echo "${RECEIVE_OUT}" | tail -n 1)

if [ -n "${BODY}" ]; then
    echo -e "Conteúdo Capturado: ${AMARELO}${BODY}${RESET}"
    
    # 6. DELEÇÃO (CONFIRMAÇÃO DE PROCESSAMENTO)
    echo -e "${CIANO}[4/4] Confirmando Liquidação (Deletando da Fila)...${RESET}"
    aws sqs delete-message --queue-url "${QUEUE_URL}" --receipt-handle "${HANDLE}"
    echo -e "${VERDE}[OK]: Mensagem removida com sucesso. RAM e Fila limpas.${RESET}"
else
    echo -e "${AMARELO}[AVISO]: Fila vazia no momento.${RESET}"
fi

echo -e "\n${VERDE}===============================================${RESET}"
echo -e "      LOGÍSTICA ASSÍNCRONA HOMOLOGADA          "
echo -e " Protocolo: FIFO-like (Simulated) | Mode: Decoupled"
echo -e "${VERDE}===============================================${RESET}"

# RESUMO TEÓRICO: MENSAGERIA E DESACOPLAMENTO
# 1. LOOSE COUPLING: O produtor não precisa saber se o consumidor 
#    está online. A fila é a "Caixa de Correio" segura.
# 2. ESCALABILIDADE HORIZONTAL: Se houver muitas mensagens, podemos 
#    colocar 10 Lambdas lendo a mesma fila em paralelo.
# 3. VISIBILITY TIMEOUT: Quando você lê a msg, ela não é deletada, 
#    apenas fica invisível. Se o seu código falhar, ela reaparece 
#    após 30s para outro tentar ler.
# 4. GARANTIA DE DADOS: O SQS armazena as mensagens em múltiplos 
#    discos na AWS. Se o seu app cair, as mensagens estão seguras.

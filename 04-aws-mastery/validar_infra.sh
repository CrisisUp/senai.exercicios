#!/bin/bash

# --- NAMESPACE DE INTERFACE (ANSI) ---
VERDE="\033[32m"
VERMELHO="\033[31m"
AMARELO="\033[33m"
CIANO="\033[36m"
RESET="\033[0m"

FAIL=0

echo -e "${CIANO}===============================================${RESET}"
echo -e "      VALIDADOR DE INFRAESTRUTURA AWS          "
echo -e "${CIANO}===============================================${RESET}"

# 1. Verifique se o aws cli está instalado
echo -ne "Verificando AWS CLI... "
if command -v aws &> /dev/null; then
    echo -e "${VERDE}[OK]${RESET}"
else
    echo -e "${VERMELHO}[FALHA]${RESET}"
    echo -e "${AMARELO}[ERRO]: AWS CLI não localizada. Instale antes de prosseguir.${RESET}"
    FAIL=1
fi

# 2. Execute 'bash -n' em todos os .sh do projeto para validar a sintaxe
echo -e "\nValidando sintaxe de scripts shell..."

# Encontrar todos os arquivos .sh a partir da raiz do projeto (onde o script está)
# Usando o diretório do script como base
BASE_DIR=$(dirname "$0")
SH_FILES=$(find "$BASE_DIR" -name "*.sh")

for file in $SH_FILES; do
    # Pular o próprio validador para evitar confusão se ele for novo
    if [[ "$(basename "$file")" == "validar_infra.sh" ]]; then
        continue
    fi

    echo -ne "Sintaxe de $file: "
    if bash -n "$file"; then
        echo -e "${VERDE}[PASSOU]${RESET}"
    else
        echo -e "${VERMELHO}[FALHA]${RESET}"
        FAIL=1
    fi
done

# 3. Resultado Final
echo -e "\n${CIANO}===============================================${RESET}"
if [ $FAIL -eq 0 ]; then
    echo -e "      ${VERDE}INFRAESTRUTURA VALIDADA${RESET}"
else
    echo -e "      ${VERMELHO}FALHA NA VALIDAÇÃO DA INFRAESTRUTURA${RESET}"
fi
echo -e "${CIANO}===============================================${RESET}"

# Sair com erro se falhou em algo
if [ $FAIL -ne 0 ]; then
    exit 1
fi

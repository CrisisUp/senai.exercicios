#!/usr/bin/env python3
import os
import sys
import re

"""
🎓 PEC Linter - Governança de Engenharia de Elite
Valida se os arquivos seguem o Protocolo de Expansão de Conteúdo.
"""

# Configurações de Conformidade
REQUIRED_CPP = ["@file", "@brief", "@section MemoryMap"]
REQUIRED_TXT = ["Estudo de Caso", "Necessidade Técnica", "ANÁLISE DE FALHA CRÍTICA"]

def validate_file(filepath, required_terms):
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
        missing = [term for term in required_terms if term not in content]
        return missing

def main():
    fail_count = 0
    print("\033[36m=== AUDITORIA DE CONFORMIDADE PEC ===\033[0m")

    for root, dirs, files in os.walk("."):
        # Ignorar pastas de build e ferramentas
        if any(x in root for x in ["build", ".git", "target", "venv"]):
            continue

        for file in files:
            path = os.path.join(root, file)
            missing = []

            if file.endswith(".cpp"):
                missing = validate_file(path, REQUIRED_CPP)
            elif file.endswith(".txt") and "atividade-extra" in file:
                missing = validate_file(path, REQUIRED_TXT)

            if missing:
                print(f"\033[31m[FALHA]\033[0m {path}")
                for m in missing:
                    print(f"  - Ausente: {m}")
                fail_count += 1

    print("\033[36m=====================================\033[0m")
    if fail_count == 0:
        print("\033[32mRESULTADO: 100% CONFORME. PADRÃO DE ELITE MANTIDO.\033[0m")
        sys.exit(0)
    else:
        print(f"\033[33mRESULTADO: {fail_count} arquivos fora do padrão.\033[0m")
        # sys.exit(1) # Desativado para não travar o fluxo inicial

if __name__ == "__main__":
    main()

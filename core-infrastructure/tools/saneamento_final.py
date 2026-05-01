
import os
import re

# Mapeamento de arquivos para seus diretórios reais
files_map = {
    "01-cpp-mastery/level-01-iniciado/atividade-extra03/atividade-extra03.cpp": "Atividade 03",
    "01-cpp-mastery/level-01-iniciado/atividade-extra04/atividade-extra04.cpp": "Atividade 04",
    "01-cpp-mastery/level-01-iniciado/atividade-extra05/atividade-extra05-saude.cpp": "Atividade 05",
    "01-cpp-mastery/level-01-iniciado/atividade-extra06/atividade-extra06-inventario.cpp": "Atividade 06",
    "01-cpp-mastery/level-01-iniciado/atividade-extra07/atividade-extra07-ponto.cpp": "Atividade 07",
    "01-cpp-mastery/level-01-iniciado/atividade-extra08/atividade-extra08-folha.cpp": "Atividade 08",
    "01-cpp-mastery/level-01-iniciado/atividade-extra09/atividade-extra09-logistica.cpp": "Atividade 09",
    "01-cpp-mastery/level-01-iniciado/atividade-extra10/atividade-extra10-seguranca.cpp": "Atividade 10",
    "01-cpp-mastery/level-02-arquiteto/atividade-extra11/GerenciadorAtendimento.h": "Atividade 11",
    "01-cpp-mastery/level-02-arquiteto/atividade-extra12/GestorBiblioteca.h": "Atividade 12",
    "01-cpp-mastery/level-02-arquiteto/atividade-extra13/GestorBiblioteca.h": "Atividade 13",
    "01-cpp-mastery/level-02-arquiteto/atividade-extra14/InterfaceBiblioteca.h": "Atividade 14-H",
    "01-cpp-mastery/level-02-arquiteto/atividade-extra14/atividade-extra14-estilos.cpp": "Atividade 14-CPP",
    "01-cpp-mastery/level-02-arquiteto/atividade-extra15/MotorFinanceiro.h": "Atividade 15",
    "01-cpp-mastery/level-02-arquiteto/atividade-extra16/MotorERP.h": "Atividade 16",
    "01-cpp-mastery/level-02-arquiteto/atividade-extra17/MonitorSaude.h": "Atividade 17",
    "01-cpp-mastery/level-02-arquiteto/atividade-extra18/PacoteLogistico.h": "Atividade 18",
    "01-cpp-mastery/level-02-arquiteto/atividade-extra19/Produto.h": "Atividade 19",
    "01-cpp-mastery/level-02-arquiteto/atividade-extra20/atividade-extra20-banco.cpp": "Atividade 20",
    "01-cpp-mastery/level-03-mestre-poo/atividade-extra21/atividade-extra21-agro.cpp": "Atividade 21",
    "01-cpp-mastery/level-03-mestre-poo/atividade-extra22/atividade-extra22-aviacao.cpp": "Atividade 22",
    "01-cpp-mastery/level-03-mestre-poo/atividade-extra23/atividade-extra23-pagamentos.cpp": "Atividade 23",
    "01-cpp-mastery/level-03-mestre-poo/atividade-extra24/atividade-extra24-ecossistema.cpp": "Atividade 24",
    "01-cpp-mastery/level-03-mestre-poo/atividade-extra25/atividade-extra25-refatoracao.cpp": "Atividade 25",
    "01-cpp-mastery/level-03-mestre-poo/atividade-extra26/atividade-extra26-templates.cpp": "Atividade 26",
    "01-cpp-mastery/level-03-mestre-poo/atividade-extra27/atividade-extra27-templates-classe.cpp": "Atividade 27",
    "01-cpp-mastery/level-03-mestre-poo/atividade-extra28/atividade-extra28-stl-map.cpp": "Atividade 28",
    "01-cpp-mastery/level-03-mestre-poo/atividade-extra29/atividade-extra29-trading.cpp": "Atividade 29",
    "01-cpp-mastery/level-03-mestre-poo/atividade-extra30/atividade-extra30-factory.cpp": "Atividade 30"
}

NEW_NAMESPACE_START = """namespace UI {
    const std::string RESET    = "\\033[0m";
    const std::string NEGRITO  = "\\033[1m";
    const std::string VERDE    = "\\033[32m";
    const std::string VERMELHO = "\\033[31m";
    const std::string AZUL     = "\\033[34m";
    const std::string CIANO    = "\\033[36m";
    const std::string AMARELO  = "\\033[33m";"""

def process_file(file_path):
    if not os.path.exists(file_path):
        return

    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()

    match = re.search(r'namespace\s+UI\s*\{', content)
    if not match:
        return

    start_idx = match.start()
    brace_count = 0
    end_idx = -1
    for i in range(match.end() - 1, len(content)):
        if content[i] == '{':
            brace_count += 1
        elif content[i] == '}':
            brace_count -= 1
            if brace_count == 0:
                end_idx = i
                break
    
    if end_idx == -1:
        return

    old_namespace_content = content[match.end():end_idx]
    lines = old_namespace_content.split('\n')
    preserved_lines = []
    for line in lines:
        stripped = line.strip()
        if not stripped: continue
        if re.match(r'const\s+(std::)?string\s+\w+', stripped): continue
        if 'const' in stripped and ('string' in stripped or 'std::string' in stripped) and '=' in stripped: continue
        preserved_lines.append(line)

    new_namespace_body = NEW_NAMESPACE_START
    if preserved_lines:
        new_namespace_body += "\n" + "\n".join(preserved_lines)
    new_namespace_body += "\n}"

    new_content = content[:start_idx] + new_namespace_body + content[end_idx+1:]

    if '#include <string>' not in new_content:
        new_content = re.sub(r'(namespace\s+UI\s*\{)', r'#include <string>\n\n\1', new_content)

    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(new_content)
    print(f"Saneado: {file_path}")

for f in files_map.keys():
    process_file(f)

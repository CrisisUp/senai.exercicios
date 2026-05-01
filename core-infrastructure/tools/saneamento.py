
import os
import re

files = [
    "01-cpp-mastery/level-04-elite/atividade-extra03/atividade-extra03.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra04/atividade-extra04.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra05/atividade-extra05-saude.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra06/atividade-extra06-inventario.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra07/atividade-extra07-ponto.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra08/atividade-extra08-folha.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra09/atividade-extra09-logistica.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra10/atividade-extra10-seguranca.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra11/GerenciadorAtendimento.h",
    "01-cpp-mastery/level-04-elite/atividade-extra12/GestorBiblioteca.h",
    "01-cpp-mastery/level-04-elite/atividade-extra13/GestorBiblioteca.h",
    "01-cpp-mastery/level-04-elite/atividade-extra14/InterfaceBiblioteca.h",
    "01-cpp-mastery/level-04-elite/atividade-extra14/atividade-extra14-estilos.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra15/MotorFinanceiro.h",
    "01-cpp-mastery/level-04-elite/atividade-extra16/MotorERP.h",
    "01-cpp-mastery/level-04-elite/atividade-extra17/MonitorSaude.h",
    "01-cpp-mastery/level-04-elite/atividade-extra18/PacoteLogistico.h",
    "01-cpp-mastery/level-04-elite/atividade-extra19/Produto.h",
    "01-cpp-mastery/level-04-elite/atividade-extra20/atividade-extra20-banco.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra21/atividade-extra21-agro.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra22/atividade-extra22-aviacao.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra23/atividade-extra23-pagamentos.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra24/atividade-extra24-ecossistema.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra25/atividade-extra25-refatoracao.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra26/atividade-extra26-templates.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra27/atividade-extra27-templates-classe.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra28/atividade-extra28-stl-map.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra29/atividade-extra29-trading.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra30/atividade-extra30-factory.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra31/atividade-extra31-validacao.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra32/atividade-extra32-observer.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra33/atividade-extra33-bacen.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra34/atividade-extra34-espacial.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra35/atividade-extra35-playlist.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra36/atividade-extra36-logistica.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra37/atividade-extra37-hospital.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra38/atividade-extra38-grafos.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra39/atividade-extra39-bfs.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra40/atividade-extra40-dijkstra.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra41/atividade-extra41-gcity.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra42/atividade-extra42-gresponse.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra43/atividade-extra43-debugging.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra44/atividade-extra44-gameloop.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra45/atividade-extra45-input.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra46/atividade-extra46-render.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra47/atividade-extra47-invaders.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra48/atividade-extra48-estoque-evolutivo.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra49/atividade-extra49-modular.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra50/atividade-extra50-iot.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra51/atividade-extra51-motor.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra52/atividade-extra52-operadores.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra53/atividade-extra53-frota.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra54/atividade-extra54-imoveis.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra55/atividade-extra55-pagamentos.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra56/atividade-extra56-templates.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra57/atividade-extra57-memoria.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra58/atividade-extra58-templates.cpp",
    "01-cpp-mastery/level-04-elite/atividade-extra59/atividade-extra59-smart.cpp",
    "01-cpp-mastery/level-01-iniciado/SA-2-Desafio-2/SA-2-Desafio-2.cpp",
    "01-cpp-mastery/level-01-iniciado/atividade01/atividade1-vetores.cpp",
    "01-cpp-mastery/level-01-iniciado/atividade02/atividade2-vetores.cpp"
]

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
        print(f"File not found: {file_path}")
        return

    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()

    # Find namespace UI block
    # Using a regex that tries to find 'namespace UI {' and the matching '}'
    # This is tricky because of nested braces, but usually namespace UI doesn't have nested braces in these files
    # except maybe for functions.
    
    match = re.search(r'namespace\s+UI\s*\{', content)
    if not match:
        return

    start_idx = match.start()
    
    # Find matching closing brace
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
        print(f"Could not find closing brace for namespace UI in {file_path}")
        return

    old_namespace_content = content[match.end():end_idx]
    
    # Extract non-constant lines (functions, etc.)
    lines = old_namespace_content.split('\n')
    preserved_lines = []
    for line in lines:
        stripped = line.strip()
        if not stripped:
            continue
        # If it's a constant definition, skip it
        # Patterns to match: const string NAME = ...; or const std::string NAME = ...;
        if re.match(r'const\s+(std::)?string\s+\w+', stripped):
            continue
        # Also skip corrupted looking lines if they are constants
        if 'const' in stripped and ('string' in stripped or 'std::string' in stripped) and '=' in stripped:
            continue
        
        preserved_lines.append(line)

    new_namespace_body = NEW_NAMESPACE_START
    if preserved_lines:
        new_namespace_body += "\n" + "\n".join(preserved_lines)
    new_namespace_body += "\n}"

    new_content = content[:start_idx] + new_namespace_body + content[end_idx+1:]

    # Ensure #include <string> is present
    if '#include <string>' not in new_content:
        # Insert before the namespace UI
        new_content = re.sub(r'(namespace\s+UI\s*\{)', r'#include <string>\n\n\1', new_content)

    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(new_content)
    print(f"Processed {file_path}")

for f in files:
    process_file(f)


import os
import re

def get_new_path(old_path):
    if "repositorio-extra/atividade-extra" in old_path:
        num_match = re.search(r"atividade-extra(\d+)", old_path)
        if num_match:
            num = int(num_match.group(1))
            filename = os.path.basename(old_path)
            if 3 <= num <= 10:
                return f"01-cpp-mastery/level-01-iniciado/atividade-extra{num:02d}/{filename}"
            elif 11 <= num <= 20:
                return f"01-cpp-mastery/level-02-arquiteto/atividade-extra{num:02d}/{filename}"
            elif 21 <= num <= 30:
                return f"01-cpp-mastery/level-03-mestre-poo/atividade-extra{num:02d}/{filename}"
            elif 31 <= num <= 59:
                return f"01-cpp-mastery/level-04-elite/atividade-extra{num:02d}/{filename}"
    elif "repositorio/SA-2" in old_path:
        return f"01-cpp-mastery/desafios-sa/SA-2-Desafio-2/{os.path.basename(old_path)}"
    elif "repositorio/atividade0" in old_path:
        num_match = re.search(r"atividade0(\d+)", old_path)
        if num_match:
            num = int(num_match.group(1))
            return f"01-cpp-mastery/level-01-iniciado/atividade0{num}/{os.path.basename(old_path)}"
    return old_path

old_files = [
    "repositorio-extra/atividade-extra03/atividade-extra03.cpp",
    "repositorio-extra/atividade-extra04/atividade-extra04.cpp",
    "repositorio-extra/atividade-extra05/atividade-extra05-saude.cpp",
    "repositorio-extra/atividade-extra06/atividade-extra06-inventario.cpp",
    "repositorio-extra/atividade-extra07/atividade-extra07-ponto.cpp",
    "repositorio-extra/atividade-extra08/atividade-extra08-folha.cpp",
    "repositorio-extra/atividade-extra09/atividade-extra09-logistica.cpp",
    "repositorio-extra/atividade-extra10/atividade-extra10-seguranca.cpp",
    "repositorio-extra/atividade-extra11/GerenciadorAtendimento.h",
    "repositorio-extra/atividade-extra12/GestorBiblioteca.h",
    "repositorio-extra/atividade-extra13/GestorBiblioteca.h",
    "repositorio-extra/atividade-extra14/InterfaceBiblioteca.h",
    "repositorio-extra/atividade-extra14/atividade-extra14-estilos.cpp",
    "repositorio-extra/atividade-extra15/MotorFinanceiro.h",
    "repositorio-extra/atividade-extra16/MotorERP.h",
    "repositorio-extra/atividade-extra17/MonitorSaude.h",
    "repositorio-extra/atividade-extra18/PacoteLogistico.h",
    "repositorio-extra/atividade-extra19/Produto.h",
    "repositorio-extra/atividade-extra20/atividade-extra20-banco.cpp",
    "repositorio-extra/atividade-extra21/atividade-extra21-agro.cpp",
    "repositorio-extra/atividade-extra22/atividade-extra22-aviacao.cpp",
    "repositorio-extra/atividade-extra23/atividade-extra23-pagamentos.cpp",
    "repositorio-extra/atividade-extra24/atividade-extra24-ecossistema.cpp",
    "repositorio-extra/atividade-extra25/atividade-extra25-refatoracao.cpp",
    "repositorio-extra/atividade-extra26/atividade-extra26-templates.cpp",
    "repositorio-extra/atividade-extra27/atividade-extra27-templates-classe.cpp",
    "repositorio-extra/atividade-extra28/atividade-extra28-stl-map.cpp",
    "repositorio-extra/atividade-extra29/atividade-extra29-trading.cpp",
    "repositorio-extra/atividade-extra30/atividade-extra30-factory.cpp",
    "repositorio-extra/atividade-extra31/atividade-extra31-validacao.cpp",
    "repositorio-extra/atividade-extra32/atividade-extra32-observer.cpp",
    "repositorio-extra/atividade-extra33/atividade-extra33-bacen.cpp",
    "repositorio-extra/atividade-extra34/atividade-extra34-espacial.cpp",
    "repositorio-extra/atividade-extra35/atividade-extra35-playlist.cpp",
    "repositorio-extra/atividade-extra36/atividade-extra36-logistica.cpp",
    "repositorio-extra/atividade-extra37/atividade-extra37-hospital.cpp",
    "repositorio-extra/atividade-extra38/atividade-extra38-grafos.cpp",
    "repositorio-extra/atividade-extra39/atividade-extra39-bfs.cpp",
    "repositorio-extra/atividade-extra40/atividade-extra40-dijkstra.cpp",
    "repositorio-extra/atividade-extra41/atividade-extra41-gcity.cpp",
    "repositorio-extra/atividade-extra42/atividade-extra42-gresponse.cpp",
    "repositorio-extra/atividade-extra43/atividade-extra43-debugging.cpp",
    "repositorio-extra/atividade-extra44/atividade-extra44-gameloop.cpp",
    "repositorio-extra/atividade-extra45/atividade-extra45-input.cpp",
    "repositorio-extra/atividade-extra46/atividade-extra46-render.cpp",
    "repositorio-extra/atividade-extra47/atividade-extra47-invaders.cpp",
    "repositorio-extra/atividade-extra48/atividade-extra48-estoque-evolutivo.cpp",
    "repositorio-extra/atividade-extra49/atividade-extra49-modular.cpp",
    "repositorio-extra/atividade-extra50/atividade-extra50-iot.cpp",
    "repositorio-extra/atividade-extra51/atividade-extra51-motor.cpp",
    "repositorio-extra/atividade-extra52/atividade-extra52-operadores.cpp",
    "repositorio-extra/atividade-extra53/atividade-extra53-frota.cpp",
    "repositorio-extra/atividade-extra54/atividade-extra54-imoveis.cpp",
    "repositorio-extra/atividade-extra55/atividade-extra55-pagamentos.cpp",
    "repositorio-extra/atividade-extra56/atividade-extra56-templates.cpp",
    "repositorio-extra/atividade-extra57/atividade-extra57-memoria.cpp",
    "repositorio-extra/atividade-extra58/atividade-extra58-templates.cpp",
    "repositorio-extra/atividade-extra59/atividade-extra59-smart.cpp",
    "repositorio/SA-2-Desafio-2/SA-2-Desafio-2.cpp",
    "repositorio/atividade01/atividade1-vetores.cpp",
    "repositorio/atividade02/atividade2-vetores.cpp"
]

files = [get_new_path(f) for f in old_files]

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
        # Try relative to script location if called from tools/
        alt_path = os.path.join("../..", file_path)
        if os.path.exists(alt_path):
            file_path = alt_path
        else:
            print(f"File not found: {file_path}")
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
        print(f"Could not find closing brace for namespace UI in {file_path}")
        return

    old_namespace_content = content[match.end():end_idx]
    
    lines = old_namespace_content.split('\n')
    preserved_lines = []
    for line in lines:
        stripped = line.strip()
        if not stripped:
            continue
        if re.match(r'const\s+(std::)?string\s+\w+', stripped):
            continue
        if 'const' in stripped and ('string' in stripped or 'std::string' in stripped) and '=' in stripped:
            continue
        
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
    print(f"Processed {file_path}")

if __name__ == "__main__":
    for f in files:
        process_file(f)

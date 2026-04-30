
import os
import re

files = [
    "repositorio-extra/atividade-extra03/atividade-extra03.cpp",
    "repositorio-extra/atividade-extra04/atividade-extra04.cpp",
    "repositorio-extra/atividade-extra05/atividade-extra05-saude.cpp",
    "repositorio-extra/atividade-extra06/atividade-extra06-inventario.cpp",
    "repositorio-extra/atividade-extra07/atividade-extra07-ponto.cpp",
    "repositorio-extra/atividade-extra08/atividade-extra08-folha.cpp",
    "repositorio-extra/atividade-extra09/atividade-extra09-logistica.cpp",
    "repositorio-extra/atividade-extra10/atividade-extra10-seguranca.cpp",
    "repositorio-extra/atividade-extra11/GerenciadorAtendimento.h",
    "repositorio-extra/atividade-extra11/GerenciadorAtendimento.cpp",
    "repositorio-extra/atividade-extra12/GestorBiblioteca.h",
    "repositorio-extra/atividade-extra12/GestorBiblioteca.cpp",
    "repositorio-extra/atividade-extra13/GestorBiblioteca.h",
    "repositorio-extra/atividade-extra13/GestorBiblioteca.cpp",
    "repositorio-extra/atividade-extra14/InterfaceBiblioteca.h",
    "repositorio-extra/atividade-extra14/InterfaceBiblioteca.cpp",
    "repositorio-extra/atividade-extra14/atividade-extra14-estilos.cpp",
    "repositorio-extra/atividade-extra15/MotorFinanceiro.h",
    "repositorio-extra/atividade-extra15/MotorFinanceiro.cpp",
    "repositorio-extra/atividade-extra16/MotorERP.h",
    "repositorio-extra/atividade-extra16/MotorERP.cpp",
    "repositorio-extra/atividade-extra17/MonitorSaude.h",
    "repositorio-extra/atividade-extra17/MonitorSaude.cpp",
    "repositorio-extra/atividade-extra17/atividade-extra17-saude.cpp",
    "repositorio-extra/atividade-extra18/PacoteLogistico.h",
    "repositorio-extra/atividade-extra18/PacoteLogistico.cpp",
    "repositorio-extra/atividade-extra18/atividade-extra18-logistica.cpp",
    "repositorio-extra/atividade-extra19/Produto.h",
    "repositorio-extra/atividade-extra19/Produto.cpp",
    "repositorio-extra/atividade-extra19/atividade-extra19-estoque.cpp",
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

mapping = {
    "BOLD": "NEGRITO",
    "RED": "VERMELHO",
    "GREEN": "VERDE",
    "BLUE": "AZUL",
    "CYAN": "CIANO",
    "CIAN": "CIANO",
    "YELLOW": "AMARELO",
    "BRANCO": "RESET",  # Map missing to RESET
    "ROXO": "CIANO",    # Map missing to CIANO
    "CINZA": "RESET",   # Map missing to RESET
    "MAGENTA": "CIANO"  # Map missing to CIANO
}

def fix_usages(file_path):
    if not os.path.exists(file_path):
        return
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    
    # Replace UI::OLD_NAME with UI::NEW_NAME
    # Only if it's not in the namespace UI definition itself (which we already fixed)
    # Actually, replacing everywhere is fine if the namespace definition is already correct.
    
    new_content = content
    for old, new in mapping.items():
        new_content = re.sub(r'UI::' + old + r'\b', 'UI::' + new, new_content)
    
    if new_content != content:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(new_content)
        print(f"Fixed usages in {file_path}")

for f in files:
    fix_usages(f)

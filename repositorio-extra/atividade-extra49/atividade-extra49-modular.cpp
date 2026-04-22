/**
 * @file atividade-extra49-modular.cpp
 * @brief Programa principal da calculadora de engenharia (UI de Elite).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra o desacoplamento total entre Interface (main) e Lógica (Calculadora).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include "Calculadora.h" 

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
    
    void cabecalho() {
        cout << UI::AZUL << UI::NEGRITO << "===============================================" << endl;
        cout << "      G-ENGINEER: CALCULADORA MODULAR v2.0     " << endl;
        cout << "       (Elite Architectural Refactoring)       " << endl;
        cout << "===============================================" << UI::RESET << endl;
    }
}

// --- 2. EXECUÇÃO DA UI ---

int main() {
    UI::limparTela();
    UI::cabecalho();

    double raio, altura;

    cout << UI::BRANCO << "Configuração de Fundação Geotécnica:" << UI::RESET << endl;
    
    cout << " >> Informe o Raio da Estaca (metros): ";
    if (!(cin >> raio)) return 1;

    cout << " >> Informe a Altura do Pilar (metros): ";
    if (!(cin >> altura)) return 1;

    // --- CONSUMO DO MÓDULO EXTERNO ---
    // A main não conhece as fórmulas, apenas o contrato em Calculadora.h
    double volume = CalculadoraEngenharia::calcularVolumeCilindro(raio, altura);

    cout << fixed << setprecision(3);
    cout << "\n" << UI::NEGRITO << "RESULTADO DA ANÁLISE ESTRUTURAL:" << UI::RESET << endl;
    cout << UI::VERDE << " >> Volume Estimado: " << UI::NEGRITO << volume << " m³" << UI::RESET << endl;
    cout << UI::CIANO << " >> Status: " << UI::RESET << "Cálculo homologado via Módulo Modular." << endl;

    cout << UI::AZUL << UI::NEGRITO << "\n===============================================" << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ARQUITETURA MODULAR (.h vs .cpp)
    ===============================================================

    1. O CONTRATO (INTERFACE .h):
       - O arquivo header define o protocolo de comunicação. Ele 
         promete que a função 'calcularVolumeCilindro' existe, mas 
         não diz como ela funciona. Isso permite que a main() seja 
         compilada sem conhecer os detalhes matemáticos internos.

    2. A CAIXA-PRETA (IMPLEMENTAÇÃO .cpp):
       - A lógica real fica escondida no .cpp. Isso protege a 
         propriedade intelectual da empresa e permite que o motor 
         seja atualizado (ex: mudar a precisão do PI) sem quebrar 
         quem usa o módulo.

    3. COMPILAÇÃO SEPARADA (PERFORMANCE):
       - Em sistemas gigantes, compilar tudo em um arquivo levaria 
         horas. Com módulos, o compilador gera arquivos '.o' 
         individuais e o Linker une apenas o que mudou, 
         economizando tempo de desenvolvimento.

    4. SEGURANÇA DE ESCOPO (NAMESPACE):
       - O uso do namespace 'CalculadoraEngenharia' impede que o 
         nome 'PI' ou 'calcularArea' entre em conflito com outras 
         bibliotecas instaladas no sistema, mantendo a higiene do 
         código global.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Makefile/CMake: Orquestrando múltiplos arquivos .cpp.
    - Static Libraries (.a / .lib): Empacotar módulos para venda.
    - Dynamic Libraries (.so / .dll): Módulos carregados no runtime.
    ===============================================================
*/

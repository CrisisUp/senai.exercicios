/**
 * @file atividade-extra50-iot.cpp
 * @brief Programa principal para monitoramento IoT Industrial (Namespaces).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a organização profissional de escopos e segurança de hardware.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include "Monitoramento.h" 

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

#include <string>

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

/**
 * Ao usar o namespace IoT, integramos os drivers industriais.
 */
using namespace IoT;

int main() {
    UI::limparTela();
    
    // Instanciação na STACK
    SensorPressao caldeira("MAIN_REACTOR_01");
    double leituraInput;

    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-SYSTEM: MONITORAMENTO IOT v2.0         " << endl;
    cout << "       (Elite Scope & Namespace Control)       " << endl;
    cout << "===============================================" << UI::RESET << endl;

    cout << UI::RESET << "ID SENSOR ATIVO: " << UI::RESET << caldeira.getId() << endl;

    cout << "\nDigite o pulso de pressão atual (psi): ";
    if (!(cin >> leituraInput)) return 1;

    // --- INTERAÇÃO MODULAR ---
    if (caldeira.registrarLeitura(leituraInput)) {
        cout << "\n" << UI::VERDE << UI::NEGRITO << "[SUCESSO]: " << UI::RESET 
             << "Telemetria estável em " << caldeira.getValor() << " psi." << endl;
    } else {
        cout << "\n" << UI::VERMELHO << UI::NEGRITO << "[ALERTA CRÍTICO]: " << UI::RESET 
             << UI::VERMELHO << "Valor (" << leituraInput << ") fora dos limites físicos!" << UI::RESET << endl;
        cout << UI::VERMELHO << "Procedimento de Evasão/Shut-down acionado." << UI::RESET << endl;
    }

    cout << UI::CIANO << UI::NEGRITO << "\n===============================================" << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: NAMESPACES E PROTEÇÃO DE ESCOPO
    ===============================================================

    1. NAMESPACES (ESPACIALIZAÇÃO LÓGICA):
       - Em sistemas industriais, centenas de módulos precisam 
         coexistir. Namespaces funcionam como "Pastas Virtuais", 
         permitindo que 'SensorPressao' em IoT não colida com 
         'SensorPressao' em uma biblioteca de meteorologia.

    2. ENCAPSULAMENTO DE HARDWARE:
       - No arquivo Monitoramento.h, 'valorEhSeguro' é privado. 
         Isso é vital; o programador da UI (main) não pode burlar a 
         validação física do reactor para registrar um valor 
         perigoso. O contrato é indestrutível.

    3. USANDO 'using namespace':
       - Embora facilite a escrita, o 'using namespace' deve ser 
         usado com cautela em arquivos .h (Headers). O ideal é 
         usá-lo apenas em arquivos .cpp para manter o controle 
         estrito de quais nomes estão sendo injetados no sistema.

    4. PERFORMANCE MODULAR:
       - Namespaces são resolvidos inteiramente pelo compilador. Não 
         há um único byte extra de RAM ou ciclo de CPU gasto para 
         organizar seu código desta forma. É organização pura e 
         gratuita.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Namespace Aliases: `namespace io = IoT;` para nomes longos.
    - Inline Namespaces (C++11): Versionamento de bibliotecas.
    - Unnamed Namespaces: Para criar funções "locais" ao arquivo .cpp.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

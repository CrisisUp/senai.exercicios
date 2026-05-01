#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file main.cpp
 * @brief Execução da Torre de Controle ATC v2.0.
 */

#include "Aeronave.h"
#include <vector>

using namespace std;

int main()
{
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      SISTEMA DE TORRE DE CONTROLE (ATC v2.0)  " << endl;
    cout << "       (Elite Polymorphic Architecture)        " << endl;
    cout << "===============================================" << UI::RESET << endl;

    vector<Aeronave*> torreDeControle;

    torreDeControle.push_back(new AviaoComercial("PT-AIR"));
    torreDeControle.push_back(new Helicoptero("PP-HELI"));
    torreDeControle.push_back(new AviaoComercial("AZ-SKY"));

    cout << "\n" << UI::RESET << "[ATC]: Autorização concedida. Iniciando sequência de decolagem em massa..." << UI::RESET << "\n" << endl;

    for (const auto& aero : torreDeControle) {
        if (aero) {
            aero->prepararParaDecolagem(); 
            aero->decolar();               
            cout << UI::RESET << "-----------------------------------------------" << UI::RESET << endl;
        }
    }

    cout << "\n" << UI::RESET << "[SISTEMA]: Encerrando turno e liberando memória..." << UI::RESET << endl;
    for (auto& aero : torreDeControle) {
        delete aero;
        aero = nullptr;
    }
    torreDeControle.clear();

    cout << UI::VERDE << "\nOperação ATC finalizada com Zero Vazamentos." << UI::RESET << endl;

    return 0;
}

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

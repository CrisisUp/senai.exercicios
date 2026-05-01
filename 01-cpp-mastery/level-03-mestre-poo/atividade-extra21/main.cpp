#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file main.cpp
 * @brief Execução principal do Sistema de Gestão Agrotech v2.0.
 */

#include "MaquinaAgricola.h"
#include <iomanip>

using namespace std;

int main()
{
    UI::limparTela();
    cout << fixed << setprecision(1);

    cout << UI::VERDE << UI::NEGRITO << "===============================================" << endl;
    cout << "      SISTEMA DE GESTÃO AGROTECH v2.0          " << endl;
    cout << "       (Elite Inheritance Module)              " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Instanciação na STACK
    Trator johnDeere("T-900", "John Deere", 18.5);

    int opt = 0;
    do {
        johnDeere.exibirStatus();
        cout << UI::RESET << "\nMENU DE COMANDO:" << UI::RESET << endl;
        cout << "[1] Arar Terra (Trabalho)" << endl;
        cout << "[2] Reabastecer Máquina" << endl;
        cout << "[3] Finalizar Turno" << endl;
        cout << UI::CIANO << "Escolha: " << UI::RESET;
        
        if (!(cin >> opt)) break;

        switch (opt) {
            case 1: johnDeere.ararTerra(); break;
            case 2: johnDeere.abastecer(); break;
            case 3: cout << UI::AMARELO << "Encerrando sistemas de bordo..." << UI::RESET << endl; break;
            default: cout << UI::VERMELHO << "Comando desconhecido." << UI::RESET << endl;
        }
    } while (opt != 3);

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

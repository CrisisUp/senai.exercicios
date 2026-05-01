#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file main.cpp
 * @brief Execução do Motor de Câmbio Forex utilizando Templates.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória
 * - Stack: Armazena variáveis locais (ienes, dolares, taxas).
 * - Code Segment: Contém as instanciações das funções template geradas pelo compilador.
 */

#include <iostream>
#include <iomanip>
#include "ForexEngine.h"

using namespace std;

int main()
{
    UI::limparTela();
    UI::cabecalho();
    cout << fixed << setprecision(4);

    // --- CENÁRIO 1: CONVERSÃO DE MOEDA INTEIRA (IENE) ---
    int ienes = 25000;
    double taxaIeneReal = 0.0345;
    auto ieneEmReal = aplicarTaxa(ienes, taxaIeneReal);

    cout << UI::AMARELO << UI::NEGRITO << "[INSTÂNCIA INT]: " << UI::RESET 
         << ienes << " JPY -> " << UI::VERDE << UI::NEGRITO << "R$ " << ieneEmReal << UI::RESET << endl;

    // --- CENÁRIO 2: CONVERSÃO DE MOEDA DOUBLE (DÓLAR) ---
    double dolares = 1450.50;
    double taxaDolarReal = 5.2410;
    auto dolarEmReal = aplicarTaxa(dolares, taxaDolarReal);

    cout << UI::AZUL << UI::NEGRITO << "[INSTÂNCIA DOUBLE]: " << UI::RESET 
         << dolares << " USD -> " << UI::VERDE << UI::NEGRITO << "R$ " << dolarEmReal << UI::RESET << endl;

    // --- CENÁRIO 3: SOMA DE TIPOS HETEROGÊNEOS ---
    auto patrimonioTotal = somarSaldos(ieneEmReal, dolarEmReal);
    
    cout << "\n" << UI::RESET << "DASHBOARD PATRIMONIAL:" << UI::RESET << endl;
    cout << "Soma Consolidada: " << UI::VERDE << UI::NEGRITO << "R$ " << patrimonioTotal << UI::RESET << endl;
    cout << UI::CIANO << "-----------------------------------------------" << endl;
    cout << "Status: " << UI::VERDE << "Tipagem Estática Garantida via Template." << UI::RESET << endl;

    return 0;
}

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

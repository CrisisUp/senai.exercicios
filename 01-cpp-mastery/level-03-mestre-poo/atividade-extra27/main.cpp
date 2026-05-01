#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file main.cpp
 * @brief Execução do sistema de logística utilizando Class Templates.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória
 * - Stack: Objetos UnidadeDeCarga<int>, UnidadeDeCarga<double>, UnidadeDeCarga<string>.
 * - Code Segment: Instanciações físicas das classes template.
 */

#include <iostream>
#include <iomanip>
#include "UnidadeDeCarga.h"

using namespace std;

int main()
{
    UI::limparTela();
    UI::cabecalho();
    cout << fixed << setprecision(2);

    // --- INSTÂNCIA 1: UNIDADES INTEIRAS (T = int) ---
    UnidadeDeCarga<int> c1("BR-778", 150.0, 500); 
    cout << UI::RESET << "[LOG]: Unidade Inteira (Sensores) configurada na STACK." << UI::RESET << endl;
    c1.exibirManifesto();

    // --- INSTÂNCIA 2: VOLUME LÍQUIDO (T = double) ---
    UnidadeDeCarga<double> c2("OIL-99", 5400.5, 450.75);
    cout << UI::RESET << "[LOG]: Unidade de Precisão (Volume) configurada na STACK." << UI::RESET << endl;
    c2.exibirManifesto();

    // --- INSTÂNCIA 3: CARGA DOCUMENTAL (T = string) ---
    UnidadeDeCarga<string> c3("DOC-001", 12.0, "CERTIFICADOS_EXPORT_A1.PDF");
    cout << UI::RESET << "[LOG]: Unidade de Texto (Log) configurada na STACK." << UI::RESET << endl;
    c3.exibirManifesto();

    cout << "\n" << UI::VERDE << UI::NEGRITO << "SISTEMA GENÉRICO HOMOLOGADO COM 100% DE TIPAGEM ESTÁTICA." << UI::RESET << endl;

    return 0;
}

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

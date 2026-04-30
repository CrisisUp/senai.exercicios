/**
 * @file MonitorSaude.cpp
 * @brief Implementação dos métodos da classe PacienteMonitorado.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "MonitorSaude.h"
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @brief Construtor otimizado com inicialização de membros.
 */
PacienteMonitorado::PacienteMonitorado(const string& n) 
    : nome(n), bpm(70), temperatura(36.5), oxigenacao(98) {}

bool PacienteMonitorado::setBPM(int valor) {
    // Validação de segurança médica
    if (valor > 0 && valor < 250) {
        bpm = valor;
        return true;
    }
    return false;
}

bool PacienteMonitorado::setTemperatura(double valor) {
    if (valor >= 30.0 && valor <= 45.0) {
        temperatura = valor;
        return true;
    }
    return false;
}

bool PacienteMonitorado::setOxigenacao(int valor) {
    if (valor >= 0 && valor <= 100) {
        oxigenacao = valor;
        return true;
    }
    return false;
}

/**
 * @brief Gera relatório clínico com feedback visual (Cores ANSI).
 */
void PacienteMonitorado::analisarEstado() const {
    cout << "\n" << UI::NEGRITO << "-----------------------------------------------" << UI::RESET << endl;
    cout << "RELATÓRIO CLÍNICO: " << UI::CIANO << UI::NEGRITO << nome << UI::RESET << endl;
    
    // Análise de Frequência Cardíaca
    cout << "Frequência Cardíaca: " << bpm << " BPM ";
    if (bpm > 110 || bpm < 50) 
        cout << UI::VERMELHO << UI::NEGRITO << "[ALERTA CRÍTICO]" << UI::RESET;
    else if (bpm > 95)
        cout << UI::AMARELO << "[TAQUICARDIA LEVE]" << UI::RESET;
    else 
        cout << UI::VERDE << "[ESTÁVEL]" << UI::RESET;

    // Análise de Temperatura
    cout << "\nTemperatura        : " << fixed << setprecision(1) << temperatura << " °C ";
    if (temperatura >= 39.0) 
        cout << UI::VERMELHO << UI::NEGRITO << "[FEBRE ALTA]" << UI::RESET;
    else if (temperatura > 37.5)
        cout << UI::AMARELO << "[ESTADO FEBRIL]" << UI::RESET;
    else 
        cout << UI::VERDE << "[AFEBRIL]" << UI::RESET;

    // Análise de Oxigenação
    cout << "\nOxigenação         : " << oxigenacao << " % ";
    if (oxigenacao < 90) 
        cout << UI::VERMELHO << UI::NEGRITO << "[HIPÓXIA GRAVE]" << UI::RESET;
    else if (oxigenacao < 94)
        cout << UI::AMARELO << "[MONITORAR OXIGÊNIO]" << UI::RESET;
    else 
        cout << UI::VERDE << "[SATURAÇÃO IDEAL]" << UI::RESET;
    
    cout << "\n" << UI::NEGRITO << "-----------------------------------------------" << UI::RESET << endl;
}
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

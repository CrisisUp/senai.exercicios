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

PacienteMonitorado::PacienteMonitorado(string n) 
    : nome(n), bpm(70), temperatura(36.5), oxigenacao(98) {}

bool PacienteMonitorado::setBPM(int valor) {
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

void PacienteMonitorado::analisarEstado() const {
    cout << "\n-----------------------------------------------" << endl;
    cout << "RELATÓRIO DE MONITORAMENTO: " << UI::CIANO << nome << UI::RESET << endl;
    
    cout << "Frequência Cardíaca: " << bpm << " BPM ";
    if (bpm > 100 || bpm < 50) cout << UI::VERMELHO << "[ALERTA]" << UI::RESET;
    else cout << UI::VERDE << "[NORMAL]" << UI::RESET;

    cout << "\nTemperatura        : " << fixed << setprecision(1) << temperatura << " °C ";
    if (temperatura > 37.5) cout << UI::VERMELHO << "[FEBRE]" << UI::RESET;
    else cout << UI::VERDE << "[NORMAL]" << UI::RESET;

    cout << "\nOxigenação         : " << oxigenacao << " % ";
    if (oxigenacao < 94) cout << UI::VERMELHO << "[CRÍTICO]" << UI::RESET;
    else cout << UI::VERDE << "[NORMAL]" << UI::RESET;
    cout << "\n-----------------------------------------------" << endl;
}

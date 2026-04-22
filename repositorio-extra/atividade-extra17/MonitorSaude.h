/**
 * @file MonitorSaude.h
 * @brief Definição da classe PacienteMonitorado e interface UI.
 * 
 * Parte da Atividade Extra 17 - Refatoração Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef MONITOR_SAUDE_H
#define MONITOR_SAUDE_H

#include <string>
#include <iostream>

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string VERMELHO = "\033[31m";
    const std::string VERDE    = "\033[32m";
    const std::string AMARELO  = "\033[33m";
    const std::string CIANO    = "\033[36m";
}

// --- 2. DEFINIÇÃO DA CLASSE (O NOVO CONCEITO) ---

class PacienteMonitorado {
private:
    std::string nome;
    int bpm;
    double temperatura;
    int oxigenacao;

public:
    /**
     * @brief Construtor: Inicializa o paciente com valores seguros.
     * @param n Nome do paciente.
     */
    PacienteMonitorado(std::string n);

    // --- MÉTODOS DE ACESSO (SETTERS COM VALIDAÇÃO) ---
    bool setBPM(int valor);
    bool setTemperatura(double valor);
    bool setOxigenacao(int valor);

    // --- MÉTODOS DE LEITURA (GETTERS) ---
    std::string getNome() const { return nome; }
    int getBPM() const { return bpm; }
    double getTemperatura() const { return temperatura; }
    int getOxigenacao() const { return oxigenacao; }

    // --- LÓGICA DE NEGÓCIO: MONITORAMENTO ---
    void analisarEstado() const;
};

#endif // MONITOR_SAUDE_H

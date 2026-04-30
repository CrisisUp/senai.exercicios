/**
 * @file MonitorSaude.h
 * @brief Definição da classe PacienteMonitorado e interface UI.
 * 
 * Parte da Atividade Extra 17 - Refatoração Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Elite Standard)
 * - Objeto PacienteMonitorado: Alocado na STACK (estático) durante o ciclo de vida da main.
 * - Atributos Primitivos (bpm, temperatura): Armazenados na STACK dentro do bloco do objeto (4-8 bytes).
 * - Atributo Dinâmico (nome): O objeto std::string fica na STACK, mas o texto real é alocado na HEAP.
 */

#ifndef MONITOR_SAUDE_H
#define MONITOR_SAUDE_H

#include <string>
#include <iostream>

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
    inline void limparTela() { std::cout << "\033[2J\033[1;1H"; }
}

// --- 2. DEFINIÇÃO DA CLASSE (O NOVO CONCEITO) ---

/**
 * @class PacienteMonitorado
 * @brief Representa um paciente em regime de monitoramento crítico.
 * Aplica o padrão de Encapsulamento para garantir integridade médica.
 */
class PacienteMonitorado {
private:
    std::string nome;
    int bpm;
    double temperatura;
    int oxigenacao;

public:
    /**
     * @brief Construtor: Inicializa o paciente com valores seguros.
     * @param n Nome do paciente (Passagem por const ref para performance).
     */
    PacienteMonitorado(const std::string& n);

    // --- MÉTODOS DE ACESSO (SETTERS COM VALIDAÇÃO) ---
    bool setBPM(int valor);
    bool setTemperatura(double valor);
    bool setOxigenacao(int valor);

    // --- MÉTODOS DE LEITURA (GETTERS - FANTASMA DO CPU) ---
    // Retornamos referência constante para evitar cópias desnecessárias na Heap
    const std::string& getNome() const { return nome; }
    int getBPM() const { return bpm; }
    double getTemperatura() const { return temperatura; }
    int getOxigenacao() const { return oxigenacao; }

    // --- LÓGICA DE NEGÓCIO: MONITORAMENTO ---
    void analisarEstado() const;
};

#endif // MONITOR_SAUDE_H

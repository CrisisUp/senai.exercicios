/**
 * @file Telemetria.h
 * @brief Definição da estrutura de dados para telemetria de frota.
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

#ifndef TELEMETRIA_H
#define TELEMETRIA_H

#include <string>
#include <iostream>

// --- NAMESPACE DE INTERFACE (PADRÃO ELITE) ---
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string AMARELO  = "\033[33m";
    const std::string CIANO    = "\033[36m";
}

/**
 * @struct Telemetria
 * @brief Dados consolidados de um veículo em trânsito.
 */
struct Telemetria {
    int idCaminhao;
    double latitude;
    double longitude;
    double velocidade;
    double combustivel;
    std::string timestamp;

    void exibir() const {
        std::cout << UI::CIANO << UI::NEGRITO << "[ID: " << idCaminhao << "] " << UI::RESET
                  << UI::VERDE << "Vel: " << velocidade << " km/h" << UI::RESET << " | "
                  << UI::AMARELO << "Comb: " << combustivel << "L" << UI::RESET << " | "
                  << "Pos: (" << latitude << ", " << longitude << ")" << std::endl;
    }
};

#endif // TELEMETRIA_H

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

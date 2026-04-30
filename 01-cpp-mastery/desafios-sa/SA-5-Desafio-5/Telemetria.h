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
        std::cout << "[ID: " << idCaminhao << "] "
                  << "Vel: " << velocidade << " km/h | "
                  << "Comb: " << combustivel << "L | "
                  << "Pos: (" << latitude << ", " << longitude << ")" << std::endl;
    }
};

#endif // TELEMETRIA_H

/**
 * @file SmartResource.cpp
 * @brief Implementação de Telemetria GPS com Automação de Ciclo de Vida.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "SmartResource.h"
#include <iostream>
#include <iomanip>

namespace Logistica {

    ModuloGPS::ModuloGPS(const std::string& _id) 
        : idCaminhao(_id), latitude(0.0), longitude(0.0) {
        std::cout << "\033[32m[SMART-ALLOC]: Módulo GPS para " << idCaminhao 
                  << " alocado com sucesso.\033[0m" << std::endl;
    }

    ModuloGPS::~ModuloGPS() {
        std::cout << "\033[31m[SMART-FREE]: Módulo GPS para " << idCaminhao 
                  << " destruído (Memória devolvida via RAII).\033[0m" << std::endl;
    }

    void ModuloGPS::atualizarCoordenadas(double lat, double lon) {
        latitude = lat;
        longitude = lon;
    }

    void ModuloGPS::mostrarStatus() const {
        std::cout << " >> GPS [" << idCaminhao << "] -> Lat: " << std::fixed 
                  << std::setprecision(4) << latitude << " | Lon: " << longitude << std::endl;
    }

} // namespace Logistica

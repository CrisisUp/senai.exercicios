/**
 * @file SmartResource.cpp
 * @brief Implementação modular do recurso crítico.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include "SmartResource.h"
#include <iostream>

namespace Logistica {

    ModuloGPS::ModuloGPS(std::string _id) : id(_id), latitude(0.0), longitude(0.0) {
        std::cout << "\033[32m[HARDWARE]:\033[0m Iniciando ModuloGPS ID: " << id << std::endl;
    }

    ModuloGPS::~ModuloGPS() {
        std::cout << "\033[31m[HARDWARE]:\033[0m Encerrando e Limpando ModuloGPS ID: " << id << std::endl;
    }

    void ModuloGPS::atualizarCoordenadas(double lat, double lon) {
        latitude = lat;
        longitude = lon;
    }

    void ModuloGPS::mostrarStatus() const {
        std::cout << "GPS: " << id << " | COORD: [" << latitude << ", " << longitude << "]" << std::endl;
    }
}

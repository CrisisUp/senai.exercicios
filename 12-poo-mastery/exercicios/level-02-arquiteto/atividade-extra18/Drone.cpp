#define ANSI_RESET "\033[0m"
/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file Drone.cpp
 * @brief Implementação da classe Drone.
 */

#include "Drone.h"
#include <iostream>

namespace Nexus {
    Drone::Drone(std::string id) : id(id) {}

    void Drone::adicionarSensor(const Sensor& s) {
        sensores.push_back(s);
    }

    void Drone::status() const {
        std::cout << "[Nexus] Drone ID: " << id << " operando com " << sensores.size() << " sensores." << std::endl;
    }
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

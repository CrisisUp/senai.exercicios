#define ANSI_RESET "\033[0m"
/**
 * @file Drone.cpp
 * @brief Implementação/Componente Drone.cpp
 * @author Cristiano
 * @date 2026
 */
#include "Drone.h"

Drone::Drone(std::string m, int b) : modelo(m), bateria(b) {}

void Drone::decolar() {
    std::cout << "[SISTEMA] Drone " << modelo << " iniciando motores..." << std::endl;
}

void Drone::verStatus() {
    std::cout << "Drone: " << modelo << " | Bateria: " << bateria << "%" << std::endl;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

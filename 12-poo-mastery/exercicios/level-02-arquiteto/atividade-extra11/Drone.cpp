/**
 * @file Drone.cpp
 * @brief Implementação/Componente Drone.cpp
 * @author Cristiano
 * @date 2026
 */
#include "Drone.h"
#include <iostream>

// Cores ANSI
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

Drone::Drone(std::string m, int b) : modelo(m), bateria(b) {}

std::string Drone::getModelo() const {
    return modelo;
}

int Drone::getBateria() const {
    return bateria;
}

void Drone::verStatus() const {
    std::cout << CYAN << "--- STATUS DO DRONE (CONST) ---" << RESET << std::endl;
    std::cout << "Modelo: " << BOLD << modelo << RESET << std::endl;
    std::cout << "Bateria: " << (bateria > 20 ? GREEN : "\033[31m") << bateria << "%" << RESET << std::endl;
}

void Drone::setBateria(int b) {
    bateria = b;
}

void Drone::decolar() {
    std::cout << "[SISTEMA] Drone " << modelo << " decolando..." << std::endl;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

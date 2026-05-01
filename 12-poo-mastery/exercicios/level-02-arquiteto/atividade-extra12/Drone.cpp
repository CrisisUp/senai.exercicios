#define ANSI_RESET "\033[0m"
/**
 * @file Drone.cpp
 * @brief Implementação/Componente Drone.cpp
 * @author Cristiano
 * @date 2026
 */
#include "Drone.h"
#include <iostream>

Drone::Drone(std::string m, std::string sensorTipo) : modelo(m) {
    gps = new Sensor(sensorTipo);
}

Drone::~Drone() {
    delete gps;
}

// Construtor de Cópia - DEEP COPY
Drone::Drone(const Drone& outro) {
    this->modelo = outro.modelo + " (Clone)";
    this->gps = new Sensor(outro.gps->tipo); // Aloca novo sensor com mesmo valor
}

// Operador de Atribuição - DEEP COPY
Drone& Drone::operator=(const Drone& outro) {
    if (this == &outro) return *this; // Proteção contra auto-atribuição

    delete this->gps; // Libera memória atual

    this->modelo = outro.modelo;
    this->gps = new Sensor(outro.gps->tipo); // Aloca novo

    return *this;
}

void Drone::setSensorTipo(std::string t) {
    gps->tipo = t;
}

void Drone::verStatus() const {
    std::cout << "Drone: " << modelo << " | Sensor: " << gps->tipo << " (Endereço Sensor: " << gps << ")" << std::endl;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

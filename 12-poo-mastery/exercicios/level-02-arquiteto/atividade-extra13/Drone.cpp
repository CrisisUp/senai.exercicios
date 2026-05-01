#define ANSI_RESET "\033[0m"
/**
 * @file Drone.cpp
 * @brief Implementação/Componente Drone.cpp
 * @author Cristiano
 * @date 2026
 */
#include "Drone.h"

Drone::Drone(std::string m, int b) : modelo(m), bateria(b) {}

// Soma baterias e cria um novo modelo combinado
Drone Drone::operator+(const Drone& outro) const {
    int novaBateria = this->bateria + outro.bateria;
    if (novaBateria > 100) novaBateria = 100; // Limite físico
    return Drone(this->modelo + " + " + outro.modelo, novaBateria);
}

// Compara se são do mesmo modelo
bool Drone::operator==(const Drone& outro) const {
    return this->modelo == outro.modelo;
}

// Implementação do operador << (Friend)
std::ostream& operator<<(std::ostream& os, const Drone& d) {
    os << "[Drone: " << d.modelo << " | Bateria: " << d.bateria << "%]";
    return os;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

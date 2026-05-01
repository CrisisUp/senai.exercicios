#define ANSI_RESET "\033[0m"
/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file Sensor.cpp
 * @brief Implementação da classe Sensor.
 */

#include "Sensor.h"
#include <iostream>

namespace Nexus {
    Sensor::Sensor(std::string t, float v) : tipo(t), valor(v) {}

    void Sensor::lerDados() {
        std::cout << "[Nexus] Lendo sensor " << tipo << ": " << valor << std::endl;
    }

    std::string Sensor::getTipo() const { return tipo; }
    float Sensor::getValor() const { return valor; }
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

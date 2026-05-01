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

Drone::Drone(std::string m) : modelo(m) {}

std::string Drone::getModelo() const { return modelo; }

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

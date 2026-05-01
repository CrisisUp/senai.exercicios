#define ANSI_RESET "\033[0m"
/**
 * @file main.cpp
 * @brief Implementação/Componente main.cpp
 * @author Cristiano
 * @date 2026
 */
#include "Drone.h"

int main() {
    Drone d("Modular-X1", 95);
    d.verStatus();
    d.decolar();
    return 0;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

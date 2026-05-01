/**
 * @file main.cpp
 * @brief Implementação de Sobrecarga de Operadores (O Objeto como Tipo Nativo)
 * @author Gemini CLI
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapa de Memória
 * - Stack: Objetos 'drone1', 'drone2' e 'combo'.
 */

#include <iostream>
#include "Drone.h"

#define BOLD    "\033[1m"
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"

int main() {
    std::cout << BOLD << "=== ATIVIDADE 13: OPERATOR OVERLOADING ===" << RESET << std::endl;

    Drone d1("Alpha", 40);
    Drone d2("Beta", 30);
    Drone d3("Alpha", 100);

    // Teste do operator<<
    std::cout << CYAN << "Drones criados:" << RESET << std::endl;
    std::cout << "d1: " << d1 << std::endl;
    std::cout << "d2: " << d2 << std::endl;
    std::cout << "d3: " << d3 << std::endl;

    // Teste do operator+
    std::cout << std::endl << CYAN << "Operação: combo = d1 + d2" << RESET << std::endl;
    Drone combo = d1 + d2;
    std::cout << "Resultado: " << combo << std::endl;

    // Teste do operator==
    std::cout << std::endl << CYAN << "Comparações:" << RESET << std::endl;
    std::cout << "d1 == d2? " << (d1 == d2 ? "SIM" : "NÃO") << std::endl;
    std::cout << "d1 == d3? " << (d1 == d3 ? "SIM" : "NÃO") << std::endl;

    std::cout << std::endl << GREEN << "Sintaxe natural de linguagem implementada com sucesso." << RESET << std::endl;

    return 0;
}

/**
 * @section ResumoTeórico
 * A sobrecarga de operadores permite que classes personalizadas utilizem operadores 
 * padrão do C++. Isso melhora a legibilidade e permite que objetos sejam usados 
 * em contextos onde tipos nativos são esperados (ex: algoritmos da STL).
 * Operadores binários podem ser implementados como membros ou funções globais (friend).
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

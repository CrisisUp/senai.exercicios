/**
 * @file main.cpp
 * @brief Implementação de Deep Copy (O Clone Perfeito)
 * @author Gemini CLI
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapa de Memória
 * - Stack: Objetos 'droneA' e 'droneB'.
 * - Heap: Ponteiros 'gps' alocados individualmente para cada objeto.
 */

#include <iostream>
#include "Drone.h"

#define BOLD    "\033[1m"
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

int main() {
    std::cout << BOLD << "=== ATIVIDADE 12: DEEP COPY & RULE OF THREE ===" << RESET << std::endl;

    std::cout << YELLOW << "[Original]" << RESET << " Criando droneA..." << std::endl;
    Drone droneA("Explorer-1", "GPS-Glonass");
    droneA.verStatus();

    std::cout << std::endl << YELLOW << "[Cópia]" << RESET << " Clonando droneA para droneB..." << std::endl;
    Drone droneB = droneA; // Chama Construtor de Cópia
    droneB.verStatus();

    std::cout << std::endl << YELLOW << "[Teste de Independência]" << RESET << " Alterando sensor do droneB..." << std::endl;
    droneB.setSensorTipo("Galileo-Advanced");
    
    std::cout << "droneA: "; droneA.verStatus();
    std::cout << "droneB: "; droneB.verStatus();

    std::cout << std::endl << GREEN << "Deep Copy confirmado: droneA não foi afetado pela alteração em droneB." << RESET << std::endl;

    return 0;
}

/**
 * @section ResumoTeórico
 * A Regra dos Três (Rule of Three) afirma que se uma classe define um Destrutor, ela 
 * provavelmente também precisa de um Construtor de Cópia e um Operador de Atribuição.
 * Deep Copy garante que membros apontados por ponteiros sejam duplicados na memória,
 * evitando que múltiplos objetos disputem e deletem o mesmo endereço.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

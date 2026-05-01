/**
 * @file atividade-extra01.cpp
 * @brief Implementação básica de classe e objetos (O Primeiro Molde)
 * @author Gemini CLI
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapa de Memória
 * - Stack: Objetos 'droneA' e 'droneB' são alocados estaticamente na stack.
 * - Heap: Strings de 'modelo' podem alocar dinamicamente na heap internamente.
 */

#include <iostream>
#include <string>

// Cores ANSI para UX profissional
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

/**
 * @class Drone
 * @brief Representa um drone de carga da SkyCargo Nexus.
 */
class Drone {
public:
    std::string modelo;
    int bateria;

    /**
     * @brief Exibe o status atual do drone.
     */
    void verStatus() {
        std::cout << CYAN << "----------------------------" << RESET << std::endl;
        std::cout << BOLD << "Drone: " << YELLOW << modelo << RESET << std::endl;
        std::cout << BOLD << "Bateria: " << (bateria > 20 ? GREEN : "\033[31m") << bateria << "%" << RESET << std::endl;
        std::cout << CYAN << "----------------------------" << RESET << std::endl;
    }

    void decolar() {
        std::cout << "[SISTEMA] Drone " << BOLD << modelo << RESET << " decolando..." << std::endl;
    }
};

int main() {
    std::cout << BOLD << YELLOW << "=== SKYCARGO NEXUS - HANGAR DE ENGENHARIA ===" << RESET << std::endl << std::endl;

    // Instanciando objetos na Stack
    Drone droneA;
    droneA.modelo = "Alpha-V1";
    droneA.bateria = 85;

    Drone droneB;
    droneB.modelo = "Beta-Transport";
    droneB.bateria = 15;

    // Chamada de métodos
    droneA.verStatus();
    droneA.decolar();

    std::cout << std::endl;

    droneB.verStatus();
    droneB.decolar();

    std::cout << std::endl << GREEN << "Processamento concluído com sucesso." << RESET << std::endl;

    return 0;
}

/**
 * @section ResumoTeórico
 * A Programação Orientada a Objetos (POO) permite encapsular dados e comportamentos.
 * A 'Classe' funciona como um molde blueprint, enquanto o 'Objeto' é a instância real.
 * Atributos (modelo, bateria) definem o estado, e Métodos (verStatus, decolar) definem o comportamento.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

/**
 * @file atividade-extra04.cpp
 * @brief Implementação de Sobrecarga de Métodos (Versatilidade de Comando)
 * @author Gemini CLI
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapa de Memória
 * - Stack: 'drone' alocado na stack. Múltiplas assinaturas de métodos no segmento de código.
 */

#include <iostream>
#include <string>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"

class Drone {
private:
    std::string modelo;

public:
    Drone(std::string m) : modelo(m) {}

    // Sobrecarga de Métodos
    void decolar() {
        std::cout << "[MODO PADRÃO] " << modelo << " decolando suavemente..." << std::endl;
    }

    void decolar(int velocidade) {
        std::cout << "[MODO TURBO] " << modelo << " decolando a " << velocidade << " km/h!" << std::endl;
    }

    void decolar(double lat, double lon) {
        std::cout << "[MODO DIRECIONADO] " << modelo << " decolando rumo a Lat: " << lat << " | Lon: " << lon << std::endl;
    }
};

int main() {
    std::cout << BOLD << YELLOW << "=== SKYCARGO NEXUS - SISTEMA DE SOBRECARGA ===" << RESET << std::endl << std::endl;

    Drone drone("Interceptor-X");

    std::cout << CYAN << "--- Teste 1: Padrão ---" << RESET << std::endl;
    drone.decolar();

    std::cout << std::endl << CYAN << "--- Teste 2: Velocidade ---" << RESET << std::endl;
    drone.decolar(150);

    std::cout << std::endl << CYAN << "--- Teste 3: Coordenadas ---" << RESET << std::endl;
    drone.decolar(-23.5505, -46.6333);

    return 0;
}

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

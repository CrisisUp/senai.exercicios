/**
 * @file main.cpp
 * @brief Programa principal para demonstrar o uso de Namespaces.
 * @author Gemini CLI
 * @date 2026-04-22
 * 
 * @section MemoryMap Mapeamento de Memória
 * - Stack: Objetos 'meuDrone', 's1', 's2' (estáticos no escopo da função).
 * - Heap: Vetor interno de sensores dentro do objeto Drone (dinâmico).
 */

#include <iostream>
#include "Drone.h"
#include "Sensor.h"

// Cores ANSI para UX profissional
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"

void demonstrarConflito() {
    std::cout << YELLOW << "\n--- Demonstrando Resolução de Escopo ---" << RESET << std::endl;
    
    // Usando classes de diferentes namespaces com o operador ::
    Nexus::Sensor s1("GPS", 45.2);
    RadarCorp::Sensor s2;
    
    s1.lerDados();
    s2.detectar();
    
    std::cout << GREEN << "Conflito evitado com sucesso usando namespaces!" << RESET << std::endl;
}

void demonstrarUsing() {
    std::cout << CYAN << "\n--- Demonstrando 'using namespace' Controlado ---" << RESET << std::endl;
    
    {
        using namespace Nexus; // Escopo limitado a este bloco
        Drone meuDrone("NX-200");
        meuDrone.adicionarSensor(Sensor("Lidar", 120.5));
        meuDrone.status();
    }
    
    // Fora do bloco, Drone não é acessível sem prefixo
    std::cout << "Fora do bloco, 'Drone' exige Nexus::Drone." << std::endl;
}

int main() {
    std::cout << RED << "=== SISTEMA NEXUS: GERENCIAMENTO DE TERRITÓRIOS ===" << RESET << std::endl;
    
    demonstrarConflito();
    demonstrarUsing();

    std::cout << CYAN << "\n====================================================" << RESET << std::endl;
    std::cout << GREEN << "RESUMO TEÓRICO:" << RESET << std::endl;
    std::cout << "1. Namespaces evitam colisão de nomes em grandes projetos." << std::endl;
    std::cout << "2. O operador :: (resolução de escopo) acessa membros específicos." << std::endl;
    std::cout << "3. 'using namespace std' é má prática pois polui o escopo global." << std::endl;
    std::cout << "4. Namespaces podem ser aninhados para maior organização." << std::endl;
    std::cout << CYAN << "====================================================" << RESET << std::endl;

    return 0;
}

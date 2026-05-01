/**
 * @file main.cpp
 * @brief Demonstração de Classes Template (Programação Genérica).
 * @author Gemini CLI
 * @date 2026-04-22
 * 
 * @section MemoryMap Mapeamento de Memória
 * - Stack: 'caixaPeso', 'caixaDrone', 'pesoReal' (alocação estática).
 * - Heap: 'meuDrone' (alocado dinamicamente via new).
 */

#include <iostream>
#include "CaixaDeTransporte.h"
#include "Drone.h"

// Cores ANSI
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"

int main() {
    std::cout << MAGENTA << "=== SISTEMA NEXUS: LOGÍSTICA UNIVERSAL (TEMPLATES) ===" << RESET << std::endl;

    // 1. Usando a caixa para um tipo primitivo (int)
    std::cout << YELLOW << "\n--- Caso 1: Transportando Pesos (int) ---" << RESET << std::endl;
    CaixaDeTransporte<int> caixaPeso("LOG-INT-001");
    int pesoReal = 450;
    caixaPeso.guardar(&pesoReal);
    caixaPeso.mostrarConteudo();
    
    int* p = caixaPeso.retirar();
    if (p) std::cout << "Peso recuperado: " << *p << "kg" << std::endl;

    // 2. Usando a mesma classe para um tipo complexo (Drone)
    std::cout << CYAN << "\n--- Caso 2: Transportando Drones (Classe Customizada) ---" << RESET << std::endl;
    CaixaDeTransporte<Drone> caixaDrone("LOG-DRN-999");
    Drone* meuDrone = new Drone("Interceptor-X");
    
    caixaDrone.guardar(meuDrone);
    caixaDrone.mostrarConteudo();
    
    Drone* d = caixaDrone.retirar();
    if (d) std::cout << "Drone recuperado: " << d->getModelo() << std::endl;

    delete meuDrone; // Limpeza da Heap

    std::cout << CYAN << "\n====================================================" << RESET << std::endl;
    std::cout << GREEN << "RESUMO TEÓRICO:" << RESET << std::endl;
    std::cout << "1. Templates permitem criar código genérico independente de tipo." << std::endl;
    std::cout << "2. O compilador gera código específico para cada 'T' usado (Instanciação)." << std::endl;
    std::cout << "3. 'Type Safety': O compilador impede que você guarde um Drone em uma caixa de int." << std::endl;
    std::cout << "4. 'Zero Overhead': Não há custo de performance em tempo de execução." << std::endl;
    std::cout << CYAN << "====================================================" << RESET << std::endl;

    return 0;
}

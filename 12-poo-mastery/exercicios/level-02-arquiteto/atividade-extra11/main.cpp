/**
 * @file main.cpp
 * @brief Implementação de Const-Correctness (O Observador Imutável)
 * @author Gemini CLI
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapa de Memória
 * - Stack: Objeto 'meuDrone' alocado na stack.
 * - Heap: Atributos dinâmicos de std::string.
 */

#include <iostream>
#include "Drone.h"

// Cores ANSI
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

/**
 * @brief Função externa que recebe uma referência constante.
 * Isso garante que o objeto não será modificado dentro da função.
 */
void analisarDrone(const Drone& d) {
    std::cout << YELLOW << "[ANALISTA] Analisando drone: " << d.getModelo() << RESET << std::endl;
    d.verStatus(); // Só funciona porque verStatus() é const
    // d.setBateria(100); // ERRO DE COMPILAÇÃO se descomentado
}

int main() {
    std::cout << BOLD << "=== ATIVIDADE 11: CONST-CORRECTNESS ===" << RESET << std::endl;

    Drone meuDrone("SkyWatcher-X", 75);

    // Uso normal
    meuDrone.verStatus();
    
    // Passagem por referência constante
    analisarDrone(meuDrone);

    std::cout << std::endl << GREEN << "Segurança de memória e imutabilidade verificadas." << RESET << std::endl;

    return 0;
}

/**
 * @section ResumoTeórico
 * Const-correctness é a prática de usar a palavra-chave 'const' para evitar modificações acidentais.
 * Métodos 'const' garantem que o 'this' seja tratado como 'const Drone* const', impedindo
 * alterações em membros de dados (exceto os marcados como 'mutable').
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

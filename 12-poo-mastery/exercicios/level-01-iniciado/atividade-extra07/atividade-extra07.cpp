#define ANSI_RESET "\033[0m"
/**
 * @file atividade-extra07.cpp
 * @brief Implementação/Componente atividade-extra07.cpp
 * @author Cristiano
 * @date 2026
 */
#include <iostream>
#include <string>

class Drone {
public:
    std::string modelo;
    Drone(std::string m) : modelo(m) { std::cout << "Drone " << m << " criado na Heap." << std::endl; }
    ~Drone() { std::cout << "Drone " << modelo << " destruído." << std::endl; }
    void decolar() { std::cout << "Drone " << modelo << " voando..." << std::endl; }
};

int main() {
    Drone* meuDrone = new Drone("Cloud-Runner");
    meuDrone->decolar();
    delete meuDrone;
    // meuDrone->decolar(); // Perigoso!
    return 0;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

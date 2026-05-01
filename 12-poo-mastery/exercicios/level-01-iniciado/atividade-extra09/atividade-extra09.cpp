#define ANSI_RESET "\033[0m"
/**
 * @file atividade-extra09.cpp
 * @brief Implementação/Componente atividade-extra09.cpp
 * @author Cristiano
 * @date 2026
 */
#include <iostream>
#include <vector>
#include <string>

class Drone {
public:
    std::string modelo;
    Drone(std::string m) : modelo(m) {}
    void verStatus() { std::cout << "Status Drone: " << modelo << std::endl; }
};

int main() {
    std::vector<Drone*> hangar;
    hangar.push_back(new Drone("Alpha"));
    hangar.push_back(new Drone("Beta"));
    hangar.push_back(new Drone("Gamma"));

    for(Drone* d : hangar) {
        d->verStatus();
    }

    // Limpeza
    for(Drone* d : hangar) {
        delete d;
    }
    hangar.clear();

    return 0;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

/**
 * @file atividade-extra03.cpp
 * @brief Implementação de Encapsulamento (Blindagem de Sistema)
 * @author Gemini CLI
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapa de Memória
 * - Stack: 'droneA' alocado na stack. Atributos privados protegidos no corpo do objeto.
 */

#include <iostream>
#include <string>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

class Drone {
private:
    std::string modelo;
    int bateria;

public:
    Drone(std::string m, int b) {
        setModelo(m);
        setBateria(b);
    }

    // Getters e Setters
    void setModelo(std::string m) { this->modelo = m; }
    std::string getModelo() { return this->modelo; }

    void setBateria(int b) {
        if (b < 0) {
            std::cout << RED << "[AVISO] Tentativa de carga negativa. Ajustando para 0%." << RESET << std::endl;
            this->bateria = 0;
        } else if (b > 100) {
            std::cout << RED << "[AVISO] Tentativa de sobrecarga. Ajustando para 100%." << RESET << std::endl;
            this->bateria = 100;
        } else {
            this->bateria = b;
        }
    }

    int getBateria() { return this->bateria; }

    void verStatus() {
        std::cout << "Drone: " << modelo << " | Bateria: " << bateria << "%" << std::endl;
    }
};

int main() {
    std::cout << BOLD << YELLOW << "=== SKYCARGO NEXUS - PROTOCOLO DE BLINDAGEM ===" << RESET << std::endl << std::endl;

    Drone droneA("Alpha-707", 80);
    
    // droneA.bateria = 150; // ERRO DE COMPILAÇÃO: 'bateria' is private
    
    std::cout << "[SISTEMA] Tentando configurar bateria inválida (150%)..." << std::endl;
    droneA.setBateria(150);
    droneA.verStatus();

    std::cout << std::endl << "[SISTEMA] Tentando configurar bateria inválida (-50%)..." << std::endl;
    droneA.setBateria(-50);
    droneA.verStatus();

    std::cout << std::endl << "[SISTEMA] Acesso via Getters:" << std::endl;
    std::cout << "Modelo: " << droneA.getModelo() << std::endl;
    std::cout << "Bateria: " << droneA.getBateria() << "%" << std::endl;

    return 0;
}

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

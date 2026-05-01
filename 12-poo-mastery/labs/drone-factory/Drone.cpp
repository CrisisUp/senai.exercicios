#define ANSI_RESET "\033[0m"
/**
 * @file Drone.cpp
 * @brief Implementação/Componente Drone.cpp
 * @author Cristiano
 * @date 2026
 */
#include "Drone.h"

int Drone::totalDrones = 0;

Drone::Drone(std::string modelo, int bateria) {
    this->modelo = modelo;
    this->setBateria(bateria);
    this->idSeguranca = 700 + totalDrones;
    
    // Alocação Inteligente na Heap (Ativ 15)
    this->gps = std::make_unique<Sensor>();
    
    totalDrones++;
    std::cout << CYAN << "[FÁBRICA] " << modelo << " montado com Smart Pointer." << RESET << std::endl;
}

// Implementação de Deep Copy (Atividade 12)
Drone::Drone(const Drone& outro) {
    this->modelo = outro.modelo + " (Clone)";
    this->bateria = outro.bateria;
    this->idSeguranca = 800 + totalDrones;
    
    // Criamos um NOVO sensor exclusivo para o clone
    this->gps = std::make_unique<Sensor>();
    
    totalDrones++;
    std::cout << YELLOW << "[CLONAGEM] " << this->modelo << " gerado via Deep Copy." << RESET << std::endl;
}

Drone::~Drone() {
    totalDrones--;
    // O unique_ptr 'gps' será destruído automaticamente aqui!
    std::cout << RED << "[HANGAR] " << modelo << " desativado. Memória limpa automaticamente." << RESET << std::endl;
}

void Drone::setBateria(int b) {
    // Lógica de Exceção (Atividade 17)
    if (b < 0 || b > 100) {
        throw BateriaInvalidaException(b);
    }
    this->bateria = b;
}

int Drone::getBateria() const { return bateria; }
std::string Drone::getModelo() const { return modelo; }

void Drone::verStatus() const {
    std::cout << BOLD << CYAN << ">>> STATUS: " << modelo << RESET << std::endl;
    std::cout << " | Energia: " << bateria << "%" << std::endl;
    // Acesso ao componente inteligente
    std::cout << " | Temp. Sensor: " << gps->obterTemperatura() << "C" << std::endl;
}

void Drone::decolar() {
    if (bateria < 10) throw BateriaInvalidaException(bateria);
    std::cout << GREEN << "[SISTEMA] Decolagem padrão executada." << RESET << std::endl;
}

int Drone::getTotalDrones() {
    return totalDrones;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

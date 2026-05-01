#include "Drone.h"
#include "Navegador.h"
#include "Logger.h"
#include <iostream>

/**
 * @file main.cpp
 * @brief Implementação da Atividade 25 - SRP (Single Responsibility Principle).
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 * 
 * @section MemoryMap
 * - Drone (Stack): Objeto de estado.
 * - Navegador (Stack): Objeto de serviço de rota.
 * - Logger (Static): Métodos de serviço de saída.
 */

// --- Implementação Drone ---
Drone::Drone(std::string name) : id(name), bateria(100) {}
std::string Drone::getId() const { return id; }
int Drone::getBateria() const { return bateria; }
void Drone::consumirBateria(int quantidade) { bateria -= quantidade; }

// --- Implementação Navegador ---
std::string Navegador::calcularRota(Coordenada destino) {
    return "Rota calculada para [X:" + std::to_string(destino.x) + " Y:" + std::to_string(destino.y) + "]";
}

// --- Implementação Logger (Cores ANSI) ---
void Logger::logInfo(std::string msg) { std::cout << "\033[36m[INFO] " << msg << "\033[0m" << std::endl; }
void Logger::logSucesso(std::string msg) { std::cout << "\033[32m[OK] " << msg << "\033[0m" << std::endl; }
void Logger::logAlerta(std::string msg) { std::cout << "\033[33m[ALERTA] " << msg << "\033[0m" << std::endl; }

int main() {
    Logger::logInfo("Iniciando Sistema Nexus SRP...");

    // 1. Criando o Drone (Apenas Estado)
    Drone meuDrone("Falcon-SRP");

    // 2. Usando o Navegador (Apenas Lógica de Rota)
    Navegador nav;
    std::string rota = nav.calcularRota({150.0, 300.5, 50.0});

    // 3. Usando o Logger (Apenas Saída)
    Logger::logSucesso("Drone " + meuDrone.getId() + " pronto.");
    Logger::logInfo(rota);

    meuDrone.consumirBateria(10);
    Logger::logAlerta("Bateria atual: " + std::to_string(meuDrone.getBateria()) + "%");

    Logger::logSucesso("Missão finalizada com responsabilidades segregadas.");

    /*
     * RESUMO TEÓRICO:
     * O SRP (Single Responsibility Principle) afirma que uma classe deve ter um, e apenas um, 
     * motivo para mudar. 
     * - Se mudarmos o hardware da bateria, mudamos apenas a classe Drone.
     * - Se mudarmos o algoritmo de GPS, mudamos apenas a Navegador.
     * - Se mudarmos de Console para Arquivo de Log, mudamos apenas a Logger.
     */

    return 0;
}

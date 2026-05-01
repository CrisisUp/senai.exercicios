#define ANSI_RESET "\033[0m"
/**
 * @file atividade-extra08.cpp
 * @brief Implementação/Componente atividade-extra08.cpp
 * @author Cristiano
 * @date 2026
 */
#include <iostream>
#include <string>

class Sensor {
public:
    float obterTemperatura() { return 24.5f; }
};

class Drone {
private:
    std::string modelo;
    Sensor sensorTermico; // Composição: Drone TEM UM Sensor

public:
    Drone(std::string m) : modelo(m) {}
    void checarSistemas() {
        std::cout << "[DIAGNÓSTICO] " << modelo << " - Temp Sensor: " << sensorTermico.obterTemperatura() << "C" << std::endl;
    }
};

int main() {
    Drone d("Sensor-Bot");
    d.checarSistemas();
    return 0;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

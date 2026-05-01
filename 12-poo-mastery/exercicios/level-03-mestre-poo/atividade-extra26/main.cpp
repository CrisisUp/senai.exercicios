#define ANSI_RESET "\033[0m"
#include "Drone.h"
#include "Sensor.h"
#include <iostream>

/**
 * @file main.cpp
 * @brief Implementação da Atividade 26 - OCP (Open/Closed Principle).
 * @author Gemini Elite Engineer
 * @date 2026-04-30
 */

// 1. Sensores Originais (O que já tínhamos)
class SensorLaser : public Sensor {
public:
    std::string lerDados() override { return "Distância: 15.4m | Precisão: 99.9%"; }
    std::string getNome() const override { return "Laser LiDAR"; }
};

class SensorCamera : public Sensor {
public:
    std::string lerDados() override { return "Objeto Detectado: Drone Hostil | Confiança: 85%"; }
    std::string getNome() const override { return "Câmera Térmica"; }
};

// 2. NOVA EXTENSÃO (Adicionada sem tocar na classe Drone!)
class SensorUltrassom : public Sensor {
public:
    std::string lerDados() override { return "Obstáculo próximo detectado a 2m."; }
    std::string getNome() const override { return "Ultrassom Proximidade"; }
};

int main() {
    std::cout << "--- SkyCargo Nexus: Sistema de Sensores OCP ---" << std::endl;

    // Criamos o Drone (Código que não será alterado)
    Drone meuDrone("Falcon-OCP");

    // Acoplando sensores originais
    meuDrone.adicionarSensor(std::make_shared<SensorLaser>());
    meuDrone.adicionarSensor(std::make_shared<SensorCamera>());

    // Acoplando a NOVA extensão (Prova do OCP)
    // Note que não mudamos nada na classe Drone para aceitar o Ultrassom!
    meuDrone.adicionarSensor(std::make_shared<SensorUltrassom>());

    // Executando a lógica genérica
    meuDrone.realizarVarredura();

    /*
     * RESUMO TEÓRICO:
     * O OCP (Open/Closed Principle) diz que entidades devem ser abertas para extensão
     * mas fechadas para modificação.
     * 
     * Aqui, o 'Drone' está fechado (não mudamos seu código), mas o sistema está 
     * aberto para novos sensores. Se amanhã criarmos um 'SensorQuimico', basta 
     * herdar de 'Sensor' e o Drone o aceitará automaticamente via polimorfismo.
     */

    return 0;
}

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

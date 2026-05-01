/**
 * @file Drone.h
 * @author Cristiano
 * @date 2026
 */
#ifndef DRONE_H
#define DRONE_H

#include "Sensor.h"
#include <vector>
#include <memory>
#include <iostream>

/**
 * @class Drone
 * @brief Classe fechada para modificação, mas aberta para expansão via Sensores (OCP).
 */
class Drone {
private:
    std::string modelo;
    std::vector<std::shared_ptr<Sensor>> sensores;

public:
    Drone(std::string mod) : modelo(mod) {}

    // Adiciona qualquer classe que herde de Sensor sem precisar mudar o Drone
    void adicionarSensor(std::shared_ptr<Sensor> s) {
        sensores.push_back(s);
        std::cout << "[Drone] Sensor '" << s->getNome() << "' acoplado com sucesso." << std::endl;
    }

    void realizarVarredura() {
        std::cout << "\n--- Iniciando Varredura de Sistemas: " << modelo << " ---" << std::endl;
        for (const auto& s : sensores) {
            std::cout << " > [" << s->getNome() << "]: " << s->lerDados() << std::endl;
        }
        std::cout << "--- Varredura Finalizada ---\n" << std::endl;
    }
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

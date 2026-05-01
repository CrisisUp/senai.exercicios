/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file Drone.h
 * @brief Definição da classe Drone dentro do namespace Nexus.
 */

#ifndef DRONE_H
#define DRONE_H

#include "Sensor.h"
#include <vector>

namespace Nexus {
    /**
     * @brief Classe que representa um drone de carga.
     */
    class Drone {
    private:
        std::string id;
        std::vector<Sensor> sensores;

    public:
        Drone(std::string id);
        void adicionarSensor(const Sensor& s);
        void status() const;
    };
}

#endif // DRONE_H

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

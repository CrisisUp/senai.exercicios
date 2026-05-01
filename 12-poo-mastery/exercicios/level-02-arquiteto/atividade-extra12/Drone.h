/**
 * @file Drone.h
 * @brief Implementação/Componente Drone.h
 * @author Cristiano
 * @date 2026
 */
#ifndef DRONE_H
#define DRONE_H

#include "Sensor.h"
#include <string>

class Drone {
private:
    std::string modelo;
    Sensor* gps; // Alocação dinâmica para demonstrar Deep Copy

public:
    Drone(std::string m, std::string sensorTipo);
    ~Drone(); // Destrutor (Rule of Three)
    Drone(const Drone& outro); // Construtor de Cópia (Deep Copy)
    Drone& operator=(const Drone& outro); // Operador de Atribuição (Deep Copy)

    void setSensorTipo(std::string t);
    void verStatus() const;
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

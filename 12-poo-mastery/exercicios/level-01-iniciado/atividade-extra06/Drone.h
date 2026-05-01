/**
 * @file Drone.h
 * @brief Implementação/Componente Drone.h
 * @author Cristiano
 * @date 2026
 */
#ifndef DRONE_H
#define DRONE_H

#include <iostream>
#include <string>

class Drone {
private:
    std::string modelo;
    int bateria;

public:
    Drone(std::string m, int b);
    void decolar();
    void verStatus();
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

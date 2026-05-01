/**
 * @file Drone.h
 * @author Cristiano
 * @date 2026
 */
#ifndef DRONE_H
#define DRONE_H

#include <string>

/**
 * @class Drone
 * @brief Gerencia apenas o estado e atributos básicos do drone (SRP: Estado).
 */
class Drone {
private:
    std::string id;
    int bateria;

public:
    Drone(std::string name);
    std::string getId() const;
    int getBateria() const;
    void consumirBateria(int quantidade);
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file Drone.h
 * @brief Definição da classe Drone para teste de templates.
 */

#ifndef DRONE_H
#define DRONE_H

#include <string>

class Drone {
private:
    std::string modelo;

public:
    Drone(std::string m);
    std::string getModelo() const;
};

#endif // DRONE_H

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

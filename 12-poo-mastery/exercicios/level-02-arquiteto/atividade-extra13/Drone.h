/**
 * @file Drone.h
 * @brief Implementação/Componente Drone.h
 * @author Cristiano
 * @date 2026
 */
#ifndef DRONE_H
#define DRONE_H

#include <string>
#include <iostream>

class Drone {
private:
    std::string modelo;
    int bateria;

public:
    Drone(std::string m, int b);

    // Sobrecarga de Operadores (Membros)
    Drone operator+(const Drone& outro) const;
    bool operator==(const Drone& outro) const;

    // Sobrecarga de Operador de Saída (Friend)
    friend std::ostream& operator<<(std::ostream& os, const Drone& d);

    std::string getModelo() const { return modelo; }
    int getBateria() const { return bateria; }
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

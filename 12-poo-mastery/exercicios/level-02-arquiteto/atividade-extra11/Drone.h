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
 * @brief Representa um drone com suporte a const-correctness.
 */
class Drone {
private:
    std::string modelo;
    int bateria;

public:
    Drone(std::string m, int b);

    // Getters marcados como const (Obrigatório Nível 11)
    std::string getModelo() const;
    int getBateria() const;

    // Métodos de consulta marcados como const
    void verStatus() const;

    // Métodos que alteram o estado (Não const)
    void setBateria(int b);
    void decolar();
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

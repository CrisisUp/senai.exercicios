/**
 * @file Drone.h
 * @brief Implementação/Componente Drone.h
 * @author Cristiano
 * @date 2026
 */
#ifndef DRONE_H
#define DRONE_H

#include "DispositivoNexus.h"
#include <string>

class Drone : public DispositivoNexus {
private:
    std::string modelo;

public:
    Drone(std::string m);
    
    // Implementação do contrato
    void executarProtocolo() override;
    std::string getIdentificacao() const override;
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

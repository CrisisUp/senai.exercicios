/**
 * @file IDrone.h
 * @author Cristiano
 * @date 2026
 */
#ifndef IDRONE_H
#define IDRONE_H

#include <string>

/**
 * @class IDrone
 * @brief Abstração para drones (DIP: Módulo de Baixo Nível depende desta interface).
 */
class IDrone {
public:
    virtual ~IDrone() = default;
    virtual void executarMissao() = 0;
    virtual std::string getModelo() const = 0;
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

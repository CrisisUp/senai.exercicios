/**
 * @file VeiculoAutonomo.h
 * @author Cristiano
 * @date 2026
 */
#ifndef VEICULO_AUTONOMO_H
#define VEICULO_AUTONOMO_H

#include <string>
#include <iostream>

/**
 * @class VeiculoAutonomo
 * @brief Base comum para todos os ativos da Nexus (LSP: Base Genérica Correta).
 */
class VeiculoAutonomo {
protected:
    std::string id;
public:
    VeiculoAutonomo(std::string name) : id(name) {}
    virtual ~VeiculoAutonomo() = default;
    
    std::string getId() const { return id; }
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

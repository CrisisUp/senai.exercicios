/**
 * @file Interfaces.h
 * @author Cristiano
 * @date 2026
 */
#ifndef INTERFACES_LSP_H
#define INTERFACES_LSP_H

/**
 * @class VeiculoVoador
 * @brief Contrato para veículos que possuem capacidade de voo.
 */
class VeiculoVoador {
public:
    virtual ~VeiculoVoador() = default;
    virtual void decolar() = 0;
};

/**
 * @class VeiculoTerrestre
 * @brief Contrato para veículos que operam em solo.
 */
class VeiculoTerrestre {
public:
    virtual ~VeiculoTerrestre() = default;
    virtual void acelerar() = 0;
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

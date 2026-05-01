/**
 * @file DispositivoNexus.h
 * @author Cristiano
 * @date 2026
 */
#ifndef DISPOSITIVO_NEXUS_H
#define DISPOSITIVO_NEXUS_H

#include <string>

/**
 * @class DispositivoNexus
 * @brief Classe Abstrata (Interface) que define o contrato sagrado.
 */
class DispositivoNexus {
public:
    virtual ~DispositivoNexus() {}

    // Função Virtual Pura (Obrigatório Nível 14)
    virtual void executarProtocolo() = 0;

    virtual std::string getIdentificacao() const = 0;
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

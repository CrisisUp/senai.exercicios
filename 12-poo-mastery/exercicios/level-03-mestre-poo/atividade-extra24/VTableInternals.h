/**
 * @file VTableInternals.h
 * @brief Definição de classes para demonstração do mecanismo de VTable e VPTR.
 * @author Gemini CLI
 * @date 30/04/2026
 */

#ifndef VTABLE_INTERNALS_H
#define VTABLE_INTERNALS_H

#include <iostream>

/**
 * @class Vazia
 * @brief Classe sem métodos virtuais para demonstrar o tamanho mínimo.
 */
class Vazia {
public:
    void metodoComum() {
        std::cout << "Método comum da classe Vazia." << std::endl;
    }
};

/**
 * @class ComVirtual
 * @brief Classe com método virtual para demonstrar a inclusão do VPTR.
 */
class ComVirtual {
public:
    virtual void metodoVirtual() {
        std::cout << "Método virtual da classe ComVirtual." << std::endl;
    }

    virtual ~ComVirtual() {
        std::cout << "Destrutor virtual da classe ComVirtual." << std::endl;
    }
};

/**
 * @class FilhaVirtual
 * @brief Classe herdeira para demonstrar a importância do destrutor virtual.
 */
class FilhaVirtual : public ComVirtual {
public:
    void metodoVirtual() override {
        std::cout << "Método sobrescrito na FilhaVirtual." << std::endl;
    }

    ~FilhaVirtual() {
        std::cout << "Destrutor da FilhaVirtual chamado!" << std::endl;
    }
};

#endif // VTABLE_INTERNALS_H

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

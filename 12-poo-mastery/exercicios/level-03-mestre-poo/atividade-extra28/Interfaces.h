/**
 * @file Interfaces.h
 * @author Cristiano
 * @date 2026
 */
#ifndef INTERFACES_ISP_H
#define INTERFACES_ISP_H

#include <iostream>
#include <string>

/**
 * @class IVoador
 * @brief Interface para capacidades de voo (ISP: Contrato Específico).
 */
class IVoador {
public:
    virtual ~IVoador() = default;
    virtual void decolar() = 0;
    virtual void pousar() = 0;
};

/**
 * @class ICamera
 * @brief Interface para capacidades de captura de imagem.
 */
class ICamera {
public:
    virtual ~ICamera() = default;
    virtual void tirarFoto() = 0;
    virtual void gravarVideo() = 0;
};

/**
 * @class ICargueiro
 * @brief Interface para capacidades de transporte de carga.
 */
class ICargueiro {
public:
    virtual ~ICargueiro() = default;
    virtual void carregarCarga(float peso) = 0;
    virtual void soltarCarga() = 0;
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

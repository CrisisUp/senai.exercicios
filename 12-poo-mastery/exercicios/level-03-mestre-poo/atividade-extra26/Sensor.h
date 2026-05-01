/**
 * @file Sensor.h
 * @author Cristiano
 * @date 2026
 */
#ifndef SENSOR_H
#define SENSOR_H

#include <string>

/**
 * @class Sensor
 * @brief Interface abstrata para todos os sensores (OCP: Contrato de Extensão).
 */
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual std::string lerDados() = 0;
    virtual std::string getNome() const = 0;
};

#endif

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

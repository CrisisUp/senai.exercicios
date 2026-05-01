/**
 * @file Sensor.h
 * @brief Definição da classe Sensor dentro do namespace Nexus.
 * @author Gemini CLI
 * @date 2026-04-22
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <string>

namespace Nexus {
    /**
     * @brief Classe que representa um sensor de telemetria.
     */
    class Sensor {
    private:
        std::string tipo;
        float valor;

    public:
        Sensor(std::string t, float v);
        void lerDados();
        std::string getTipo() const;
        float getValor() const;
    };
}

namespace RadarCorp {
    /**
     * @brief Classe de conflito proposital para demonstrar namespaces.
     */
    class Sensor {
    public:
        void detectar() { /* Mock */ }
    };
}

#endif // SENSOR_H

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

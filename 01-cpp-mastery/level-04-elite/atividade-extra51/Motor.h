#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file Motor.h
 * @brief Interface para o Módulo de Motores Industriais (Composição).
 * 
 * Atividade Extra 51 - Arquitetura Modular (Nível 11+).
 * Demonstra o relacionamento "Has-A" entre classes.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Composition Layout)
 * - Objeto MotorIndustrial: Alocado na STACK da main.
 * - Sensor Interno: Alocado NA STACK, dentro do corpo do objeto Motor.
 * - Agregação de Memória: O tamanho total do Motor na RAM é a soma (sizeof(Motor) + sizeof(Sensor)).
 * - Localidade de Referência: A composição garante que o sensor esteja fisicamente próximo 
 *   do motor na RAM, otimizando o cache da CPU.
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <string>
#include "../atividade-extra50/Monitoramento.h" // Importação modular do sensor

namespace IoT {

    /**
     * @class MotorIndustrial
     * @brief Representa um equipamento crítico composto por múltiplos subsistemas.
     */
    class MotorIndustrial {
    private:
        std::string modelo;
        bool ligado;
        SensorPressao sensorInterno; // COMPOSIÇÃO: O Motor TEM UM Sensor

    public:
        /**
         * @brief Construtor: Inicializa motor e compõe o sensor.
         */
        MotorIndustrial(const std::string& _modelo, const std::string& _idSensor);

        /**
         * @brief Ativa o sistema elétrico do motor.
         */
        void ligar();

        /**
         * @brief Desativa o sistema por segurança ou comando.
         */
        void desligar();

        /**
         * @brief Processa um ciclo de operação baseado na telemetria.
         * @return false se o motor precisar ser abortado por segurança.
         */
        bool atualizarOperacao(double pressao);

        // Getters de Estado (FANTASMA DO CPU)
        bool estaLigado() const { return ligado; }
        std::string statusMotor() const;
    };

} // namespace IoT

#endif // MOTOR_H

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

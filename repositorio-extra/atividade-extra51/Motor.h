/**
 * @file Motor.h
 * @brief Definição modular de Motores Industriais usando Composição.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <string>
#include "../atividade-extra50/Monitoramento.h" // Reutilização modular

namespace IoT {

    /**
     * @brief Classe MotorIndustrial (Composição: O Motor TEM UM Sensor).
     */
    class MotorIndustrial {
    private:
        std::string modelo;
        bool ligado;
        
        // COMPOSIÇÃO: O objeto SensorPressao agora é um ATRIBUTO do Motor.
        SensorPressao sensorPressao;

    public:
        /**
         * @brief Construtor do motor que também inicializa o sensor interno.
         */
        MotorIndustrial(std::string mod, std::string idSensor);

        void ligar();
        void desligar();
        
        /**
         * @brief Atualiza a pressão do sensor interno do motor.
         */
        bool atualizarOperacao(double pressaoLida);

        /**
         * @brief Retorna o estado de saúde do motor.
         */
        std::string statusMotor() const;
        
        bool estaLigado() const { return ligado; }
    };
}

#endif // MOTOR_H

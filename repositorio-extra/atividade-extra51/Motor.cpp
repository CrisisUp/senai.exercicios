/**
 * @file Motor.cpp
 * @brief Implementação modular do Motor Industrial usando composição.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include "Motor.h"
#include <iostream>

namespace IoT {

    /**
     * @brief O construtor do Motor deve inicializar seus objetos internos
     * através da Lista de Inicialização (Member Initializer List).
     */
    MotorIndustrial::MotorIndustrial(std::string mod, std::string idSensor) 
        : modelo(mod), ligado(false), sensorPressao(idSensor) {}

    void MotorIndustrial::ligar() {
        ligado = true;
    }

    void MotorIndustrial::desligar() {
        ligado = false;
    }

    bool MotorIndustrial::atualizarOperacao(double pressaoLida) {
        if (!ligado) return false;

        // Delegando a tarefa de validação para o sensor interno (COMPOSTO)
        bool sucesso = sensorPressao.registrarLeitura(pressaoLida);

        if (!sucesso) {
            // Em caso de perigo detectado pelo sensor, o Motor DESLIGA automaticamente.
            desligar();
            return false;
        }
        return true;
    }

    std::string MotorIndustrial::statusMotor() const {
        std::string status = "MOTOR: " + modelo;
        status += (ligado ? " [LIGADO]" : " [DESLIGADO - EMERGENCIA]");
        status += " | PRESSÃO: " + std::to_string(sensorPressao.getValor()) + " psi";
        return status;
    }
}

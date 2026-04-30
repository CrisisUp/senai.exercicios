/**
 * @file Motor.cpp
 * @brief Implementação da Lógica do Motor Industrial (Delegacia de Sensores).
 * 
 * Demonstra como a classe mestre delega responsabilidades para seus componentes.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "Motor.h"
#include <sstream>

namespace IoT {

    /**
     * @brief Uso de Member Initializer List para instanciar o sensor interno.
     */
    MotorIndustrial::MotorIndustrial(const std::string& _modelo, const std::string& _idSensor)
        : modelo(_modelo), ligado(false), sensorInterno(_idSensor) {}

    void MotorIndustrial::ligar() {
        ligado = true;
    }

    void MotorIndustrial::desligar() {
        ligado = false;
    }

    bool MotorIndustrial::atualizarOperacao(double pressao) {
        if (!ligado) return false;

        // DELEGAÇÃO: O motor não valida pressão, ele pergunta ao seu sensor.
        if (sensorInterno.registrarLeitura(pressao)) {
            return true;
        } else {
            // Se o sensor falhar, o motor desliga imediatamente (Autoproteção)
            desligar();
            return false;
        }
    }

    std::string MotorIndustrial::statusMotor() const {
        std::stringstream ss;
        ss << "[MOTOR: " << modelo << "] -> Status: " 
           << (ligado ? "EM OPERAÇÃO" : "INATIVO/SEGURANÇA")
           << " | Última Pressão: " << sensorInterno.getValor() << " psi.";
        return ss.str();
    }

} // namespace IoT
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

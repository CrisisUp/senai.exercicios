/**
 * @file Monitoramento.cpp
 * @brief Implementação modular da lógica de sensores IoT.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include "Monitoramento.h"
#include <iostream>

/**
 * Ao implementar dentro do namespace IoT, as definições da classe 
 * são reconhecidas.
 */
namespace IoT {

    SensorPressao::SensorPressao(std::string id) : idSensor(id), valorAtual(0.0) {}

    bool SensorPressao::registrarLeitura(double novoValor) {
        // Chamada de método privado interno
        if (valorEhSeguro(novoValor)) {
            valorAtual = novoValor;
            return true;
        }
        return false;
    }

    bool SensorPressao::valorEhSeguro(double valor) {
        // Lógica de segurança de fábrica (0-100 psi)
        return (valor >= 0.0 && valor <= 100.0);
    }
}

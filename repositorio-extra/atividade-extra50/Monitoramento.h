/**
 * @file Monitoramento.h
 * @brief Definição modular de sensores industriais usando namespaces.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef MONITORAMENTO_H
#define MONITORAMENTO_H

#include <string>

/**
 * @brief Namespace para organizar todas as funcionalidades de IoT Industrial.
 * Isso evita colisões de nomes com outras partes do sistema.
 */
namespace IoT {

    /**
     * @brief Classe para representar um sensor de pressão industrial.
     */
    class SensorPressao {
    private:
        std::string idSensor;
        double valorAtual;

        /**
         * @brief Método Privado (Encapsulamento):
         * Verifica internamente se o valor é seguro (entre 0 e 100 psi).
         */
        bool valorEhSeguro(double valor);

    public:
        SensorPressao(std::string id);
        
        /**
         * @brief Registra uma nova leitura no sensor.
         * @return true se a leitura foi aceita, false se for perigosa.
         */
        bool registrarLeitura(double novoValor);
        
        double getValor() const { return valorAtual; }
        std::string getId() const { return idSensor; }
    };
}

#endif // MONITORAMENTO_H

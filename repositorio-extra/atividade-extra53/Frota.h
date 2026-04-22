/**
 * @file Frota.h
 * @brief Definição modular de Veículos e Caminhões usando Herança.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef FROTA_H
#define FROTA_H

#include <string>

namespace Logistica {

    /**
     * @brief Classe Base (Pai): Define o que TODO veículo possui.
     */
    class Veiculo {
    protected:
        // 'protected' permite que classes filhas acessem, mas protege do mundo externo.
        std::string placa;
        std::string marca;
        double odometro;

    public:
        Veiculo(std::string p, std::string m);
        
        void viajar(double km);
        
        std::string getInfo() const;
        double getOdometro() const { return odometro; }
    };

    /**
     * @brief Classe Derivada (Filho): Especialização de um Veículo.
     * RELAÇÃO: Caminhao É-UM Veiculo.
     */
    class Caminhao : public Veiculo {
    private:
        double capacidadeCarga; // Atributo específico do Caminhão
        double cargaAtual;

    public:
        Caminhao(std::string p, std::string m, double cap);

        /**
         * @brief Carrega o caminhão (Valida contra a capacidade).
         */
        bool carregar(double toneladas);

        /**
         * @brief Retorna as informações completas (Base + Especialização).
         */
        std::string getRelatorioCaminhao() const;
    };
}

#endif // FROTA_H

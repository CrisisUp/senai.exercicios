/**
 * @file Imovel.h
 * @brief Definição modular de Imóveis usando Herança e Polimorfismo.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef IMOVEL_H
#define IMOVEL_H

#include <string>

namespace Imobiliaria {

    /**
     * @brief Classe Base (Pai): Define os atributos genéricos de um imóvel.
     */
    class Imovel {
    protected:
        std::string endereco;
        double valorBase;

    public:
        Imovel(std::string end, double valor);
        
        // Destrutor Virtual: Essencial ao usar herança para evitar memory leaks.
        virtual ~Imovel() {}

        /**
         * @brief Método Virtual: Define um comportamento que as subclasses podem sobrescrever.
         * @return O valor total (neste caso, apenas o valor base).
         */
        virtual double calcularTotal() const;

        std::string getEndereco() const { return endereco; }
    };

    /**
     * @brief Classe Derivada (Filho): Especialização para Apartamentos.
     */
    class Apartamento : public Imovel {
    private:
        double condomínio;

    public:
        Apartamento(std::string end, double valor, double cond);

        /**
         * @brief Sobrescrita do Cálculo (Override):
         * Adiciona o valor do condomínio ao valor base do aluguel.
         */
        double calcularTotal() const override;
    };

    /**
     * @brief Classe Derivada (Filho): Especialização para Casas.
     */
    class Casa : public Imovel {
    private:
        double manutencaoJardim;

    public:
        Casa(std::string end, double valor, double jard);

        /**
         * @brief Sobrescrita do Cálculo (Override):
         * Adiciona a manutenção de jardim ao valor base.
         */
        double calcularTotal() const override;
    };
}

#endif // IMOVEL_H

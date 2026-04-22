/**
 * @file Pagamento.h
 * @brief Definição modular de Meios de Pagamento usando Classes Abstratas.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef PAGAMENTO_H
#define PAGAMENTO_H

#include <string>

namespace Financeiro {

    /**
     * @brief Classe Abstrata (Interface): Define o contrato para qualquer pagamento.
     * Uma classe é abstrata se contiver pelo menos um método virtual puro.
     */
    class MetodoPagamento {
    public:
        // Destrutor virtual para garantir a limpeza correta das classes filhas.
        virtual ~MetodoPagamento() {}

        /**
         * @brief Método Virtual Puro (= 0):
         * Força as classes filhas a fornecerem sua própria implementação.
         */
        virtual void processar(double valor) const = 0;

        /**
         * @brief Métodos comuns podem coexistir em classes abstratas.
         */
        void exibirRecibo(double valor, std::string tipo) const;
    };

    /**
     * @brief Implementação de Pagamento via Cartão de Crédito.
     */
    class CartaoCredito : public MetodoPagamento {
    private:
        std::string numeroCartao;

    public:
        CartaoCredito(std::string num);
        
        // OBRIGATÓRIO: Implementar o método herdado da classe abstrata.
        void processar(double valor) const override;
    };

    /**
     * @brief Implementação de Pagamento via Pix.
     */
    class Pix : public MetodoPagamento {
    private:
        std::string chavePix;

    public:
        Pix(std::string chave);

        // OBRIGATÓRIO: Implementar o método herdado da classe abstrata.
        void processar(double valor) const override;
    };
}

#endif // PAGAMENTO_H

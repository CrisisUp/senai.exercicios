/**
 * @file Pagamento.h
 * @brief Interface Abstrata para Motores de Pagamento.
 * 
 * Atividade Extra 55 - Arquitetura Modular (Nível 21+).
 * Define o contrato obrigatório para qualquer gateway de liquidação.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Abstract Layout)
 * - MetodoPagamento (ABC): Não ocupa espaço por si só. Define a V-TABLE.
 * - Classes Concretas (Pix/Cartão): Instanciadas na HEAP via make_unique.
 * - Gestão RAII: O ciclo de vida é gerido pelo unique_ptr, garantindo limpeza atômica.
 */

#ifndef PAGAMENTO_H
#define PAGAMENTO_H

#include <string>

namespace Financeiro {

    /**
     * @class MetodoPagamento
     * @brief Interface Abstrata (ABC - Abstract Base Class).
     */
    class MetodoPagamento {
    public:
        /**
         * @brief MÉTODO VIRTUAL PURO: Obriga a implementação nas subclasses.
         * @param valor Valor total da transação (convetido para centavos internamente).
         */
        virtual void processar(double valor) = 0;

        /** @brief Destrutor Virtual: VITAL para polimorfismo de interface. */
        virtual ~MetodoPagamento() {}
    };

    /**
     * @class CartaoCredito
     * @brief Especialização para transações via rede adquirente.
     */
    class CartaoCredito : public MetodoPagamento {
    private:
        std::string numeroCartao;
    public:
        CartaoCredito(const std::string& _num);
        void processar(double valor) override;
        ~CartaoCredito() override;
    };

    /**
     * @class Pix
     * @brief Especialização para liquidação via BACEN (Instantâneo).
     */
    class Pix : public MetodoPagamento {
    private:
        std::string chavePix;
    public:
        Pix(const std::string& _chave);
        void processar(double valor) override;
        ~Pix() override;
    };

} // namespace Financeiro

#endif // PAGAMENTO_H

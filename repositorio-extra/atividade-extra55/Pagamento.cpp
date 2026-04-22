/**
 * @file Pagamento.cpp
 * @brief Implementação das formas de pagamento modulares.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include "Pagamento.h"
#include <iostream>
#include <iomanip>

namespace Financeiro {

    // IMPLEMENTAÇÃO CLASSE BASE (ABSTRATA)
    void MetodoPagamento::exibirRecibo(double valor, std::string tipo) const {
        std::cout << "\033[32m[RECIBO]:\033[0m Pagamento de R$ " << std::fixed 
                  << std::setprecision(2) << valor << " realizado via: " << tipo << std::endl;
    }

    // IMPLEMENTAÇÃO CARTÃO DE CRÉDITO
    CartaoCredito::CartaoCredito(std::string num) : numeroCartao(num) {}

    void CartaoCredito::processar(double valor) const {
        std::cout << "Conectando com a operadora de cartões..." << std::endl;
        std::cout << "Autorizando transação no cartão: ****" << numeroCartao.substr(numeroCartao.length() - 4) << std::endl;
        exibirRecibo(valor, "Cartão de Crédito");
    }

    // IMPLEMENTAÇÃO PIX
    Pix::Pix(std::string chave) : chavePix(chave) {}

    void Pix::processar(double valor) const {
        std::cout << "Gerando QR Code Dinâmico para a chave: " << chavePix << std::endl;
        std::cout << "Aguardando confirmação do Banco Central..." << std::endl;
        exibirRecibo(valor, "Pix");
    }
}

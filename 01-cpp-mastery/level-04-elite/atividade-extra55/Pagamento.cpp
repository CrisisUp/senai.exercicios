/**
 * @file Pagamento.cpp
 * @brief Implementação dos Motores de Liquidação (ABC Pattern).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "Pagamento.h"
#include <iostream>
#include <iomanip>

namespace Financeiro {

    // --- CARTÃO DE CRÉDITO ---

    CartaoCredito::CartaoCredito(const std::string& _num) 
        : numeroCartao(_num) {}

    void CartaoCredito::processar(double valor) {
        // Guardião Financeiro: Operando em centavos internamente
        long long centavos = static_cast<long long>(valor * 100);
        
        std::cout << "[GATEWAY ADQUIRENTE]: Comunicando com rede Visa/Master..." << std::endl;
        std::cout << " >> Cartão: " << numeroCartao.substr(0, 4) << " XXXX XXXX " << numeroCartao.substr(12) << std::endl;
        std::cout << " >> Autorizado: R$ " << std::fixed << std::setprecision(2) << (centavos/100.0) << std::endl;
    }

    CartaoCredito::~CartaoCredito() {}

    // --- PIX ---

    Pix::Pix(const std::string& _chave) 
        : chavePix(_chave) {}

    void Pix::processar(double valor) {
        long long centavos = static_cast<long long>(valor * 100);

        std::cout << "[GATEWAY PIX]: Gerando Payload de Liquidação Instantânea..." << std::endl;
        std::cout << " >> Chave Destino: " << chavePix << std::endl;
        std::cout << " >> Valor Pendente: R$ " << (centavos/100.0) << std::endl;
        std::cout << " >> [SISTEMA]: QR-Code gerado. Aguardando confirmação do BACEN..." << std::endl;
        std::cout << " >> [SUCESSO]: Liquidação concluída via G-Pay." << std::endl;
    }

    Pix::~Pix() {}

} // namespace Financeiro
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

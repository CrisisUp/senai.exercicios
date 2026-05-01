/**
 * @file MetodoPagamento.h
 * @brief Gateway de Pagamentos: Classes Abstratas e Interfaces de Elite.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef METODO_PAGAMENTO_H
#define METODO_PAGAMENTO_H

#include <iostream>
#include <string>
#include <iomanip>

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
    inline void limparTela() { std::cout << "\033[2J\033[1;1H"; }
}

/**
 * @class MetodoPagamento
 * @brief Define o contrato obrigatório para qualquer gateway de pagamento.
 * Aplica o padrão 'Guardião Financeiro' para precisão de centavos.
 */
class MetodoPagamento {
protected:
    long long valorCentavos; // Integridade Bancária (Int64)

public:
    /**
     * @brief Construtor: Recebe valor e converte internamente para centavos.
     */
    MetodoPagamento(double v);

    /**
     * @brief MÉTODO VIRTUAL PURO: Torna a classe abstrata.
     * Obriga a implementação nas classes filhas.
     */
    virtual void processar() = 0; 

    /**
     * @brief Método Concreto: Implementação comum de comprovante.
     */
    void exibirRecibo() const;

    virtual ~MetodoPagamento(); // Destrutor virtual essencial
};

/**
 * @class PagamentoPix
 * @brief Especialização para transações instantâneas via BACEN.
 */
class PagamentoPix : public MetodoPagamento {
public:
    PagamentoPix(double v);
    void processar() override;
};

/**
 * @class PagamentoCartao
 * @brief Especialização para transações via Adquirentes (Visa/Master).
 */
class PagamentoCartao : public MetodoPagamento {
private:
    std::string numeroMascarado;

public:
    PagamentoCartao(double v, const std::string& n);
    void processar() override;
};

#endif // METODO_PAGAMENTO_H

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

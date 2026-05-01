/**
 * @file ProdutoIndustrial.h
 * @brief Definição da classe ProdutoIndustrial e gestão de estoque.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef PRODUTO_INDUSTRIAL_H
#define PRODUTO_INDUSTRIAL_H

#include <iostream>
#include <string>
#include <exception>
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
    void cabecalho();
}

// --- 2. GESTÃO DE EXCEÇÕES INDUSTRIAIS ---
class ErroEstoque : public std::exception {
    std::string msg;
public:
    ErroEstoque(std::string m);
    const char* what() const throw() override;
};

// --- 3. CLASSE MODERNIZADA (O GUARDIÃO FINANCEIRO) ---
class ProdutoIndustrial {
private:
    std::string nome;
    long long precoCentavos; // Integridade Bancária (Guardião Financeiro)
    int quantidade;

    // Membros Estáticos: Visão Global do Patrimônio (Data Segment)
    static long long valorGlobalCentavos;
    static int totalItens;

public:
    ProdutoIndustrial(const std::string& _nome, double _preco, int _qtd);

    void registrarSaida(int qtd);
    void exibirItem() const;

    const std::string& getNome() const;
    static double getValorGlobal();
    static int getTotalItens();
};

#endif // PRODUTO_INDUSTRIAL_H

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

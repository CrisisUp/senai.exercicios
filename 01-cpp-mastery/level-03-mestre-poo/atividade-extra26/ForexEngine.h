/**
 * @file ForexEngine.h
 * @brief Motor Genérico de Câmbio utilizando Templates para Finanças.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef FOREX_ENGINE_H
#define FOREX_ENGINE_H

#include <iostream>
#include <string>

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
    
    inline void cabecalho() {
        std::cout << CIANO << NEGRITO << "===============================================" << std::endl;
        std::cout << "      FOREX TEMPLATE ENGINE v2.0 (ELITE)       " << std::endl;
        std::cout << "       (Generic Financial Architecture)        " << std::endl;
        std::cout << "===============================================" << RESET << std::endl;
    }
}

// --- 2. MOTOR GENÉRICO DE CÂMBIO (TEMPLATES) ---

/**
 * @brief Template Universal para aplicação de taxas.
 * Usa Trailing Return Type para dedução precisa da operação.
 */
template <typename T, typename U>
auto aplicarTaxa(T valor, U taxa) -> decltype(valor * taxa) {
    return valor * taxa;
}

/**
 * @brief Template de Soma Genérica (Inter-moedas).
 */
template <typename T1, typename T2>
auto somarSaldos(T1 s1, T2 s2) -> decltype(s1 + s2) {
    return s1 + s2;
}

#endif // FOREX_ENGINE_H

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

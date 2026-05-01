/**
 * @file UnidadeDeCarga.h
 * @brief Definição da Class Template UnidadeDeCarga para Logística Global.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef UNIDADE_DE_CARGA_H
#define UNIDADE_DE_CARGA_H

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

    inline void cabecalho() {
        std::cout << VERDE << NEGRITO << "===============================================" << std::endl;
        std::cout << "      LOGÍSTICA GLOBAL: CONTAINER ENGINE v2.0  " << std::endl;
        std::cout << "       (Elite Class Template Instance)         " << std::endl;
        std::cout << "===============================================" << RESET << std::endl;
    }
}

// --- 2. DEFINIÇÃO DA CLASS TEMPLATE (CONTEINER UNIVERSAL) ---

/**
 * @class UnidadeDeCarga
 * @brief Abstração genérica para armazenamento e transporte de qualquer tipo de dado.
 * @tparam T Tipo do conteúdo transportado (Pode ser primitivo ou objeto complexo).
 */
template <typename T>
class UnidadeDeCarga {
private:
    std::string id;
    double pesoTotal;
    T conteudo; // Memória reservada dinamicamente pelo compilador conforme o tipo T

public:
    /**
     * @brief Construtor Universal.
     * @param _conteudo Passagem por Referência Constante (FANTASMA DO CPU).
     */
    UnidadeDeCarga(const std::string& _id, double _peso, const T& _conteudo) 
        : id(_id), pesoTotal(_peso), conteudo(_conteudo) {}

    /**
     * @brief Atualiza o conteúdo genérico com proteção contra cópias pesadas.
     */
    void atualizarConteudo(const T& novoConteudo) {
        conteudo = novoConteudo;
    }

    /**
     * @brief Gera manifesto técnico baseado no tipo T instanciado.
     */
    void exibirManifesto() const {
        std::cout << UI::CIANO << UI::NEGRITO << "-----------------------------------------------" << UI::RESET << std::endl;
        std::cout << UI::NEGRITO << "MANIFESTO DE CARGA [" << UI::CIANO << id << UI::RESET << UI::NEGRITO << "]" << UI::RESET << std::endl;
        std::cout << UI::RESET << "PESO BRUTO: " << UI::RESET << std::fixed << std::setprecision(2) << pesoTotal << " kg" << std::endl;
        std::cout << UI::RESET << "CONTEÚDO  : " << UI::RESET << UI::AMARELO << UI::NEGRITO << conteudo << UI::RESET << std::endl;
        std::cout << UI::CIANO << UI::NEGRITO << "-----------------------------------------------" << UI::RESET << std::endl;
    }
};

#endif // UNIDADE_DE_CARGA_H

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

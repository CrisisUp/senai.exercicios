/**
 * @file PacoteLogistico.h
 * @brief Declaração da classe PacoteLogistico e interface UI.
 * 
 * Parte da Atividade Extra 18 - Refatoração Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Elite Standard)
 * - Objeto PacienteMonitorado: Alocado na STACK (estático) durante o ciclo de vida da main.
 * - Atributos Primitivos (peso): Armazenados na STACK dentro do bloco do objeto (8 bytes).
 * - Atributos Dinâmicos (codigoRastreio, destino): Os objetos std::string ficam na STACK, 
 *   mas o conteúdo real (texto) é alocado na HEAP.
 */

#ifndef PACOTE_LOGISTICO_H
#define PACOTE_LOGISTICO_H

#include <string>
#include <iostream>

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERMELHO = "\033[31m";
    const std::string VERDE    = "\033[32m";
    const std::string AMARELO  = "\033[33m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string BRANCO   = "\033[37m";

    inline void limparTela() { std::cout << "\033[2J\033[1;1H"; }
}

// --- 2. CLASSE PACOTE LOGÍSTICO ---
/**
 * @class PacoteLogistico
 * @brief Representa um pacote no sistema de logística 4.0.
 * Demonstra sobrecarga de construtores e lista de inicialização.
 */
class PacoteLogistico {
private:
    std::string codigoRastreio;
    double peso;
    std::string destino;

public:
    /**
     * @brief Construtor Completo (Scanner)
     * @param cod Código de rastreio (const ref p/ performance)
     * @param p Peso inicial
     * @param dest Destino final (const ref p/ performance)
     */
    PacoteLogistico(const std::string& cod, double p, const std::string& dest);

    /**
     * @brief Construtor Parcial (Manual)
     * @param cod Código de rastreio (const ref p/ performance)
     */
    PacoteLogistico(const std::string& cod);

    // --- SETTERS (VALIDAÇÃO E ENCAPSULAMENTO) ---
    bool setPeso(double p);
    bool setDestino(const std::string& dest);

    // --- GETTERS (FANTASMA DO CPU - LEITURA OTIMIZADA) ---
    const std::string& getCodigoRastreio() const { return codigoRastreio; }
    double getPeso() const { return peso; }
    const std::string& getDestino() const { return destino; }

    // --- EXIBIÇÃO ---
    void exibirEtiqueta() const;
};

#endif // PACOTE_LOGISTICO_H

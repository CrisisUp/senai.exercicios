/**
 * @file PacoteLogistico.h
 * @brief Declaração da classe PacoteLogistico e interface UI.
 * 
 * Parte da Atividade Extra 18 - Refatoração Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef PACOTE_LOGISTICO_H
#define PACOTE_LOGISTICO_H

#include <string>
#include <iostream>

// --- 1. NAMESPACE DE INTERFACE ---
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string VERDE    = "\033[32m";
    const std::string AMARELO  = "\033[33m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
}

// --- 2. CLASSE PACOTE LOGÍSTICO ---
class PacoteLogistico {
private:
    std::string codigoRastreio;
    double peso;
    std::string destino;

public:
    /**
     * @brief Construtor Completo (Scanner)
     * @param cod Código de rastreio
     * @param p Peso inicial
     * @param dest Destino final
     */
    PacoteLogistico(std::string cod, double p, std::string dest);

    /**
     * @brief Construtor Parcial (Manual)
     * @param cod Código de rastreio
     */
    PacoteLogistico(std::string cod);

    // Setters
    void setPeso(double p);
    void setDestino(std::string dest);

    // Exibição
    void exibirEtiqueta() const;
};

#endif // PACOTE_LOGISTICO_H

/**
 * @file Imovel.cpp
 * @brief Implementação da lógica de Imóveis com polimorfismo.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include "Imovel.h"
#include <iostream>

namespace Imobiliaria {

    // IMPLEMENTAÇÃO CLASSE BASE (IMOVEL)
    Imovel::Imovel(std::string end, double valor) : endereco(end), valorBase(valor) {}

    double Imovel::calcularTotal() const {
        return valorBase; // Valor genérico
    }

    // IMPLEMENTAÇÃO CLASSE FILHA (APARTAMENTO)
    Apartamento::Apartamento(std::string end, double valor, double cond)
        : Imovel(end, valor), condomínio(cond) {}

    double Apartamento::calcularTotal() const {
        // Redefine (Sobrescreve) o comportamento base.
        return valorBase + condomínio;
    }

    // IMPLEMENTAÇÃO CLASSE FILHA (CASA)
    Casa::Casa(std::string end, double valor, double jard)
        : Imovel(end, valor), manutencaoJardim(jard) {}

    double Casa::calcularTotal() const {
        // Redefine (Sobrescreve) o comportamento base.
        return valorBase + manutencaoJardim;
    }
}

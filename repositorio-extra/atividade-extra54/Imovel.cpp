/**
 * @file Imovel.cpp
 * @brief Implementação das Regras de Negócio Imobiliárias (Polimorfismo).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "Imovel.h"
#include <iostream>

namespace Imobiliaria {

    // --- BASE ---
    Imovel::Imovel(const std::string& _end, double _valor)
        : endereco(_end), valorBaseCentavos(static_cast<long long>(_valor * 100)) {}

    double Imovel::calcularTotal() const {
        return static_cast<double>(valorBaseCentavos) / 100.0;
    }

    Imovel::~Imovel() {
        // Log de depuração para provar a destruição polimórfica
        // std::cout << "[BASE]: Memória base de " << endereco << " purgada." << std::endl;
    }

    // --- APARTAMENTO ---
    Apartamento::Apartamento(const std::string& _e, double _v, double _condo)
        : Imovel(_e, _v), taxaCondominioCentavos(static_cast<long long>(_condo * 100)) {}

    double Apartamento::calcularTotal() const {
        long long total = valorBaseCentavos + taxaCondominioCentavos;
        return static_cast<double>(total) / 100.0;
    }

    Apartamento::~Apartamento() {
        // std::cout << "[FILHA]: Memória de APARTAMENTO limpa." << std::endl;
    }

    // --- CASA ---
    Casa::Casa(const std::string& _e, double _v, double _jardim)
        : Imovel(_e, _v), taxaJardimCentavos(static_cast<long long>(_jardim * 100)) {}

    double Casa::calcularTotal() const {
        long long total = valorBaseCentavos + taxaJardimCentavos;
        return static_cast<double>(total) / 100.0;
    }

    Casa::~Casa() {
        // std::cout << "[FILHA]: Memória de CASA limpa." << std::endl;
    }

} // namespace Imobiliaria

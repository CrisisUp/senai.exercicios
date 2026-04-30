/**
 * @file Frota.cpp
 * @brief Implementação da Lógica de Frota (Herança e Cadeia de Construtores).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "Frota.h"
#include <sstream>
#include <iomanip>

namespace Logistica {

    // --- IMPLEMENTAÇÃO VEICULO (BASE) ---

    Veiculo::Veiculo(const std::string& _placa, const std::string& _marca)
        : placa(_placa), marca(_marca), odometro(0.0) {}

    void Veiculo::viajar(double km) {
        if (km > 0) odometro += km;
    }

    // --- IMPLEMENTAÇÃO CAMINHAO (FILHA) ---

    /**
     * @brief Construtor da Filha chamando o construtor da Mãe via Initializer List.
     */
    Caminhao::Caminhao(const std::string& _p, const std::string& _m, double cap)
        : Veiculo(_p, _m), capacidadeCarga(cap), cargaAtual(0.0) {}

    bool Caminhao::carregar(double peso) {
        // A filha acessa 'placa' e 'marca' livremente porque são protected na mãe.
        if (cargaAtual + peso <= capacidadeCarga) {
            cargaAtual += peso;
            return true;
        }
        return false;
    }

    std::string Caminhao::getRelatorioCaminhao() const {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2);
        ss << "[RELATÓRIO DE FROTA]" << "\n"
           << " >> PLACA : " << placa << "\n"
           << " >> MARCA : " << marca << "\n"
           << " >> KM    : " << odometro << " km" << "\n"
           << " >> CARGA : " << cargaAtual << " / " << capacidadeCarga << " ton.";
        return ss.str();
    }

} // namespace Logistica
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

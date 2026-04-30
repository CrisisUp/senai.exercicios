/**
 * @file Tanque.cpp
 * @brief Implementação da lógica de Tanques da Refinaria (Modular).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include "Tanque.h"
#include <iomanip>
#include <stdexcept>

namespace Refinaria {

    Tanque::Tanque(std::string _id, std::string _produto, double _cap) 
        : id(_id), produto(_produto), volumeAtual(0.0), capacidadeMax(_cap) {}

    bool Tanque::carregar(double litros) {
        if (volumeAtual + litros > capacidadeMax) {
            return false; // Transbordo
        }
        volumeAtual += litros;
        return true;
    }

    void Tanque::esvaziar() {
        volumeAtual = 0.0;
    }

    // Sobrecarga de Operador + (Combina tanques)
    Tanque Tanque::operator+(const Tanque& outro) const {
        if (this->produto != outro.produto) {
            throw std::runtime_error("ERRO: Tentativa de misturar produtos químicos diferentes!");
        }

        // Cria um novo tanque consolidado (ex: Tanque de Fusão)
        Tanque fusao("FUSAO-" + this->id, this->produto, this->capacidadeMax + outro.capacidadeMax);
        fusao.carregar(this->volumeAtual + outro.volumeAtual);
        return fusao;
    }

    // Sobrecarga de Operador > (Compara níveis de estoque)
    bool Tanque::operator>(const Tanque& outro) const {
        return (this->volumeAtual > outro.volumeAtual);
    }

    // Sobrecarga de Operador << (Relatório Visual)
    std::ostream& operator<<(std::ostream& os, const Tanque& t) {
        double percentual = (t.volumeAtual / t.capacidadeMax) * 100.0;
        
        std::string cor = (percentual > 90.0) ? "\033[31m" : "\033[32m"; // Vermelho se > 90%

        os << "[TANQUE: " << t.id << " | " << t.produto << "]\n";
        os << "  Volume: " << t.volumeAtual << " L / " << t.capacidadeMax << " L (";
        os << cor << std::fixed << std::setprecision(1) << percentual << "%\033[0m)";
        
        return os;
    }
}
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

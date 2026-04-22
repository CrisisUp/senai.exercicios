/**
 * @file Medicao.cpp
 * @brief Implementação da Sobrecarga de Operadores para medições IoT.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include "Medicao.h"
#include <stdexcept>

namespace IoT {

    Medicao::Medicao(double v, std::string u) : valor(v), unidade(u) {}

    // Implementação do operador +
    Medicao Medicao::operator+(const Medicao& outra) const {
        // Regra de Negócio: Não podemos somar unidades diferentes (ex: C + psi).
        if (this->unidade != outra.unidade) {
            throw std::runtime_error("ERRO: Unidades incompatíveis para soma!");
        }
        return Medicao(this->valor + outra.valor, this->unidade);
    }

    // Implementação do operador <
    bool Medicao::operator<(const Medicao& outra) const {
        if (this->unidade != outra.unidade) {
            throw std::runtime_error("ERRO: Unidades incompatíveis para comparação!");
        }
        return (this->valor < outra.valor);
    }

    // Implementação do operador ==
    bool Medicao::operator==(const Medicao& outra) const {
        return (this->valor == outra.valor && this->unidade == outra.unidade);
    }

    // Sobrecarga amigável do operador <<
    std::ostream& operator<<(std::ostream& os, const Medicao& m) {
        os << m.valor << " " << m.unidade;
        return os;
    }
}

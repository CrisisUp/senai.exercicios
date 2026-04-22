/**
 * @file Medicao.cpp
 * @brief Implementação da Sobrecarga de Operadores para Sensores.
 * 
 * Demonstra as regras de negócio aplicadas aos operadores matemáticos.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "Medicao.h"
#include <iomanip>

namespace IoT {

    Medicao::Medicao(double v, const std::string& u) 
        : valor(v), unidade(u) {}

    Medicao Medicao::operator+(const Medicao& outra) const {
        // Validação de Integridade Física
        if (this->unidade != outra.unidade) {
            throw IncompatibilidadeUnidade();
        }
        return Medicao(this->valor + outra.valor, this->unidade);
    }

    bool Medicao::operator<(const Medicao& outra) const {
        return (this->valor < outra.valor);
    }

    bool Medicao::operator==(const Medicao& outra) const {
        return (this->valor == outra.valor && this->unidade == outra.unidade);
    }

    /**
     * @brief Operador de Saída: Permite 'cout << medicao' de forma elegante.
     */
    std::ostream& operator<<(std::ostream& os, const Medicao& m) {
        os << std::fixed << std::setprecision(2) << m.valor << " " << m.unidade;
        return os;
    }

} // namespace IoT

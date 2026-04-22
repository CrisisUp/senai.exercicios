/**
 * @file Medicao.h
 * @brief Definição modular de medições com Sobrecarga de Operadores.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef MEDICAO_H
#define MEDICAO_H

#include <string>
#include <iostream>

namespace IoT {

    /**
     * @brief Classe para representar uma medição física de um sensor.
     */
    class Medicao {
    private:
        double valor;
        std::string unidade;

    public:
        Medicao(double v = 0.0, std::string u = "psi");

        // Sobrecarga do Operador de Adição (Soma duas medições)
        Medicao operator+(const Medicao& outra) const;

        // Sobrecarga do Operador de Menor (Compara leituras)
        bool operator<(const Medicao& outra) const;

        // Sobrecarga do Operador de Igualdade (Verifica precisão)
        bool operator==(const Medicao& outra) const;

        // Getters para exibição
        double getValor() const { return valor; }
        std::string getUnidade() const { return unidade; }

        /**
         * @brief Sobrecarga do Operador de Saída (<<)
         * Amiga da classe para acessar membros privados facilmente.
         */
        friend std::ostream& operator<<(std::ostream& os, const Medicao& m);
    };
}

#endif // MEDICAO_H

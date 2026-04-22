/**
 * @file Comparador.h
 * @brief Definição modular de Templates de Funções e Especialização.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef COMPARADOR_H
#define COMPARADOR_H

#include <iostream>
#include <string>

namespace IoT {

    /**
     * @brief Template Genérico de Função.
     * Retorna o maior entre dois valores de qualquer tipo 'T'.
     * Requisito: O tipo 'T' deve suportar o operador '>'.
     */
    template <typename T>
    T obterMaior(T a, T b) {
        std::cout << "[INFO]: Usando Template Genérico." << std::endl;
        return (a > b) ? a : b;
    }

    /**
     * @brief Especialização Explícita de Template para o tipo std::string.
     * Em vez de comparar alfabeticamente, vamos comparar por COMPRIMENTO.
     * Note a sintaxe: template<> para indicar a especialização.
     */
    template <>
    inline std::string obterMaior<std::string>(std::string a, std::string b) {
        std::cout << "[INFO]: Usando Especialização para std::string (Comprimento)." << std::endl;
        return (a.length() > b.length()) ? a : b;
    }

    /**
     * @brief Struct para representar uma leitura complexa.
     */
    struct LeituraSensor {
        int id;
        double valor;

        // Sobrecarga de Operador para que o template genérico funcione.
        bool operator>(const LeituraSensor& outra) const {
            return (this->valor > outra.valor);
        }
    };
}

#endif // COMPARADOR_H

/**
 * @file Produto.cpp
 * @brief Implementação da lógica de validação do Produto.
 */

#include "Produto.h"

namespace Industrial {

    Produto::Produto(std::string _nome, int _atual, int _minimo, double _preco) 
        : nome(_nome), estoqueAtual(_atual), estoqueMinimo(_minimo), precoUnitario(_preco) 
    {
        // BLINDAGEM: Não permitimos estados inválidos no sistema
        if (_preco < 0) {
            throw std::invalid_argument("Preço unitário não pode ser negativo.");
        }
        if (_atual < 0 || _minimo < 0) {
            throw std::invalid_argument("Quantidades de estoque não podem ser negativas.");
        }
    }

    bool Produto::precisaRepor() const {
        return estoqueAtual < estoqueMinimo;
    }

    int Produto::calcularQuantidadeFaltante() const {
        if (!precisaRepor()) return 0;
        return estoqueMinimo - estoqueAtual;
    }
}

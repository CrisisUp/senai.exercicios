/**
 * @file Produto.h
 * @brief Entidade de Produto com validação rigorosa.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 21/04/2026
 */
#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include <stdexcept>

namespace Industrial {
    /**
     * @brief Classe que representa um item de inventário industrial.
     * Implementa validação no construtor (Fail-Fast).
     */
    class Produto {
    private:
        std::string nome;
        int estoqueAtual;
        int estoqueMinimo;
        double precoUnitario;

    public:
        Produto(std::string _nome, int _atual, int _minimo, double _preco);

        // Getters (Somente leitura para garantir encapsulamento)
        std::string getNome() const { return nome; }
        int getEstoqueAtual() const { return estoqueAtual; }
        int getEstoqueMinimo() const { return estoqueMinimo; }
        double getPrecoUnitario() const { return precoUnitario; }

        // Lógica de negócio
        bool precisaRepor() const;
        int calcularQuantidadeFaltante() const;
    };
}

#endif // PRODUTO_H

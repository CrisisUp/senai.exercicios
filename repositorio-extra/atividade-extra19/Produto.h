/**
 * @file Produto.h
 * @brief Modelo de dados para o Inventário Tech-Flow.
 * 
 * Atividade Extra 19 - Gestão de Coleções com STL e Lambdas.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include <iostream>
#include <vector>

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string VERMELHO = "\033[31m";
    const std::string VERDE    = "\033[32m";
    const std::string AMARELO  = "\033[33m";
    const std::string CIANO    = "\033[36m";
}

class Produto {
private:
    std::string sku;
    std::string nome;
    int quantidade;
    double preco;

public:
    Produto(std::string s, std::string n, int q, double p);

    // Getters para ordenação
    std::string getNome() const { return nome; }
    double getPreco() const { return preco; }
    int getQuantidade() const { return quantidade; }

    void exibirLinha() const;
};

#endif // PRODUTO_H

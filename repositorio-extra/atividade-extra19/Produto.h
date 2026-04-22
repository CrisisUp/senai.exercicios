/**
 * @file Produto.h
 * @brief Modelo de dados para o Inventário Tech-Flow.
 * 
 * Atividade Extra 19 - Gestão de Coleções com STL e Lambdas.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Elite Standard)
 * - Container std::vector<Produto>: O descritor do vetor (ponteiro, size, capacity) fica na STACK.
 * - Elementos do Vetor: Todos os objetos 'Produto' são alocados em um bloco contíguo na HEAP.
 * - Strings (sku, nome): Cada produto possui strings que gerenciam seus próprios blocos na HEAP.
 * - Alocação Dinâmica: O vetor dobra de tamanho na HEAP quando atinge a capacidade, exigindo realocação.
 */

#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include <iostream>
#include <vector>

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERMELHO = "\033[31m";
    const std::string VERDE    = "\033[32m";
    const std::string AMARELO  = "\033[33m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string BRANCO   = "\033[37m";

    inline void limparTela() { std::cout << "\033[2J\033[1;1H"; }
}

// --- 2. MODELO DE DADOS ---
class Produto {
private:
    std::string sku;
    std::string nome;
    int quantidade;
    double preco;

public:
    /**
     * @brief Construtor com Lista de Inicialização (Performance).
     */
    Produto(const std::string& s, const std::string& n, int q, double p);

    // --- GETTERS (FANTASMA DO CPU - REFERÊNCIAS CONSTANTES) ---
    const std::string& getNome() const { return nome; }
    const std::string& getSKU() const { return sku; }
    double getPreco() const { return preco; }
    int getQuantidade() const { return quantidade; }

    /**
     * @brief Exibe o produto formatado como uma linha de tabela.
     */
    void exibirLinha() const;
};

#endif // PRODUTO_H

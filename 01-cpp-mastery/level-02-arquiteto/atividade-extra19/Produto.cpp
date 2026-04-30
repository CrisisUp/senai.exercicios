/**
 * @file Produto.cpp
 * @brief Implementação dos métodos da classe Produto.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "Produto.h"
#include <iomanip>

using namespace std;

/**
 * @brief Construtor otimizado (Fase 3+).
 */
Produto::Produto(const string& s, const string& n, int q, double p)
    : sku(s), nome(n), quantidade(q), preco(p) {}

/**
 * @brief Exibe dados formatados com cores ANSI para status de estoque.
 */
void Produto::exibirLinha() const {
    cout << left << setw(12) << sku 
         << left << setw(20) << nome;
    
    // Feedback visual para estoque crítico
    if (quantidade < 5) {
        cout << UI::VERMELHO << UI::NEGRITO << right << setw(10) << quantidade << UI::RESET;
    } else {
        cout << UI::VERDE << right << setw(10) << quantidade << UI::RESET;
    }

    cout << fixed << setprecision(2) 
         << right << setw(12) << "R$ " << preco << endl;
}
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

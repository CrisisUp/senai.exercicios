/**
 * @file Produto.cpp
 * @brief Implementação dos métodos do modelo Produto.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "Produto.h"
#include <iomanip>

using namespace std;

Produto::Produto(string s, string n, int q, double p) 
    : sku(s), nome(n), quantidade(q), preco(p) {}

void Produto::exibirLinha() const {
    cout << left << setw(10) << sku 
         << setw(25) << nome 
         << right << setw(10) << fixed << setprecision(2) << preco;
    
    // Alerta visual de estoque baixo
    if (quantidade < 5) {
        cout << UI::VERMELHO << setw(10) << quantidade << " [!] " << UI::RESET << endl;
    } else {
        cout << UI::VERDE << setw(10) << quantidade << UI::RESET << endl;
    }
}

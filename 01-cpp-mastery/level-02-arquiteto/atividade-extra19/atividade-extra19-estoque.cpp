/**
 * @file atividade-extra19-estoque.cpp
 * @brief Gestão de Inventário Dinâmico com STL, Sort e Lambdas.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Foco em performance de algoritmos e gestão eficiente de coleções na HEAP.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <vector>
#include <algorithm> // Para std::sort
#include <iomanip>
#include "Produto.h"

using namespace std;

/**
 * @brief Exibe o cabeçalho da tabela de inventário.
 */
void exibirCabecalho() {
    cout << "\n" << UI::NEGRITO << left << setw(12) << "SKU" 
         << left << setw(20) << "NOME" 
         << right << setw(10) << "ESTOQUE" 
         << right << setw(15) << "PREÇO" << UI::RESET << endl;
    cout << string(60, '-') << endl;
}

int main() {
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "     TECH-FLOW: GESTÃO DE INVENTÁRIO v3.0      " << endl;
    cout << "       (Elite Performance & STL Edition)       " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // --- COLEÇÃO DINÂMICA (ALOCADA NA HEAP) ---
    vector<Produto> estoque;

    // Alimentação manual simulada para demonstração rápida
    estoque.push_back(Produto("COMP-001", "Resistor 10k", 150, 0.15));
    estoque.push_back(Produto("IC-555", "Timer NE555", 3, 2.50));
    estoque.push_back(Produto("MCU-32", "ESP32 DevKit", 12, 45.90));
    estoque.push_back(Produto("DISP-OLED", "Display OLED I2C", 2, 28.00));
    estoque.push_back(Produto("SENS-TEMP", "Sensor DHT22", 25, 18.50));

    int opcao = 0;
    do {
        cout << "\n" << UI::NEGRITO << "MENU DE OPERAÇÕES:" << UI::RESET << endl;
        cout << "1. Listar Estoque (Ordem de Entrada)" << endl;
        cout << "2. Ordenar por NOME (A-Z)" << endl;
        cout << "3. Ordenar por PREÇO (Crescente)" << endl;
        cout << "4. Ordenar por ESTOQUE (Crítico Primeiro)" << endl;
        cout << "0. Sair" << endl;
        cout << UI::RESET << "Escolha: " << UI::RESET;
        
        if (!(cin >> opcao)) break;

        switch (opcao) {
            case 1:
                exibirCabecalho();
                for (const auto& p : estoque) p.exibirLinha();
                break;

            case 2:
                // FANTASMA DO CPU: Usamos 'const auto&' na Lambda para evitar cópias durante as trocas
                sort(estoque.begin(), estoque.end(), [](const auto& a, const auto& b) {
                    return a.getNome() < b.getNome();
                });
                cout << UI::VERDE << "Estoque ordenado por NOME." << UI::RESET << endl;
                break;

            case 3:
                sort(estoque.begin(), estoque.end(), [](const auto& a, const auto& b) {
                    return a.getPreco() < b.getPreco();
                });
                cout << UI::VERDE << "Estoque ordenado por PREÇO." << UI::RESET << endl;
                break;

            case 4:
                sort(estoque.begin(), estoque.end(), [](const auto& a, const auto& b) {
                    return a.getQuantidade() < b.getQuantidade();
                });
                cout << UI::VERDE << "Estoque ordenado por PRIORIDADE DE REPOSIÇÃO." << UI::RESET << endl;
                break;
        }

    } while (opcao != 0);

    cout << UI::CIANO << "\nSistema encerrado. Integridade de memória garantida." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ALGORITMOS, COLEÇÕES E PERFORMANCE
    ===============================================================

    1. O PODER DO std::vector:
       - Diferente do array comum, o vector gerencia sua própria 
         memória na HEAP. Ele cresce dinamicamente. A complexidade 
         de inserção (push_back) é O(1) amortizado, tornando-o a 
         escolha ideal para inventários.

    2. std::sort E FUNÇÕES LAMBDA:
       - O 'std::sort' usa o algoritmo Introsort (híbrido de QuickSort 
         e HeapSort) com complexidade O(n log n). As lambdas `[](){}` 
         permitem injetar critérios de comparação personalizados 
         sem a necessidade de criar funções globais pesadas.

    3. MEDALHA ⚡ FANTASMA DO CPU (REFERÊNCIAS EM LAMBDAS):
       - Ao ordenar, o C++ realiza milhares de comparações. Se a 
         lambda recebesse `(Produto a, Produto b)`, o sistema criaria 
         duas cópias de cada produto a cada comparação. Usando 
         `const auto&`, trabalhamos diretamente com os dados originais 
         na HEAP, eliminando o overhead de cópia.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Big O Notation: Entendendo a escala de algoritmos.
    - Capacity vs Size: Como o vector reserva memória antecipadamente.
    - Stable Sort: Quando a ordem relativa de itens iguais deve ser mantida.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

/**
 * @file atividade-extra19-estoque.cpp
 * @brief Gestão de Inventário com STL Vector e Algoritmos de Ordenação.
 * 
 * Demonstra o uso de coleções dinâmicas e lambdas para ordenação flexível.
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
 * @brief Função auxiliar para exibir o cabeçalho da tabela.
 */
void exibirCabecalho() {
    cout << "\n" << UI::CIANO << left << setw(10) << "SKU" 
         << setw(25) << "NOME" 
         << right << setw(10) << "PREÇO" 
         << setw(15) << "ESTOQUE" << UI::RESET << endl;
    cout << string(60, '-') << endl;
}

int main() {
    // 1. VETOR DINÂMICO (O coração da STL)
    vector<Produto> estoque;

    // 2. CADASTRO INICIAL (Simulando carga de dados)
    estoque.push_back(Produto("RES-10K", "Resistor 10k Ohms", 150, 0.05));
    estoque.push_back(Produto("CAP-100u", "Capacitor 100uF 25V", 3, 0.45));
    estoque.push_back(Produto("LED-RED", "LED Difuso Vermelho", 200, 0.12));
    estoque.push_back(Produto("ARD-UNO", "Arduino Uno R3 Original", 4, 185.90));
    estoque.push_back(Produto("ESP-32", "Módulo ESP32 DevKit V1", 12, 45.00));

    int opcao = 0;
    while (opcao != 4) {
        cout << "\n" << UI::CIANO << "===============================================" << endl;
        cout << "      SISTEMA TECH-FLOW: CONTROLE DE ESTOQUE   " << endl;
        cout << "===============================================" << UI::RESET << endl;
        cout << "1. Listar Estoque (Original)\n";
        cout << "2. Ordenar por NOME (A-Z)\n";
        cout << "3. Ordenar por PREÇO (Maior -> Menor)\n";
        cout << "4. Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                exibirCabecalho();
                for (const auto& p : estoque) p.exibirLinha();
                break;

            case 2:
                // 3. ORDENAÇÃO COM LAMBDA (Nome)
                sort(estoque.begin(), estoque.end(), [](const Produto& a, const Produto& b) {
                    return a.getNome() < b.getNome();
                });
                cout << UI::VERDE << "[OK]: Estoque ordenado por Nome." << UI::RESET << endl;
                break;

            case 3:
                // 4. ORDENAÇÃO COM LAMBDA (Preço Descendente)
                sort(estoque.begin(), estoque.end(), [](const Produto& a, const Produto& b) {
                    return a.getPreco() > b.getPreco();
                });
                cout << UI::VERDE << "[OK]: Estoque ordenado por Preço (Decrescente)." << UI::RESET << endl;
                break;
        }
    }

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: VETORES DINÂMICOS E ALGORITMOS STL
    ===============================================================

    1. O QUE É O std::vector?
       - Diferente do array comum (int v[5]), o vector gerencia sua 
         própria memória. Ele cresce conforme você usa push_back() 
         e libera memória ao ser destruído. É o container padrão 
         para 90% das tarefas em C++.

    2. O ALGORITMO std::sort:
       - Um dos algoritmos mais rápidos do mundo. Ele não te obriga 
         a saber COMO ordenar (bolha, inserção, etc), apenas QUAL 
         é o critério de comparação.

    3. FUNÇÕES LAMBDA (Closures):
       - São funções "sem nome" criadas na hora.
       - Sintaxe: [](params) { corpo }.
       - No código, usamos a lambda para dizer ao sort: "Compare o 
         produto A com o B usando o preço como critério".

    4. ITERAÇÃO MODERNA (Range-based for):
       - for (const auto& p : estoque)
       - Evita erros de índice e é muito mais legível.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Complexidade de Tempo (O log N): Por que o sort é rápido.
    - Iteradores (begin/end): As "pontes" entre containers e algoritmos.
    - Reserva de Memória (reserve()): Otimizando vetores gigantes.
    - std::map: Coleções baseadas em chave-valor (Dicionários).
    ===============================================================
*/

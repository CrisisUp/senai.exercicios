#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file main.cpp
 * @brief Execução do simulador de ecossistema Bio-CPP.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <string>
#include <ctime>
#include "Reserva.h"

using namespace std;

int main()
{
    Reserva amazonia;
    int opcao = 0;

    do {
        UI::limparTela();
        UI::banner();
        
        amazonia.dashboard();

        cout << UI::RESET << "\nMENU DE GENÉTICA:" << UI::RESET << endl;
        cout << "[1] Criar Planta      [2] Criar Herbívoro  [3] Criar Carnívoro" << endl;
        cout << "[4] Iniciar Evolução  [5] Encerrar Biosfera" << endl;
        cout << UI::CIANO << "Escolha: " << UI::RESET;
        
        if (!(cin >> opcao)) break;

        if (opcao >= 1 && opcao <= 3) {
            string n;
            cout << "Nome do espécime: ";
            getline(cin >> ws, n);
            
            if (opcao == 1) amazonia.adicionar(new Planta(n));
            else if (opcao == 2) amazonia.adicionar(new Herbivoro(n));
            else if (opcao == 3) amazonia.adicionar(new Carnivoro(n));
            
            cout << UI::VERDE << "[SISTEMA]: DNA codificado e injetado." << UI::RESET << endl;
            // Pequena pausa para UX
            clock_t goal = 500000 + clock();
            while (goal > clock());
        } 
        else if (opcao == 4) {
            amazonia.evoluir();
            cout << UI::AMARELO << "\nPressione ENTER para o próximo ciclo..." << UI::RESET;
            cin.ignore(1000, '\n'); cin.get();
        }

    } while (opcao != 5);

    cout << UI::VERMELHO << "\nSimulação encerrada. Todos os processos vitais suspensos." << UI::RESET << endl;

    return 0;
}

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

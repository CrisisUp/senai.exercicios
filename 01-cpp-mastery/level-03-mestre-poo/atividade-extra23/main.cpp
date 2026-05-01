#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file main.cpp
 * @brief Execução do Checkout Gateway de Pagamentos.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <vector>
#include "MetodoPagamento.h"

using namespace std;

int main()
{
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      GATEWAY DE PAGAMENTOS (G-PAY v2.0)       " << endl;
    cout << "       (Elite Abstract Infrastructure)         " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // A mágica: Polimorfismo através de uma Interface Abstrata
    vector<MetodoPagamento*> filaProcessamento;

    // Alocação na HEAP para vida dinâmica
    filaProcessamento.push_back(new PagamentoPix(250.75));
    filaProcessamento.push_back(new PagamentoCartao(1200.00, "4532-XXXX-XXXX-8899"));
    filaProcessamento.push_back(new PagamentoPix(15.90));

    cout << "\n" << UI::RESET << "[OPERACIONAL]: Iniciando processamento de fila assíncrona...\n" << UI::RESET << endl;

    // Execução polimórfica (Fantasma do CPU)
    for (auto* pgto : filaProcessamento) {
        if (pgto) {
            pgto->processar();    // Chamada dinâmica via V-Table
            pgto->exibirRecibo(); // Chamada estática da Base
            cout << endl;
        }
    }

    // --- CICLO DE DESALOCAÇÃO SEGURA ---
    cout << UI::RESET << "[SISTEMA]: Limpando buffer de transações..." << UI::RESET << endl;
    for (auto& pgto : filaProcessamento) {
        delete pgto;
        pgto = nullptr;
    }
    filaProcessamento.clear();

    cout << UI::VERDE << UI::NEGRITO << "\nCheckpoint: Todos os pagamentos liquidados com 100% de integridade." << UI::RESET << endl;

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

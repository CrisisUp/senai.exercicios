#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file main.cpp
 * @brief Execução do sistema de almoxarifado industrial refatorado.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <vector>
#include "ProdutoIndustrial.h"

using namespace std;

int main()
{
    UI::limparTela();
    UI::cabecalho();

    vector<ProdutoIndustrial*> almoxarifado;

    try {
        cout << UI::AMARELO << "[SISTEMA]: Migrando dados do legado (Atividade 01)..." << UI::RESET << endl;
        
        // Simulação de entrada de itens industriais
        almoxarifado.push_back(new ProdutoIndustrial("Inversor de Frequência", 2850.75, 4));
        almoxarifado.push_back(new ProdutoIndustrial("Sensor Ultrassônico", 115.20, 50));
        almoxarifado.push_back(new ProdutoIndustrial("Relé Industrial 24V", 45.00, 120));

        cout << "\nStatus Atual do Armazém:" << endl;
        cout << "-> Unidades Cadastradas : " << ProdutoIndustrial::getTotalItens() << endl;
        cout << "-> Patrimônio Líquido   : " << UI::VERDE << "R$ " << ProdutoIndustrial::getValorGlobal() << UI::RESET << endl;
        cout << string(60, '-') << endl;

        // Simulando Operação Crítica
        cout << "\n" << UI::RESET << "[REQUISIÇÃO]: Solicitando saída de material..." << UI::RESET << endl;
        almoxarifado[0]->registrarSaida(2); // Retira 2 inversores

        // Listagem Consolidada
        cout << "\n" << UI::NEGRITO << "RELATÓRIO DE INVENTÁRIO CONSOLIDADO:" << UI::RESET << endl;
        for (const auto* item : almoxarifado) {
            if (item) item->exibirItem();
        }

        cout << string(60, '-') << endl;
        cout << "Patrimônio Consolidado : " << UI::VERDE << UI::NEGRITO << "R$ " << ProdutoIndustrial::getValorGlobal() << UI::RESET << endl;

        // Testando Resiliência (🧪 Cientista do Caos)
        cout << "\n" << UI::VERMELHO << "[STRESS TEST]: Tentando retirar estoque fantasma..." << UI::RESET << endl;
        almoxarifado[1]->registrarSaida(1000); // Força erro

    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // --- LIMPEZA DE MEMÓRIA (BOA PRÁTICA DE ENGENHARIA) ---
    cout << "\n" << UI::RESET << "[SISTEMA]: Encerrando e desalocando recursos..." << UI::RESET << endl;
    for (auto& item : almoxarifado) {
        delete item;
        item = nullptr;
    }
    almoxarifado.clear();

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

#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file atividade-extra15-financeiro.cpp
 * @brief ATIVIDADE 15: Financeiro, Conversões e Segurança de Dados.
 * 
 * Versão Refatorada: Arquitetura Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include "MotorFinanceiro.h"

using namespace std;

int main()
{
    GestorFinanceiro financeiro;
    int opcao = 0;

    GestorFinanceiro::exibirBanner();

    try {
        financeiro.carregarCatalogo();

        do {
            cout << "\n" << UI::CIANO << UI::NEGRITO << "--- SISTEMA FINANCEIRO (MODULAR) ---" << UI::RESET << endl;
            cout << "Fila: " << UI::AMARELO << financeiro.getFila().size() << UI::RESET;
            cout << " | Caixa do Dia: " << UI::VERDE << GestorFinanceiro::formatarMoeda(financeiro.getCaixa()) << UI::RESET << endl;
            cout << "[1] Novo Leitor | [2] Atender (Aluguel) | [3] Resumo | [4] Sair" << endl;
            
            try {
                opcao = GestorFinanceiro::lerInteiro("Escolha: ");

                if (opcao == 1) {
                    string nome;
                    cout << "Nome do Leitor: ";
                    getline(cin >> ws, nome);
                    financeiro.adicionarLeitor(nome);
                }
                else if (opcao == 2) {
                    if (financeiro.getFila().empty()) throw ErroBiblioteca("Fila de atendimento vazia.");
                    
                    cout << "\n--- CATÁLOGO DE ALUGUEL ---" << endl;
                    cout << left << setw(4) << "ID" << setw(25) << "LIVRO" << "PREÇO/ALUGUEL" << endl;
                    
                    const auto& catalogo = financeiro.getCatalogo();
                    for (int i = 0; i < (int)catalogo.size(); i++) {
                        const Livro& l = catalogo[i];
                        cout << "[" << i << "] " << setw(25) << l.titulo 
                             << UI::AMARELO << GestorFinanceiro::formatarMoeda(l.precoCentavos) << UI::RESET 
                             << (l.estoque > 0 ? "" : UI::VERMELHO + " (ESGOTADO)" + UI::RESET) << endl;
                    }

                    int idx = GestorFinanceiro::lerInteiro("\nEscolha o Livro (ID): ");
                    
                    if (idx < 0 || idx >= (int)catalogo.size()) throw ErroBiblioteca("ID inválido.");

                    cout << "Total a pagar: " << UI::VERDE << GestorFinanceiro::formatarMoeda(catalogo[idx].precoCentavos) << UI::RESET << endl;
                    string valorStr;
                    cout << "Digite o valor recebido (ex: 5.00 ou 5,00): ";
                    cin >> valorStr;

                    financeiro.processarAluguel(idx, valorStr);
                }
                else if (opcao == 3) {
                    cout << "\n--- RELATÓRIO DE CAIXA ---" << endl;
                    cout << "Total Arrecadado: " << UI::VERDE << GestorFinanceiro::formatarMoeda(financeiro.getCaixa()) << UI::RESET << endl;
                    cout << "Operações Realizadas: " << financeiro.getOperacoesCount() << endl;
                }

            } catch (const exception& e) {
                cout << e.what() << endl;
            }

        } while (opcao != 4);

    } catch (const exception& e) {
        cerr << UI::VERMELHO << "FALHA CRÍTICA: " << e.what() << UI::RESET << endl;
        return 1;
    }

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: INTEGRIDADE FINANCEIRA E MODULARIZAÇÃO
    ===============================================================

    1. ARITMÉTICA DE CENTAVOS (Ponto Fixo):
       - Ao centralizar a lógica de centavos no módulo MotorFinanceiro, 
         garantimos que NENHUMA outra parte do sistema possa cometer 
         erros de arredondamento de ponto flutuante acidentalmente.

    2. static_cast E SEGURANÇA:
       - O uso de conversões explícitas dentro do módulo protege a 
         precisão dos dados antes de qualquer exibição visual.

    3. DESACOPLAMENTO DO PDV:
       - A main funciona apenas como a interface do caixa (PDV). 
         Toda a inteligência de validação de moeda (ponto vs vírgula) 
         está encapsulada e protegida.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Floating Point Inaccuracy: Por que 0.1 + 0.2 != 0.3 em binário.
    - Currency Localization: Tratamento de diferentes moedas e símbolos.
    - Transaction Logs: Como registrar cada centavo para auditoria.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */


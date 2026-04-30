/**
 * @file atividade-extra13-excecoes.cpp
 * @brief ATIVIDADE 13: Robustez e Tratamento de Exceções.
 * 
 * Versão Refatorada: Arquitetura Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include "GestorBiblioteca.h"

using namespace std;

int main()
{
    GestorBiblioteca biblioteca;
    int opcao = 0;

    GestorBiblioteca::exibirBanner();

    try {
        biblioteca.carregarCatalogo();

        if (biblioteca.getCatalogo().empty()) {
            throw ErroBiblioteca("O catálogo está vazio. Impossível prosseguir.");
        }

        do {
            cout << "\n--- " << UI::CIANO << "PAINEL DE CONTROLE (MODULAR)" << UI::RESET << " ---" << endl;
            cout << "Leitores na Fila: " << UI::AMARELO << biblioteca.totalFila() << UI::RESET << " | ";
            cout << "Empréstimos na Sessão: " << UI::AMARELO << biblioteca.totalHistorico() << UI::RESET << endl;
            cout << "[1] Adicionar Leitor à Fila" << endl;
            cout << "[2] Atender Próximo Leitor (Empréstimo)" << endl;
            cout << "[3] Cancelar Último Empréstimo (DESFAZER)" << endl;
            cout << "[4] Salvar e Encerrar Expediente" << endl;
            
            try {
                opcao = GestorBiblioteca::lerInteiro("Escolha: ");

                if (opcao == 1) {
                    string nome;
                    cout << "Nome do Leitor: ";
                    getline(cin >> ws, nome);
                    biblioteca.adicionarLeitor(nome);
                }
                else if (opcao == 2) {
                    if (biblioteca.totalFila() == 0) {
                        cout << UI::AMARELO << "[AVISO]: " << UI::RESET << "Fila de atendimento vazia." << endl;
                    } else {
                        const string& leitorAtual = biblioteca.getProximoLeitor();
                        cout << UI::CIANO << "\n--- ATENDENDO: " << UI::RESET << leitorAtual << " ---" << endl;
                        cout << left << setw(4) << "ID" << setw(30) << "TÍTULO" << "ESTOQUE" << endl;
                        cout << "--------------------------------------------------------" << endl;
                        const auto& catalogo = biblioteca.getCatalogo();
                        for (int i = 0; i < (int)catalogo.size(); i++) {
                            const Livro& l = catalogo[i];
                            cout << left << "[" << i << "] " 
                                 << setw(30) << (l.titulo.length() > 28 ? l.titulo.substr(0, 25) + "..." : l.titulo)
                                 << (l.estoque > 0 ? to_string(l.estoque) : UI::VERMELHO + "ESGOTADO" + UI::RESET) << endl;
                        }
                        
                        int index = GestorBiblioteca::lerInteiro("\nÍndice do livro (ou -1 para cancelar): ");
                        if (index != -1) {
                            biblioteca.registrarEmprestimo(index);
                        }
                    }
                }
                else if (opcao == 3) {
                    biblioteca.cancelarUltimoEmprestimo();
                }
                else if (opcao != 4) {
                    cout << UI::AMARELO << "[AVISO]: " << UI::RESET << "Opção inválida." << endl;
                }

            } catch (const ErroBiblioteca& e) {
                cout << UI::VERMELHO << e.what() << UI::RESET << endl;
            }

        } while (opcao != 4);

        biblioteca.salvarRelatorio();

    } catch (const exception& e) {
        cerr << UI::VERMELHO << "\nFALHA NO SISTEMA: " << e.what() << UI::RESET << endl;
        return 1;
    }

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: HIERARQUIA DE EXCEÇÕES E ARQUITETURA MODULAR
    ===============================================================

    1. MODULARIZAÇÃO COM EXCEÇÕES:
       - Ao mover as exceções para o .h, permitimos que qualquer parte 
         do sistema (ou outros módulos futuros) as utilize para manter 
         a padronização do tratamento de erros.

    2. ENCAPSULAMENTO DE LÓGICA DE PERSISTÊNCIA:
       - A main não precisa saber COMO o catálogo é lido ou COMO o 
         relatório é salvo. Ela apenas solicita a ação ao GestorBiblioteca.

    3. PROTEÇÃO DE DADOS:
       - O uso de métodos como getFila() e getHistorico() permite 
         acesso controlado às coleções internas, enquanto métodos de 
         ação como registrarEmprestimo() garantem que as regras de 
         negócio (ex: estoque) sejam respeitadas.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Exception Safety: Garantir que o programa continue em estado válido.
    - RAII (Resource Acquisition Is Initialization): Gestão de recursos.
    - Standard Library Containers (queue/stack): Diferenças e usos.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

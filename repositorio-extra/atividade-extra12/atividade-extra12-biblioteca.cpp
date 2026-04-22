/**
 * @file atividade-extra12-biblioteca.cpp
 * @brief DESAFIO DE FASE: Sistema Integrado de Gestão Bibliotecária.
 * 
 * Versão Refatorada: Agora utilizando Arquitetura Modular (.h e .cpp)
 * seguindo as normas do Nível 11+ do SENAI C++.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 24/04/2026
 */

#include <iostream>
#include <string>
#include <iomanip>
#include "GestorBiblioteca.h"

using namespace std;

/**
 * @brief Lê um inteiro do teclado com proteção contra caracteres.
 */
int lerInteiro(string prompt) {
    int valor;
    cout << prompt;
    while (!(cin >> valor)) {
        cin.clear(); // Limpa estado de erro
        cin.ignore(1000, '\n'); // Descarta caracteres inválidos
        throw ErroEntrada();
    }
    return valor;
}

int main()
{
    GestorBiblioteca gestor;
    int opcao = 0;

    GestorBiblioteca::exibirBanner();

    try {
        gestor.carregarCatalogo("repositorio-extra/atividade-extra12/catalogo.txt");

        if (gestor.getCatalogo().empty()) {
            throw ErroBiblioteca("O catálogo está vazio. Impossível iniciar sistema.");
        }

        do {
            cout << "\n--- PAINEL DE CONTROLE ---" << endl;
            cout << "Leitores na Fila: " << gestor.totalFila() << " | ";
            cout << "Empréstimos na Sessão: " << gestor.totalHistorico() << endl;
            cout << "[1] Adicionar Leitor à Fila" << endl;
            cout << "[2] Atender Próximo Leitor (Empréstimo)" << endl;
            cout << "[3] Cancelar Último Empréstimo (DESFAZER)" << endl;
            cout << "[4] Salvar e Encerrar Expediente" << endl;
            
            try {
                opcao = lerInteiro("Escolha: ");

                if (opcao == 1) {
                    string nome;
                    cout << "Nome do Leitor: ";
                    getline(cin >> ws, nome);
                    gestor.adicionarLeitor(nome);
                }
                else if (opcao == 2) {
                    if (gestor.filaVazia()) {
                        cout << "[AVISO]: Fila de atendimento vazia." << endl;
                    } else {
                        string leitorAtual = gestor.getProximoLeitor();
                        
                        cout << "\n--- LIVROS DISPONÍVEIS ---" << endl;
                        cout << left << setw(4) << "ID" << setw(30) << "TÍTULO" << "ESTOQUE" << endl;
                        cout << "--------------------------------------------------------" << endl;
                        const auto& catalogo = gestor.getCatalogo();
                        for (int i = 0; i < (int)catalogo.size(); i++) {
                            cout << left << "[" << i << "] " 
                                 << setw(30) << (catalogo[i].titulo.length() > 28 ? catalogo[i].titulo.substr(0, 25) + "..." : catalogo[i].titulo)
                                 << (catalogo[i].estoque > 0 ? to_string(catalogo[i].estoque) : "ESGOTADO") << endl;
                        }
                        
                        int index = lerInteiro("\nEscolha o índice do livro para " + leitorAtual + " (ou -1 para cancelar): ");

                        if (index == -1) {
                            cout << "[AVISO]: Atendimento cancelado." << endl;
                        } else {
                            gestor.realizarEmprestimo(index);
                        }
                    }
                }
                else if (opcao == 3) {
                    gestor.desfazerEmprestimo();
                }
                else if (opcao != 4) {
                    cout << "[AVISO]: Opção inválida." << endl;
                }

            } catch (const ErroBiblioteca& e) {
                cout << e.what() << endl;
            }

        } while (opcao != 4);

        gestor.salvarRelatorio("repositorio-extra/atividade-extra12/relatorio_dia.txt");

    } catch (const exception& e) {
        cerr << "\nFATAL: " << e.what() << endl;
        return 1;
    }

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ARQUITETURA MODULAR E PERSISTÊNCIA
    ===============================================================

    1. SEPARAÇÃO DE INTERFACE E IMPLEMENTAÇÃO:
       - A lógica de gerenciamento da biblioteca foi movida para a 
         classe GestorBiblioteca, separando a interface do usuário 
         (main) do processamento de dados.

    2. MANIPULAÇÃO DE ARQUIVOS (fstream):
       - O sistema carrega o catálogo e salva relatórios em arquivos 
         externos, garantindo que os dados não sejam perdidos.

    3. TRATAMENTO DE EXCEÇÕES:
       - O uso de blocos try-catch e classes de exceção customizadas 
         permite que o sistema lide com erros de forma graciosa.

    ===============================================================
    ASSUNTOS CORRELATOS
    ===============================================================
    - Encapsulamento: Atributos privados protegem o estado da classe.
    - STL Containers: vector, queue e stack organizam os dados.
    - Doxygen: Documentação técnica integrada ao código.
    ===============================================================
*/

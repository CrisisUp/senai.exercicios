/**
 * @file atividade-extra14-estilos.cpp
 * @brief ATIVIDADE 14: Estilo Visual e Cores ANSI no Terminal.
 * 
 * Versão Refatorada: Arquitetura Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include "InterfaceBiblioteca.h"

using namespace std;

int main()
{
    GestorEstilizado biblioteca;
    int opcao = 0;

    GestorEstilizado::exibirBanner();

    try {
        biblioteca.carregarCatalogo();

        if (biblioteca.getCatalogo().empty()) {
            throw ErroBiblioteca(UI::VERMELHO + "Catálogo vazio. Sistema encerrado." + UI::RESET);
        }

        do {
            cout << "\n" << UI::CIANO << UI::NEGRITO << "--- PAINEL DE CONTROLE (MODULAR & COLORIDO) ---" << UI::RESET << endl;
            cout << "Leitores na Fila: " << UI::AZUL << biblioteca.getFila().size() << UI::RESET << " | ";
            cout << "Empréstimos na Sessão: " << UI::VERDE << biblioteca.getHistorico().size() << UI::RESET << endl;
            cout << UI::BRANCO << "[1] Adicionar Leitor à Fila" << endl;
            cout << "[2] Atender Próximo Leitor (Empréstimo)" << endl;
            cout << "[3] Cancelar Último Empréstimo (DESFAZER)" << endl;
            cout << "[4] Salvar e Encerrar Expediente" << UI::RESET << endl;
            
            try {
                opcao = GestorEstilizado::lerInteiro(UI::NEGRITO + "Escolha: " + UI::RESET);

                if (opcao == 1) {
                    string nome;
                    cout << "Nome do Leitor: ";
                    getline(cin >> ws, nome);
                    biblioteca.adicionarLeitor(nome);
                }
                else if (opcao == 2) {
                    if (biblioteca.getFila().empty()) {
                        cout << UI::AMARELO << "[AVISO]: Fila vazia." << UI::RESET << endl;
                    } else {
                        cout << "\n" << UI::NEGRITO << "--- LIVROS DISPONÍVEIS ---" << UI::RESET << endl;
                        cout << left << setw(4) << "ID" << setw(30) << "TÍTULO" << "ESTOQUE" << endl;
                        cout << "--------------------------------------------------------" << endl;
                        
                        const auto& catalogo = biblioteca.getCatalogo();
                        for (int i = 0; i < (int)catalogo.size(); i++) {
                            const Livro& l = catalogo[i];
                            cout << left << "[" << i << "] " 
                                 << setw(30) << (l.titulo.length() > 28 ? l.titulo.substr(0, 25) + "..." : l.titulo);
                            
                            if (l.estoque <= 0) {
                                cout << UI::VERMELHO << "ESGOTADO" << UI::RESET << endl;
                            } else {
                                cout << UI::VERDE << l.estoque << UI::RESET << endl;
                            }
                        }
                        
                        int index = GestorEstilizado::lerInteiro("\nÍndice para o leitor (ou -1): ");
                        if (index != -1) {
                            biblioteca.atenderLeitor(index);
                        }
                    }
                }
                else if (opcao == 3) {
                    biblioteca.desfazerUltimo();
                }
                else if (opcao != 4) {
                    cout << UI::AMARELO << "[AVISO]: Opção inválida." << UI::RESET << endl;
                }

            } catch (const ErroBiblioteca& e) {
                cout << e.what() << endl;
            }

        } while (opcao != 4);

        biblioteca.salvarRelatorio();

    } catch (const exception& e) {
        cerr << "\n" << UI::VERMELHO << UI::NEGRITO << "FALHA CRÍTICA: " << e.what() << UI::RESET << endl;
        return 1;
    }

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ESTILIZAÇÃO (ANSI) E ARQUITETURA DE UI
    ===============================================================

    1. DESACOPLAMENTO VISUAL:
       - Ao centralizar as cores em um módulo (InterfaceBiblioteca), 
         podemos mudar o tema de todo o sistema alterando apenas um 
         arquivo, sem tocar na lógica de negócio da main.

    2. UX EM CLIS:
       - O uso de cores ajuda a destacar informações críticas 
         (ESGOTADO em Vermelho) e status de sucesso (Verde), 
         reduzindo a carga cognitiva do usuário.

    3. NAMESPACES PARA ORGANIZAÇÃO:
       - O namespace UI:: funciona como um "Dicionário de Estilos", 
         mantendo o código limpo e evitando colisões de nomes.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Temas Dinâmicos: Carregar cores de arquivos de configuração.
    - Suporte ao Windows: O uso de 'virtual terminal sequences'.
    - UX/UI design para DevOps e ferramentas de linha de comando.
    ===============================================================
*/

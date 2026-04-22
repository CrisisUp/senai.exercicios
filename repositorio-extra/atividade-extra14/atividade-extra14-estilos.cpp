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
            throw ErroBiblioteca(Cor::VERMELHO + "Catálogo vazio. Sistema encerrado." + Cor::RESET);
        }

        do {
            cout << "\n" << Cor::CIANO << Cor::NEGRITO << "--- PAINEL DE CONTROLE (MODULAR & COLORIDO) ---" << Cor::RESET << endl;
            cout << "Leitores na Fila: " << Cor::AZUL << biblioteca.getFila().size() << Cor::RESET << " | ";
            cout << "Empréstimos na Sessão: " << Cor::VERDE << biblioteca.getHistorico().size() << Cor::RESET << endl;
            cout << Cor::BRANCO << "[1] Adicionar Leitor à Fila" << endl;
            cout << "[2] Atender Próximo Leitor (Empréstimo)" << endl;
            cout << "[3] Cancelar Último Empréstimo (DESFAZER)" << endl;
            cout << "[4] Salvar e Encerrar Expediente" << Cor::RESET << endl;
            
            try {
                opcao = GestorEstilizado::lerInteiro(Cor::NEGRITO + "Escolha: " + Cor::RESET);

                if (opcao == 1) {
                    string nome;
                    cout << "Nome do Leitor: ";
                    getline(cin >> ws, nome);
                    biblioteca.adicionarLeitor(nome);
                }
                else if (opcao == 2) {
                    if (biblioteca.getFila().empty()) {
                        cout << Cor::AMARELO << "[AVISO]: Fila vazia." << Cor::RESET << endl;
                    } else {
                        cout << "\n" << Cor::NEGRITO << "--- LIVROS DISPONÍVEIS ---" << Cor::RESET << endl;
                        cout << left << setw(4) << "ID" << setw(30) << "TÍTULO" << "ESTOQUE" << endl;
                        cout << "--------------------------------------------------------" << endl;
                        for (int i = 0; i < (int)biblioteca.getCatalogo().size(); i++) {
                            Livro& l = biblioteca.getCatalogo()[i];
                            cout << left << "[" << i << "] " 
                                 << setw(30) << (l.titulo.length() > 28 ? l.titulo.substr(0, 25) + "..." : l.titulo);
                            
                            if (l.estoque <= 0) {
                                cout << Cor::VERMELHO << "ESGOTADO" << Cor::RESET << endl;
                            } else {
                                cout << Cor::VERDE << l.estoque << Cor::RESET << endl;
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
                    cout << Cor::AMARELO << "[AVISO]: Opção inválida." << Cor::RESET << endl;
                }

            } catch (const ErroBiblioteca& e) {
                cout << e.what() << endl;
            }

        } while (opcao != 4);

        biblioteca.salvarRelatorio();

    } catch (const exception& e) {
        cerr << "\n" << Cor::VERMELHO << Cor::NEGRITO << "FALHA CRÍTICA: " << e.what() << Cor::RESET << endl;
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
       - O namespace Cor:: funciona como um "Dicionário de Estilos", 
         mantendo o código limpo e evitando colisões de nomes.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Temas Dinâmicos: Carregar cores de arquivos de configuração.
    - Suporte ao Windows: O uso de 'virtual terminal sequences'.
    - UX/UI design para DevOps e ferramentas de linha de comando.
    ===============================================================
*/

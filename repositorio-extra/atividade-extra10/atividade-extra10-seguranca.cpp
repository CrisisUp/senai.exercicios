/**
 * @file atividade-extra10-seguranca.cpp
 * @brief Sistema de Histórico com Pilhas e Persistência de Arquivos.
 * 
 * Este programa demonstra o uso da estrutura de dados Pilha (Stack) 
 * para gerenciar eventos e da biblioteca fstream para gravar o 
 * histórico permanentemente em disco.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <stack>    // Estrutura de Pilha
#include <fstream>  // Manipulação de Arquivos
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

// --- 1. Protótipos das Funções ---
void exibirBanner();
string obterHoraAtual();
void salvarHistorico(stack<string> s);

// --- 2. Função Principal ---
int main()
{
    stack<string> historico;
    int opcao;

    exibirBanner();

    do {
        cout << "\n--- MENU DE OPERAÇÕES ---" << endl;
        cout << "[1] Registrar Nova Ação" << endl;
        cout << "[2] Desfazer Última Ação (POP)" << endl;
        cout << "[3] Salvar Histórico e Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;

        if (opcao == 1) {
            string acao;
            cout << "Descreva a ocorrência: ";
            getline(cin >> ws, acao);
            
            // Adicionando na pilha: "HORA | ACAO"
            string registro = obterHoraAtual() + " | " + acao;
            historico.push(registro);
            cout << "[OK]: Registro adicionado ao topo da pilha." << endl;
        } 
        else if (opcao == 2) {
            if (!historico.empty()) {
                cout << "[AVISO]: Removendo: " << historico.top() << endl;
                historico.pop(); // Remove o topo (LIFO)
            } else {
                cout << "[ERRO]: Histórico vazio. Nada para desfazer." << endl;
            }
        }

    } while (opcao != 3);

    // Salvando os dados antes de encerrar
    salvarHistorico(historico);

    return 0;
}

// --- 3. Implementação das Funções ---

/**
 * Captura a hora do sistema para o Log.
 */
string obterHoraAtual() {
    time_t agora = time(0);
    tm *ltm = localtime(&agora);
    char buffer[10];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", ltm);
    return string(buffer);
}

/**
 * Grava o conteúdo da pilha em um arquivo .txt permanente.
 */
void salvarHistorico(stack<string> s) 
{
    // Criando o canal de saída para o arquivo
    ofstream arquivo;
    arquivo.open("repositorio-extra/atividade-extra10/log_seguranca.txt");

    if (arquivo.is_open()) {
        arquivo << "===============================================" << endl;
        arquivo << "       RELATÓRIO DE SEGURANÇA PERMANENTE       " << endl;
        arquivo << "===============================================" << endl;
        
        if (s.empty()) {
            arquivo << "Nenhuma atividade registrada." << endl;
        }

        // Como a pilha é LIFO, os itens saem do último para o primeiro
        while (!s.empty()) {
            arquivo << s.top() << endl;
            s.pop();
        }

        arquivo << "===============================================" << endl;
        arquivo.close(); // Sempre feche o arquivo após usar!
        
        cout << "\n[SUCESSO]: Histórico salvo em 'log_seguranca.txt'!" << endl;
    } else {
        cout << "\n[ERRO]: Não foi possível criar o arquivo de log." << endl;
    }
}

void exibirBanner() {
    cout << "===============================================" << endl;
    cout << "       SISTEMA DE MONITORAMENTO VIGIA 1.0      " << endl;
    cout << "===============================================" << endl;
}

/* 
    ===============================================================
    RESUMO TEÓRICO PARA EXAME FINAL (PILHAS E ARQUIVOS)
    ===============================================================

    1. ESTRUTURA STACK (PILHA):
       - Segue o princípio LIFO (Last In, First Out).
       - push(): Empilha. top(): Olha o topo. pop(): Desempilha.
       - empty(): Verifica se a pilha está vazia.

    2. BIBLIOTECA FSTREAM (ARQUIVOS):
       - ofstream: Para SAÍDA de dados (escrever no HD).
       - .open(): Cria ou abre o arquivo físico.
       - .is_open(): Verifica se o sistema permitiu criar o arquivo.
       - .close(): Libera o arquivo para que outros programas o usem.

    3. PERSISTÊNCIA:
       - Diferente da memória RAM (volátil), o arquivo no disco (HD) 
         mantém os dados mesmo após o programa ser encerrado.

    ===============================================================
    TÓPICOS COMPLEMENTARES PARA O EXAME
    ===============================================================

    A. MODOS DE ABERTURA:
       - ios::app: Abre o arquivo para "adicionar" (append) no final 
         em vez de apagar o conteúdo antigo.

    B. FUNÇÃO strftime():
       - Uma forma profissional e rápida de formatar datas como 
         strings prontas para impressão.
    ===============================================================
*/

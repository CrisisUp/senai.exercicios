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

/**
 * @namespace UI
 * @brief Gerencia as cores e estilos da interface CLI.
 */
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
}

/**
 * @section MemoryMap
 * - Pilha (std::stack): Alocada na Stack Frame da função main.
 * - Heap: Utilizado dinamicamente pelo std::string para armazenar as mensagens de log.
 * - fstream: Buffer de arquivo gerenciado pelo SO, aberto via stack objects.
 */

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
        cout << "\n" << UI::NEGRITO << "--- MENU DE OPERAÇÕES ---" << UI::RESET << endl;
        cout << "[1] Registrar Nova Ação" << endl;
        cout << "[2] Desfazer Última Ação (POP)" << endl;
        cout << "[3] Visualizar Pilha (Preview)" << endl;
        cout << "[4] Salvar Histórico e Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;

        if (opcao == 1) {
            string acao;
            cout << "Descreva a ocorrência: ";
            getline(cin >> ws, acao);
            
            // Adicionando na pilha: "HORA | ACAO"
            string registro = obterHoraAtual() + " | " + acao;
            historico.push(registro);
            cout << UI::VERDE << "[OK]: Registro adicionado ao topo da pilha." << UI::RESET << endl;
        } 
        else if (opcao == 2) {
            if (!historico.empty()) {
                cout << UI::AMARELO << "[AVISO]: Removendo: " << historico.top() << UI::RESET << endl;
                historico.pop(); // Remove o topo (LIFO)
            } else {
                cout << UI::VERMELHO << "[ERRO]: Histórico vazio. Nada para desfazer." << UI::RESET << endl;
            }
        }
        else if (opcao == 3) {
            if (historico.empty()) {
                cout << UI::VERMELHO << "[ERRO]: Nada para exibir." << UI::RESET << endl;
            } else {
                cout << UI::CIANO << "\n--- PREVIEW DO LOG (TOPO PARA BASE) ---" << UI::RESET << endl;
                stack<string> copia = historico; // Copiamos para não destruir a original
                while (!copia.empty()) {
                    // "Fantasma do CPU": Uso de const auto& para evitar cópia desnecessária do objeto string
                    const auto& log = copia.top();
                    cout << " > " << log << endl;
                    copia.pop();
                }
            }
        }

    } while (opcao != 4);

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
            // "Fantasma do CPU": Evitando cópia da string ao referenciá-la diretamente no topo
            const auto& log = s.top();
            arquivo << log << endl;
            s.pop();
        }

        arquivo << "===============================================" << endl;
        arquivo.close(); // Sempre feche o arquivo após usar!
        
        cout << UI::VERDE << "\n[SUCESSO]: Histórico salvo em 'log_seguranca.txt'!" << UI::RESET << endl;
    } else {
        cout << UI::VERMELHO << "\n[ERRO]: Não foi possível criar o arquivo de log." << UI::RESET << endl;
    }
}

void exibirBanner() {
    cout << UI::CIANO << "===============================================" << UI::RESET << endl;
    cout << UI::NEGRITO << "       SISTEMA DE MONITORAMENTO VIGIA 1.0      " << UI::RESET << endl;
    cout << UI::CIANO << "===============================================" << UI::RESET << endl;
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

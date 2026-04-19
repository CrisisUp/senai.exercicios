/**
 * @file atividade-extra11-atendimento.cpp
 * @brief Sistema de Atendimento Clínico (Filas e Leitura de Arquivo).
 * 
 * Este programa demonstra como carregar dados de um arquivo externo para 
 * dentro de uma estrutura de Fila (Queue), respeitando o princípio 
 * FIFO (First In, First Out).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <queue>    // Estrutura de Fila
#include <fstream>  // Leitura de Arquivos
#include <string>
#include <iomanip>

using namespace std;

// --- 1. Protótipos das Funções ---
void exibirBanner();
void carregarPacientes(queue<string> &f);

// --- 2. Função Principal ---
int main()
{
    queue<string> filaAtendimento;
    int opcao;

    exibirBanner();

    // Etapa Inicial: Carregar dados do arquivo para a memória (Fila)
    carregarPacientes(filaAtendimento);

    do {
        cout << "\n--- PAINEL DE CONTROLE DE FILA ---" << endl;
        cout << "Total na fila: " << filaAtendimento.size() << " pacientes." << endl;
        cout << "[1] Adicionar Novo Paciente" << endl;
        cout << "[2] Chamar Próximo (ATENDER)" << endl;
        cout << "[3] Ver Quem é o Próximo (FRONT)" << endl;
        cout << "[4] Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;

        if (opcao == 1) {
            string nome;
            cout << "Nome do Paciente: ";
            getline(cin >> ws, nome);
            filaAtendimento.push(nome);
            cout << "[OK]: " << nome << " entrou no final da fila." << endl;
        } 
        else if (opcao == 2) {
            if (!filaAtendimento.empty()) {
                cout << "[ATENDIMENTO]: Próximo paciente: " 
                     << filaAtendimento.front() << endl;
                filaAtendimento.pop(); // Remove quem estava na frente
            } else {
                cout << "[AVISO]: A fila está vazia!" << endl;
            }
        }
        else if (opcao == 3) {
            if (!filaAtendimento.empty()) {
                cout << "[INFO]: O primeiro da fila é: " 
                     << filaAtendimento.front() << endl;
            } else {
                cout << "[AVISO]: Ninguém aguardando." << endl;
            }
        }

    } while (opcao != 4);

    return 0;
}

// --- 3. Implementação das Funções ---

/**
 * Abre o arquivo pacientes.txt e transfere os nomes para a fila.
 */
void carregarPacientes(queue<string> &f) 
{
    ifstream arquivo;
    string nome;
    
    cout << "\n[SISTEMA]: Carregando lista de espera..." << endl;
    
    arquivo.open("repositorio-extra/atividade-extra11/pacientes.txt");

    if (arquivo.is_open()) {
        // Enquanto o programa conseguir ler uma linha completa...
        while (getline(arquivo, nome)) {
            if (!nome.empty()) {
                f.push(nome); // Adiciona na fila
            }
        }
        arquivo.close();
        cout << "[SUCESSO]: Lista carregada com sucesso!" << endl;
    } else {
        cout << "[AVISO]: Arquivo de pacientes não encontrado. Fila iniciada vazia." << endl;
    }
}

void exibirBanner() {
    cout << "===============================================" << endl;
    cout << "       SISTEMA DE TRIAGEM - CLÍNICA SENAI      " << endl;
    cout << "===============================================" << endl;
}

/* 
    ===============================================================
    RESUMO TEÓRICO PARA EXAME FINAL (FILAS E LEITURA)
    ===============================================================

    1. ESTRUTURA QUEUE (FILA):
       - Segue o princípio FIFO (First In, First Out).
       - push(): Entra no FINAL da fila.
       - front(): Olha quem está na FRENTE (o próximo a sair).
       - pop(): Remove quem está na FRENTE.
       - size(): Retorna quantos itens existem na fila.

    2. BIBLIOTECA IFSTREAM (LEITURA):
       - ifstream: Para ENTRADA de dados (ler do HD para o C++).
       - while(getline(arquivo, variavel)): Loop clássico para ler 
         um arquivo de texto linha por linha até o fim.

    3. PASSAGEM POR REFERÊNCIA (&):
       - Note o '&' em 'queue<string> &f'. Isso é vital! Sem ele, 
         a função carregaria os pacientes em uma "cópia" e a fila 
         da função main continuaria vazia.

    ===============================================================
    TÓPICOS COMPLEMENTARES PARA O EXAME
    ===============================================================

    A. MÉTODO back():
       - O queue também permite olhar quem é o ÚLTIMO da fila 
         através do método .back().

    B. EOF (End of File):
       - O C++ identifica automaticamente quando o arquivo acabou, 
         fazendo com que o loop 'while' encerre sozinho.
    ===============================================================
*/

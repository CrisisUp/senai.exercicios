/**
 * @file atividade-extra11-atendimento.cpp
 * @brief Sistema de Atendimento Clínico (Filas e Leitura de Arquivo).
 * 
 * Versão Refatorada: Agora utilizando Arquitetura Modular (.h e .cpp)
 * seguindo as normas do Nível 11+ do SENAI C++.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 24/04/2026
 */

#include <iostream>
#include <string>
#include "GerenciadorAtendimento.h"

using namespace std;

int main()
{
    GerenciadorAtendimento sistema;
    int opcao;

    GerenciadorAtendimento::exibirBanner();

    try {
        // Etapa Inicial: Carregar dados do arquivo para a memória (Fila)
        sistema.carregarPacientes("repositorio-extra/atividade-extra11/pacientes.txt");
    } catch (const exception& e) {
        cout << UI::VERMELHO << "[ERRO]: " << UI::RESET << e.what() << endl;
        cout << UI::CIANO << "[INFO]: " << UI::RESET << "Iniciando com fila vazia." << endl;
    }

    do {
        try {
            cout << "\n--- PAINEL DE CONTROLE DE FILA ---" << endl;
            cout << "Total na fila: " << sistema.totalFila() << " pacientes." << endl;
            cout << "[1] Adicionar Novo Paciente" << endl;
            cout << "[2] Chamar Próximo (ATENDER)" << endl;
            cout << "[3] Ver Quem é o Próximo (FRONT)" << endl;
            cout << "[4] Sair" << endl;
            cout << "Escolha: ";
            
            if (!(cin >> opcao)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << UI::VERMELHO << "[ERRO]: Entrada inválida!" << UI::RESET << endl;
                continue;
            }

            if (opcao == 1) {
                string nome;
                cout << "Nome do Paciente: ";
                getline(cin >> ws, nome);
                sistema.adicionarPaciente(nome);
            } 
            else if (opcao == 2) {
                string atendido = sistema.atenderProximo();
                cout << UI::CIANO << "[ATENDIMENTO]: " << UI::RESET << "Próximo paciente: " << atendido << endl;
            }
            else if (opcao == 3) {
                const string& proximo = sistema.verProximo();
                cout << UI::CIANO << "[INFO]: " << UI::RESET << "O primeiro da fila é: " << proximo << endl;
            }
        } catch (const exception& e) {
            cout << UI::VERMELHO << e.what() << UI::RESET << endl;
        }

    } while (opcao != 4);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ARQUITETURA MODULAR (Nível 11+)
    ===============================================================

    1. SEPARAÇÃO DE RESPONSABILIDADES:
       - O arquivo .h contém a estrutura da classe (interface).
       - O arquivo .cpp contém a lógica de implementação.
       - O arquivo principal (main) foca no fluxo do usuário.

    2. ENCAPSULAMENTO:
       - A fila 'filaAtendimento' agora é privada, protegida dentro 
         da classe GerenciadorAtendimento.

    3. ESTRUTURA QUEUE (FILA):
       - Segue o princípio FIFO (First In, First Out).
       - push(): Entra no FINAL da fila.
       - front(): Olha quem está na FRENTE (o próximo a sair).
       - pop(): Remove quem está na FRENTE.

    ===============================================================
    ASSUNTOS CORRELATOS
    ===============================================================
    - Include Guards (#ifndef): Evitam múltiplas inclusões do mesmo header.
    - Operador de Escopo (::): Acessa membros de classes e namespaces.
    - Métodos Estáticos (static): Funções que pertencem à classe, não ao objeto.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

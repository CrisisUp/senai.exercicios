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

    // Etapa Inicial: Carregar dados do arquivo para a memória (Fila)
    // Tenta carregar do caminho relativo ao build ou ao root
    sistema.carregarPacientes("repositorio-extra/atividade-extra11/pacientes.txt");

    do {
        cout << "\n--- PAINEL DE CONTROLE DE FILA ---" << endl;
        cout << "Total na fila: " << sistema.totalFila() << " pacientes." << endl;
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
            sistema.adicionarPaciente(nome);
        } 
        else if (opcao == 2) {
            string atendido = sistema.atenderProximo();
            if (!atendido.empty()) {
                cout << "[ATENDIMENTO]: Próximo paciente: " << atendido << endl;
            } else {
                cout << "[AVISO]: A fila está vazia!" << endl;
            }
        }
        else if (opcao == 3) {
            string proximo = sistema.verProximo();
            if (!proximo.empty()) {
                cout << "[INFO]: O primeiro da fila é: " << proximo << endl;
            } else {
                cout << "[AVISO]: Ninguém aguardando." << endl;
            }
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

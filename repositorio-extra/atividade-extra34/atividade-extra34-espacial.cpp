/**
 * @file atividade-extra34-espacial.cpp
 * @brief Exploração Espacial: Implementação Manual de Lista Encadeada.
 * 
 * Demonstra como criar e gerenciar uma estrutura de dados dinâmica do zero,
 * utilizando alocação de memória manual (new/delete) e encadeamento por ponteiros.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string CIANO    = "\033[36m";
    const string AMARELO  = "\033[33m";
    const string ROXO     = "\033[35m";
}

// --- 2. O NÓ (DADO + PONTEIRO) ---

struct TelemetriaNode {
    int id;
    string mensagem;
    TelemetriaNode* proximo; // O elo da corrente

    TelemetriaNode(int _id, string _msg) : id(_id), mensagem(_msg), proximo(nullptr) {}
};

// --- 3. A LISTA (GERENCIADORA DA MEMÓRIA) ---

class BufferEspacial {
private:
    TelemetriaNode* cabeca; // Início da lista

public:
    BufferEspacial() : cabeca(nullptr) {}

    /**
     * @brief Insere um novo nó no início da lista (O(1)).
     */
    void receberDados(int id, string msg) {
        TelemetriaNode* novo = new TelemetriaNode(id, msg);
        novo->proximo = cabeca;
        cabeca = novo;
        cout << UI::VERDE << "[SISTEMA]: Pacote " << id << " acoplado ao buffer." << UI::RESET << endl;
    }

    /**
     * @brief Percorre a lista exibindo os dados de cada nó.
     */
    void transmitirRelatorio() const {
        cout << UI::CIANO << "\n--- TRANSMISSÃO DE TELEMETRIA ESPACIAL ---" << UI::RESET << endl;
        TelemetriaNode* atual = cabeca;

        if (!atual) {
            cout << "(Buffer vazio)" << endl;
            return;
        }

        while (atual != nullptr) {
            cout << "[ID: " << atual->id << "] Mensagem: " << UI::AMARELO << atual->mensagem << UI::RESET << endl;
            atual = atual->proximo; // Pula para o próximo endereço de memória
        }
        cout << "--- FIM DA TRANSMISSÃO ---" << endl;
    }

    /**
     * @brief Destrutor: Limpa toda a memória alocada manualmente.
     * Crucial para evitar Memory Leaks.
     */
    ~BufferEspacial() {
        cout << UI::ROXO << "\n[LIMPEZA]: Desalocando memória do buffer..." << UI::RESET << endl;
        TelemetriaNode* atual = cabeca;
        while (atual != nullptr) {
            TelemetriaNode* temp = atual;
            atual = atual->proximo;
            delete temp; // Libera o nó atual
        }
        cout << "[OK]: Memória RAM totalmente liberada." << endl;
    }
};

// --- 4. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << UI::CIANO << "===============================================" << endl;
    cout << "      VOYAGER CORE: SISTEMA DE DADOS v1.0      " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Criando a lista manual
    BufferEspacial voyagerBuffer;

    // Recebendo dados aleatórios do espaço
    voyagerBuffer.receberDados(101, "Radiação solar detectada.");
    voyagerBuffer.receberDados(102, "Foto da lua de Júpiter processada.");
    voyagerBuffer.receberDados(103, "Anomalia magnética no setor 7.");

    // Visualizando o encadeamento
    voyagerBuffer.transmitirRelatorio();

    /* 
       DICA DIDÁTICA:
       Note que, como inserimos no INÍCIO, os dados aparecem em ordem 
       INVERSA à chegada. Isso é uma característica da inserção O(1).
    */

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: LISTA ENCADEADA MANUAL
    ===============================================================

    1. ALOCAÇÃO DINÂMICA (new):
       - Diferente do 'vector', onde os dados estão lado a lado na 
         memória, aqui cada nó pode estar em qualquer lugar da RAM. 
         O que os une é o endereço guardado no ponteiro 'proximo'.

    2. CUSTO DE INSERÇÃO:
       - Inserir no início de uma lista encadeada é O(1) (constante). 
         É muito mais rápido que inserir no início de um vector, 
         que exigiria mover todos os outros elementos.

    3. O PERIGO DO MEMORY LEAK:
       - Como usamos 'new' para cada nó, se perdermos o ponteiro da 
         cabeça sem dar 'delete' nos nós, aquela memória fica "presa" 
         até o computador ser reiniciado. O Destrutor é vital aqui.

    4. NAVEGAÇÃO POR PONTEIROS:
       - Aprendemos a usar o loop 'while (atual != nullptr)'. É a 
         forma mais pura de percorrer estruturas de dados.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Lista Duplamente Encadeada (Anterior e Próximo).
    - Complexidade Algorítmica (Big O notation).
    - Smart Pointers (unique_ptr) para automação de listas.
    ===============================================================
*/

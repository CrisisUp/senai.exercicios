/**
 * @file atividade-extra36-logistica.cpp
 * @brief Logística Aeroportuária: Pilha e Fila Manuais.
 * 
 * Demonstra a implementação e as diferenças entre LIFO (Pilha) e FIFO (Fila),
 * sem o uso da STL, focando no gerenciamento manual de nós e ponteiros.
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
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string VERMELHO = "\033[31m";
}

// --- 2. O NÓ GENÉRICO PARA AMBAS AS ESTRUTURAS ---

struct Node {
    string dado;
    Node* proximo;
    Node(string d) : dado(d), proximo(nullptr) {}
};

// --- 3. PILHA MANUAL (LIFO - Last-In, First-Out) ---

class StackBagagens {
private:
    Node* topo;
public:
    StackBagagens() : topo(nullptr) {}

    void empilhar(string mala) {
        Node* novo = new Node(mala);
        novo->proximo = topo;
        topo = novo;
        cout << UI::VERDE << "[PILHA]: " << mala << " colocada no topo." << UI::RESET << endl;
    }

    void desempilhar() {
        if (!topo) {
            cout << UI::AMARELO << "[PILHA]: Compartimento vazio." << UI::RESET << endl;
            return;
        }
        Node* temp = topo;
        cout << UI::VERMELHO << "[PILHA]: Retirando " << temp->dado << " (LIFO)." << UI::RESET << endl;
        topo = topo->proximo;
        delete temp;
    }

    ~StackBagagens() {
        while (topo) desempilhar();
    }
};

// --- 4. FILA MANUAL (FIFO - First-In, First-Out) ---

class QueueDecolagem {
private:
    Node* inicio;
    Node* fim;
public:
    QueueDecolagem() : inicio(nullptr), fim(nullptr) {}

    void entrarNaFila(string aviao) {
        Node* novo = new Node(aviao);
        if (!inicio) {
            inicio = fim = novo;
        } else {
            fim->proximo = novo;
            fim = novo;
        }
        cout << UI::CIANO << "[FILA]: " << aviao << " entrou na pista de táxi." << UI::RESET << endl;
    }

    void decolar() {
        if (!inicio) {
            cout << UI::AMARELO << "[FILA]: Nenhum avião na fila." << UI::RESET << endl;
            return;
        }
        Node* temp = inicio;
        cout << UI::VERDE << "[FILA]: Avião " << temp->dado << " DECOLANDO (FIFO)!" << UI::RESET << endl;
        inicio = inicio->proximo;
        if (!inicio) fim = nullptr;
        delete temp;
    }

    ~QueueDecolagem() {
        while (inicio) decolar();
    }
};

// --- 5. FUNÇÃO PRINCIPAL ---

int main()
{
    StackBagagens malas;
    QueueDecolagem pista;

    cout << UI::CIANO << "===============================================" << endl;
    cout << "      G-WING LOGISTICS: PÁTIO DE OPERAÇÕES     " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Simulação 1: Gerindo Bagagens (Pilha)
    cout << "\n--- OPERAÇÃO DE CARREGAMENTO (MALA DIRETA) ---" << endl;
    malas.empilhar("Mala Azul");
    malas.empilhar("Maleta Executiva");
    malas.empilhar("Mochila Verde");
    
    malas.desempilhar(); // Deve sair a Mochila Verde (última que entrou)

    // Simulação 2: Gerindo Fila de Pista (Fila)
    cout << "\n--- OPERAÇÃO DE PISTA (TORRE DE CONTROLE) ---" << endl;
    pista.entrarNaFila("LATAM 442");
    pista.entrarNaFila("GOL 108");
    pista.entrarNaFila("AZUL 99");

    pista.decolar(); // Deve sair o LATAM 442 (primeiro que entrou)
    pista.decolar();

    cout << "\n[SISTEMA]: Operações concluídas. Limpando memória..." << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: PILHA (STACK) VS FILA (QUEUE)
    ===============================================================

    1. LÓGICA LIFO (Pilha):
       - Last-In, First-Out. O último a chegar é o primeiro a sair. 
         É como uma pilha de pratos. Útil para: Botão Desfazer, 
         Chamadas de Funções (Call Stack), Navegação 'Voltar'.

    2. LÓGICA FIFO (Fila):
       - First-In, First-Out. O primeiro a chegar é o primeiro a ser 
         atendido. É como uma fila de banco. Útil para: 
         Impressão de documentos, Buffers de rede, Processamento 
         em ordem cronológica.

    3. MANIPULAÇÃO DE PONTEIROS:
       - Na Fila, o ponteiro de 'fim' (Tail) é essencial para que a 
         inserção seja rápida (O(1)). Sem ele, teríamos que 
         atravessar toda a fila para achar o lugar de inserir.

    4. GESTÃO DE MEMÓRIA:
       - Vimos que a lógica de exclusão (delete) é idêntica para 
         ambas: remover o nó e ajustar o ponteiro para o próximo, 
         evitando deixar memória "órfã".

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Fila de Prioridade (Priority Queue).
    - Deque (Double-ended Queue): Fila que permite entrar/sair por 
      ambos os lados.
    - Stack Overflow: Quando a pilha de memória estoura.
    ===============================================================
*/

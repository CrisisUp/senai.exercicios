/**
 * @file atividade-extra36-logistica.cpp
 * @brief G-Wing Logistics: Engenharia de Pilhas e Filas Manuais.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a implementação de baixo nível de LIFO e FIFO para missões críticas.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Stack & Queue Manual)
 * - Pilha: Gerencia um único ponteiro 'topo' na STACK. Novos nós na HEAP.
 * - Fila: Gerencia 'inicio' e 'fim' na STACK (16 bytes). Nós na HEAP.
 * - Eficiência: Inserção e Remoção em O(1) para ambas as estruturas.
 * - RAII: Destrutores garantem que nenhum nó zumbi permaneça na HEAP após o uso.
 */

#include <iostream>
#include <string>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string VERMELHO = "\033[31m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. O NÓ DE DADOS (BASE ARQUITETURAL) ---

/**
 * @struct Node
 * @brief Container atômico de informação e link de encadeamento.
 */
struct Node {
    string dado;
    Node* proximo;
    Node(const string& d) : dado(d), proximo(nullptr) {}
};

// --- 3. PILHA DE BAGAGENS (LIFO CORE) ---

/**
 * @class StackBagagens
 * @brief Gerencia o carregamento de bagagens (Last-In, First-Out).
 */
class StackBagagens {
private:
    Node* topo;
public:
    StackBagagens() : topo(nullptr) {}

    /**
     * @brief Empilha item no topo (O(1)).
     */
    void empilhar(const string& mala) {
        Node* novo = new Node(mala);
        novo->proximo = topo;
        topo = novo;
        cout << UI::VERDE << "[LIFO PUSH]: " << UI::RESET << mala << " adicionada ao topo da pilha." << endl;
    }

    /**
     * @brief Desempilha o item do topo (O(1)).
     */
    void desempilhar() {
        if (!topo) {
            cout << UI::AMARELO << "[LIFO AVISO]: Compartimento de carga vazio." << UI::RESET << endl;
            return;
        }
        Node* temp = topo;
        cout << UI::VERMELHO << "[LIFO POP]: " << UI::RESET << "Retirando " << temp->dado << " do avião." << endl;
        topo = topo->proximo;
        delete temp;
    }

    ~StackBagagens() {
        while (topo) desempilhar();
    }
};

// --- 4. FILA DE PISTA (FIFO CORE) ---

/**
 * @class QueueDecolagem
 * @brief Gerencia a fila de aeronaves na pista (First-In, First-Out).
 */
class QueueDecolagem {
private:
    Node* inicio;
    Node* fim;
public:
    QueueDecolagem() : inicio(nullptr), fim(nullptr) {}

    /**
     * @brief Insere no final da fila (O(1) via Tail Pointer).
     */
    void entrarNaFila(const string& aviao) {
        Node* novo = new Node(aviao);
        if (!inicio) {
            inicio = fim = novo;
        } else {
            fim->proximo = novo;
            fim = novo;
        }
        cout << UI::CIANO << "[FIFO ENQUEUE]: " << UI::RESET << aviao << " em posição de táxi." << endl;
    }

    /**
     * @brief Remove do início da fila (O(1) via Head Pointer).
     */
    void decolar() {
        if (!inicio) {
            cout << UI::AMARELO << "[FIFO AVISO]: Torre informa: Fila de decolagem vazia." << UI::RESET << endl;
            return;
        }
        Node* temp = inicio;
        cout << UI::VERDE << UI::NEGRITO << "[FIFO DEQUEUE]: " << UI::RESET 
             << "Autorizada decolagem imediata para " << UI::NEGRITO << temp->dado << UI::RESET << "!" << endl;
        
        inicio = inicio->proximo;
        if (!inicio) fim = nullptr; // Reset total se a fila esvaziar
        delete temp;
    }

    ~QueueDecolagem() {
        while (inicio) decolar();
    }
};

// --- 5. EXECUÇÃO DO CENTRO LOGÍSTICO ---

int main()
{
    UI::limparTela();
    StackBagagens setorCarga;
    QueueDecolagem pistaSul;

    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-WING LOGISTICS: PÁTIO DE OPERAÇÕES v2.0" << endl;
    cout << "       (Elite Data Structures Control)         " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // --- OPERAÇÃO 1: CARREGAMENTO LIFO ---
    cout << "\n" << UI::BRANCO << "FASE A: PROCESSAMENTO DE BAGAGENS (LIFO)" << UI::RESET << endl;
    setorCarga.empilhar("Mala_Executiva_001");
    setorCarga.empilhar("Case_Equipamento_X");
    setorCarga.empilhar("Mochila_Pessoal_Alpha");
    
    setorCarga.desempilhar(); // Remove a última (Mochila Alpha)

    // --- OPERAÇÃO 2: FLUXO DE PISTA FIFO ---
    cout << "\n" << UI::BRANCO << "FASE B: GESTÃO DE TRÁFEGO AÉREO (FIFO)" << UI::RESET << endl;
    pistaSul.entrarNaFila("LATAM-442");
    pistaSul.entrarNaFila("GOL-108");
    pistaSul.entrarNaFila("AZUL-99");

    pistaSul.decolar(); // Decola o primeiro (LATAM-442)
    pistaSul.decolar();

    cout << "\n" << UI::VERDE << UI::NEGRITO << "Logística de solo finalizada. Sincronizando memória..." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ESTRUTURAS SEQUENCIAIS MANUAIS
    ===============================================================

    1. PILHA (STACK - LIFO):
       - O último dado que entra é o primeiro a sair. É a base das 
         chamadas de sistema. Cada função que você chama no C++ é 
         \"empilhada\" na Stack de memória do processador.

    2. FILA (QUEUE - FIFO):
       - O primeiro que chega é o primeiro que sai. Essencial para 
         agendadores de tarefas (Schedulers) e sistemas de mensageria 
         onde a ordem cronológica deve ser preservada.

    3. OTIMIZAÇÃO DO TAIL POINTER (FILA):
       - Note que sem o ponteiro 'fim', a inserção na fila seria 
         O(n). Com ele, saltamos diretamente para o final da 
         corrente, mantendo a performance O(1).

    4. PROTEÇÃO FANTASMA DO CPU:
       - Parâmetros como 'const string& d' evitam a clonagem de 
         strings na transição entre as funções de interface e a 
         criação física do nó na HEAP.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Priority Queues (Filas com Peso).
    - Circular Buffers: Usados em processamento de áudio digital.
    - Lock-free Data Structures: Pilhas e Filas para Multiprocessamento.
    ===============================================================
*/

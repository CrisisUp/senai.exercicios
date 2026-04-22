/**
 * @file atividade-extra34-espacial.cpp
 * @brief Voyager Core: Engenharia de Estruturas Dinâmicas (Linked List).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Implementação manual de lista encadeada para máxima eficiência em memória.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Linked Chain)
 * - Cabeça (TelemetriaNode*): Um único ponteiro na STACK (8 bytes).
 * - Nós da Lista: Espalhados de forma não-contígua na HEAP.
 * - Cada Nó: Contém dados (int + string) e o endereço do próximo (ponteiro).
 * - Diferencial: Ocupa apenas o necessário por item, mas perde localidade de cache.
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
    const string ROXO     = "\033[35m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. O NÓ (DADO + PONTEIRO) ---

/**
 * @struct TelemetriaNode
 * @brief Elo fundamental da corrente de dados espaciais.
 */
struct TelemetriaNode {
    int id;
    string mensagem;
    TelemetriaNode* proximo; // O elo para o próximo endereço na HEAP

    TelemetriaNode(int _id, const string& _msg) 
        : id(_id), mensagem(_msg), proximo(nullptr) {}
};

// --- 3. A LISTA (GERENCIADORA DE MEMÓRIA DE ELITE) ---

class BufferEspacial {
private:
    TelemetriaNode* cabeca; // Ponto de entrada da estrutura

public:
    BufferEspacial() : cabeca(nullptr) {}

    /**
     * @brief Inserção O(1) no início da lista.
     * @param id Identificador do pacote.
     * @param msg Referência constante (Fantasma do CPU).
     */
    void receberDados(int id, const string& msg) {
        TelemetriaNode* novo = new TelemetriaNode(id, msg);
        novo->proximo = cabeca;
        cabeca = novo;
        cout << UI::VERDE << "[SISTEMA]: " << UI::RESET << "Pacote " << id << " acoplado ao buffer (Stack Entry)." << endl;
    }

    /**
     * @brief Percurso linear da lista via indereçamento indireto.
     */
    void transmitirRelatorio() const {
        cout << "\n" << UI::CIANO << UI::NEGRITO << "--- TRANSMISSÃO DE TELEMETRIA: VOYAGER ENGINE ---" << UI::RESET << endl;
        TelemetriaNode* atual = cabeca;

        if (!atual) {
            cout << UI::AMARELO << "[AVISO]: Buffer de telemetria vazio." << UI::RESET << endl;
            return;
        }

        while (atual != nullptr) {
            cout << UI::BRANCO << "[PKG " << atual->id << "]: " << UI::RESET 
                 << UI::AMARELO << atual->mensagem << UI::RESET << endl;
            atual = atual->proximo; // Pulo para o próximo bloco na HEAP
        }
        cout << UI::CIANO << UI::NEGRITO << "-----------------------------------------------" << UI::RESET << endl;
    }

    /**
     * @brief Destrutor Industrial: Evita Memory Leaks via limpeza iterativa.
     */
    ~BufferEspacial() {
        cout << "\n" << UI::ROXO << "[LIMPEZA]: Iniciando purga de memória do satélite..." << UI::RESET << endl;
        int nosLimpos = 0;
        TelemetriaNode* atual = cabeca;
        
        while (atual != nullptr) {
            TelemetriaNode* temp = atual;
            atual = atual->proximo;
            delete temp; // Liberação física na HEAP
            nosLimpos++;
        }
        cabeca = nullptr;
        cout << UI::VERDE << "[OK]: " << nosLimpos << " blocos de memória purgados com sucesso." << UI::RESET << endl;
    }
};

// --- 4. EXECUÇÃO DO NÚCLEO VOYAGER ---

int main()
{
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      VOYAGER CORE: SISTEMA DE DADOS v2.0      " << endl;
    cout << "       (Elite Linked-Data Architecture)        " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Buffer instanciado na STACK (RAII pattern)
    BufferEspacial voyagerBuffer;

    // Simulação de telemetria recebida em tempo real
    voyagerBuffer.receberDados(101, "Radiação solar detectada (Setor Alpha).");
    voyagerBuffer.receberDados(102, "Análise espectral de Europa concluída.");
    voyagerBuffer.receberDados(103, "Variação gravitacional: +0.02 G.");
    voyagerBuffer.receberDados(104, "Check-list de propulsão: Estável.");

    // Transmissão consolidada
    voyagerBuffer.transmitirRelatorio();

    /* 
       DICA DIDÁTICA DE ENGENHARIA:
       Ao usar Lista Encadeada, temos flexibilidade total. Poderíamos 
       adicionar milhões de pacotes sem nunca precisar realocar ou 
       copiar a memória anterior (diferente do vector).
    */

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ESTRUTURAS DINÂMICAS MANUAIS
    ===============================================================

    1. ANATOMIA DO PONTEIRO 'PRÓXIMO':
       - É o "fio" que une a lista. Sem ele, a memória HEAP estaria 
         cheia de dados órfãos. Gerenciar esse ponteiro manualmente 
         é a forma mais pura de programação de sistemas.

    2. CUSTO O(1) vs O(n):
       - Adicionar no início é O(1). Buscar um item pelo ID, porém, 
         exige percorrer toda a corrente (O(n)). Em sistemas 
         espaciais, a velocidade de gravação costuma ser mais vital 
         que a de busca.

    3. PROTEÇÃO CONTRA VAZAMENTOS:
       - O C++ não tem Garbage Collector automático. Se o satélite 
         esquecer de deletar um nó, a memória "morre" e a missão 
         falha por falta de recursos (System Hang). O Destrutor é o 
         zelador da memória.

    4. PASSAGEM POR REFERÊNCIA (ELITE):
       - As mensagens de texto são passadas por 'const string&', 
         evitando cópias temporárias entre a função de recebimento 
         e a criação do nó na HEAP.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Double Linked Lists (Lista Dupla): Navegação para frente e trás.
    - Stack & Queue (Pilha e Fila): Implementadas via Lista Encadeada.
    - Pointer Arithmetic: Manipulando endereços de memória diretamente.
    ===============================================================
*/

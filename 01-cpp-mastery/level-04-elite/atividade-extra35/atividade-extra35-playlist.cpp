/**
 * @file atividade-extra35-playlist.cpp
 * @brief G-Stream Player: Engenharia de Listas Duplamente Encadeadas.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Implementa navegação bidirecional e gestão de memória industrial.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Double Link Layout)
 * - Cabeça & Cauda: Dois ponteiros na STACK (16 bytes totais).
 * - Cursor 'atual': Ponteiro na STACK rastreando o nó ativo na HEAP.
 * - Nós (MusicaNode): Alocados de forma não-contígua na HEAP.
 * - Elo Duplo: Cada nó consome 16 bytes apenas em ponteiros (prev + next), 
 *   além das strings de título e artista.
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. O NÓ DUPLO (ESTRUTURA DE DADOS) ---

/**
 * @struct MusicaNode
 * @brief Representação atômica de uma faixa na memória com elos bidirecionais.
 */
struct MusicaNode {
    string titulo;
    string artista;
    MusicaNode* proximo;
    MusicaNode* anterior;

    MusicaNode(const string& t, const string& a) 
        : titulo(t), artista(a), proximo(nullptr), anterior(nullptr) {}
};

// --- 3. A PLAYLIST (CONTROLADOR DE ELITE) ---

class Playlist {
private:
    MusicaNode* cabeca; // Start point
    MusicaNode* cauda;  // End point (O(1) insertion)
    MusicaNode* atual;  // Cursor de áudio

public:
    Playlist() : cabeca(nullptr), cauda(nullptr), atual(nullptr) {}

    /**
     * @brief Adiciona faixa ao final da lista com complexidade O(1).
     * @param t Título (const ref).
     * @param a Artista (const ref).
     */
    void adicionarMusica(const string& t, const string& a) {
        MusicaNode* novo = new MusicaNode(t, a);
        
        if (cabeca == nullptr) {
            cabeca = cauda = atual = novo;
        } else {
            cauda->proximo = novo;
            novo->anterior = cauda;
            cauda = novo;
        }
        cout << UI::VERDE << "[SISTEMA]: " << UI::RESET << "'" << t << "' indexada ao Stream Cache." << endl;
    }

    /**
     * @brief Avança o cursor para a próxima faixa via ponteiro 'proximo'.
     */
    void proxima() {
        if (atual && atual->proximo) {
            atual = atual->proximo;
            cout << UI::AZUL << "[STREAMING]: Transição de faixa concluída." << UI::RESET << endl;
        } else {
            cout << UI::AMARELO << UI::NEGRITO << "[AVISO]: Fim da playlist alcançado." << UI::RESET << endl;
        }
    }

    /**
     * @brief Retrocede o cursor via ponteiro 'anterior' (O diferencial da lista dupla).
     */
    void anterior() {
        if (atual && atual->anterior) {
            atual = atual->anterior;
            cout << UI::AZUL << "[STREAMING]: Retornando à faixa anterior." << UI::RESET << endl;
        } else {
            cout << UI::AMARELO << UI::NEGRITO << "[AVISO]: Início da playlist alcançado." << UI::RESET << endl;
        }
    }

    /**
     * @brief Renderiza telemetria de reprodução.
     */
    void exibirStatus() const {
        if (!atual) {
            cout << UI::AMARELO << "\n(Nenhuma faixa em reprodução)" << UI::RESET << endl;
            return;
        }
        cout << "\n" << UI::CIANO << UI::NEGRITO << "===============================================" << UI::RESET << endl;
        cout << UI::RESET << "   PLAYING: " << UI::RESET << UI::NEGRITO << atual->titulo << UI::RESET << endl;
        cout << UI::RESET << "   ARTIST : " << UI::RESET << atual->artista << endl;
        cout << UI::CIANO << UI::NEGRITO << "===============================================" << UI::RESET << endl;
    }

    /**
     * @brief Exibe a trilha de ponteiros do fim ao início.
     */
    void exibirFilaReversa() const {
        cout << "\n" << UI::NEGRITO << "TRACE: NAVEGAÇÃO REVERSA (TAIL TO HEAD):" << UI::RESET << endl;
        MusicaNode* p = cauda;
        while (p != nullptr) {
            cout << UI::AMARELO << " <- " << UI::RESET << p->titulo;
            p = p->anterior; // Caminhada via Back-Pointer
        }
        cout << endl;
    }

    /**
     * @brief Destrutor Linear: Garante purga completa da HEAP.
     */
    ~Playlist() {
        cout << "\n" << UI::CIANO << "[LIMPEZA]: Desalocando biblioteca de mídia..." << UI::RESET << endl;
        MusicaNode* p = cabeca;
        int count = 0;
        while (p != nullptr) {
            MusicaNode* temp = p;
            p = p->proximo;
            delete temp;
            count++;
        }
        cout << UI::VERDE << "[OK]: " << count << " faixas purgadas da RAM." << UI::RESET << endl;
    }
};

// --- 4. EXECUÇÃO DO PLAYER ---

int main()
{
    UI::limparTela();
    Playlist player;

    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-STREAM PLAYER: ELITE AUDIO CORE        " << endl;
    cout << "       (Double-Linked Data Architecture)       " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // População da estrutura dinâmica
    player.adicionarMusica("Bohemian Rhapsody", "Queen");
    player.adicionarMusica("Imagine", "John Lennon");
    player.adicionarMusica("Hotel California", "Eagles");
    player.adicionarMusica("Comfortably Numb", "Pink Floyd");

    int opt = 0;
    do {
        player.exibirStatus();
        cout << UI::RESET << "[1] Next  [2] Prev  [3] Trace Map  [4] Shutdown" << UI::RESET << endl;
        cout << "Action: ";
        if (!(cin >> opt)) break;

        switch (opt) {
            case 1: player.proxima(); break;
            case 2: player.anterior(); break;
            case 3: player.exibirFilaReversa(); break;
            case 4: cout << UI::VERMELHO << "Shutting down audio engine..." << UI::RESET << endl; break;
        }

    } while (opt != 4);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: LISTAS DUPLAMENTE ENCADEADAS
    ===============================================================

    1. O CUSTO DA NAVEGAÇÃO:
       - Em uma lista simples, retroceder um item é O(n). Na lista 
         dupla, o ponteiro 'anterior' reduz esse custo para O(1). 
         É o padrão industrial para navegação de UI e histórico.

    2. PONTEIRO DE CAUDA (TAIL):
       - Ao manter 'cauda', a inserção no final não depende de 
         percorrer a lista. Isso é vital para playlists ou logs, 
         onde sempre adicionamos dados ao final da coleção.

    3. PROTEÇÃO FANTASMA DO CPU:
       - Note o uso intensivo de ponteiros constantes no loop de 
         exibição e referências constantes na criação. Manipulamos 
         apenas endereços (8 bytes), nunca clonamos os dados da 
         mídia.

    4. RESILIÊNCIA DE PONTEIROS:
       - A complexidade da lista dupla está na atualização de 
         endereços. Cada nó inserido requer 4 atribuições de 
         ponteiros para manter a integridade bidirecional da cadeia.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Circular Doubly Linked Lists (Loop de Playlist).
    - Skip Lists: Melhorando a busca em listas encadeadas.
    - Sentinel Nodes: Simplificando o código de inserção/emoção.
    ===============================================================
*/

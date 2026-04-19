/**
 * @file atividade-extra35-playlist.cpp
 * @brief Player de Música: Implementação de Lista Duplamente Encadeada.
 * 
 * Demonstra a navegação bidirecional em estruturas de dados, permitindo
 * caminhar para o próximo nó ou retornar ao anterior de forma eficiente.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string AMARELO  = "\033[33m";
    const string NEGRITO  = "\033[1m";
}

// --- 2. O NÓ DUPLO (DADO + 2 PONTEIROS) ---

struct MusicaNode {
    string titulo;
    string artista;
    MusicaNode* proximo;
    MusicaNode* anterior;

    MusicaNode(string t, string a) 
        : titulo(t), artista(a), proximo(nullptr), anterior(nullptr) {}
};

// --- 3. A PLAYLIST (ESTRUTURA DUPLA) ---

class Playlist {
private:
    MusicaNode* cabeca; // Primeiro da lista
    MusicaNode* cauda;  // Último da lista
    MusicaNode* atual;  // Cursor de reprodução

public:
    Playlist() : cabeca(nullptr), cauda(nullptr), atual(nullptr) {}

    /**
     * @brief Adiciona uma música no final da playlist (O(1) graças à cauda).
     */
    void adicionarMusica(string t, string a) {
        MusicaNode* novo = new MusicaNode(t, a);
        
        if (cabeca == nullptr) {
            cabeca = cauda = atual = novo;
        } else {
            cauda->proximo = novo;
            novo->anterior = cauda;
            cauda = novo;
        }
        cout << UI::VERDE << "[OK]: '" << t << "' adicionada à fila." << UI::RESET << endl;
    }

    void proxima() {
        if (atual && atual->proximo) {
            atual = atual->proximo;
            cout << UI::AZUL << "[PLAY]: " << atual->titulo << " - " << atual->artista << UI::RESET << endl;
        } else {
            cout << UI::AMARELO << "[FIM]: Você já está na última música." << UI::RESET << endl;
        }
    }

    void anterior() {
        if (atual && atual->anterior) {
            atual = atual->anterior;
            cout << UI::AZUL << "[PLAY]: " << atual->titulo << " - " << atual->artista << UI::RESET << endl;
        } else {
            cout << UI::AMARELO << "[INÍCIO]: Você já está na primeira música." << UI::RESET << endl;
        }
    }

    void exibirStatus() const {
        if (!atual) return;
        cout << "\n" << UI::CIANO << "===============================================" << endl;
        cout << "   TOCANDO AGORA: " << UI::NEGRITO << atual->titulo << UI::RESET << endl;
        cout << "   ARTISTA: " << atual->artista << endl;
        cout << "===============================================" << UI::RESET << endl;
    }

    /**
     * @brief Percorre do fim para o início (Prova da lista dupla).
     */
    void exibirFilaReversa() const {
        cout << "\n--- FILA DE REPRODUÇÃO (ORDEM INVERSA) ---" << endl;
        MusicaNode* p = cauda;
        while (p != nullptr) {
            cout << " <- " << p->titulo;
            p = p->anterior;
        }
        cout << endl;
    }

    ~Playlist() {
        MusicaNode* p = cabeca;
        while (p != nullptr) {
            MusicaNode* temp = p;
            p = p->proximo;
            delete temp;
        }
    }
};

// --- 4. FUNÇÃO PRINCIPAL ---

int main()
{
    Playlist minhaLista;

    cout << UI::CIANO << "===============================================" << endl;
    cout << "      G-STREAM PLAYER: LISTA DINÂMICA v1.0     " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Montando a playlist
    minhaLista.adicionarMusica("Bohemian Rhapsody", "Queen");
    minhaLista.adicionarMusica("Imagine", "John Lennon");
    minhaLista.adicionarMusica("Hotel California", "Eagles");
    minhaLista.adicionarMusica("Comfortably Numb", "Pink Floyd");

    int opcao = 0;
    do {
        minhaLista.exibirStatus();
        cout << "[1] Próxima  [2] Anterior  [3] Ver Fila Reversa  [4] Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1: minhaLista.proxima(); break;
            case 2: minhaLista.anterior(); break;
            case 3: minhaLista.exibirFilaReversa(); system("sleep 2"); break;
        }

    } while (opcao != 4);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: LISTA DUPLAMENTE ENCADEADA
    ===============================================================

    1. O PODER DOS DOIS PONTEIROS:
       - Cada nó agora tem consciência de quem vem antes e de quem 
         vem depois. Isso permite que a navegação seja 
         bidirecional, algo vital para Players, Navegadores Web 
         (Botão Voltar/Avançar) e Editores de Texto.

    2. PONTEIRO DE CAUDA (Tail):
       - Manter uma referência para o último nó torna a inserção 
         no final da lista uma operação O(1). Sem a cauda, 
         teríamos que percorrer a lista toda só para achar o 
         lugar de inserir a nova música.

    3. COMPLEXIDADE DE MANIPULAÇÃO:
       - Embora mais poderosa, a lista dupla exige mais cuidado: 
         ao inserir ou remover um nó, você precisa atualizar 4 
         ponteiros em vez de 2, para não quebrar a corrente.

    4. APLICAÇÕES REAIS:
       - Histórico de Navegação, Algoritmos de Cache (LRU), e 
         qualquer sistema que exija o conceito de "Desfazer/Refazer" 
         (Undo/Redo).

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Lista Circular (O último aponta para o primeiro).
    - Iteradores Bidirecionais da STL.
    - Estruturas de Dados Persistentes.
    ===============================================================
*/

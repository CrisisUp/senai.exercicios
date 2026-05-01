/**
 * @file atividade-extra47-invaders.cpp
 * @brief G-INVADERS: Motor de Jogo Profissional e Gestão RAII.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Integração Final: Delta Time, Raw Input, Grid Render e Smart Pointers.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Smart Pointer Ownership)
 * - unique_ptr<Player>: Objeto mestre na HEAP, posse única garantida.
 * - vector<unique_ptr<Alien>>: Vetor na STACK, lista de Smart Pointers na HEAP.
 * - Destruição Automática: Quando uma entidade é removida do vetor, o unique_ptr 
 *   aciona 'delete' automaticamente. Sem risco de Memory Leak.
 * - Screen Buffer: Matriz 2D contígua na HEAP (O(LxA)).
 */

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <memory>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI ENGINE) ---

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
    inline void moverCursor(int x, int y) { cout << "\033[" << y << ";" << x << "H"; }
    inline void limparTela() { cout << "\033[2J\033[H"; }
    inline void ocultarCursor() { cout << "\033[?25l"; }
    inline void mostrarCursor() { cout << "\033[?25h"; }
}

// --- 2. ASYNC INPUT HANDLER (RAW MODE) ---

class Input {
private:
    struct termios original;
public:
    Input() {
        tcgetattr(STDIN_FILENO, &original);
        struct termios raw = original;
        raw.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    }
    char get() { char ch; if (read(STDIN_FILENO, &ch, 1) > 0) return ch; return 0; }
    ~Input() { tcsetattr(STDIN_FILENO, TCSANOW, &original); }
};

// --- 3. HIERARQUIA DE ENTIDADES (POO ELITE) ---

class Entidade {
public:
    double x, y;
    char sprite;
    bool ativo;
    Entidade(double _x, double _y, char s) : x(_x), y(_y), sprite(s), ativo(true) {}
    virtual void update(double dt) = 0;
    virtual ~Entidade() {}
};

class Projetil : public Entidade {
public:
    Projetil(double _x, double _y) : Entidade(_x, _y, '|') {}
    void update(double dt) override {
        y -= 35.0 * dt; // Laser orbital rápido
        if (y < 1) ativo = false;
    }
};

class Alien : public Entidade {
public:
    static double direcaoGlobal;
    Alien(double _x, double _y) : Entidade(_x, _y, 'M') {}
    void update(double dt) override {
        x += direcaoGlobal * 12.0 * dt;
    }
};
double Alien::direcaoGlobal = 1.0;

class Player : public Entidade {
public:
    Player(double _x, double _y) : Entidade(_x, _y, 'A') {}
    void update(double dt) override { (void)dt; } 
    void mover(int d, int limite) {
        x += d;
        if (x < 1) x = 1;
        if (x > limite - 1) x = limite - 1;
    }
};

// --- 4. MOTOR DO JOGO (GAME ARCHITECTURE) ---

class GInvaders {
private:
    int L = 40, A = 20;
    vector<vector<char>> buffer;
    unique_ptr<Player> player;
    vector<unique_ptr<Alien>> aliens;
    vector<unique_ptr<Projetil>> balas;
    int score;

public:
    GInvaders() : score(0) {
        buffer.resize(A, vector<char>(L, ' '));
        player = make_unique<Player>(L/2, A-2);
        
        for(int i=0; i<3; i++)
            for(int j=0; j<8; j++)
                aliens.push_back(make_unique<Alien>(j*4 + 5, i*2 + 2));
    }

    void processarFisica() {
        for (auto& b : balas) {
            if (!b->ativo) continue;
            for (auto& a : aliens) {
                if (a->ativo && (int)b->x == (int)a->x && (int)b->y == (int)a->y) {
                    a->ativo = b->ativo = false;
                    score += 100;
                }
            }
        }
    }

    void update(double dt, char input) {
        // 1. Processar Comandos
        if (input == 'a' || input == 'A') player->mover(-1, L);
        if (input == 'd' || input == 'D') player->mover(1, L);
        if (input == ' ') {
            if (balas.size() < 5) // Limite de cadência para evitar spam na RAM
                balas.push_back(make_unique<Projetil>(player->x, player->y - 1));
        }

        // 2. Movimentação dos Aliens (Lógica de Borda)
        bool inverter = false;
        for (auto& a : aliens) {
            if (!a->ativo) continue;
            a->update(dt);
            if (a->x >= L-2 || a->x <= 1) inverter = true;
        }

        if (inverter) {
            Alien::direcaoGlobal *= -1;
            for (auto& a : aliens) a->y += 0.8; // Descida lenta
        }

        // 3. Atualizar Projéteis
        for (auto& b : balas) b->update(dt);

        // 4. Colisões
        processarFisica();

        // 5. GARBAGE COLLECTION RAII (Auto-limpeza via Smart Pointers)
        balas.erase(remove_if(balas.begin(), balas.end(), [](const unique_ptr<Projetil>& p){ 
            return !p->ativo; 
        }), balas.end());

        aliens.erase(remove_if(aliens.begin(), aliens.end(), [](const unique_ptr<Alien>& a){ 
            return !a->ativo; 
        }), aliens.end());
    }

    void renderizar() {
        for(auto& row : buffer) fill(row.begin(), row.end(), ' ');

        // Plotagem no Buffer
        if (player->ativo) buffer[(int)player->y][(int)player->x] = player->sprite;
        for (auto& a : aliens) if (a->ativo) buffer[(int)a->y][(int)a->x] = a->sprite;
        for (auto& b : balas) if (b->ativo) buffer[(int)b->y][(int)b->x] = b->sprite;

        // Despejo no stdout (Otimização: sem limpar tela, apenas move cursor)
        UI::moverCursor(1, 1);
        cout << UI::CIANO << UI::NEGRITO << "SCORE: " << score << " | G-INVADERS: DEFESA ORBITAL v2.0" << UI::RESET << endl;
        cout << UI::RESET << "┌" << string(L, '-') << "┐" << UI::RESET << endl;
        
        for (int y = 0; y < A; y++) {
            cout << UI::RESET << "│" << UI::RESET;
            for (int x = 0; x < L; x++) {
                char c = buffer[y][x];
                if (c == 'M') cout << UI::VERMELHO << UI::NEGRITO << "M" << UI::RESET;
                else if (c == 'A') cout << UI::VERDE << UI::NEGRITO << "A" << UI::RESET;
                else if (c == '|') cout << UI::AMARELO << "|" << UI::RESET;
                else cout << " ";
            }
            cout << UI::RESET << "│" << UI::RESET << endl;
        }
        cout << UI::RESET << "└" << string(L, '-') << "┘" << UI::RESET << endl;
    }
};

// --- 5. CORE GAME LOOP ---

int main() {
    UI::limparTela();
    UI::ocultarCursor();
    Input lowLevelInput;
    GInvaders engine;

    auto tempoAnterior = chrono::steady_clock::now();
    bool rodando = true;

    while (rodando) {
        // Sincronismo Temporal
        auto tempoAtual = chrono::steady_clock::now();
        chrono::duration<double> gap = tempoAtual - tempoAnterior;
        double dt = gap.count();
        tempoAnterior = tempoAtual;

        // Captura de Eventos
        char cmd = lowLevelInput.get();
        if (cmd == 'q' || cmd == 'Q') rodando = false;

        // Update & Render
        engine.update(dt, cmd);
        engine.renderizar();

        // 30 FPS Cap (Cuidado térmico da CPU)
        this_thread::sleep_for(chrono::milliseconds(33)); 
    }

    UI::mostrarCursor();
    UI::limparTela();
    cout << UI::VERDE << UI::NEGRITO << "\n[MISSÃO CUMPRIDA]: A Terra está segura (por enquanto)." << UI::RESET << endl;
    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ARQUITETURA DE JOGOS MODERNOS
    ===============================================================

    1. GESTÃO DE MEMÓRIA ELITE (SMART POINTERS):
       - O uso de 'unique_ptr' dentro de um 'std::vector' é o padrão 
         industrial do C++ moderno (C++11/14/17/20). Ele garante 
         que quando um alien morre (removido do vetor), sua memória 
         é devolvida ao S.O. sem um único comando 'delete'.

    2. O GAME LOOP DETERMINÍSTICO:
       - Ao multiplicar o movimento pelo 'dt', garantimos que a 
         nave percorra X metros por segundo em qualquer taxa de 
         atualização. Isso evita que o jogo fique "acelerado" em 
         computadores potentes.

    3. SCREEN BUFFERING:
       - Montamos a cena completa em uma matriz de caracteres antes 
         de enviar para o console. Isso permite aplicar cores ANSI 
         e molduras complexas sem causar atrasos de renderização.

    4. ASYNC POLLING:
       - O drone (nave) responde instantaneamente porque o input é 
         não-bloqueante. O sistema não para para esperar você 
         digitar; ele consulta o buffer e segue processando.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Component-Entity-System (ECS): Arquitetura de jogos AAA.
    - Pathfinding (A*): Inimigos que te perseguem.
    - OpenGL/DirectX: O próximo nível da renderização.
    ===============================================================
*/

/**
 * @file atividade-extra47-invaders.cpp
 * @brief G-INVADERS: Motor de Jogo Senior em Tempo Real.
 * 
 * Este projeto é a culminação de todas as técnicas de Engine:
 * 1. Delta Time & Game Loop (Chrono)
 * 2. Raw Input (Termios)
 * 3. Grid Rendering (Buffer de Memória)
 * 4. POO & Polimorfismo (Entidades)
 * 5. Colisão e Lógica de Jogo.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
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
#include <memory> // Necessário para Smart Pointers (C++ Moderno)

using namespace std;

// --- 1. CORE ENGINE: UTILS E INPUT ---
// ... (UI e Input permanecem iguais)
namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string VERMELHO = "\033[31m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";

    void moverCursor(int x, int y) { cout << "\033[" << y << ";" << x << "H"; }
    void limparTela() { cout << "\033[2J\033[H"; }
    void esconderCursor() { cout << "\033[?25l"; }
    void mostrarCursor() { cout << "\033[?25h"; }
}

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

// --- 2. ENTIDADES DO JOGO ---

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
        y -= 30.0 * dt; // Sobe rápido
        if (y < 1) ativo = false;
    }
};

class Alien : public Entidade {
public:
    static double dir;
    Alien(double _x, double _y) : Entidade(_x, _y, 'M') {}
    void update(double dt) override {
        x += dir * 10.0 * dt;
    }
};
double Alien::dir = 1.0;

class Player : public Entidade {
public:
    Player(double _x, double _y) : Entidade(_x, _y, 'A') {}
    void update(double dt) override { (void)dt; } // Atualizado via input
    void mover(int d, int limite) {
        x += d;
        if (x < 1) x = 1;
        if (x > limite) x = limite;
    }
};

// --- 3. MOTOR GRÁFICO E LÓGICA ---

class GInvaders {
private:
    int L = 40, A = 20;
    vector<vector<char>> buffer;
    unique_ptr<Player> player;          // Smart Pointer: Posse única e automática
    vector<unique_ptr<Alien>> aliens;   // Coleção de Smart Pointers
    vector<unique_ptr<Projetil>> balas; // Coleção de Smart Pointers
    int score;
    bool ganhou;

public:
    GInvaders() : score(0), ganhou(false) {
        buffer.resize(A, vector<char>(L, ' '));
        // std::make_unique é a forma segura e moderna de criar objetos
        player = make_unique<Player>(L/2, A-2);
        
        for(int i=0; i<3; i++)
            for(int j=0; j<8; j++)
                aliens.push_back(make_unique<Alien>(j*4 + 5, i*2 + 2));
    }

    void processarColisões() {
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
        if (input == 'a' || input == 'A') player->mover(-1, L-1);
        if (input == 'd' || input == 'D') player->mover(1, L-1);
        if (input == ' ') balas.push_back(make_unique<Projetil>(player->x, player->y - 1));

        bool tocarBorda = false;
        for (auto& a : aliens) {
            if (!a->ativo) continue;
            a->update(dt);
            if (a->x >= L-1 || a->x <= 1) tocarBorda = true;
        }

        if (tocarBorda) {
            Alien::dir *= -1;
            for (auto& a : aliens) a->y += 1.0;
        }

        for (auto& b : balas) b->update(dt);

        processarColisões();

        // Limpeza de inativos (O unique_ptr deleta a memória automaticamente aqui)
        balas.erase(remove_if(balas.begin(), balas.end(), [](const unique_ptr<Projetil>& p){ 
            return !p->ativo; 
        }), balas.end());

        aliens.erase(remove_if(aliens.begin(), aliens.end(), [](const unique_ptr<Alien>& a){ 
            return !a->ativo; 
        }), aliens.end());
    }

    void desenhar() {
        for(auto& row : buffer) fill(row.begin(), row.end(), ' ');

        if (player->ativo) buffer[(int)player->y][(int)player->x] = player->sprite;
        for (auto& a : aliens) if (a->ativo) buffer[(int)a->y][(int)a->x] = a->sprite;
        for (auto& b : balas) if (b->ativo) buffer[(int)b->y][(int)b->x] = b->sprite;

        UI::moverCursor(1, 1);
        cout << UI::CIANO << "SCORE: " << score << " | G-INVADERS MODERN C++" << UI::RESET << endl;
        cout << "+" << string(L, '-') << "+" << endl;
        for (int y = 0; y < A; y++) {
            cout << "|";
            for (int x = 0; x < L; x++) {
                char c = buffer[y][x];
                if (c == 'M') cout << UI::VERMELHO << c << UI::RESET;
                else if (c == 'A') cout << UI::VERDE << c << UI::RESET;
                else if (c == '|') cout << UI::AMARELO << c << UI::RESET;
                else cout << c;
            }
            cout << "|" << endl;
        }
        cout << "+" << string(L, '-') << "+" << endl;
    }

    // O DESTRUTOR MANUAL FOI REMOVIDO! 
    // O RAII (Resource Acquisition Is Initialization) cuida de tudo.
};

// --- 4. MAIN LOOP ---

int main() {
    UI::limparTela();
    UI::esconderCursor();
    Input input;
    GInvaders jogo;

    auto t_ant = chrono::steady_clock::now();
    bool rodando = true;

    while (rodando) {
        auto t_atual = chrono::steady_clock::now();
        chrono::duration<double> delta = t_atual - t_ant;
        double dt = delta.count();
        t_ant = t_atual;

        char c = input.get();
        if (c == 'q') rodando = false;

        jogo.update(dt, c);
        jogo.desenhar();

        this_thread::sleep_for(chrono::milliseconds(33)); 
    }

    UI::mostrarCursor();
    UI::limparTela();
    cout << "Obrigado por jogar G-INVADERS!" << endl;
    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: GESTÃO DE MEMÓRIA MODERNA (RAII)
    ===============================================================

    1. O FIM DO 'NEW' E 'DELETE':
       - No C++ moderno, não usamos 'new' e 'delete' manuais. Isso 
         evita o maior problema da linguagem: Memory Leaks (esquecer 
         de liberar memória).

    2. SMART POINTERS (std::unique_ptr):
       - É um "ponteiro inteligente" que possui a posse exclusiva de 
         um objeto. Quando o 'unique_ptr' sai de escopo (ou é removido 
         do vector), ele deleta o objeto automaticamente.

    3. std::make_unique:
       - É a fábrica de objetos. Mais segura que o 'new' direto pois 
         garante exceção segura e clareza de intenção.

    4. RAII (Resource Acquisition Is Initialization):
       - É o padrão onde a vida de um recurso (memória) é ligada ao 
         tempo de vida de um objeto local. Se o objeto 'GInvaders' 
         morre, todos os aliens e balas morrem com ele, sem esforço.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Smart Pointers: shared_ptr (posse compartilhada) e weak_ptr.
    - Move Semantics: Como transferir posse de objetos sem copiar.
    - Valgrind: Ferramenta para provar que não há vazamentos.
    ===============================================================
*/


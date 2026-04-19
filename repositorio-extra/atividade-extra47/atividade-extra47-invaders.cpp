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

using namespace std;

// --- 1. CORE ENGINE: UTILS E INPUT ---

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
    void update(double dt) override {} // Atualizado via input
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
    Player* player;
    vector<Alien*> aliens;
    vector<Projetil*> balas;
    int score;
    bool ganhou;

public:
    GInvaders() : score(0), ganhou(false) {
        buffer.resize(A, vector<char>(L, ' '));
        player = new Player(L/2, A-2);
        for(int i=0; i<3; i++)
            for(int j=0; j<8; j++)
                aliens.push_back(new Alien(j*4 + 5, i*2 + 2));
    }

    void processarColisões() {
        for (auto b : balas) {
            if (!b->ativo) continue;
            for (auto a : aliens) {
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
        if (input == ' ') balas.push_back(new Projetil(player->x, player->y - 1));

        bool tocarBorda = false;
        for (auto a : aliens) {
            if (!a->ativo) continue;
            a->update(dt);
            if (a->x >= L-1 || a->x <= 1) tocarBorda = true;
            if (a->y >= A-2) { /* Game Over - simplificado */ }
        }

        if (tocarBorda) {
            Alien::dir *= -1;
            for (auto a : aliens) a->y += 1.0;
        }

        for (auto b : balas) b->update(dt);

        processarColisões();

        // Limpeza de inativos
        balas.erase(remove_if(balas.begin(), balas.end(), [](Projetil* p){ 
            if(!p->ativo){ delete p; return true; } return false; 
        }), balas.end());
    }

    void desenhar() {
        // Limpa buffer
        for(auto& row : buffer) fill(row.begin(), row.end(), ' ');

        // Desenha entidades
        if (player->ativo) buffer[(int)player->y][(int)player->x] = player->sprite;
        for (auto a : aliens) if (a->ativo) buffer[(int)a->y][(int)a->x] = a->sprite;
        for (auto b : balas) if (b->ativo) buffer[(int)b->y][(int)b->x] = b->sprite;

        // Renderiza no terminal
        UI::moverCursor(1, 1);
        cout << UI::CIANO << "SCORE: " << score << " | G-INVADERS" << UI::RESET << endl;
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

    ~GInvaders() {
        delete player;
        for (auto a : aliens) delete a;
        for (auto b : balas) delete b;
    }
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

        this_thread::sleep_for(chrono::milliseconds(33)); // ~30 FPS
    }

    UI::mostrarCursor();
    UI::limparTela();
    cout << "Obrigado por jogar G-INVADERS!" << endl;
    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ARQUITETURA DE JOGOS SENIOR
    ===============================================================

    1. DESACOPLAMENTO DE FPS:
       - O Delta Time (dt) é o parâmetro de toda função de update. 
         Isso garante que o Alien ande na mesma velocidade 
         independente da lentidão do terminal.

    2. GESTÃO DINÂMICA DE OBJETOS:
       - Usamos o padrão de "Active Flag" e remoção em lote 
         (remove_if). Isso evita que o jogo fique lento por 
         processar balas que já saíram da tela.

    3. POLIMORFISMO E HERANÇA:
       - Todas as entidades derivam de uma classe base, mas cada 
         uma tem seu comportamento de atualização e seu "desenho" 
         específico no buffer de vídeo.

    4. RAW INPUT E BUFFERING:
       - A união da Atividade 45 (Input) com a 46 (Grid) permite 
         que o jogador sinta o controle da nave como se estivesse 
         em um console real.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Motores 2D modernos (SFML, SDL, Raylib).
    - Teoria de Colisão de AABB (Axis-Aligned Bounding Box).
    - Shaders e Efeitos de Partícula (conceitual).
    ===============================================================
*/

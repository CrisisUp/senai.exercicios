/**
 * @file atividade-extra44-gameloop.cpp
 * @brief Core Engine: Implementação de Game Loop e Delta Time.
 * 
 * Este programa demonstra o padrão de arquitetura fundamental para jogos
 * em tempo real, utilizando a biblioteca <chrono> para garantir que a 
 * simulação seja independente da taxa de quadros (FPS).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string CIANO    = "\033[36m";
    const string AMARELO  = "\033[33m";
    
    void moverCursor(int x, int y) {
        cout << "\033[" << y << ";" << x << "H";
    }

    void limparTela() {
        cout << "\033[2J\033[H";
    }
}

// --- 2. CLASSE ENGINE (O MOTOR DO JOGO) ---

class GameEngine {
private:
    bool rodando;
    double xPos;
    double velocidade; // Unidades por segundo

    // Controle de Tempo
    chrono::steady_clock::time_point tempoAnterior;

public:
    GameEngine() : rodando(true), xPos(1.0), velocidade(10.0) {
        tempoAnterior = chrono::steady_clock::now();
    }

    void rodar() {
        UI::limparTela();
        cout << UI::CIANO << "ENGINE STATUS: ATIVA | Mova o cursor do terminal para ver..." << UI::RESET << endl;

        // O LOOP INFINITO (GAME LOOP)
        while (rodando && xPos < 50.0) {
            
            // 1. CÁLCULO DO DELTA TIME
            auto tempoAtual = chrono::steady_clock::now();
            chrono::duration<double> diferenca = tempoAtual - tempoAnterior;
            double deltaTime = diferenca.count();
            tempoAnterior = tempoAtual;

            // 2. PROCESSAR INPUT (Simplificado: apenas tempo por enquanto)

            // 3. ATUALIZAR LÓGICA (Independente de FPS)
            xPos += velocidade * deltaTime;

            // 4. RENDERIZAR
            desenhar(deltaTime);

            // Pequeno descanso para o CPU (Simula 60 FPS aprox.)
            this_thread::sleep_for(chrono::milliseconds(16));
        }

        UI::moverCursor(1, 10);
        cout << UI::VERDE << "\n[SIMULAÇÃO]: Trajeto concluído com precisão de tempo." << UI::RESET << endl;
    }

    void desenhar(double dt) {
        // Desenha na linha 5
        UI::moverCursor(1, 5);
        cout << "Progresso: [";
        for(int i=0; i<50; i++) {
            if(i < (int)xPos) cout << "=";
            else cout << " ";
        }
        cout << "] " << fixed << setprecision(2) << xPos << " units" << endl;

        // Mostra o FPS em tempo real
        UI::moverCursor(1, 7);
        cout << UI::AMARELO << "Delta Time: " << dt << " s | FPS: " << (1.0 / dt) << UI::RESET << "    ";
        fflush(stdout); // Garante que o desenho apareça sem precisar de '\n'
    }
};

// --- 3. FUNÇÃO PRINCIPAL ---

int main()
{
    GameEngine engine;
    
    try {
        engine.rodar();
    } catch (const exception& e) {
        cerr << "Erro fatal na Engine: " << e.what() << endl;
    }

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: GAME LOOP E DELTA TIME
    ===============================================================

    1. O CONCEITO DE DELTA TIME (dt):
       - É o tempo que passou desde o último frame. Se o loop rodou 
         rápido, o dt é pequeno. Se rodou lento, o dt é grande.
       - Fórmula Mestra: posicao += velocidade * dt.
       - Isso garante que seu jogo rode na mesma velocidade em um 
         PC de 1990 ou em um de 2026.

    2. BIBLIOTECA <chrono>:
       - É a forma moderna do C++ de medir tempo com precisão de 
         nanossegundos, evitando as limitações da antiga <ctime>.

    3. ANSI ESCAPE SEQUENCES:
       - Usamos '\033[y;xH' para mover o cursor sem limpar a tela 
         toda. Isso é vital para evitar o 'Flicker' (piscar) nos 
         jogos de terminal.

    4. MULTITHREADING BÁSICO:
       - 'this_thread::sleep_for' é usado para não consumir 100% 
         da CPU desnecessariamente, permitindo que o sistema 
         operacional respire entre os quadros.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Fixed Time Step vs Variable Time Step.
    - Double Buffering: Técnica para renderização suave.
    - Latência de Input: O atraso entre o comando e a reação.
    ===============================================================
*/

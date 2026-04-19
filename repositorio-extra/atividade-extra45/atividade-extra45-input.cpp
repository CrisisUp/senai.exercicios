/**
 * @file atividade-extra45-input.cpp
 * @brief G-PILOT Engine: Input Não-Bloqueante e Raw Mode.
 * 
 * Este programa demonstra como manipular as configurações do terminal Unix/macOS
 * para capturar teclas instantaneamente, permitindo interações em tempo real
 * essenciais para jogos e sistemas de controle.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <thread>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    
    void moverCursor(int x, int y) { cout << "\033[" << y << ";" << x << "H"; }
    void limparTela() { cout << "\033[2J\033[H"; }
    void esconderCursor() { cout << "\033[?25l"; }
    void mostrarCursor() { cout << "\033[?25h"; }
}

// --- 2. GESTOR DE INPUT (SISTEMA DE BAIXO NÍVEL) ---

class InputManager {
private:
    struct termios original; // Para restaurar o terminal no fim

public:
    InputManager() {
        // Salva as configurações atuais do terminal
        tcgetattr(STDIN_FILENO, &original);
        
        struct termios raw = original;
        // Desativa modo canônico (esperar Enter) e eco (mostrar tecla)
        raw.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);

        // Configura a leitura como não-bloqueante (Non-blocking)
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    }

    /**
     * @brief Tenta ler um caractere do teclado sem parar o programa.
     * @return Caractere pressionado ou 0 se nada foi apertado.
     */
    char getTecla() {
        char ch;
        if (read(STDIN_FILENO, &ch, 1) > 0) return ch;
        return 0;
    }

    /**
     * @brief Destrutor: Devolve o terminal ao estado original.
     * Sem isso, seu terminal ficaria "bugado" após o programa fechar!
     */
    ~InputManager() {
        tcsetattr(STDIN_FILENO, TCSANOW, &original);
        UI::mostrarCursor();
    }
};

// --- 3. FUNÇÃO PRINCIPAL (SIMULADOR DE DRONE) ---

int main()
{
    UI::limparTela();
    UI::esconderCursor();
    
    InputManager input;
    
    int droneX = 20, droneY = 10;
    bool rodando = true;
    int frames = 0;

    cout << UI::CIANO << "CONTROLE DE DRONE ATIVO [WASD para mover | Q para sair]" << UI::RESET << endl;

    // Loop de Tempo Real
    while (rodando) {
        frames++;
        
        // 1. Processar Input (INSTANTÂNEO)
        char tecla = input.getTecla();
        if (tecla == 'q' || tecla == 'Q') rodando = false;
        
        if (tecla == 'w' || tecla == 'W') droneY--;
        if (tecla == 's' || tecla == 'S') droneY++;
        if (tecla == 'a' || tecla == 'A') droneX--;
        if (tecla == 'd' || tecla == 'D') droneX++;

        // Limites da tela
        if (droneX < 1) droneX = 1;
        if (droneY < 2) droneY = 2;

        // 2. Renderizar (Sem apagar a tela toda para evitar flicker)
        UI::moverCursor(1, 2);
        cout << "Frames processados: " << frames << " | Posição: (" << droneX << "," << droneY << ")   " << endl;

        // Desenha o drone
        UI::moverCursor(droneX, droneY);
        cout << UI::VERDE << "<^>" << UI::RESET;
        
        // Pequena pausa e limpeza do rastro (simplificada)
        fflush(stdout);
        this_thread::sleep_for(chrono::milliseconds(30));
        
        UI::moverCursor(droneX, droneY);
        cout << "   "; // Apaga a posição antiga
    }

    UI::limparTela();
    cout << "Simulação de voo encerrada com sucesso." << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: INPUT NÃO-BLOQUEANTE (NON-BLOCKING)
    ===============================================================

    1. MODO CANÔNICO VS BRUTO (RAW):
       - No modo canônico, o SO processa o texto e espera o Enter. 
         No modo Raw, os bytes do teclado chegam diretamente ao 
         seu programa. Isso é o segredo de qualquer jogo.

    2. FCNTL E O_NONBLOCK:
       - Por padrão, a função 'read' espera um dado chegar. O 
         O_NONBLOCK diz: "Se não tiver nada agora, não espere, 
         retorne erro imediatamente e deixe o programa seguir".

    3. LIMPEZA DE RASTRO (Ghosting):
       - Em jogos de terminal, para evitar que o rastro do objeto 
         fique na tela, desenhamos o objeto, esperamos o frame e 
         depois desenhamos espaços vazios na mesma posição antes 
         de mover.

    4. TERMIOS (O contrato com o SO):
       - Gerenciar o terminal é uma responsabilidade pesada. O uso 
         de 'tcgetattr' e 'tcsetattr' garante que o usuário não 
         perca o controle do terminal dele após jogar seu jogo.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Buffering de Saída (fflush).
    - Event Polling: Sistemas que verificam múltiplos inputs.
    - Signal Handling: Capturar Ctrl+C para sair limpando a memória.
    ===============================================================
*/

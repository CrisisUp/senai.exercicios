/**
 * @file atividade-extra46-render.cpp
 * @brief G-TERRAIN: Sistema de Renderização por Grade e Matrizes Dinâmicas.
 * 
 * Demonstra como gerenciar o espaço bidimensional do jogo utilizando um buffer
 * de memória (Matriz) que é desenhado de forma otimizada no terminal.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string BRANCO   = "\033[37m";
    
    void limparTela() { cout << "\033[2J\033[H"; }
}

// --- 2. CLASS TEMPLATE: GRADE DE RENDERIZAÇÃO ---

template <typename T>
class GradeRender {
private:
    int largura, altura;
    vector<vector<T>> buffer; // A "memória de vídeo" da nossa engine
    T charFundo;

public:
    GradeRender(int l, int a, T fundo) 
        : largura(l), altura(a), charFundo(fundo) {
        // Inicializa o buffer com o caractere de fundo
        buffer.resize(altura, vector<T>(largura, charFundo));
    }

    void limpar() {
        for(int y = 0; y < altura; y++) {
            for(int x = 0; x < largura; x++) {
                buffer[y][x] = charFundo;
            }
        }
    }

    void setPixel(int x, int y, T valor) {
        if (x >= 0 && x < largura && y >= 0 && y < altura) {
            buffer[y][x] = valor;
        }
    }

    void desenhar() const {
        // Desenha a borda superior
        cout << UI::CIANO << "+" << string(largura * 2, '-') << "+" << UI::RESET << endl;

        for (int y = 0; y < altura; y++) {
            cout << UI::CIANO << "|" << UI::RESET; // Borda lateral esquerda
            for (int x = 0; x < largura; x++) {
                T pixel = buffer[y][x];
                
                // Lógica de cores baseada no caractere (Cromia básica)
                if (pixel == '#') cout << UI::BRANCO << "##" << UI::RESET;
                else if (pixel == 'X') cout << UI::VERDE << "[]" << UI::RESET;
                else cout << "  "; // Espaço vazio para manter a proporção quadrada
            }
            cout << UI::CIANO << "|" << UI::RESET << endl; // Borda lateral direita
        }

        // Desenha a borda inferior
        cout << UI::CIANO << "+" << string(largura * 2, '-') << "+" << UI::RESET << endl;
    }
};

// --- 3. FUNÇÃO PRINCIPAL ---

int main()
{
    UI::limparTela();
    cout << UI::AMARELO << "G-TERRAIN RENDER ENGINE v1.0" << UI::RESET << endl;

    // Criando uma grade de 20x10 para o mapa
    GradeRender<char> mapa(20, 10, '.');

    // 1. Desenhando obstáculos (Rochas)
    for(int i = 0; i < 20; i++) {
        mapa.setPixel(i, 0, '#'); // Teto
        mapa.setPixel(i, 9, '#'); // Piso
    }
    mapa.setPixel(5, 5, '#');
    mapa.setPixel(6, 5, '#');
    mapa.setPixel(7, 5, '#');

    // 2. Posicionando o Robô explorador
    int roboX = 10, roboY = 5;
    mapa.setPixel(roboX, roboY, 'X');

    // 3. Renderização Final
    mapa.desenhar();

    cout << "\n[SISTEMA]: Mapa renderizado via Buffer de Matriz." << endl;
    cout << "Legenda: " << UI::BRANCO << "## (Rocha) " << UI::VERDE << "[] (Robô) " << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: RENDERIZAÇÃO POR GRADE (GRID)
    ===============================================================

    1. O CONCEITO DE BUFFER:
       - Em vez de dar 'cout' em cada objeto conforme ele é criado, 
         nós guardamos tudo em uma matriz central. Só depois de 
         montar a "foto" completa do mundo é que fazemos um único 
         ciclo de impressão.

    2. ASPECT RATIO NO TERMINAL:
       - Um caractere de terminal é mais alto do que largo. Para 
         que o mapa pareça quadrado e não "esticado", usamos dois 
         espaços ou dois caracteres para cada 'pixel' (ex: "##").

    3. COORDENADAS CARTESIANAS (x, y):
       - A matriz inverte o pensamento comum: matriz[y][x]. O 
         índice externo é a LINHA (Y) e o interno é a COLUNA (X). 
         Dominar essa inversão é vital para algoritmos de colisão.

    4. TEMPLATES PARA FLEXIBILIDADE:
       - Usamos 'GradeRender<T>' para que possamos trocar de 'char' 
         para um 'int' (códigos de cores) ou até para uma struct 
         'Celula' sem mudar o código da engine.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Raycasting: Como jogos tipo Doom simulam 3D em grades 2D.
    - Tile-based Games: Jogos baseados em blocos (Zelda, Pokémon).
    - Bitmaps: Como imagens reais são armazenadas na memória.
    ===============================================================
*/

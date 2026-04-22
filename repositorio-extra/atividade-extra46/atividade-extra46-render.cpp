/**
 * @file atividade-extra46-render.cpp
 * @brief G-TERRAIN: Sistema de Renderização por Grade e Matriz de Elite.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Implementa Buffer de Tela 2D genérico com otimização de Aspect Ratio.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Screen Buffer Layout)
 * - Objeto GradeRender: Alocado na STACK da main.
 * - std::vector<vector<T>>: O descritor mestre vive na STACK (24 bytes aprox).
 * - Buffer de Pixel: Matriz dinâmica alocada na HEAP (O(LxA * sizeof(T))).
 * - Performance: Acesso bi-indexado [][] traduzido em aritmética de ponteiros direta.
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI GRAPHICS) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string BRANCO   = "\033[37m";
    const string CINZA    = "\033[90m";
    
    inline void limparTela() { cout << "\033[2J\033[H"; }
}

// --- 2. CLASS TEMPLATE: GRADE DE RENDERIZAÇÃO (ENGINE) ---

/**
 * @class GradeRender
 * @brief Gerencia um buffer de memória 2D para visualização espacial.
 * @tparam T Tipo do pixel (char, int, ou custom struct).
 */
template <typename T>
class GradeRender {
private:
    int largura, altura;
    vector<vector<T>> buffer; // Memória de vídeo simulada
    T fundo;

public:
    /**
     * @brief Construtor: Inicializa o cenário na HEAP.
     */
    GradeRender(int l, int a, const T& _fundo) 
        : largura(l), altura(a), fundo(_fundo) {
        buffer.resize(altura, vector<T>(largura, fundo));
    }

    /**
     * @brief Purgar o buffer voltando ao estado original.
     */
    void limpar() {
        for(auto& linha : buffer) {
            fill(linha.begin(), linha.end(), fundo);
        }
    }

    /**
     * @brief Define valor de um pixel com validação de limites (Bound Checking).
     */
    void setPixel(int x, int y, const T& valor) {
        if (x >= 0 && x < largura && y >= 0 && y < altura) {
            buffer[y][x] = valor;
        }
    }

    /**
     * @brief Despeja o buffer no stdout em um único ciclo de renderização.
     */
    void desenhar() const {
        // Moldura Superior
        cout << UI::CIANO << "┌" << string(largura * 2, '─') << "┐" << UI::RESET << endl;

        for (int y = 0; y < altura; y++) {
            cout << UI::CIANO << "│" << UI::RESET; // Moldura Lateral
            for (int x = 0; x < largura; x++) {
                const T& pixel = buffer[y][x]; // Fantasma do CPU
                
                // Lógica de Renderização Baseada em Caracteres
                if (pixel == '#') cout << UI::BRANCO << "██" << UI::RESET; // Rocha Sólida
                else if (pixel == 'X') cout << UI::VERDE << UI::NEGRITO << "[]" << UI::RESET; // Robô
                else if (pixel == '.') cout << UI::CINZA << " ." << UI::RESET; // Solo Vazio
                else cout << "  ";
            }
            cout << UI::CIANO << "│" << UI::RESET << endl;
        }

        // Moldura Inferior
        cout << UI::CIANO << "└" << string(largura * 2, '─') << "┘" << UI::RESET << endl;
    }
};

// --- 3. EXECUÇÃO DO MAPEADOR DE TERRENO ---

int main()
{
    UI::limparTela();
    cout << UI::AMARELO << UI::NEGRITO << "G-TERRAIN RENDER ENGINE v2.0 (ELITE)" << UI::RESET << endl;
    cout << "Status: Mapeamento de Terreno Ativo (Buffer Logic)" << endl;

    // Cenário 24x12 (Aspect Ratio Compensado)
    GradeRender<char> mapa(24, 12, '.');

    // 1. GERAÇÃO DE OBSTÁCULOS (PERÍMETRO)
    for(int i = 0; i < 24; i++) {
        mapa.setPixel(i, 0, '#');
        mapa.setPixel(i, 11, '#');
    }
    
    // 2. FORMAÇÕES ROCHOSAS (RANDOM SEED SIMULADO)
    mapa.setPixel(5, 5, '#'); mapa.setPixel(5, 6, '#');
    mapa.setPixel(6, 5, '#'); mapa.setPixel(6, 6, '#');
    
    mapa.setPixel(18, 3, '#'); mapa.setPixel(19, 3, '#');
    mapa.setPixel(18, 4, '#'); mapa.setPixel(19, 4, '#');

    // 3. POSICIONAMENTO DO ROBÔ EXPLORADOR
    int roboX = 12, roboY = 6;
    mapa.setPixel(roboX, roboY, 'X');

    // 4. RENDERIZAÇÃO FINAL
    mapa.desenhar();

    cout << "\n" << UI::BRANCO << "TELEMETRIA DE CAMPO:" << UI::RESET << endl;
    cout << " >> Localização do Sensor: " << UI::VERDE << "(" << roboX << ", " << roboY << ")" << UI::RESET << endl;
    cout << " >> Densidade Terreno    : " << UI::AMARELO << "Alta (Rochas detectadas)" << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: RENDERIZAÇÃO POR GRADE (GRID)
    ===============================================================

    1. O PODER DO BUFFER:
       - Escrever no terminal é caro (lento). Escrever na memória 
         (vetor) é barato (rápido). Ao montar o mapa na RAM e 
         imprimir de uma vez, reduzimos drasticamente o jitter 
         do sistema.

    2. ASPECT RATIO (REVISITADO):
       - Caracteres de terminal têm largura ~0.5 da altura. Usar 
         duas posições horizontais ("██" ou " .") para cada 
         unidade de grade é o padrão de elite para manter mapas 
         com proporção 1:1.

    3. MATRIZES GENÉRICAS:
       - O uso de Templates permite que esta mesma engine seja 
         usada para renderizar caracteres, códigos de cores (int) 
         ou até objetos complexos contendo física e cor.

    4. SEGURANÇA DE MEMÓRIA (BOUND CHECKING):
       - O método setPixel() atua como um firewall, impedindo que 
         coordenadas fora da tela corrompam a memória adjacente 
         na HEAP.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Z-Buffer: Para lidar com profundidade (3D).
    - Sprite Sheets: Desenhar imagens complexas a partir de blocos.
    - Pathfinding (A*): Rodar algoritmos de busca sobre o buffer.
    ===============================================================
*/

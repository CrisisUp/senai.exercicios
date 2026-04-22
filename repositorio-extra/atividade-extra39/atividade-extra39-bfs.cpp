/**
 * @file atividade-extra39-bfs.cpp
 * @brief G-Tracker: Rastreamento Epidemiológico via Busca em Largura (BFS).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a técnica de exploração por níveis para contenção de surtos.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (BFS Execution Layout)
 * - Fila (std::queue): Alocada na STACK (descritor), gerencia nós na HEAP.
 * - Vetor 'visitados': Bitmap na STACK (ou HEAP se grande) para controle O(1).
 * - Matriz de Adjacência: Bloco O(V²) na HEAP garantindo persistência da rede.
 * - Algoritmo: Utiliza a FILA para transformar a recursão teórica em iteração.
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERMELHO = "\033[31m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. MOTOR DE RASTREAMENTO (GRAFO + BFS) ---

class RedeEpidemica {
private:
    int totalPessoas;
    vector<vector<int>> matriz; // Adjacency Matrix O(V²)
    vector<string> catalogoNomes;

public:
    RedeEpidemica(int n) : totalPessoas(n) {
        matriz.resize(n, vector<int>(n, 0));
        catalogoNomes.resize(n, "ID_" + to_string(n));
    }

    /**
     * @brief Associa identidade ao vértice.
     */
    void registrarNome(int id, const string& nome) {
        if (id >= 0 && id < totalPessoas) catalogoNomes[id] = nome;
    }

    /**
     * @brief Define contato físico entre dois indivíduos.
     */
    void registrarContato(int p1, int p2) {
        if (p1 >= 0 && p1 < totalPessoas && p2 >= 0 && p2 < totalPessoas) {
            matriz[p1][p2] = 1;
            matriz[p2][p1] = 1;
        }
    }

    /**
     * @brief Algoritmo BFS: Exploração por ondas de choque (Níveis).
     * @param inicio ID do infectado original (Index Zero).
     */
    void executarRastreamento(int inicio) {
        if (inicio < 0 || inicio >= totalPessoas) return;

        cout << UI::VERMELHO << UI::NEGRITO << "\n[PROTOCOLO DE CONTENÇÃO ATIVO]" << UI::RESET << endl;
        cout << "PONTO ZERO: " << UI::CIANO << catalogoNomes[inicio] << UI::RESET << "\n" << endl;

        vector<bool> visitado(totalPessoas, false); 
        queue<int> fila; // Motor FIFO (First-In, First-Out)

        // Inicialização do BFS
        visitado[inicio] = true;
        fila.push(inicio);

        int nivel = 0;
        while (!fila.empty()) {
            int tamanhoNivel = fila.size();
            cout << UI::NEGRITO << "ONDA DE EXPOSIÇÃO #" << nivel << UI::RESET << endl;

            // Processamento do nível atual (Distância 'nivel' do ponto zero)
            for (int i = 0; i < tamanhoNivel; i++) {
                int atual = fila.front();
                fila.pop();

                cout << " >> " << left << setw(15) << catalogoNomes[atual] << UI::VERDE << " [TESTADO]" << UI::RESET << endl;

                // Exploração de contatos diretos (Adjacência)
                for (int vizinho = 0; vizinho < totalPessoas; vizinho++) {
                    if (matriz[atual][vizinho] == 1 && !visitado[vizinho]) {
                        visitado[vizinho] = true;
                        fila.push(vizinho);
                        cout << UI::AMARELO << "    [!] Risco imediato detectado: " << catalogoNomes[vizinho] << UI::RESET << endl;
                    }
                }
            }
            cout << UI::BRANCO << "-----------------------------------------------" << UI::RESET << endl;
            nivel++;
        }
        cout << UI::VERDE << UI::NEGRITO << "\n[SISTEMA]: Varredura de rede concluída. Quarentena recomendada para " << nivel << " níveis." << UI::RESET << endl;
    }
};

// --- 3. EXECUÇÃO DO G-TRACKER ---

int main()
{
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-TRACKER: ALGORITMO DE BUSCA BFS v2.0   " << endl;
    cout << "       (Elite Pathfinding & Epidemiology)      " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Rede de 7 pessoas (Topologia de Estrela/Árvore)
    RedeEpidemica gTracker(7);
    gTracker.registrarNome(0, "Cristiano (P0)");
    gTracker.registrarNome(1, "Elizabeth");
    gTracker.registrarNome(2, "Joao");
    gTracker.registrarNome(3, "Maria");
    gTracker.registrarNome(4, "Carlos");
    gTracker.registrarNome(5, "Ana");
    gTracker.registrarNome(6, "Roberto");

    // Definição da malha de contatos
    gTracker.registrarContato(0, 1); // Cristiano -> Elizabeth
    gTracker.registrarContato(0, 4); // Cristiano -> Carlos
    gTracker.registrarContato(1, 2); // Elizabeth -> Joao
    gTracker.registrarContato(2, 3); // Joao -> Maria
    gTracker.registrarContato(4, 5); // Carlos -> Ana
    gTracker.registrarContato(5, 6); // Ana -> Roberto

    // Início do Rastreamento Viral
    gTracker.executarRastreamento(0);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: TRAVESSIA EM LARGURA (BFS)
    ===============================================================

    1. LÓGICA DE EXPLORAÇÃO:
       - O BFS garante que visitamos todos os vizinhos diretos (dist. 1) 
         antes de avançar para os netos (dist. 2). É ideal para 
         achar o caminho mais curto em redes não-valorizadas.

    2. O MOTOR FIFO (std::queue):
       - A Fila é o que torna a "Largura" possível. Ao colocar 
         os vizinhos no final da fila e processar o início, o 
         algoritmo expande horizontalmente pela memória.

    3. MARCAÇÃO DE SEGURANÇA:
       - O vetor 'visitado' é vital. Sem ele, o algoritmo entraria 
         em loop infinito entre A e B (Ping-pong de ponteiros), 
         estourando a memória HEAP da fila.

    4. PERFORMANCE FANTASMA DO CPU:
       - Usamos o tamanho da fila (tamanhoNivel) para processar 
         blocos de ondas. Isso minimiza chamadas de sistema e 
         organiza a saída visual de forma lógica e profissional.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Pathfinding (A*): BFS com inteligência heurística.
    - Grafo Bipartido: Testar se a rede pode ser dividida em dois grupos.
    - Network Flow: Analisar a capacidade de tráfego na rede.
    ===============================================================
*/

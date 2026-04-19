/**
 * @file atividade-extra40-dijkstra.cpp
 * @brief Algoritmo de Dijkstra: Otimização de Rotas de Emergência.
 * 
 * Demonstra a implementação clássica do caminho mais curto em um grafo
 * valorizado, permitindo encontrar a rota mais rápida em um mapa de conexões.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string CIANO    = "\033[36m";
    const string AMARELO  = "\033[33m";
    const string VERMELHO = "\033[31m";
    const int INF = numeric_limits<int>::max(); // Representa o "Infinito"
}

// --- 2. CLASSE GESTORA DE ROTAS (DIJKSTRA) ---

class GRescueRouter {
private:
    int totalPontos;
    vector<vector<int>> grafo; // Matriz de Adjacência Valorizada
    vector<string> locais;

public:
    GRescueRouter(int n) : totalPontos(n) {
        // Inicializa com INF (sem conexões diretas)
        grafo.resize(n, vector<int>(n, UI::INF));
        // A distância de um ponto para ele mesmo é 0
        for(int i = 0; i < n; i++) grafo[i][i] = 0;
        locais.resize(n);
    }

    void setLocal(int id, string nome) { locais[id] = nome; }

    void conectar(int p1, int p2, int tempoMinutos) {
        grafo[p1][p2] = tempoMinutos;
        grafo[p2][p1] = tempoMinutos; // Grafo não-direcionado
    }

    /**
     * @brief Executa o Algoritmo de Dijkstra.
     */
    void calcularMelhorRota(int origem, int destino) {
        vector<int> distancias(totalPontos, UI::INF);
        vector<bool> visitados(totalPontos, false);
        vector<int> antecessor(totalPontos, -1);

        distancias[origem] = 0;

        for (int i = 0; i < totalPontos - 1; i++) {
            // Escolhe o nó com a menor distância atual que ainda não foi visitado
            int u = encontrarMenorDistancia(distancias, visitados);
            if (u == -1) break;

            visitados[u] = true;

            // Relaxamento das arestas dos vizinhos de u
            for (int v = 0; v < totalPontos; v++) {
                if (!visitados[v] && grafo[u][v] != UI::INF && 
                    distancias[u] + grafo[u][v] < distancias[v]) {
                    distancias[v] = distancias[u] + grafo[u][v];
                    antecessor[v] = u;
                }
            }
        }

        exibirResultado(origem, destino, distancias, antecessor);
    }

private:
    int encontrarMenorDistancia(const vector<int>& dist, const vector<bool>& visit) {
        int min = UI::INF, min_index = -1;
        for (int v = 0; v < totalPontos; v++) {
            if (!visit[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }
        return min_index;
    }

    void exibirResultado(int ori, int dest, const vector<int>& dist, const vector<int>& ant) {
        cout << "\n--- RELATÓRIO DE ROTA OTIMIZADA ---" << endl;
        if (dist[dest] == UI::INF) {
            cout << UI::VERMELHO << "[ERRO]: Não há caminho possível entre os locais." << UI::RESET << endl;
            return;
        }

        cout << "Origem : " << locais[ori] << endl;
        cout << "Destino: " << locais[dest] << endl;
        cout << "Tempo Estimado: " << UI::VERDE << dist[dest] << " minutos" << UI::RESET << endl;

        // Reconstruindo o caminho (Backtracking)
        cout << "Trajeto sugerido: ";
        vector<int> caminho;
        for (int v = dest; v != -1; v = ant[v]) caminho.push_back(v);
        
        for (int i = caminho.size() - 1; i >= 0; i--) {
            cout << locais[caminho[i]] << (i > 0 ? " -> " : "");
        }
        cout << endl;
    }
};

// --- 3. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << UI::CIANO << "===============================================" << endl;
    cout << "      G-RESCUE: AMBULANCE ROUTING SYSTEM       " << endl;
    cout << "===============================================" << UI::RESET << endl;

    GRescueRouter cidade(6);
    cidade.setLocal(0, "Hospital Central");
    cidade.setLocal(1, "Bairro Norte");
    cidade.setLocal(2, "Centro Comercial");
    cidade.setLocal(3, "Zona Industrial");
    cidade.setLocal(4, "Residencial Sul");
    cidade.setLocal(5, "Local do Acidente");

    // Definindo as vias e seus tempos (em minutos)
    cidade.conectar(0, 1, 10); // Hospital -> Norte: 10 min
    cidade.conectar(0, 2, 5);  // Hospital -> Centro: 5 min
    cidade.conectar(1, 3, 2);  // Norte -> Ind: 2 min
    cidade.conectar(2, 1, 3);  // Centro -> Norte: 3 min
    cidade.conectar(2, 4, 15); // Centro -> Sul: 15 min
    cidade.conectar(3, 5, 8);  // Ind -> Acidente: 8 min
    cidade.conectar(4, 5, 4);  // Sul -> Acidente: 4 min

    cout << "[SISTEMA]: Mapa de tráfego carregado." << endl;
    cout << "[LOG]: Chamada de emergência recebida no 'Local do Acidente'." << endl;

    // Calculando a melhor rota
    cidade.calcularMelhorRota(0, 5);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ALGORITMO DE DIJKSTRA
    ===============================================================

    1. ALGORITMO GULOSO (GREEDY):
       - O Dijkstra toma decisões baseadas no "melhor agora". Ele 
         sempre escolhe o nó mais próximo da origem para explorar, 
         garantindo que, quando um nó é visitado, já conhecemos o 
         menor caminho possível até ele.

    2. O CONCEITO DE RELAXAMENTO:
       - É o ato de atualizar a distância de um vizinho se um novo 
         caminho for melhor: d(v) = min( d(v), d(u) + custo(u,v) ).

    3. COMPLEXIDADE:
       - Usando matriz de adjacência, a complexidade é O(V²). Em 
         sistemas gigantes como o Google Maps, usa-se Listas de 
         Adjacência com Filas de Prioridade para atingir O(A log V).

    4. APLICAÇÕES:
       - Além de GPS, é usado em roteamento de redes (Protocolo OSPF), 
         redes de energia elétrica e até em inteligência de NPCs 
         em jogos de vídeo-game.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Algoritmo A* (A-Star): Uma evolução do Dijkstra para IA.
    - Algoritmo de Bellman-Ford: Funciona com pesos negativos.
    - Árvore Geradora Mínima (Prim/Kruskal).
    ===============================================================
*/

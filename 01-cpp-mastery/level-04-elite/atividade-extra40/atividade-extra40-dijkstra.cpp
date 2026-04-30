/**
 * @file atividade-extra40-dijkstra.cpp
 * @brief G-Rescue: Otimização de Rotas de Emergência via Algoritmo de Dijkstra.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Implementa a descoberta de caminho ótimo em redes de tráfego valorizadas.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Dijkstra Resource Layout)
 * - Matriz de Custos: Alocada na HEAP (O(V²) bytes).
 * - Vetor de Distâncias: Array de inteiros na STACK/HEAP rastreando o custo acumulado.
 * - Vetor de Antecessores: Mapa de backtracking para reconstrução do trajeto.
 * - Complexidade: O(V²) devido à matriz de adjacência e busca linear de mínimo.
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
    const int INF = numeric_limits<int>::max(); // Infinito matemático para custos
    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. GESTOR DE ROTAS DE EMERGÊNCIA (DIJKSTRA CORE) ---

class GRescueRouter {
private:
    int totalPontos;
    vector<vector<int>> matrizCustos; 
    vector<string> catalogoLocais;

public:
    /**
     * @brief Construtor: Inicializa mapa de pesos infinitos.
     */
    GRescueRouter(int n) : totalPontos(n) {
        matrizCustos.resize(n, vector<int>(n, UI::INF));
        for(int i = 0; i < n; i++) matrizCustos[i][i] = 0; // Custo zero para si mesmo
        catalogoLocais.resize(n, "Ponto_Indefinido");
    }

    /**
     * @brief Define a identificação do vértice.
     */
    void registrarLocal(int id, const string& nome) {
        if (id >= 0 && id < totalPontos) catalogoLocais[id] = nome;
    }

    /**
     * @brief Cria via de tráfego com peso (tempo de trânsito).
     */
    void conectarVias(int p1, int p2, int tempo) {
        if (p1 >= 0 && p1 < totalPontos && p2 >= 0 && p2 < totalPontos) {
            matrizCustos[p1][p2] = tempo;
            matrizCustos[p2][p1] = tempo; // Simetria bidirecional
        }
    }

    /**
     * @brief Executa Dijkstra para encontrar o caminho de menor tempo.
     * @param origem ID de saída (Hospital).
     * @param destino ID de chegada (Acidente).
     */
    void calcularRotaOtima(int origem, int destino) {
        vector<int> distancias(totalPontos, UI::INF);
        vector<bool> visitados(totalPontos, false);
        vector<int> pais(totalPontos, -1); // Para o Backtracking

        distancias[origem] = 0;

        for (int i = 0; i < totalPontos - 1; i++) {
            // Escolha Gulosa (Greedy Step)
            int u = encontrarPontoMaisProximo(distancias, visitados);
            if (u == -1 || u == UI::INF) break;

            visitados[u] = true;

            // Relaxamento de vizinhos (Edge Relaxation)
            for (int v = 0; v < totalPontos; v++) {
                if (!visitados[v] && matrizCustos[u][v] != UI::INF && 
                    distancias[u] + matrizCustos[u][v] < distancias[v]) {
                    distancias[v] = distancias[u] + matrizCustos[u][v];
                    pais[v] = u;
                }
            }
        }

        renderizarResultado(origem, destino, distancias, pais);
    }

private:
    /**
     * @brief Busca linear pelo nó de menor custo ainda não fechado.
     */
    int encontrarPontoMaisProximo(const vector<int>& dists, const vector<bool>& visits) {
        int minVal = UI::INF, minIdx = -1;
        for (int v = 0; v < totalPontos; v++) {
            if (!visits[v] && dists[v] <= minVal) {
                minVal = dists[v];
                minIdx = v;
            }
        }
        return minIdx;
    }

    /**
     * @brief Exibe o trajeto otimizado com cores de urgência.
     */
    void renderizarResultado(int ori, int dest, const vector<int>& dists, const vector<int>& pais) {
        cout << "\n" << UI::CIANO << UI::NEGRITO << "--- G-RESCUE: RELATÓRIO DE DESLOCAMENTO ---" << UI::RESET << endl;
        
        if (dists[dest] == UI::INF) {
            cout << UI::VERMELHO << "[FALHA]: Não há rotas terrestres viáveis para o local." << UI::RESET << endl;
            return;
        }

        cout << UI::RESET << "Hospital  : " << UI::RESET << catalogoLocais[ori] << endl;
        cout << UI::RESET << "Emergência: " << UI::RESET << catalogoLocais[dest] << endl;
        cout << UI::RESET << "ETA (Tempo): " << UI::RESET << UI::VERDE << UI::NEGRITO << dists[dest] << " min" << UI::RESET << endl;

        // Backtracking via Parent Map
        cout << UI::NEGRITO << "\nTRAJETO SUGERIDO (GPS):" << UI::RESET << endl;
        vector<int> path;
        for (int v = dest; v != -1; v = pais[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        
        for (size_t i = 0; i < path.size(); i++) {
            cout << UI::CIANO << catalogoLocais[path[i]] << UI::RESET << (i < path.size() - 1 ? " -> " : "");
        }
        cout << endl;
    }
};

// --- 3. EXECUÇÃO DO SISTEMA DE DESPACHO ---

int main()
{
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-RESCUE: AMBULANCE ROUTING ENGINE v2.0  " << endl;
    cout << "       (Elite Pathfinding Architecture)        " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Mapa Urbano (6 pontos críticos)
    GRescueRouter sp_central(6);
    sp_central.registrarLocal(0, "Base_SAMU_Central");
    sp_central.registrarLocal(1, "Posto_Norte");
    sp_central.registrarLocal(2, "Cruzamento_Centro");
    sp_central.registrarLocal(3, "Viaduto_Industrial");
    sp_central.registrarLocal(4, "Terminal_Sul");
    sp_central.registrarLocal(5, "SINISTRO_REPORTADO");

    // Configuração das Vias (Tempo em minutos considerando tráfego)
    sp_central.conectarVias(0, 1, 8);  // Base -> Norte
    sp_central.conectarVias(0, 2, 4);  // Base -> Centro (Rápida)
    sp_central.conectarVias(1, 3, 2);  // Norte -> Ind
    sp_central.conectarVias(2, 1, 3);  // Centro -> Norte
    sp_central.conectarVias(2, 4, 12); // Centro -> Sul
    sp_central.conectarVias(3, 5, 7);  // Ind -> Sinistro
    sp_central.conectarVias(4, 5, 3);  // Sul -> Sinistro (Perto)

    cout << UI::AMARELO << "[ALERTA]: Acionamento código 1 em 'SINISTRO_REPORTADO'." << UI::RESET << endl;
    cout << "[INFO]: Calculando rota de menor latência temporal..." << endl;

    // Cálculo da Rota Otimizada
    sp_central.calcularRotaOtima(0, 5);

    cout << "\n" << UI::VERDE << UI::NEGRITO << "Despacho autorizado. Sincronizando com unidade móvel." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ALGORITMO DE DIJKSTRA (ELITE)
    ===============================================================

    1. LÓGICA GULOSA (GREEDY):
       - O Dijkstra assume que a melhor escolha local levará à 
         melhor escolha global. Ele "fecha" o nó mais próximo, 
         garantindo que o custo para chegar nele nunca mais mudará 
         naquela execução.

    2. RELAXAMENTO DE ARESTAS:
       - É o motor do algoritmo. Ele verifica: "É mais rápido ir 
         direto de A para C, ou ir de A para B e depois para C?". 
         Se a segunda opção for menor, a distância é atualizada.

    3. COMPLEXIDADE E MATRIZES:
       - Usar matrizes simplifica o código (O(1) access), mas para 
         redes gigantes (ex: Internet/GPS), a memória V² se torna 
         um problema. Em engenharia avançada, usa-se Listas de 
         Adjacência com Heaps (Priority Queues).

    4. FANTASMA DO CPU (PERFORMANCE):
       - O backtracking reconstrói o caminho em O(V), o que é 
         insignificante perto do tempo de cálculo O(V²), garantindo 
         que o GPS responda instantaneamente ao socorrista.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Bellman-Ford: Lida com pesos negativos (créditos/bônus).
    - Heurística de Manhattan (A*): Dijkstra com bússola.
    - Graph Partitioning: Dividir a cidade em setores de resgate.
    ===============================================================
*/

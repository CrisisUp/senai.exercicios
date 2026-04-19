/**
 * @file atividade-extra39-bfs.cpp
 * @brief Algoritmo BFS: Rastreamento Automático de Cadeia de Contágio.
 * 
 * Demonstra a técnica de Busca em Largura (Breadth-First Search) para 
 * percorrer um grafo de forma sistemática, explorando vizinhos por níveis.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERMELHO = "\033[31m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
}

// --- 2. CLASSE DO GRAFO COM ALGORITMO DE TRAVESSIA ---

class RedeEpidemica {
private:
    int totalPessoas;
    vector<vector<int>> matriz; // Matriz de Adjacência
    vector<string> nomes;

public:
    RedeEpidemica(int n) : totalPessoas(n) {
        matriz.resize(n, vector<int>(n, 0));
        nomes.resize(n);
    }

    void setNome(int id, string nome) { nomes[id] = nome; }

    void registrarContato(int p1, int p2) {
        matriz[p1][p2] = 1;
        matriz[p2][p1] = 1;
    }

    /**
     * @brief Algoritmo BFS para descobrir a cadeia completa de exposição.
     * @param inicio ID da pessoa que testou positivo (Ponto Zero).
     */
    void executarBFS(int inicio) {
        cout << UI::VERMELHO << "\n[ALERTA]: Iniciando Rastreamento a partir de " << nomes[inicio] << UI::RESET << endl;

        vector<bool> visitado(totalPessoas, false); // Vetor de controle
        queue<int> fila; // Fila de processamento (O motor do BFS)

        // 1. Início do processo
        visitado[inicio] = true;
        fila.push(inicio);

        int nivel = 0;
        while (!fila.empty()) {
            int tamanhoNivel = fila.size();
            cout << "\n--- ONDA DE EXPOSIÇÃO " << nivel << " ---" << endl;

            // Processa todas as pessoas do nível atual
            for (int i = 0; i < tamanhoNivel; i++) {
                int atual = fila.front();
                fila.pop();

                cout << " >> " << nomes[atual] << " (Monitorado)" << endl;

                // 2. Explora vizinhos (Contatos)
                for (int vizinho = 0; vizinho < totalPessoas; vizinho++) {
                    if (matriz[atual][vizinho] == 1 && !visitado[vizinho]) {
                        visitado[vizinho] = true;
                        fila.push(vizinho);
                        cout << UI::AMARELO << "    [!] Risco detectado para: " << nomes[vizinho] << UI::RESET << endl;
                    }
                }
            }
            nivel++;
        }
        cout << UI::VERDE << "\n[SISTEMA]: Fim do rastreamento. Cadeia de contágio mapeada." << UI::RESET << endl;
    }
};

// --- 3. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << UI::CIANO << "===============================================" << endl;
    cout << "      G-TRACKER: ALGORITMO DE BUSCA BFS        " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Criando uma rede mais complexa (6 pessoas)
    RedeEpidemica rede(6);
    rede.setNome(0, "Cristiano (Ponto Zero)");
    rede.setNome(1, "Elizabeth");
    rede.setNome(2, "Joao");
    rede.setNome(3, "Maria");
    rede.setNome(4, "Carlos");
    rede.setNome(5, "Ana");

    // Montando a teia de contatos
    rede.registrarContato(0, 1); // Cristiano -> Elizabeth
    rede.registrarContato(0, 4); // Cristiano -> Carlos
    rede.registrarContato(1, 2); // Elizabeth -> Joao
    rede.registrarContato(2, 3); // Joao -> Maria
    rede.registrarContato(4, 5); // Carlos -> Ana

    // Executando o algoritmo a partir do Cristiano
    rede.executarBFS(0);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: TRAVESSIA BFS (BUSCA EM LARGURA)
    ===============================================================

    1. O CONCEITO DE "ONDA":
       - O BFS funciona como uma pedra jogada no lago. Ele explora 
         em círculos concêntricos. Primeiro todos a distância 1, 
         depois todos a distância 2, e assim por diante.

    2. POR QUE USAR UMA FILA (std::queue)?
       - A fila garante que a ordem de visita seja respeitada. Quem 
         é encontrado primeiro (contato direto) é processado antes 
         de seus próprios contatos (contatos indiretos).

    3. MARCAÇÃO DE VISITADOS:
       - Em um grafo, é fácil andar em círculos (A->B, B->A). O 
         vetor 'visitado' é o que impede o algoritmo de entrar em 
         um loop infinito, garantindo que cada nó seja tocado uma 
         única vez.

    4. COMPLEXIDADE:
       - O BFS tem complexidade O(V + A), onde V é o número de 
         vértices e A o de arestas. É um algoritmo extremamente 
         eficiente para encontrar o caminho mais curto em grafos 
         não-valorizados.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - DFS (Busca em Profundidade): Explora um caminho até o fim 
      antes de voltar.
    - Componentes Conectados: Descobrir se a rede está partida.
    - Algoritmos de GPS: Baseados em variações de travessia.
    ===============================================================
*/

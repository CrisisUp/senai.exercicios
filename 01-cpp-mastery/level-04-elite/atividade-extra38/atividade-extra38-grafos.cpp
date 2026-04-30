/**
 * @file atividade-extra38-grafos.cpp
 * @brief Epidemic-Graph: Mapeamento de Contágio via Matriz de Adjacência.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a representação de redes sociais complexas para análise de risco.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Adjacency Matrix Layout)
 * - Objeto MapaContagio: Alocado na STACK.
 * - vector<vector<int>>: O descritor mestre vive na STACK.
 * - Matriz 2D: Vetor de vetores alocado contiguamente na HEAP (O(V²) bytes).
 * - Eficiência de Acesso: Busca de aresta em tempo constante O(1).
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

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
    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. MOTOR DE ANÁLISE DE REDE (GRAFOS) ---

/**
 * @class MapaContagio
 * @brief Gerencia a conectividade entre indivíduos em um cenário de pandemia.
 */
class MapaContagio {
private:
    int numPessoas;
    vector<vector<int>> matriz; // Matriz de Adjacência (Binary Connectivity)
    vector<string> catalogoNomes;

public:
    /**
     * @brief Construtor: Inicializa matriz isolada O(V²).
     */
    MapaContagio(int n) : numPessoas(n) {
        matriz.resize(n, vector<int>(n, 0));
        catalogoNomes.resize(n, "Desconhecido");
    }

    /**
     * @brief Associa um nome amigável ao ID numérico.
     * @param nome Referência constante (Fantasma do CPU).
     */
    void registrarIdentidade(int id, const string& nome) {
        if (id >= 0 && id < numPessoas) catalogoNomes[id] = nome;
    }

    /**
     * @brief Cria uma aresta bidirecional entre dois vértices.
     */
    void registrarContato(int p1, int p2) {
        if (p1 >= 0 && p1 < numPessoas && p2 >= 0 && p2 < numPessoas) {
            matriz[p1][p2] = 1; // A -> B
            matriz[p2][p1] = 1; // B -> A (Sincronismo de Simetria)
            cout << UI::AMARELO << "[LOG]: Contato físico registrado entre " 
                 << UI::NEGRITO << catalogoNomes[p1] << UI::RESET 
                 << UI::AMARELO << " e " << UI::NEGRITO << catalogoNomes[p2] << UI::RESET << endl;
        }
    }

    /**
     * @brief Renderiza a matriz de adjacência com cores de calor.
     */
    void exibirMatriz() const {
        cout << "\n" << UI::NEGRITO << "--- MATRIZ DE ADJACÊNCIA (TOPOLOGIA DA REDE) ---" << UI::RESET << endl;
        cout << "    ";
        for (int i = 0; i < numPessoas; i++) cout << i << " ";
        cout << endl;

        for (int i = 0; i < numPessoas; i++) {
            cout << i << " | ";
            for (int j = 0; j < numPessoas; j++) {
                if (matriz[i][j] == 1) cout << UI::VERMELHO << UI::NEGRITO << "1 " << UI::RESET;
                else cout << UI::RESET << "0 " << UI::RESET;
            }
            cout << "| " << UI::CIANO << catalogoNomes[i] << UI::RESET << endl;
        }
    }

    /**
     * @brief Lista todos os vizinhos diretos de um vértice.
     */
    void analisarExposicao(int p) const {
        if (p < 0 || p >= numPessoas) return;

        cout << "\nANÁLISE DE EXPOSIÇÃO PARA: " << UI::CIANO << UI::NEGRITO << catalogoNomes[p] << UI::RESET << endl;
        bool temExposicao = false;
        for (int j = 0; j < numPessoas; j++) {
            if (matriz[p][j] == 1) {
                cout << " -> Contato de risco detectado com: " << UI::NEGRITO << catalogoNomes[j] << UI::RESET << " (ID " << j << ")" << endl;
                temExposicao = true;
            }
        }
        if (!temExposicao) cout << UI::VERDE << " -> Nenhum contato registrado. Isolamento social mantido." << UI::RESET << endl;
    }
};

// --- 3. EXECUÇÃO DA VIGILÂNCIA SANITÁRIA ---

int main()
{
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      EPIDEMIC-GRAPH: RASTREADOR DE VÍRUS v2.0 " << endl;
    cout << "       (Elite Computational Epidemiology)      " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Rede de 6 indivíduos (Vértices 0 a 5)
    MapaContagio rede(6);
    
    rede.registrarIdentidade(0, "Cristiano");
    rede.registrarIdentidade(1, "Elizabeth");
    rede.registrarIdentidade(2, "Joao");
    rede.registrarIdentidade(3, "Maria");
    rede.registrarIdentidade(4, "Carlos");
    rede.registrarIdentidade(5, "Ana (Visitante)");

    // Simulação de eventos de contato
    rede.registrarContato(0, 1); 
    rede.registrarContato(1, 2); 
    rede.registrarContato(2, 3); 
    rede.registrarContato(0, 4); 
    rede.registrarContato(4, 5); 

    // Renderização Visual
    rede.exibirMatriz();

    // Consultas Forenses
    rede.analisarExposicao(0); // Quem Cristiano pode ter exposto?
    rede.analisarExposicao(5); // Quem Ana visitou?

    cout << "\n" << UI::VERDE << UI::NEGRITO << "Sincronização de rede concluída. Dados prontos para modelagem." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ESTRUTURAS NÃO-LINEARES (GRAFOS)
    ===============================================================

    1. O PODER DOS GRAFOS:
       - Diferente de listas ou pilhas, os grafos representam relações 
         arbitrárias. Se você tem "muitos para muitos", você tem 
         um grafo.

    2. MATRIZ DE ADJACÊNCIA (TRADE-OFFS):
       - É a estrutura favorita para grafos DENSOS (muitas arestas). 
         A memória é fixa em V², mas a velocidade de saber se A 
         conhece B é o limite físico do silício (O(1)).

    3. SIMETRIA E NÃO-DIRECIONAMENTO:
       - No contágio físico, o grafo é não-direcionado. Garantir que 
         matriz[i][j] == matriz[j][i] é uma responsabilidade 
         do desenvolvedor de sistemas para evitar falhas de lógica.

    4. PROTEÇÃO FANTASMA DO CPU:
       - Note o uso de 'vector<vector<int>>'. Embora dinâmico, o 
         acesso bi-indexado [][] é extremamente otimizado pelos 
         compiladores modernos, mantendo a performance de arrays 
         C puros.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - BFS/DFS: Algoritmos de busca para percorrer o grafo.
    - Dijkstra: Encontrar o caminho mais curto (mínimo contágio).
    - Adjacency List: Otimização de RAM para grafos esparsos.
    ===============================================================
*/

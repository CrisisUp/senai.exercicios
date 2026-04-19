/**
 * @file atividade-extra38-grafos.cpp
 * @brief Rastreamento de Contágio: Introdução a Grafos e Matriz de Adjacência.
 * 
 * Demonstra como representar conexões complexas entre entidades (Pessoas)
 * utilizando uma matriz de adjacência para mapear arestas em um grafo.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERMELHO = "\033[31m";
    const string VERDE    = "\033[32m";
    const string CIANO    = "\033[36m";
    const string AMARELO  = "\033[33m";
}

// --- 2. CLASSE GESTORA DE GRAFOS ---

class MapaContagio {
private:
    int numPessoas;
    vector<vector<int>> matriz; // Matriz de Adjacência
    vector<string> nomes;      // Mapeamento de índice para nome real

public:
    MapaContagio(int n) : numPessoas(n) {
        // Inicializa matriz n x n com zeros (sem contatos iniciais)
        matriz.resize(n, vector<int>(n, 0));
        nomes.resize(n, "Desconhecido");
    }

    void setNome(int id, string nome) {
        if (id >= 0 && id < numPessoas) nomes[id] = nome;
    }

    /**
     * @brief Cria uma aresta entre dois vértices (contato entre pessoas).
     * Como é um contato físico, o grafo é NÃO-DIRECIONADO (A encontrou B = B encontrou A).
     */
    void registrarContato(int p1, int p2) {
        if (p1 >= 0 && p1 < numPessoas && p2 >= 0 && p2 < numPessoas) {
            matriz[p1][p2] = 1;
            matriz[p2][p1] = 1;
            cout << UI::AMARELO << "[CONTATO]: " << nomes[p1] << " <---> " << nomes[p2] << UI::RESET << endl;
        }
    }

    void exibirMatriz() const {
        cout << "\n--- MATRIZ DE ADJACÊNCIA (MAPA DE REDE) ---" << endl;
        cout << "    ";
        for (int i = 0; i < numPessoas; i++) cout << i << " ";
        cout << endl;

        for (int i = 0; i < numPessoas; i++) {
            cout << i << " | ";
            for (int j = 0; j < numPessoas; j++) {
                if (matriz[i][j] == 1) cout << UI::VERMELHO << "1 " << UI::RESET;
                else cout << "0 ";
            }
            cout << "| " << nomes[i] << endl;
        }
    }

    void listarContatos(int p) const {
        cout << "\nContatos diretos de " << UI::CIANO << nomes[p] << UI::RESET << ":" << endl;
        bool teveContato = false;
        for (int j = 0; j < numPessoas; j++) {
            if (matriz[p][j] == 1) {
                cout << " -> " << nomes[j] << " (ID: " << j << ")" << endl;
                teveContato = true;
            }
        }
        if (!teveContato) cout << " (Isolamento total: Nenhum contato registrado)" << endl;
    }
};

// --- 3. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << UI::CIANO << "===============================================" << endl;
    cout << "      EPIDEMIC-GRAPH: RASTREADOR DE VÍRUS      " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Criando um grupo de 5 pessoas (Vértices 0 a 4)
    MapaContagio rede(5);
    
    rede.setNome(0, "Cristiano");
    rede.setNome(1, "Elizabeth");
    rede.setNome(2, "Joao");
    rede.setNome(3, "Maria");
    rede.setNome(4, "Carlos");

    // Simulando encontros (Criando Arestas)
    rede.registrarContato(0, 1); // Cristiano encontrou Elizabeth
    rede.registrarContato(1, 2); // Elizabeth encontrou João
    rede.registrarContato(2, 3); // João encontrou Maria
    rede.registrarContato(0, 4); // Cristiano encontrou Carlos

    // Visualizando o Grafo
    rede.exibirMatriz();

    // Consultando riscos
    rede.listarContatos(0); // Quem Cristiano pode ter infectado?
    rede.listarContatos(3); // Quem Maria encontrou?

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: INTRODUÇÃO A GRAFOS
    ===============================================================

    1. O QUE SÃO GRAFOS?
       - É uma estrutura composta por Vértices (os círculos) e 
         Arestas (as linhas que os unem). São ideais para 
         representar redes onde os elementos não seguem uma fila.

    2. MATRIZ DE ADJACÊNCIA:
       - É a forma mais simples de guardar um grafo. Se você tem 
         N vértices, usa uma matriz N x N. 
       - Vantagem: É instantâneo (O(1)) saber se A está conectado a B.
       - Desvantagem: Gasta muita memória (N²) se o grafo for gigante.

    3. GRAFO NÃO-DIRECIONADO:
       - Como neste exemplo de contato físico, se A toca B, B 
         automaticamente toca A. Por isso a matriz é SIMÉTRICA 
         (o triângulo superior é igual ao inferior).

    4. A IMPORTÂNCIA NO MUNDO REAL:
       - O Google é um grande grafo de páginas web. O Facebook é 
         um grande grafo de pessoas. O GPS é um grafo de ruas.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Grafo Direcionado (Dígrafo): Quando a relação tem sentido único.
    - Grafo Valorizado: Quando a aresta tem um "peso" (ex: distância).
    - Lista de Adjacência: Uma alternativa à matriz usando listas.
    ===============================================================
*/

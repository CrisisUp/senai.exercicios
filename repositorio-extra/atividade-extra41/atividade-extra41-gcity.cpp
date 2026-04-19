/**
 * @file atividade-extra41-gcity.cpp
 * @brief DESAFIO SUPREMO DE REDES: Smart City Central Hub (G-CITY).
 * 
 * Integração total de:
 * - Algoritmos: Dijkstra (Rotas) e BFS (Alertas em Onda).
 * - Padrões: Singleton (Validação) e Observer (Notificações).
 * - POO Avançada e STL avançada.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

// --- 1. INTERFACE E CORES (UI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string VERMELHO = "\033[31m";
    const string CIANO    = "\033[36m";
    const string AMARELO  = "\033[33m";
    const string NEGRITO  = "\033[1m";
    const int INF = 99999;

    void limpar() { cout << "\033[2J\033[1;1H"; }
    void banner() {
        cout << CIANO << "===============================================" << endl;
        cout << "      G-CITY: SMART CITY CENTRAL HUB v1.0      " << endl;
        cout << "===============================================" << RESET << endl;
    }
}

// --- 2. SINGLETON: VALIDADOR DE ENTRADA ---

class ValidadorUrbano {
private:
    ValidadorUrbano() {}
public:
    static ValidadorUrbano& get() {
        static ValidadorUrbano instancia;
        return instancia;
    }

    template <typename T>
    T ler(string msg) {
        T dado;
        while (true) {
            cout << msg;
            if (cin >> dado) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return dado;
            }
            cout << UI::VERMELHO << " [ERRO]: Entrada inválida." << UI::RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
};

// --- 3. PADRÃO OBSERVER: SISTEMA DE ALERTA DE BAIRROS ---

class IBairroMonitorado {
public:
    virtual void receberAlerta(string motivo, int nivel) = 0;
    virtual ~IBairroMonitorado() {}
};

class BairroResidencial : public IBairroMonitorado {
private:
    string nome;
public:
    BairroResidencial(string n) : nome(n) {}
    void receberAlerta(string motivo, int nivel) override {
        cout << UI::AMARELO << " [MORADOR-" << nome << "]: Alerta de " << motivo 
             << " (Risco: " << nivel << "). Evite sair de casa." << UI::RESET << endl;
    }
};

// --- 4. O HUB DA SMART CITY (GRAFOS E ALGORITMOS) ---

class GCityHub {
private:
    int n;
    vector<vector<int>> mapa; // Dijkstra
    vector<string> nomesBairros;
    vector<IBairroMonitorado*> observadores;

public:
    GCityHub(int _n) : n(_n) {
        mapa.resize(n, vector<int>(n, UI::INF));
        for(int i=0; i<n; i++) mapa[i][i] = 0;
        nomesBairros.resize(n);
        observadores.resize(n, nullptr);
    }

    void configurarBairro(int id, string nome) {
        nomesBairros[id] = nome;
        observadores[id] = new BairroResidencial(nome);
    }

    void conectarVias(int b1, int b2, int tempo) {
        mapa[b1][b2] = tempo;
        mapa[b2][b1] = tempo;
    }

    // --- ALGORITMO 1: DIJKSTRA (Rota de Ambulância) ---
    void despacharAmbulancia(int origem, int destino) {
        vector<int> dist(n, UI::INF);
        vector<int> ant(n, -1);
        vector<bool> visitado(n, false);

        dist[origem] = 0;
        for (int i = 0; i < n - 1; i++) {
            int u = -1;
            for(int j=0; j<n; j++) if(!visitado[j] && (u==-1 || dist[j]<dist[u])) u=j;
            if(dist[u] == UI::INF) break;
            visitado[u] = true;
            for(int v=0; v<n; v++) {
                if(dist[u] + mapa[u][v] < dist[v]) {
                    dist[v] = dist[u] + mapa[u][v];
                    ant[v] = u;
                }
            }
        }

        cout << UI::VERDE << "\n[LOGÍSTICA]: Rota de emergência calculada!" << UI::RESET << endl;
        cout << "Tempo total: " << dist[destino] << " min." << endl;
        
        vector<int> path;
        for(int v=destino; v!=-1; v=ant[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        
        cout << "Trajeto: ";
        for(int i=0; i<path.size(); i++) cout << nomesBairros[path[i]] << (i<path.size()-1 ? " -> " : "");
        cout << endl;
    }

    // --- ALGORITMO 2: BFS + OBSERVER (Onda de Alerta Sanitário) ---
    void simularContagio(int inicio) {
        cout << UI::VERMELHO << "\n[EPIDEMIA]: Surto detectado em " << nomesBairros[inicio] << "!" << UI::RESET << endl;
        
        queue<int> q;
        vector<int> nivel(n, -1);
        
        q.push(inicio);
        nivel[inicio] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            
            // Notifica via Observer
            if (observadores[u]) observadores[u]->receberAlerta("Propagação Viral", nivel[u]);

            for (int v = 0; v < n; v++) {
                if (mapa[u][v] != UI::INF && mapa[u][v] > 0 && nivel[v] == -1) {
                    nivel[v] = nivel[u] + 1;
                    q.push(v);
                }
            }
        }
    }

    ~GCityHub() {
        for (auto o : observadores) delete o;
    }
};

// --- 5. MAIN ---

int main()
{
    UI::limpar();
    UI::banner();

    GCityHub gcity(5);
    gcity.configurarBairro(0, "Centro");
    gcity.configurarBairro(1, "Norte");
    gcity.configurarBairro(2, "Sul");
    gcity.configurarBairro(3, "Leste");
    gcity.configurarBairro(4, "Oeste");

    // Mapa de vias (Tempos em minutos)
    gcity.conectarVias(0, 1, 5);  // Centro -> Norte (5 min)
    gcity.conectarVias(0, 2, 10); // Centro -> Sul (10 min)
    gcity.conectarVias(1, 3, 2);  // Norte -> Leste (2 min)
    gcity.conectarVias(2, 4, 3);  // Sul -> Oeste (3 min)
    gcity.conectarVias(3, 4, 15); // Leste -> Oeste (15 min)

    ValidadorUrbano& val = ValidadorUrbano::get();
    int opt = 0;

    do {
        cout << "\n--- PAINEL DO GESTOR URBANO ---" << endl;
        cout << "[1] Calcular Rota Ambulância" << endl;
        cout << "[2] Simular Alerta Sanitário (BFS)" << endl;
        cout << "[3] Sair" << endl;
        opt = val.ler<int>("Ação: ");

        if (opt == 1) {
            int d = val.ler<int>("Destino da Emergência (0-4): ");
            gcity.despacharAmbulancia(0, d); // Sempre sai do Centro (Hospital)
        }
        else if (opt == 2) {
            int b = val.ler<int>("Ponto de Origem do Surto (0-4): ");
            gcity.simularContagio(b);
        }

    } while (opt != 3);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: O ÁPICE DA INTEGRAÇÃO (G-CITY)
    ===============================================================

    1. SINFONIA ALGORÍTMICA:
       - No G-CITY, os algoritmos não estão isolados. O BFS detecta 
         a propagação (Rede Social/Física) e o Dijkstra resolve a 
         logística (Mapa Físico). Essa é a base de softwares de 
         Gestão de Crises reais.

    2. INTEGRAÇÃO DE PADRÕES:
       - O Singleton Validador protege o sistema.
       - O Observer garante que os bairros reajam às notificações 
         do Hub de forma independente e automática.

    3. MATURIDADE TÉCNICA:
       - O uso de ponteiros para interfaces, templates de leitura, 
         e a manipulação de grafos valorizados e não-valorizados 
         simultaneamente mostra que o aluno atingiu o nível de 
         Arquiteto de Sistemas.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Geo-fencing: Notificar dispositivos baseados em GPS.
    - Big Data Urbano: Analisar milhões de sensores em grafos gigantes.
    - Protocolos de Redes Mesh: Como o G-CITY funcionaria sem internet.
    ===============================================================
*/

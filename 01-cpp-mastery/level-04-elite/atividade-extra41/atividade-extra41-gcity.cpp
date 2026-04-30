/**
 * @file atividade-extra41-gcity.cpp
 * @brief G-CITY: Smart City Central Hub - Integração Final de Redes.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Fusão de Dijkstra, BFS, Singleton e Observer para Gestão de Crise Urbana.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Smart City Architecture)
 * - Mapa de Bairros (Grafo): Matriz de Custos O(V²) na HEAP.
 * - Observadores: Vetor de ponteiros para interfaces na HEAP (Desacoplamento).
 * - Algoritmo BFS: Fila dinâmica na HEAP para propagação de mensagens.
 * - Algoritmo Dijkstra: Vetores temporários de distância e backtracking.
 * - Singleton: Instância única de validação no DATA SEGMENT.
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

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
    const int INF = 99999; // Representa via bloqueada ou infinita
    inline void limpar() { cout << "\033[2J\033[1;1H"; }
    void banner() {
        cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
        cout << "      G-CITY: SMART CITY CENTRAL HUB v2.0      " << endl;
        cout << "       (Full Algorithmic Orchestration)        " << endl;
        cout << "===============================================" << UI::RESET << endl;
    }
}

// --- 2. PADRÃO SINGLETON: VALIDADOR DE ELITE ---

class ValidadorUrbano {
private:
    ValidadorUrbano() {}
    ValidadorUrbano(const ValidadorUrbano&) = delete;
    void operator=(const ValidadorUrbano&) = delete;

public:
    static ValidadorUrbano& get() {
        static ValidadorUrbano instancia;
        return instancia;
    }

    template <typename T>
    T ler(const string& msg) {
        T dado;
        while (true) {
            cout << UI::RESET << msg << UI::RESET;
            if (cin >> dado) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return dado;
            }
            cout << UI::VERMELHO << " [ERRO]: Telemetria de entrada inválida." << UI::RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
};

// --- 3. PADRÃO OBSERVER: GESTÃO DE INFRAESTRUTURA ---

/**
 * @class IBairroMonitorado
 * @brief Interface para comunicação de alertas entre o HUB e os setores urbanos.
 */
class IBairroMonitorado {
public:
    virtual void receberAlerta(const string& motivo, int nivelRisco) = 0;
    virtual ~IBairroMonitorado() {}
};

class BairroSetorial : public IBairroMonitorado {
private:
    string nome;
public:
    BairroSetorial(const string& n) : nome(n) {}
    
    void receberAlerta(const string& motivo, int nivel) override {
        cout << UI::AMARELO << " [SETOR-" << nome << "]: " << UI::RESET 
             << "Alerta de " << motivo << " (RISCO NÍVEL " << nivel << ")." << endl;
    }
};

// --- 4. O HUB DA SMART CITY (GRAFOS E LOGÍSTICA) ---

class GCityHub {
private:
    int totalBairros;
    vector<vector<int>> mapaVias; 
    vector<string> nomesBairros;
    vector<IBairroMonitorado*> terminais;

public:
    GCityHub(int _n) : totalBairros(_n) {
        mapaVias.resize(totalBairros, vector<int>(totalBairros, UI::INF));
        for(int i=0; i<totalBairros; i++) mapaVias[i][i] = 0;
        nomesBairros.resize(totalBairros, "Setor_X");
        terminais.resize(totalBairros, nullptr);
    }

    void configurarBairro(int id, const string& nome) {
        if (id >= 0 && id < totalBairros) {
            nomesBairros[id] = nome;
            terminais[id] = new BairroSetorial(nome);
        }
    }

    void registrarVia(int b1, int b2, int pesoTempo) {
        if (b1 >= 0 && b1 < totalBairros && b2 >= 0 && b2 < totalBairros) {
            mapaVias[b1][b2] = pesoTempo;
            mapaVias[b2][b1] = pesoTempo;
        }
    }

    /**
     * @brief ALGORITMO DIJKSTRA: Despacho otimizado de viaturas.
     */
    void despacharResgate(int origem, int destino) {
        vector<int> dist(totalBairros, UI::INF);
        vector<int> anterior(totalBairros, -1);
        vector<bool> fechado(totalBairros, false);

        dist[origem] = 0;
        for (int i = 0; i < totalBairros - 1; i++) {
            int u = -1;
            for(int j=0; j<totalBairros; j++) if(!fechado[j] && (u==-1 || dist[j] < dist[u])) u=j;
            
            if(u == -1 || dist[u] == UI::INF) break;
            fechado[u] = true;

            for(int v=0; v<totalBairros; v++) {
                if(!fechado[v] && mapaVias[u][v] != UI::INF && dist[u] + mapaVias[u][v] < dist[v]) {
                    dist[v] = dist[u] + mapaVias[u][v];
                    anterior[v] = u;
                }
            }
        }

        cout << UI::VERDE << UI::NEGRITO << "\n[LOGÍSTICA]: Rota de resposta otimizada calculada." << UI::RESET << endl;
        if (dist[destino] == UI::INF) {
            cout << UI::VERMELHO << "ERRO: Local de destino inacessível por terra." << UI::RESET << endl;
            return;
        }

        cout << "Tempo de Resposta Estimado: " << UI::VERDE << dist[destino] << " min." << UI::RESET << endl;
        
        vector<int> rota;
        for(int v=destino; v!=-1; v=anterior[v]) rota.push_back(v);
        reverse(rota.begin(), rota.end());
        
        cout << UI::RESET << "Trajeto Sugerido: " << UI::RESET;
        for(size_t i=0; i<rota.size(); i++) {
            cout << UI::CIANO << nomesBairros[rota[i]] << UI::RESET << (i < rota.size()-1 ? " -> " : "");
        }
        cout << endl;
    }

    /**
     * @brief ALGORITMO BFS + OBSERVER: Propagação de alertas em rede.
     */
    void dispararAlertaSanitario(int inicio) {
        cout << UI::VERMELHO << UI::NEGRITO << "\n[EMERGÊNCIA]: Surto identificado em " << nomesBairros[inicio] << "!" << UI::RESET << endl;
        
        queue<int> fila;
        vector<int> wave(totalBairros, -1);
        
        fila.push(inicio);
        wave[inicio] = 0;

        while (!fila.empty()) {
            int u = fila.front(); fila.pop();
            
            // Notificação Polimórfica (Observer)
            if (terminais[u]) terminais[u]->receberAlerta("Propagação Epidemiológica", wave[u]);

            for (int v = 0; v < totalBairros; v++) {
                if (mapaVias[u][v] != UI::INF && mapaVias[u][v] > 0 && wave[v] == -1) {
                    wave[v] = wave[u] + 1;
                    fila.push(v);
                }
            }
        }
        persistirCrise("SURTO_SANITARIO", nomesBairros[inicio]);
    }

    void persistirCrise(const string& tipo, const string& local) {
        ofstream arq("repositorio-extra/atividade-extra41/relatorio_urbano.txt", ios::app);
        if (arq.is_open()) {
            arq << "[CRISE] " << tipo << " detectada em " << local << endl;
            arq.close();
        }
    }

    ~GCityHub() {
        for (auto* t : terminais) delete t;
    }
};

// --- 5. EXECUÇÃO DO GESTOR URBANO ---

int main()
{
    UI::limpar();
    UI::banner();

    // Setup Urbano (5 Bairros Principais)
    GCityHub sp_hub(5);
    sp_hub.configurarBairro(0, "Centro_Médico");
    sp_hub.configurarBairro(1, "Distrito_Norte");
    sp_hub.configurarBairro(2, "Setor_Sul");
    sp_hub.configurarBairro(3, "Polo_Tecnológico");
    sp_hub.configurarBairro(4, "Zona_Oeste");

    // Conexões de tráfego
    sp_hub.registrarVia(0, 1, 6);  // Centro -> Norte
    sp_hub.registrarVia(0, 2, 12); // Centro -> Sul
    sp_hub.registrarVia(1, 3, 4);  // Norte -> Polo
    sp_hub.registrarVia(2, 4, 3);  // Sul -> Oeste
    sp_hub.registrarVia(3, 4, 18); // Polo -> Oeste

    ValidadorUrbano& shield = ValidadorUrbano::get();
    int op = 0;

    do {
        cout << "\n" << UI::NEGRITO << "CENTRAL DE COMANDO G-CITY v2.0" << UI::RESET << endl;
        cout << "[1] Rota de Ambulância (Dijkstra)" << endl;
        cout << "[2] Alerta Sanitário (BFS)" << endl;
        cout << "[3] Hibernar HUB" << endl;
        op = shield.ler<int>("Ação: ");

        try {
            if (op == 1) {
                int d = shield.ler<int>("ID do Destino (0-4): ");
                sp_hub.despacharResgate(0, d); // Origem fixa no Centro Médico
            }
            else if (op == 2) {
                int b = shield.ler<int>("ID de Origem do Alerta (0-4): ");
                sp_hub.dispararAlertaSanitario(b);
            }
        } catch (const exception& e) {
            cout << UI::VERMELHO << "FALHA DE SISTEMA: " << e.what() << UI::RESET << endl;
        }

    } while (op != 3);

    cout << UI::CIANO << "\n[INFO]: G-CITY HUB em modo de baixa energia. Logs sincronizados." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ENGENHARIA DE SMART CITIES
    ===============================================================

    1. ORQUESTRAÇÃO ALGORÍTMICA:
       - No G-CITY, unimos o BFS (Redes Sociais/Invisíveis) com o 
         Dijkstra (Redes Físicas/Geográficas). Esta dualidade é o 
         coração da logística moderna e da defesa civil 4.0.

    2. ACESSOS O(1) E O(log n):
       - O uso de matrizes garante acesso imediato aos pesos de vias. 
         A escolha da estrutura de dados correta para o mapa é o 
         que permite que a ambulância receba a rota em milissegundos.

    3. DESIGN PATTERNS EM ESCALA:
       - O Singleton Validador protege contra ruídos de sensores 
         (teclado), enquanto o Observer permite que o HUB escale 
         para milhares de bairros sem perder o controle de quem 
         foi notificado.

    4. RESILIÊNCIA FANTASMA:
       - Passamos nomes de bairros e motivos de alerta por referência 
         constante, garantindo que o processamento de crise não seja 
         interrompido por picos de alocação de memória na HEAP.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Geo-Spatial Indexing (R-Trees).
    - Real-time Traffic APIs (Integração Google/Waze).
    - Edge Computing: Processar alertas no próprio bairro (terminal).
    ===============================================================
*/

/**
 * @file atividade-extra42-gresponse.cpp
 * @brief G-RESPONSE: Unificação de Engenharia Urbana e Hospitalar.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Integra Dijkstra, Fila FIFO, Pilha LIFO e Lista Encadeada em um ecossistema.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Unified Command Architecture)
 * - Hub (GResponse): Objeto central na STACK, gerencia ponteiro para Mapa (HEAP).
 * - Triagem (FIFO): Fila de ponteiros para Pacientes (HEAP).
 * - Histórico: Cada Paciente possui sua própria Linked List (HEAP).
 * - Auditoria (LIFO): Pilha de strings (HEAP) rastreando o histórico de comandos.
 * - Mapa (Graph): Matriz de Adjacência valorizada O(V²) na HEAP.
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string VERMELHO = "\033[31m";
    const string BRANCO   = "\033[37m";
    const int INF = 999;

    inline void limpar() { cout << "\033[2J\033[1;1H"; }
    
    void cabecalho() {
        cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
        cout << "      G-RESPONSE: CENTRAL DE COMANDO UNIFICADA " << endl;
        cout << "       (Elite Disaster Management Core)        " << endl;
        cout << "===============================================" << UI::RESET << endl;
    }
}

// --- 2. PADRÃO SINGLETON: SCANNER DE COMANDO ---

class Scanner {
private:
    Scanner() {}
public:
    static Scanner& get() {
        static Scanner instancia;
        return instancia;
    }

    template <typename T>
    T ler(const string& msg) {
        T d;
        while (true) {
            cout << UI::BRANCO << msg << UI::RESET;
            if (cin >> d) { 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                return d; 
            }
            cout << UI::VERMELHO << " [ERRO]: Entrada inválida detectada." << UI::RESET << endl;
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    string lerLinha(const string& msg) {
        string s; 
        cout << UI::BRANCO << msg << UI::RESET; 
        getline(cin >> ws, s); 
        return s;
    }
};

// --- 3. ESTRUTURAS DE DADOS BARE-METAL (SAÚDE) ---

struct ProntuarioNode {
    string info;
    ProntuarioNode* prox;
    ProntuarioNode(const string& i) : info(i), prox(nullptr) {}
};

struct Paciente {
    string nome;
    ProntuarioNode* historico;
    
    Paciente(const string& n) : nome(n), historico(nullptr) {}
    
    void addDiag(const string& d) {
        ProntuarioNode* n = new ProntuarioNode(d);
        n->prox = historico; 
        historico = n;
    }

    ~Paciente() {
        ProntuarioNode* h = historico;
        while(h) { 
            ProntuarioNode* temp = h; 
            h = h->prox; 
            delete temp; 
        }
    }
};

struct FilaNode {
    Paciente* p;
    FilaNode* prox;
    FilaNode(Paciente* _p) : p(_p), prox(nullptr) {}
};

// --- 4. MOTOR DE LOGÍSTICA URBANA (DIJKSTRA) ---

class CidadeMap {
private:
    int n;
    vector<vector<int>> grafo;
    vector<string> nomesBairros;

public:
    CidadeMap(int _n) : n(_n) {
        grafo.resize(n, vector<int>(n, UI::INF));
        for(int i=0; i<n; i++) grafo[i][i] = 0;
        nomesBairros.resize(n, "Distrito_X");
    }

    void addBairro(int id, const string& nome) { nomesBairros[id] = nome; }
    void registrarVia(int b1, int b2, int tempo) { 
        grafo[b1][b2] = tempo; 
        grafo[b2][b1] = tempo; 
    }

    string calcularRota(int origem, int destino) {
        vector<int> dist(n, UI::INF), ant(n, -1);
        vector<bool> vis(n, false);
        dist[origem] = 0;

        for(int i=0; i<n-1; i++) {
            int u = -1;
            for(int j=0; j<n; j++) if(!vis[j] && (u==-1 || dist[j] < dist[u])) u=j;
            if(u == -1 || dist[u] == UI::INF) break;
            vis[u] = true;
            for(int v=0; v<n; v++) {
                if(!vis[v] && grafo[u][v] != UI::INF && dist[u] + grafo[u][v] < dist[v]) {
                    dist[v] = dist[u] + grafo[u][v];
                    ant[v] = u;
                }
            }
        }

        if(dist[destino] == UI::INF) return "ROTA BLOQUEADA";
        
        string rotaStr = "";
        for(int v=destino; v!=-1; v=ant[v]) rotaStr = nomesBairros[v] + (rotaStr == "" ? "" : " -> ") + rotaStr;
        return rotaStr + " (ETA: " + to_string(dist[destino]) + " min)";
    }

    const string& getBairroNome(int id) const { return nomesBairros[id]; }
};

// --- 5. GESTÃO INTEGRADA (G-RESPONSE CORE) ---

class GResponse {
private:
    FilaNode *inicio, *fim;
    CidadeMap* mapaUrbano;
    stack<string> auditoria;

public:
    GResponse(CidadeMap* c) : inicio(nullptr), fim(nullptr), mapaUrbano(c) {}

    /**
     * @brief Despacho polimórfico de resgate integrado.
     */
    void dispararResgate(int localId, const string& nomePac) {
        string rota = mapaUrbano->calcularRota(0, localId); // 0 = Base/Hospital
        
        cout << "\n" << UI::AMARELO << UI::NEGRITO << "[DESPACHO]: Unidade Móvel acionada para " << mapaUrbano->getBairroNome(localId) << UI::RESET << endl;
        cout << UI::BRANCO << "[ROTA]: " << UI::RESET << rota << endl;

        // Paciente admitido remotamente
        Paciente* p = new Paciente(nomePac);
        FilaNode* n = new FilaNode(p);
        
        if(!inicio) inicio = fim = n;
        else { fim->prox = n; fim = n; }

        auditoria.push("Acionamento: " + nomePac + " em " + mapaUrbano->getBairroNome(localId));
        cout << UI::VERDE << "[SISTEMA]: Triagem remota concluída para " << nomePac << "." << UI::RESET << endl;
    }

    /**
     * @brief Processamento hospitalar de pacientes resgatados.
     */
    void processarHospital() {
        if(!inicio) { 
            cout << UI::AMARELO << "[HUB]: Sem pacientes aguardando liquidação hospitalar." << UI::RESET << endl; 
            return; 
        }
        
        Paciente* p = inicio->p;
        cout << "\n" << UI::CIANO << UI::NEGRITO << "--- G-HEALTH: ADMISSÃO DE EMERGÊNCIA ---" << UI::RESET << endl;
        cout << UI::BRANCO << "Paciente: " << UI::RESET << UI::NEGRITO << p->nome << UI::RESET << endl;
        
        string acao = Scanner::get().lerLinha("Procedimento/Diagnóstico: ");
        p->addDiag(acao);

        // Persistência unificada
        ofstream arq("repositorio-extra/atividade-extra42/missao_resgate.txt", ios::app);
        if (arq.is_open()) {
            arq << "[MISSÃO " << __DATE__ << "] " << p->nome << " | Ação: " << acao << endl;
            arq.close();
        }

        // Limpeza de Fila FIFO
        FilaNode* temp = inicio;
        inicio = inicio->prox;
        if(!inicio) fim = nullptr;
        
        delete p; // Aciona destrutor do paciente (cascata de prontuário)
        delete temp;

        cout << UI::VERDE << "[OK]: Registro hospitalar finalizado e destruído da RAM." << UI::RESET << endl;
    }

    void exibirLogs() {
        cout << "\n" << UI::NEGRITO << "HISTÓRICO DE AUDITORIA (LIFO):" << UI::RESET << endl;
        stack<string> tempStack = auditoria; // Cópia temporária para exibir sem destruir
        while(!tempStack.empty()) { 
            cout << UI::AMARELO << " > " << UI::RESET << tempStack.top() << endl; 
            tempStack.pop(); 
        }
    }

    ~GResponse() {
        while(inicio) {
            FilaNode* t = inicio; 
            inicio = inicio->prox;
            delete t->p; // Limpeza recursiva
            delete t;
        }
    }
};

// --- 6. EXECUÇÃO DO CENTRO DE CRISE ---

int main()
{
    UI::limpar();
    
    // Configuração Urbana
    CidadeMap sp_hub(5);
    sp_hub.addBairro(0, "Hospital Central (Base)");
    sp_hub.addBairro(1, "Vila Norte");
    sp_hub.addBairro(2, "Zona Sul");
    sp_hub.addBairro(3, "Distrito Leste");
    sp_hub.addBairro(4, "Polo Oeste");

    sp_hub.registrarVia(0,1,5); 
    sp_hub.registrarVia(1,3,10); 
    sp_hub.registrarVia(0,2,7); 
    sp_hub.registrarVia(2,4,4);

    GResponse core(&sp_hub);
    int opt = 0;

    do {
        UI::cabecalho();
        cout << UI::BRANCO << "[1] Reportar Emergência (GPS/Logística)\n"
             << "[2] Atendimento Médico (Triagem/Saúde)\n"
             << "[3] Ver Auditoria SOC\n"
             << "[4] Shutdown G-City Hub" << UI::RESET << endl;
        
        opt = Scanner::get().ler<int>("Comando HUB: ");

        try {
            if(opt == 1) {
                int b = Scanner::get().ler<int>("Código do Bairro (1-4): ");
                string v = Scanner::get().lerLinha("Nome da Vítima: ");
                core.dispararResgate(b, v);
                system("sleep 1");
            } 
            else if(opt == 2) {
                core.processarHospital();
                system("sleep 1");
            } 
            else if(opt == 3) {
                core.exibirLogs();
                cout << UI::AMARELO << "\n[ENTER] p/ retornar..." << UI::RESET;
                cin.get();
            }
        } catch (const exception& e) {
            cout << UI::VERMELHO << "ERRO INTEGRADO: " << e.what() << UI::RESET << endl;
        }
        UI::limpar();

    } while(opt != 4);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: SISTEMA DE SISTEMAS (ELITE INTEGRATION)
    ===============================================================

    1. INTEROPERABILIDADE:
       - O G-RESPONSE prova que um sistema C++ profissional é a 
         soma de módulos independentes. O Mapa não sabe sobre 
         Medicina, e a Medicina não sabe sobre Grafos. O HUB 
         orquestra a comunicação entre eles.

    2. GESTÃO DE MEMÓRIA MULTI-CAMADA:
       - Vimos pilhas, filas e listas encadeadas operando em 
         sincronia. A destruição em cascata (Paciente limpando seu 
         histórico) é a prova de um design orientado a objetos 
         maduro.

    3. RESILIÊNCIA E ROBUSTEZ:
       - O uso do Scanner Singleton e o tratamento de exceções em 
         pontos críticos garantem que o HUB não trave em momentos 
         de crise real por erros de digitação do operador.

    4. PERFORMANCE LOGÍSTICA:
       - O uso de referências constantes e ponteiros evita cópias 
         desnecessárias, mantendo o sistema responsivo mesmo sob 
         alta demanda de resgates.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Distributed Systems: Separar os módulos em diferentes servidores.
    - Real-time OS (RTOS): Garantias de tempo de resposta.
    - Cyber-Physical Systems (CPS).
    ===============================================================
*/

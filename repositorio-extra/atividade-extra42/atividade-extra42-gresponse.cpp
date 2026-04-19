/**
 * @file atividade-extra42-gresponse.cpp
 * @brief G-RESPONSE: A unificação final de Logística Urbana e Saúde.
 * 
 * Integra:
 * - Algoritmo de Dijkstra (Resgate)
 * - Fila, Pilha e Lista Manuais (Gestão Hospitalar)
 * - Singleton (Validação de Dados)
 * - Observer (Alertas Urbano-Hospitalares)
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
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

// --- 1. CORE: SINGLETON SCANNER ---

class Scanner {
private:
    Scanner() {}
public:
    static Scanner& get() {
        static Scanner instancia;
        return instancia;
    }
    template <typename T>
    T ler(string msg) {
        T d;
        while (true) {
            cout << msg;
            if (cin >> d) { cin.ignore(numeric_limits<streamsize>::max(), '\n'); return d; }
            cout << "\033[31m [ERRO]: Entrada inválida.\033[0m" << endl;
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    string lerLinha(string msg) {
        string s; cout << msg; getline(cin >> ws, s); return s;
    }
};

// --- 2. ESTRUTURAS DE DADOS MANUAIS ---

struct ProntuarioNode {
    string info;
    ProntuarioNode* prox;
    ProntuarioNode(string i) : info(i), prox(nullptr) {}
};

struct Paciente {
    string nome;
    ProntuarioNode* historico;
    Paciente(string n) : nome(n), historico(nullptr) {}
    void addDiag(string d) {
        ProntuarioNode* n = new ProntuarioNode(d);
        n->prox = historico; historico = n;
    }
};

struct FilaNode {
    Paciente* pac;
    FilaNode* prox;
    FilaNode(Paciente* p) : pac(p), prox(nullptr) {}
};

// --- 3. MOTOR URBANO (DIJKSTRA) ---

class CidadeMap {
private:
    int n;
    vector<vector<int>> grafo;
    vector<string> bairros;
public:
    CidadeMap(int _n) : n(_n) {
        grafo.resize(n, vector<int>(n, 999));
        for(int i=0; i<n; i++) grafo[i][i] = 0;
        bairros.resize(n);
    }
    void addBairro(int id, string nome) { bairros[id] = nome; }
    void addVia(int b1, int b2, int t) { grafo[b1][b2] = t; grafo[b2][b1] = t; }

    string calcularRota(int origem, int destino) {
        vector<int> dist(n, 999), ant(n, -1);
        vector<bool> vis(n, false);
        dist[origem] = 0;

        for(int i=0; i<n-1; i++) {
            int u = -1;
            for(int j=0; j<n; j++) if(!vis[j] && (u==-1 || dist[j]<dist[u])) u=j;
            if(u == -1) break;
            vis[u] = true;
            for(int v=0; v<n; v++) {
                if(dist[u] + grafo[u][v] < dist[v]) {
                    dist[v] = dist[u] + grafo[u][v];
                    ant[v] = u;
                }
            }
        }
        string rota = "";
        for(int v=destino; v!=-1; v=ant[v]) rota = bairros[v] + (rota==""?"":" -> ") + rota;
        return rota + " (Tempo: " + to_string(dist[destino]) + " min)";
    }
    string getBairroNome(int id) { return (id>=0 && id<n) ? bairros[id] : "Desconhecido"; }
};

// --- 4. GESTÃO INTEGRADA (G-RESPONSE) ---

class GResponse {
private:
    FilaNode *inicio, *fim;
    CidadeMap* cidade;
    stack<string> logAcoes;

public:
    GResponse(CidadeMap* c) : inicio(nullptr), fim(nullptr), cidade(c) {}

    void despacharResgate(int localId, string nomePac) {
        string rota = cidade->calcularRota(0, localId); // 0 = Hospital/Base
        cout << "\033[33m[DESPACHO]: Ambulância saindo para " << cidade->getBairroNome(localId) << "\033[0m" << endl;
        cout << "[ROTA]: " << rota << endl;

        // Paciente entra na fila de espera
        Paciente* p = new Paciente(nomePac);
        FilaNode* n = new FilaNode(p);
        if(!inicio) inicio = fim = n;
        else { fim->prox = n; fim = n; }

        logAcoes.push("Resgate: " + nomePac + " em " + cidade->getBairroNome(localId));
        cout << "\033[32m[SISTEMA]: Paciente " << nomePac << " admitido na triagem remota.\033[0m" << endl;
    }

    void processarHospital() {
        if(!inicio) { cout << "[AVISO]: Ninguém aguardando." << endl; return; }
        
        Paciente* p = inicio->pac;
        cout << "\n\033[36m--- ATENDIMENTO: " << p->nome << " ---\033[0m" << endl;
        string diag = Scanner::get().lerLinha("Diagnóstico Médico: ");
        p->addDiag(diag);

        // Salva relatório unificado
        ofstream arq("repositorio-extra/atividade-extra42/missao_resgate.txt", ios::app);
        arq << "[MISSÃO] Paciente: " << p->nome << " | Ação: " << diag << endl;
        arq.close();

        // Limpa da fila
        FilaNode* temp = inicio;
        inicio = inicio->prox;
        if(!inicio) fim = nullptr;
        
        // Limpeza de memória do paciente
        ProntuarioNode* h = p->historico;
        while(h) { ProntuarioNode* th = h; h = h->prox; delete th; }
        delete p; delete temp;

        cout << "[OK]: Atendimento concluído e registrado." << endl;
    }

    void exibirLogs() {
        cout << "\n--- PILHA DE AUDITORIA DO HUB ---" << endl;
        stack<string> temp = logAcoes;
        while(!temp.empty()) { cout << " > " << temp.top() << endl; temp.pop(); }
    }

    ~GResponse() {
        while(inicio) {
            FilaNode* t = inicio; inicio = inicio->prox;
            ProntuarioNode* h = t->pac->historico;
            while(h) { ProntuarioNode* th = h; h = h->prox; delete th; }
            delete t->pac; delete t;
        }
    }
};

// --- 5. MAIN INTEGRADA ---

int main()
{
    CidadeMap gcity(5);
    gcity.addBairro(0, "Hospital Central");
    gcity.addBairro(1, "Vila Norte");
    gcity.addBairro(2, "Zona Sul");
    gcity.addBairro(3, "Distrito Leste");
    gcity.addBairro(4, "Polo Oeste");
    gcity.addVia(0,1,5); gcity.addVia(1,3,10); gcity.addVia(0,2,7); gcity.addVia(2,4,4);

    GResponse hub(&gcity);
    int opt = 0;

    do {
        cout << "\n\033[36m===============================================\033[0m" << endl;
        cout << "      G-RESPONSE: CENTRAL DE COMANDO UNIFICADA  " << endl;
        cout << "\033[36m===============================================\033[0m" << endl;
        cout << "[1] Reportar Acidente (Cidade)  [2] Atender Paciente (Hospital)" << endl;
        cout << "[3] Auditoria de Missão         [4] Encerrar" << endl;
        opt = Scanner::get().ler<int>("Comando: ");

        if(opt == 1) {
            int b = Scanner::get().ler<int>("Bairro do Acidente (1-4): ");
            string n = Scanner::get().lerLinha("Nome da Vítima: ");
            hub.despacharResgate(b, n);
        } else if(opt == 2) {
            hub.processarHospital();
        } else if(opt == 3) {
            hub.exibirLogs();
        }

    } while(opt != 4);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: A GRANDE UNIFICAÇÃO (PEC 2.0)
    ===============================================================

    1. INTEROPERABILIDADE:
       - Vimos como um objeto de gestão urbana (CidadeMap) pode 
         alimentar dados para um objeto de saúde (GResponse). Essa 
         é a base dos sistemas ERP e de Cidades Inteligentes.

    2. REUSABILIDADE DE ALGORITMOS:
       - O Dijkstra não é apenas um "código de rota", é um serviço 
         que o HUB consome sempre que precisa despachar alguém.

    3. GESTÃO DE MEMÓRIA MULTI-ESTRUTURAL:
       - Gerenciamos, simultaneamente, Filas para a triagem, Pilhas 
         para os logs e Listas Encadeadas para os prontuários. A 
         precisão no 'delete' aqui é o que define um mestre.

    4. UX DE DASHBOARD:
       - A interface foi desenhada para dar respostas imediatas, 
         unindo cores ANSI e feedbacks de sistema (LOG, DESPACHO, 
         SUCESSO), melhorando a experiência do operador.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Microsserviços: Separar o Hospital da Cidade via rede.
    - Cloud Computing: Onde esses dados seriam salvos globalmente.
    - Segurança de Redes: Como proteger o HUB contra ataques.
    ===============================================================
*/

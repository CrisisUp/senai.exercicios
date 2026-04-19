/**
 * @file atividade-extra37-hospital.cpp
 * @brief DESAFIO SUPREMO: G-HEALTH - Integrated Hospital Management System.
 * 
 * Este projeto é a síntese final de Estruturas Manuais e Padrões de Projeto:
 * - Fila FIFO (Recepção)
 * - Lista Encadeada (Prontuário Individual)
 * - Pilha LIFO (Auditoria de Eventos)
 * - Singleton (Validação Robusta)
 * - Gestão de Memória Dinâmica Manual.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <exception>

using namespace std;

// --- 1. INTERFACE E CORES (UI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string VERMELHO = "\033[31m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string NEGRITO  = "\033[1m";

    void limpar() { cout << "\033[2J\033[1;1H"; }
    void banner() {
        cout << CIANO << "===============================================" << endl;
        cout << "      G-HEALTH: SISTEMA HOSPITALAR v1.0        " << endl;
        cout << "===============================================" << RESET << endl;
    }
}

// --- 2. SINGLETON: SCANNER DE DADOS BLINDADO ---

class Scanner {
private:
    Scanner() {}
    Scanner(const Scanner&) = delete;
    void operator=(const Scanner&) = delete;

public:
    static Scanner& get() {
        static Scanner instancia;
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
            cout << UI::VERMELHO << " [ERRO]: Entrada inválida. Tente novamente." << UI::RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    string lerTexto(string msg) {
        string t;
        cout << msg;
        getline(cin >> ws, t);
        return t;
    }
};

// --- 3. ESTRUTURAS DINÂMICAS MANUAIS ---

// Nó do Prontuário (Lista Simples)
struct ProntuarioNode {
    string diagnostico;
    string data;
    ProntuarioNode* proximo;
    ProntuarioNode(string d, string dt) : diagnostico(d), data(dt), proximo(nullptr) {}
};

// Nó do Paciente (Para a Fila de Triagem)
struct Paciente {
    string nome;
    int idade;
    ProntuarioNode* historico; // Lista encadeada interna

    Paciente(string n, int i) : nome(n), idade(i), historico(nullptr) {}

    void adicionarAoProntuario(string diag) {
        ProntuarioNode* novo = new ProntuarioNode(diag, "19/04/2026");
        novo->proximo = historico;
        historico = novo;
    }
};

struct QueueNode {
    Paciente* paciente;
    QueueNode* proximo;
    QueueNode(Paciente* p) : paciente(p), proximo(nullptr) {}
};

// Nó da Auditoria (Pilha)
struct LogNode {
    string acao;
    LogNode* proximo;
    LogNode(string a) : acao(a), proximo(nullptr) {}
};

// --- 4. GESTOR DO HOSPITAL (A CLASSE MESTRE) ---

class GHealth {
private:
    // Fila FIFO (Triagem)
    QueueNode *inicioFila, *fimFila;
    
    // Pilha LIFO (Auditoria)
    LogNode* topoLogs;

    static int pacientesAtendidos;

public:
    GHealth() : inicioFila(nullptr), fimFila(nullptr), topoLogs(nullptr) {}

    // Lógica da Fila (FIFO)
    void registrarEntrada(string nome, int idade) {
        Paciente* p = new Paciente(nome, idade);
        QueueNode* novoNode = new QueueNode(p);
        
        if (!inicioFila) {
            inicioFila = fimFila = novoNode;
        } else {
            fimFila->proximo = novoNode;
            fimFila = novoNode;
        }
        registrarLog("Entrada: " + nome);
        cout << UI::VERDE << "[OK]: Paciente em triagem." << UI::RESET << endl;
    }

    void atenderProximo() {
        if (!inicioFila) {
            cout << UI::AMARELO << "[AVISO]: Fila vazia." << UI::RESET << endl;
            return;
        }
        QueueNode* temp = inicioFila;
        Paciente* p = temp->paciente;

        UI::limpar();
        cout << UI::CIANO << "--- CONSULTA MÉDICA ---" << UI::RESET << endl;
        cout << "Paciente: " << p->nome << " (" << p->idade << " anos)" << endl;
        
        string diag = Scanner::get().lerTexto("Digite o Diagnóstico: ");
        p->adicionarAoProntuario(diag);
        pacientesAtendidos++;
        
        registrarLog("Atendimento: " + p->nome);

        // Remove da fila
        inicioFila = inicioFila->proximo;
        if (!inicioFila) fimFila = nullptr;
        
        salvarExtrato(p);
        
        // Limpeza do paciente atendido (Neste sistema, assumimos que ele vai pra casa)
        deletarPaciente(p);
        delete temp;
        
        cout << UI::VERDE << "[SUCESSO]: Prontuário atualizado e salvo." << UI::RESET << endl;
        system("sleep 1");
    }

    void registrarLog(string acao) {
        LogNode* novo = new LogNode(acao);
        novo->proximo = topoLogs;
        topoLogs = novo;
    }

    void exibirLogs() {
        cout << "\n--- ÚLTIMOS EVENTOS (AUDITORIA) ---" << endl;
        LogNode* p = topoLogs;
        while (p) {
            cout << " >> " << p->acao << endl;
            p = p->proximo;
        }
    }

    void salvarExtrato(Paciente* p) {
        ofstream arq("repositorio-extra/atividade-extra37/prontuario_" + p->nome + ".txt");
        arq << "=== G-HEALTH HOSPITAL ===\n";
        arq << "PACIENTE: " << p->nome << "\n";
        arq << "DIAGNÓSTICOS:\n";
        ProntuarioNode* h = p->historico;
        while (h) {
            arq << "- " << h->data << ": " << h->diagnostico << "\n";
            h = h->proximo;
        }
        arq.close();
    }

    void deletarPaciente(Paciente* p) {
        ProntuarioNode* h = p->historico;
        while (h) {
            ProntuarioNode* t = h;
            h = h->proximo;
            delete t;
        }
        delete p;
    }

    ~GHealth() {
        // Limpeza total (Zero Memory Leak)
        while (inicioFila) {
            QueueNode* t = inicioFila;
            inicioFila = inicioFila->proximo;
            deletarPaciente(t->paciente);
            delete t;
        }
        while (topoLogs) {
            LogNode* t = topoLogs;
            topoLogs = topoLogs->proximo;
            delete t;
        }
    }
};

int GHealth::pacientesAtendidos = 0;

// --- 5. MAIN INTERATIVA ---

int main()
{
    GHealth hospital;
    Scanner& scan = Scanner::get();
    int opt = 0;

    do {
        UI::limpar();
        UI::banner();
        cout << "[1] Nova Triagem  [2] Atender  [3] Auditoria  [4] Sair" << endl;
        opt = scan.ler<int>("Escolha: ");

        try {
            if (opt == 1) {
                string nome = scan.lerTexto("Nome do Paciente: ");
                int idade = scan.ler<int>("Idade: ");
                hospital.registrarEntrada(nome, idade);
                system("sleep 1");
            }
            else if (opt == 2) {
                hospital.atenderProximo();
            }
            else if (opt == 3) {
                hospital.exibirLogs();
                cout << "\n[ENTER] para voltar...";
                cin.ignore(1000, '\n'); cin.get();
            }
        } catch (const exception& e) {
            cout << UI::VERMELHO << "ERRO: " << e.what() << UI::RESET << endl;
        }

    } while (opt != 4);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: O DESAFIO DA MAESTRIA LENDÁRIA
    ===============================================================

    1. GESTÃO DE MEMÓRIA EM MÚLTIPLAS CAMADAS:
       - Este projeto demonstra como objetos complexos (Paciente) 
         podem conter suas próprias estruturas dinâmicas (Lista 
         Encadeada de Prontuários). A destruição deve ser em cascata 
         para não deixar "órfãos" na memória.

    2. FUSÃO DE LÓGICAS (FIFO vs LIFO):
       - Aplicamos a Fila na Triagem (ordem de chegada) e a Pilha 
         na Auditoria (o evento mais recente no topo). É a prova 
         definitiva de que você sabe quando usar cada estrutura.

    3. ROBUSTEZ SINGLETON:
       - O uso do Scanner Singleton garante que a interface com o 
         humano seja o ponto mais forte, e não o mais fraco, do 
         seu sistema.

    4. ENGENHARIA DE QUALIDADE (VAZAMENTO ZERO):
       - O uso intensivo de destrutores que percorrem listas para 
         liberar memória (`while(p) { delete ... }`) é o que 
         diferencia um software acadêmico de um industrial.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Grafos: Para mapear a propagação de doenças no hospital.
    - Árvores Binárias (BST): Para busca rápida de pacientes por ID.
    - Ponteiros Inteligentes (C++11): Como automatizar essa limpeza.
    ===============================================================
*/

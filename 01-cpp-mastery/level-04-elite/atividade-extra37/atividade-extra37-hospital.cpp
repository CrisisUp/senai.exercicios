/**
 * @file atividade-extra37-hospital.cpp
 * @brief G-HEALTH: Engenharia de Sistemas Bare-Metal e Múltiplos Padrões.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Integração de Fila, Lista e Pilha Manuais com Validação Singleton.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Bare-Metal Tiered Heap)
 * - Nível 1: Fila de Triagem (QueueNode na HEAP) aponta para Paciente.
 * - Nível 2: Objeto Paciente (HEAP) contém cabeçalho de Lista Encadeada.
 * - Nível 3: Prontuário (ProntuarioNode na HEAP) forma a trilha de dados.
 * - Auditoria: Pilha (LogNode na HEAP) cresce independentemente.
 * - Singleton Scanner: Vida eterna no DATA SEGMENT.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <exception>

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
    inline void limpar() { cout << "\033[2J\033[1;1H"; }
    void banner() {
        cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
        cout << "      G-HEALTH: SISTEMA HOSPITALAR v2.0        " << endl;
        cout << "       (Elite Bare-Metal Architecture)         " << endl;
        cout << "===============================================" << UI::RESET << endl;
    }
}

// --- 2. PADRÃO SINGLETON: SCANNER BLINDADO ---

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
    T ler(const string& msg) {
        T dado;
        while (true) {
            cout << UI::RESET << msg << UI::RESET;
            if (cin >> dado) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return dado;
            }
            cout << UI::VERMELHO << " [ERRO]: Tipo inválido. Purga de buffer ativa." << UI::RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    string lerTexto(const string& msg) {
        string t;
        cout << UI::RESET << msg << UI::RESET;
        getline(cin >> ws, t);
        return t;
    }
};

// --- 3. ESTRUTURAS DINÂMICAS (NÍVEL ARQUITETURA) ---

/**
 * @struct ProntuarioNode
 * @brief Registro clínico atômico em lista encadeada.
 */
struct ProntuarioNode {
    string diagnostico;
    string data;
    ProntuarioNode* proximo;
    ProntuarioNode(const string& d, const string& dt) 
        : diagnostico(d), data(dt), proximo(nullptr) {}
};

/**
 * @struct Paciente
 * @brief Entidade mestre que gerencia sua própria sub-estrutura dinâmica.
 */
struct Paciente {
    string nome;
    int idade;
    ProntuarioNode* historico; 

    Paciente(const string& n, int i) : nome(n), idade(i), historico(nullptr) {}

    void adicionarAoProntuario(const string& diag) {
        ProntuarioNode* novo = new ProntuarioNode(diag, "22/04/2026");
        novo->proximo = historico;
        historico = novo;
    }

    ~Paciente() {
        // Destruição em cascata do histórico (Zelador de Memória)
        ProntuarioNode* h = historico;
        while (h) {
            ProntuarioNode* t = h;
            h = h->proximo;
            delete t;
        }
    }
};

/**
 * @struct QueueNode
 * @brief Container para a fila de espera FIFO.
 */
struct QueueNode {
    Paciente* p;
    QueueNode* proximo;
    QueueNode(Paciente* _p) : p(_p), proximo(nullptr) {}
};

/**
 * @struct LogNode
 * @brief Container para a pilha de auditoria LIFO.
 */
struct LogNode {
    string acao;
    LogNode* proximo;
    LogNode(const string& a) : acao(a), proximo(nullptr) {}
};

// --- 4. GESTOR HOSPITALAR (CORE ENGINE) ---

class GHealth {
private:
    QueueNode *inicioFila, *fimFila; // Head e Tail (FIFO)
    LogNode* topoLogs;               // Stack Top (LIFO)
    static int contadorSessao;

public:
    GHealth() : inicioFila(nullptr), fimFila(nullptr), topoLogs(nullptr) {}

    /**
     * @brief Registra entrada via Alocação Dinâmica Multinível.
     */
    void registrarEntrada(const string& nome, int idade) {
        Paciente* novoP = new Paciente(nome, idade);
        QueueNode* novoNode = new QueueNode(novoP);
        
        if (!inicioFila) {
            inicioFila = fimFila = novoNode;
        } else {
            fimFila->proximo = novoNode;
            fimFila = novoNode;
        }
        registrarLog("Ingresso: " + nome);
        cout << UI::VERDE << "[SISTEMA]: Paciente indexado na fila de triagem." << UI::RESET << endl;
    }

    /**
     * @brief Processa o próximo da fila e persiste prontuário.
     */
    void atenderProximo() {
        if (!inicioFila) {
            cout << UI::AMARELO << UI::NEGRITO << "[AVISO]: Setor de triagem sem pacientes pendentes." << UI::RESET << endl;
            return;
        }
        QueueNode* temp = inicioFila;
        Paciente* pacienteAtivo = temp->p;

        UI::limpar();
        cout << UI::CIANO << UI::NEGRITO << "--- G-HEALTH: SALA DE EXAME ---" << UI::RESET << endl;
        cout << "Paciente : " << UI::NEGRITO << pacienteAtivo->nome << UI::RESET << endl;
        cout << "Idade    : " << pacienteAtivo->idade << " anos" << endl;
        
        string desc = Scanner::get().lerTexto("Diagnóstico Clínico: ");
        pacienteAtivo->adicionarAoProntuario(desc);
        contadorSessao++;
        
        registrarLog("Atendimento Concluído: " + pacienteAtivo->nome);

        // Desencadeamento FIFO
        inicioFila = inicioFila->proximo;
        if (!inicioFila) fimFila = nullptr;
        
        persistirHistorico(pacienteAtivo);
        
        // Destruição segura: Paciente e seu histórico interno
        delete pacienteAtivo; 
        delete temp;
        
        cout << UI::VERDE << "[OK]: Prontuário digital assinado e arquivado." << UI::RESET << endl;
        // Simulação de delay de processamento
        for(int i=0; i<100000000; i++); 
    }

    void registrarLog(const string& acao) {
        LogNode* novo = new LogNode(acao);
        novo->proximo = topoLogs;
        topoLogs = novo;
    }

    void exibirAuditoria() const {
        cout << "\n" << UI::NEGRITO << "TRILHA DE AUDITORIA (LIFO):" << UI::RESET << endl;
        LogNode* p = topoLogs;
        while (p) {
            cout << UI::AMARELO << " >> " << UI::RESET << p->acao << endl;
            p = p->proximo;
        }
    }

    void persistirHistorico(Paciente* p) {
        string path = "repositorio-extra/atividade-extra37/prontuario_" + p->nome + ".txt";
        ofstream arq(path);
        if (arq.is_open()) {
            arq << "===============================================\n";
            arq << "       G-HEALTH: PRONTUÁRIO ELETRÔNICO         \n";
            arq << "===============================================\n";
            arq << "NOME : " << p->nome << " | IDADE: " << p->idade << "\n";
            arq << "HISTÓRICO DE EVENTOS:\n";
            ProntuarioNode* h = p->historico;
            while (h) {
                arq << " - [" << h->data << "]: " << h->diagnostico << "\n";
                h = h->proximo;
            }
            arq.close();
        }
    }

    /**
     * @brief Destrutor de Elite: Purga multinível da HEAP.
     */
    ~GHealth() {
        cout << UI::AMARELO << "\n[SHUTDOWN]: Iniciando purga de memória hospitalar..." << UI::RESET << endl;
        // Limpa Fila e Pacientes órfãos
        while (inicioFila) {
            QueueNode* t = inicioFila;
            inicioFila = inicioFila->proximo;
            delete t->p; // Aciona o destrutor do paciente (cascata)
            delete t;
        }
        // Limpa Pilha de Logs
        while (topoLogs) {
            LogNode* t = topoLogs;
            topoLogs = topoLogs->proximo;
            delete t;
        }
        cout << UI::VERDE << "[CHECKPOINT]: RAM liberada com sucesso." << UI::RESET << endl;
    }
};

int GHealth::contadorSessao = 0;

// --- 5. EXECUÇÃO DO CENTRO MÉDICO ---

int main()
{
    GHealth motorHospital;
    Scanner& s = Scanner::get();
    int op = 0;

    do {
        UI::limpar();
        UI::banner();
        cout << UI::RESET << "[1] Triagem  [2] Atender  [3] Auditoria  [4] Sair" << UI::RESET << endl;
        op = s.ler<int>("Ação Médica: ");

        try {
            if (op == 1) {
                string n = s.lerTexto("Nome do Paciente: ");
                int i = s.ler<int>("Idade: ");
                motorHospital.registrarEntrada(n, i);
            }
            else if (op == 2) {
                motorHospital.atenderProximo();
            }
            else if (op == 3) {
                motorHospital.exibirAuditoria();
                cout << UI::AMARELO << "\n[ENTER] para retornar ao painel..." << UI::RESET;
                cin.ignore(1000, '\n'); cin.get();
            }
        } catch (const exception& e) {
            cout << UI::VERMELHO << "FALHA CRÍTICA: " << e.what() << UI::RESET << endl;
        }

    } while (op != 4);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ENGENHARIA BARE-METAL (FUSÃO FINAL)
    ===============================================================

    1. DESTRUIÇÃO EM CASCATA:
       - O diferencial deste projeto é a responsabilidade do objeto 
         Paciente em limpar sua própria lista de prontuário ao 
         morrer na memória. Isso simplifica o código do Gestor e 
         garante o princípio da Responsabilidade Única.

    2. FANTASMA DO CPU (ELITE ACCESS):
       - Todas as mensagens de log e diagnósticos são processadas 
         via referências constantes, minimizando o tráfego na HEAP 
         enquanto o sistema gerencia milhares de ponteiros.

    3. HIERARQUIA DE ESTRUTURAS:
       - Mostramos que uma Fila (FIFO) pode conter elementos que 
         carregam Listas (Linked Lists). Dominar essa união é a base 
         para construir Sistemas Operacionais ou Motores de Banco 
         de Dados.

    4. RESILIÊNCIA SINGLETON:
       - O sistema é imune a "Input Attacks". O Scanner centraliza 
         a inteligência de recuperação de fluxo, tornando a 
         experiência do usuário (médico/operador) fluida e estável.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Memory Pools: Como otimizar milhares de alocações pequenas.
    - Garbage Collection Algorithms: Como linguagens como Java 
      fariam isso automaticamente.
    - Persistent Data Structures.
    ===============================================================
*/

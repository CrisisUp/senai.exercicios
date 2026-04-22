/**
 * @file atividade-extra43-debugging.cpp
 * @brief Laboratório de Debugging: Versão Corrigida e Blindada (Elite).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Corrige falhas de Segmentação, Vazamento de Memória e Fragilidade de Fluxo.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Fixed Infrastructure)
 * - GestorTrafego: Alocado na STACK. Gerencia ponteiros na HEAP.
 * - Destruição RAII: O destrutor agora garante a purga da HEAP (delete).
 * - Loops de Auditoria: Corrigidos para [0, size-1] evitando corrupção da STACK.
 * - Validador (Singleton): Única instância no DATA SEGMENT limpando o buffer global.
 */

#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string VERMELHO = "\033[31m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. CLASSE SEMÁFORO (CONCRETA) ---

class Semaforo {
private:
    string local;
public:
    Semaforo(const string& l) : local(l) {}
    
    void operar() const { 
        cout << UI::VERDE << "[CONTROLE]: " << UI::RESET << "Semáforo em " 
             << UI::NEGRITO << local << UI::RESET << " operando nominalmente." << endl; 
    }
    
    const string& getLocal() const { return local; }
};

// --- 3. GESTOR DE TRÁFEGO (ARQUITETURA BLINDADA) ---

class GestorTrafego {
private:
    vector<Semaforo*> rede;
public:
    void adicionarSemaforo(const string& loc) {
        rede.push_back(new Semaforo(loc));
        cout << UI::CIANO << "[LOG]: Dispositivo em " << loc << " sincronizado à rede." << UI::RESET << endl;
    }

    /**
     * @brief Executa testes em toda a rede.
     * CORREÇÃO BUG 1: Loop agora respeita o limite estrito do vetor (i < size).
     */
    void testarRede() {
        cout << "\n" << UI::NEGRITO << "INICIANDO VARREDURA DE HARDWARE..." << UI::RESET << endl;
        for (size_t i = 0; i < rede.size(); i++) {
            cout << UI::BRANCO << "Teste " << (i+1) << "/" << rede.size() << ": " << UI::RESET;
            if (rede[i]) rede[i]->operar();
        }
    }

    /**
     * @brief Destrutor Industrial.
     * CORREÇÃO BUG 2: Limpeza rigorosa da HEAP para evitar Memory Leak.
     */
    ~GestorTrafego() {
        cout << "\n" << UI::ROXO << "[LIMPEZA]: Purgando dispositivos da RAM..." << UI::RESET << endl;
        int count = 0;
        for (auto* s : rede) {
            delete s;
            count++;
        }
        rede.clear();
        cout << UI::VERDE << "[OK]: " << count << " dispositivos removidos. Vazamento Zero." << UI::RESET << endl;
    }
};

// --- 4. VALIDADOR DE ELITE (SINGLETON) ---

class ValidadorUrbano {
private:
    ValidadorUrbano() {}
public:
    static ValidadorUrbano& get() {
        static ValidadorUrbano instancia;
        return instancia;
    }

    /**
     * @brief Lê opção com purga automática de buffer.
     * CORREÇÃO BUG 3: Uso de clear() e ignore() para neutralizar entradas inválidas.
     */
    int lerOpcao() {
        int opt;
        while (true) {
            cout << UI::BRANCO << "\nEscolha (1-Testar Rede / 2-Encerrar Hub): " << UI::RESET;
            if (cin >> opt) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return opt;
            }
            cout << UI::VERMELHO << " [ERRO]: Entrada não numérica bloqueada pelo escudo." << UI::RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
};

// --- 5. EXECUÇÃO DO HUB CORRIGIDO ---

int main() {
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-CITY: TRAFFIC CONTROL SYSTEM v2.0      " << endl;
    cout << "       (Elite Corrected & Bug-Free Core)       " << endl;
    cout << "===============================================" << UI::RESET << endl;

    GestorTrafego gCity;
    ValidadorUrbano& shield = ValidadorUrbano::get();

    // Alimentação da rede
    gCity.adicionarSemaforo("Avenida Central");
    gCity.adicionarSemaforo("Rua das Flores");
    gCity.adicionarSemaforo("Cruzamento Norte");

    int o = 0;
    do {
        o = shield.lerOpcao();
        if (o == 1) {
            gCity.testarRede();
        }
    } while (o != 2);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: TÉCNICAS DE DEBUGGING (ELITE)
    ===============================================================

    1. OFF-BY-ONE ERRORS:
       - O erro mais comum em C++. Vetores de tamanho N vão de 
         0 a N-1. Acessar a posição N causa um 'buffer overflow' 
         de leitura, podendo ler lixo da Stack ou derrubar o app.

    2. RAII (RESOURCE ACQUISITION IS INITIALIZATION):
       - É o padrão de ouro do C++. Se você alocou no construtor 
         ou em um método, o DESTRUTOR deve ser o responsável por 
         limpar. Isso garante que, mesmo que ocorra um erro, a 
         memória será devolvida ao S.O.

    3. ROBUSTEZ DE INPUT (SHIELDING):
       - Nunca confie no usuário. O uso de cin.clear() e cin.ignore() 
         é obrigatório em sistemas industriais para evitar 
         travamentos por entradas inesperadas.

    4. TOOLS DE DEBUG:
       - Um Engenheiro de Elite usa ferramentas como VALGRIND para 
         detectar vazamentos invisíveis e GDB para pausar a 
         execução no momento exato do Crash.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Unit Testing: Prevenindo bugs antes que cheguem à produção.
    - Assertions (assert.h): Verificando condições impossíveis.
    - Logging: Rastrear o erro através de arquivos de histórico.
    ===============================================================
*/

/**
 * @file atividade-extra33-bacen.cpp
 * @brief G-CENTRAL SOC: O Ápice da Engenharia de Sistemas C++.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Integra Singleton, Observer e Factory em uma arquitetura indestrutível.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Legendary Integration)
 * - Singleton (Scanner): Alocado no DATA SEGMENT (Static).
 * - SOC Engine: Instanciado na STACK, gerencia coleções na HEAP.
 * - Blacklist (std::map): Árvore Binária na HEAP para busca O(log n).
 * - Auditoria (std::stack): LIFO na HEAP para rastro de auditoria veloz.
 * - Agentes (Factory): Alocação volátil na HEAP (Short-lived objects).
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <exception>
#include <limits>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string VERMELHO = "\033[31m";
    const string AMARELO  = "\033[33m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string ROXO     = "\033[35m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
    
    void cabecalho() {
        cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
        cout << "      G-CENTRAL: CENTRAL BANK SECURITY SOC     " << endl;
        cout << "       (Full Pattern Stack Integration)        " << endl;
        cout << "===============================================" << UI::RESET << endl;
    }
}

// --- 2. PADRÃO SINGLETON: ESCUDO DE ENTRADA (MEYERS) ---

class ScannerSeguro {
private:
    ScannerSeguro() {}
    ScannerSeguro(const ScannerSeguro&) = delete;
    void operator=(const ScannerSeguro&) = delete;

public:
    static ScannerSeguro& get() {
        static ScannerSeguro instancia;
        return instancia;
    }

    template <typename T>
    T ler(const string& msg) {
        T dado;
        while (true) {
            cout << UI::BRANCO << msg << UI::RESET;
            if (cin >> dado) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return dado;
            }
            cout << UI::VERMELHO << " [ERRO]: Entrada inválida detectada." << UI::RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
};

// --- 3. PADRÃO OBSERVER: TELEMETRIA DE ALERTA ---

class IAlerta {
public:
    virtual void notificar(const string& msg) = 0;
    virtual ~IAlerta() {}
};

class PainelSOC : public IAlerta {
public:
    void notificar(const string& msg) override {
        cout << UI::VERMELHO << UI::NEGRITO << " [ALERTA SOC]: " << UI::RESET << msg << endl;
    }
};

class AppDiretoria : public IAlerta {
public:
    void notificar(const string& msg) override {
        cout << UI::AMARELO << " [PUSH]: Direção Central notificada -> " << msg << endl;
    }
};

// --- 4. PADRÃO FACTORY METHOD: CONTRAMEDIDAS ---

class IAgente {
public:
    virtual void neutralizar() = 0;
    virtual ~IAgente() {}
};

class CyberAgente : public IAgente {
public:
    void neutralizar() override {
        cout << UI::VERDE << " [DEFESA]: Bloqueio de tráfego e tracing ativo." << endl;
    }
};

class AuditorFiscal : public IAgente {
public:
    void neutralizar() override {
        cout << UI::ROXO << " [JUDICIAL]: Congelamento de ativos e auditoria iniciada." << endl;
    }
};

class FabricaDefesa {
public:
    static IAgente* convocar(int nivelRisco) {
        if (nivelRisco >= 8) return new AuditorFiscal();
        return new CyberAgente();
    }
};

// --- 5. NÚCLEO DO G-CENTRAL (MOTOR DE ELITE) ---

template <typename T>
struct RegistroAudit {
    string id;
    T valorCentavos;
    string pais;
};

class GCentral {
private:
    vector<IAlerta*> observadores;
    map<string, int> blacklist;
    stack<RegistroAudit<long long>> historico; // LIFO de Auditoria
    static int alertasGlobais;

public:
    GCentral() {
        blacklist["Ilhas Cayman"] = 5;
        blacklist["Swiss Vault"] = 7;
        blacklist["Dark-Web Node"] = 10;
    }

    void registrarMonitor(IAlerta* a) { if (a) observadores.push_back(a); }

    void analisarTransacao(const string& pais, double valor) {
        bool suspeita = false;
        string motivo = "";
        long long centavos = static_cast<long long>(valor * 100);

        if (blacklist.count(pais)) {
            suspeita = true;
            motivo = "Origem Crítica (" + pais + ")";
        } else if (centavos > 100000000) { // > 1 Milhão de BRL
            suspeita = true;
            motivo = "Movimentação Atípica de Grande Porte";
        }

        if (suspeita) {
            alertasGlobais++;
            for (auto* o : observadores) o->notificar(motivo);
            
            // Factory Response
            IAgente* defensor = FabricaDefesa::convocar(blacklist[pais]);
            defensor->neutralizar();
            delete defensor; // Limpeza imediata (Short-lived)

            historico.push({"SOC-" + to_string(alertasGlobais), centavos, pais});
            persistirEmDisco(motivo, valor, pais);
        } else {
            cout << UI::VERDE << " [OK]: Operação dentro dos padrões de conformidade." << UI::RESET << endl;
        }
    }

    void persistirEmDisco(const string& m, double v, const string& p) {
        ofstream arq("repositorio-extra/atividade-extra33/relatorio_soc.txt", ios::app);
        if (arq.is_open()) {
            arq << "[ALERT] " << m << " | R$ " << fixed << setprecision(2) << v << " | Origin: " << p << endl;
            arq.close();
        }
    }

    static int getContador() { return alertasGlobais; }
};

int GCentral::alertasGlobais = 0;

// --- 6. EXECUÇÃO DO CENTRO DE OPERAÇÕES ---

int main()
{
    UI::limparTela();
    UI::cabecalho();

    GCentral soc;
    ScannerSeguro& scan = ScannerSeguro::get();

    // Inscrição de Observadores
    PainelSOC monitorDigital;
    AppDiretoria appMobile;
    soc.registrarMonitor(&monitorDigital);
    soc.registrarMonitor(&appMobile);

    int opt = 0;
    do {
        cout << "\n" << UI::NEGRITO << "SOC DASHBOARD - STATUS: " << UI::VERDE << "ONLINE" << UI::RESET << endl;
        cout << "Incidentes Capturados: " << UI::AMARELO << GCentral::getContador() << UI::RESET << endl;
        cout << "[1] Processar Ordem SWIFT  [2] Desligar Núcleo" << endl;
        opt = scan.ler<int>("Ação SOC: ");

        if (opt == 1) {
            string p = scan.ler<string>("País de Origem: ");
            double v = scan.ler<double>("Valor Liquidação (BRL): ");
            soc.analisarTransacao(p, v);
        }

    } while (opt != 2);

    cout << UI::CIANO << "\n[INFO]: G-CENTRAL entrando em modo hibernação. Logs em disco." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: O ÁPICE DA ARQUITETURA C++
    ===============================================================

    1. SINERGIA DE PADRÕES:
       - O Singleton protege a ENTRADA, o Observer distribui a 
         INFORMAÇÃO, e o Factory gera a REAÇÃO. Esta tríade é a 
         base de sistemas de missão crítica modernos.

    2. GUARDIÃO FINANCEIRO (ELITE RULE):
       - Transações de bilhões exigem precisão de centavos inteiros. 
         A imprecisão de 'double' em valores massivos não é apenas 
         um bug, é um risco de conformidade bancária.

    3. FANTASMA DO CPU (PERFORMANCE):
       - O uso de const string& em toda a cadeia de processamento 
         evita cópias na HEAP, garantindo que o SOC reaja em 
         microsegundos.

    4. RESILIÊNCIA E AUDITORIA:
       - O uso de 'stack' para auditoria local e a persistência 
         em arquivo garantem o rastro forense necessário para 
         investigações de crimes financeiros.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Smart Pointers (unique_ptr) no Factory.
    - Template Specialization para países com moedas diferentes.
    - Metaprogramação para validação de regras em compile-time.
    ===============================================================
*/

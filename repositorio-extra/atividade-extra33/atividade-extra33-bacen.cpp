/**
 * @file atividade-extra33-bacen.cpp
 * @brief DESAFIO LENDÁRIO: G-CENTRAL - Security Operations Center.
 * 
 * Este projeto é a consolidação final de todo o aprendizado:
 * - Padrões de Projeto: Singleton (Scanner), Observer (Alertas), Factory (Defesa).
 * - POO Avançada: Classes Abstratas, Polimorfismo, Membros Estáticos.
 * - Programação Genérica: Templates de Transação.
 * - STL: Mapas de Risco e Pilhas de Auditoria.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
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

// --- 1. NAMESPACE DE INTERFACE (UI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string VERMELHO = "\033[31m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string ROXO     = "\033[35m";
    const string NEGRITO  = "\033[1m";

    void limparTela() { cout << "\033[2J\033[1;1H"; }
    void cabecalho() {
        cout << CIANO << "===============================================" << endl;
        cout << "      G-CENTRAL: CENTRAL BANK SECURITY SOC     " << endl;
        cout << "===============================================" << RESET << endl;
    }
}

// --- 2. PADRÃO SINGLETON: ESCUDO DE VALIDAÇÃO ---

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

// --- 3. PADRÃO OBSERVER: MONITORAMENTO DE ALERTAS ---

class IAlerta {
public:
    virtual void notificar(string msg) = 0;
    virtual ~IAlerta() {}
};

class PainelSOC : public IAlerta {
public:
    void notificar(string msg) override {
        cout << UI::VERMELHO << " [ALERTA SOC]: " << msg << UI::RESET << endl;
    }
};

class AppDiretoria : public IAlerta {
public:
    void notificar(string msg) override {
        cout << UI::AMARELO << " [MOBILE]: Diretor avisado sobre: " << msg << UI::RESET << endl;
    }
};

// --- 4. PADRÃO FACTORY METHOD: AGENTES DE RESPOSTA ---

class IAgente {
public:
    virtual void neutralizar() = 0;
    virtual ~IAgente() {}
};

class CyberAgente : public IAgente {
public:
    void neutralizar() override {
        cout << UI::VERDE << " [DEFESA]: Protocolo de contra-ataque cibernético ativo. IP Bloqueado." << UI::RESET << endl;
    }
};

class AuditorFraude : public IAgente {
public:
    void neutralizar() override {
        cout << UI::ROXO << " [DEFESA]: Auditoria fiscal iniciada. Contas congeladas judicialmente." << UI::RESET << endl;
    }
};

class FabricaDefesa {
public:
    static IAgente* convocar(int perigo) {
        if (perigo >= 10) return new AuditorFraude();
        return new CyberAgente();
    }
};

// --- 5. MOTOR DO SOC (SÍNTESE FINAL) ---

template <typename T>
struct RegistroAudit {
    string id;
    T valor;
    string origem;
};

class GCentral {
private:
    vector<IAlerta*> observadores;
    map<string, int> blacklistPaises;
    stack<RegistroAudit<double>> logs;
    static int alertasEmitidos;

public:
    GCentral() {
        blacklistPaises["Ilhas Cayman"] = 5;
        blacklistPaises["Paraiso Fiscal X"] = 8;
        blacklistPaises["Z-Hackland"] = 10;
    }

    void registrarMonitor(IAlerta* a) { observadores.push_back(a); }

    void analisarTransacao(string pais, double valor) {
        bool suspeita = false;
        string motivo = "";

        if (blacklistPaises.count(pais)) {
            suspeita = true;
            motivo = "Origem de Alto Risco (" + pais + ")";
        } else if (valor > 1000000.0) {
            suspeita = true;
            motivo = "Valor Atípico (> 1 Milhão)";
        }

        if (suspeita) {
            alertasEmitidos++;
            for (auto o : observadores) o->notificar(motivo);
            
            IAgente* defensor = FabricaDefesa::convocar(blacklistPaises[pais]);
            defensor->neutralizar();
            delete defensor;

            logs.push({"ALERTA-" + to_string(alertasEmitidos), valor, pais});
            salvarEmDisco(motivo, valor, pais);
        } else {
            cout << UI::VERDE << " [SISTEMA]: Transação processada com segurança." << UI::RESET << endl;
        }
    }

    void salvarEmDisco(string m, double v, string p) {
        ofstream arq("repositorio-extra/atividade-extra33/relatorio_soc.txt", ios::app);
        arq << "[ALERTA] Motivo: " << m << " | Valor: R$ " << v << " | Pais: " << p << endl;
        arq.close();
    }

    static int getContador() { return alertasEmitidos; }
};

int GCentral::alertasEmitidos = 0;

// --- 6. FUNÇÃO PRINCIPAL ---

int main()
{
    UI::limparTela();
    UI::cabecalho();

    GCentral soc;
    ScannerSeguro& scan = ScannerSeguro::get();

    // Setup de Observadores
    PainelSOC painel;
    AppDiretoria app;
    soc.registrarMonitor(&painel);
    soc.registrarMonitor(&app);

    int opcao = 0;
    do {
        cout << "\n--- PAINEL DE CONTROLE DE SEGURANÇA ---" << endl;
        cout << "Alertas Totais na Sessão: " << GCentral::getContador() << endl;
        cout << "[1] Simular Transferência PIX/SWIFT" << endl;
        cout << "[2] Sair do Sistema" << endl;
        opcao = scan.ler<int>("Escolha: ");

        if (opcao == 1) {
            string pais = scan.ler<string>("País de Origem: ");
            double valor = scan.ler<double>("Valor da Transação (BRL): ");
            soc.analisarTransacao(pais, valor);
        }

    } while (opcao != 2);

    cout << UI::CIANO << "\n[INFO]: G-CENTRAL encerrado. Relatório salvo na pasta da atividade." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: O ÁPICE DA ENGENHARIA C++
    ===============================================================

    1. SINGLETON (O Guardião):
       - A classe ScannerSeguro garante que o buffer do teclado seja 
         gerenciado por uma única inteligência imune a falhas.

    2. OBSERVER (A Vigilância):
       - O SOC notifica múltiplos sistemas (Painel e App) sem que 
         a lógica do Banco Central dependa de classes concretas.

    3. FACTORY (A Resposta Ágil):
       - Dependendo do nível de risco (int perigo), a fábrica decide 
         quem deve agir: um algoritmo (Cyber) ou um humano (Auditor).

    4. INTEGRALIDADE TÉCNICA:
       - Unimos Templates, STL (map, stack, vector), Static, POO 
         e Exceções em um software que simula um ambiente de 
         missão crítica real.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Padrão Strategy: Para trocar algoritmos de análise de risco.
    - Padrão Decorator: Para adicionar camadas de segurança dinâmicas.
    - Concorrência (Threads): Analisar transações em paralelo.
    ===============================================================
*/

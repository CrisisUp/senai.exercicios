/**
 * @file atividade-extra29-trading.cpp
 * @brief DESAFIO DE ELITE: Plataforma G-CRYPTO v2.0 (Elite Trading Core).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Integra Templates, STL Maps e Integridade Bancária (Guardião Financeiro).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Trading Engine Architecture)
 * - Carteira<T>: Instância na STACK. Gerencia um map na HEAP.
 * - std::map: Cada nó na HEAP contém o Símbolo (string) e a Quantidade (T).
 * - BRL Balance: Armazenado como long long (Centavos) para evitar drifting binário.
 * - Performance: Busca logarítmica O(log n) para preços e balanços.
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
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
    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. GESTÃO DE ERROS FINANCEIROS ---

class ErroTrade : public exception {
    string msg;
public:
    ErroTrade(const string& m) : msg(UI::VERMELHO + "[EXCHANGE ERROR]: " + m + UI::RESET) {}
    const char* what() const throw() { return msg.c_str(); }
};

// --- 3. CLASSE TEMPLATE: CARTEIRA GENÉRICA (ELITE) ---

/**
 * @class Carteira
 * @brief Motor de custódia universal para qualquer tipo de ativo digital.
 * @tparam T Tipo numérico da quantidade (ex: double para BTC, long para Ações).
 */
template <typename T>
class Carteira {
private:
    map<string, T> balancos; // Ativo -> Qtd
    long long saldoBRLCentavos; // Guardião Financeiro: Integridade para moeda FIAT

public:
    Carteira(double saldoInicialBRL) 
        : saldoBRLCentavos(static_cast<long long>(saldoInicialBRL * 100)) {}

    void adicionarAtivo(const string& simbolo, const T& qtd) {
        balancos[simbolo] += qtd;
    }

    bool removerAtivo(const string& simbolo, const T& qtd) {
        if (balancos[simbolo] >= qtd) {
            balancos[simbolo] -= qtd;
            return true;
        }
        return false;
    }

    void debitarBRL(double valor) {
        long long debitoCentavos = static_cast<long long>(valor * 100);
        if (debitoCentavos > saldoBRLCentavos) throw ErroTrade("Saldo BRL insuficiente para liquidação.");
        saldoBRLCentavos -= debitoCentavos;
    }

    void creditarBRL(double valor) {
        saldoBRLCentavos += static_cast<long long>(valor * 100);
    }

    // Getters de Elite
    double getSaldoReal() const { return static_cast<double>(saldoBRLCentavos) / 100.0; }
    const map<string, T>& getAtivos() const { return balancos; }
};

// --- 4. MOTOR DE MERCADO (ORDER BOOK REAL-TIME) ---

class MarketEngine {
private:
    map<string, double> orderBook; // Símbolo -> Preço em BRL

public:
    MarketEngine() {
        orderBook["BTC"] = 320500.50; 
        orderBook["ETH"] = 12450.25;  
        orderBook["SOL"] = 745.10;    
        orderBook["DOT"] = 42.15;     
    }

    double getPreco(const string& simbolo) const {
        auto it = orderBook.find(simbolo);
        if (it == orderBook.end()) throw ErroTrade("Par de negociação '" + simbolo + "/BRL' não localizado.");
        return it->second;
    }

    void dashboardMercado() const {
        cout << "\n" << UI::AMARELO << UI::NEGRITO << "--- ORDER BOOK (LIVE TELEMETRY) ---" << UI::RESET << endl;
        cout << string(40, '-') << endl;
        for (const auto& [ativo, preco] : orderBook) {
            cout << "Pair: " << left << setw(8) << (ativo + "/BRL") 
                 << " | Last: " << UI::VERDE << UI::NEGRITO << "R$ " << fixed << setprecision(2) << preco << UI::RESET << endl;
        }
        cout << string(40, '-') << endl;
    }
};

// --- 5. EXECUÇÃO DA PLATAFORMA ---

int main()
{
    MarketEngine core;
    Carteira<double> wallet(50000.00); // 50k BRL na STACK

    int opcao = 0;

    do {
        UI::limparTela();
        cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
        cout << "      G-CRYPTO: ELITE TRADING INTERFACE        " << endl;
        cout << "       (High-Precision Financial Core)         " << endl;
        cout << "===============================================" << UI::RESET << endl;

        cout << UI::RESET << "EQUITY BRL: " << UI::RESET << UI::VERDE << UI::NEGRITO 
             << "R$ " << fixed << setprecision(2) << wallet.getSaldoReal() << UI::RESET << endl;

        core.dashboardMercado();

        cout << "\n" << UI::NEGRITO << "MY PORTFOLIO:" << UI::RESET << endl;
        bool hasAssets = false;
        for (const auto& [simbolo, qtd] : wallet.getAtivos()) {
            if (qtd > 0.00000001) {
                cout << "-> " << left << setw(5) << simbolo << ": " << UI::CIANO << UI::NEGRITO << qtd << UI::RESET << endl;
                hasAssets = true;
            }
        }
        if (!hasAssets) cout << UI::AMARELO << "(Portfolio is currently empty)" << UI::RESET << endl;

        cout << UI::RESET << "\n[1] BUY ORDER  [2] SELL ORDER  [3] EXIT" << UI::RESET << endl;
        cout << "Action: ";
        cin >> opcao;

        try {
            if (opcao == 1) {
                string sim; double qtd;
                cout << "Asset Symbol: "; cin >> sim;
                cout << "Quantity to BUY: "; cin >> qtd;

                double px = core.getPreco(sim);
                double totalBRL = px * qtd;

                cout << UI::AMARELO << "Order Cost: R$ " << totalBRL << " (Confirm? 1-Yes): " << UI::RESET;
                int confirm; cin >> confirm;

                if (confirm == 1) {
                    wallet.debitarBRL(totalBRL); // Validação de Saldo
                    wallet.adicionarAtivo(sim, qtd);
                    cout << UI::VERDE << UI::NEGRITO << "\n[SUCCESS]: Order filled at R$ " << px << UI::RESET << endl;
                }
            }
            else if (opcao == 2) {
                string sim; double qtd;
                cout << "Asset Symbol: "; cin >> sim;
                cout << "Quantity to SELL: "; cin >> qtd;

                if (wallet.removerAtivo(sim, qtd)) {
                    double px = core.getPreco(sim);
                    double profit = px * qtd;
                    wallet.creditarBRL(profit);
                    cout << UI::VERDE << UI::NEGRITO << "\n[SUCCESS]: Assets liquidated. BRL balance updated." << UI::RESET << endl;
                } else {
                    throw ErroTrade("Insufficient asset balance for liquidation.");
                }
            }
        } catch (const exception& e) {
            cout << e.what() << endl;
            cout << UI::RESET << "Press ENTER to continue..." << UI::RESET;
            cin.ignore(1000, '\n'); cin.get();
        }

    } while (opcao != 3);

    cout << UI::CIANO << "\nTerminating session. Secure vault locked." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO DE ELITE (TRADING ENGINE)
    ===============================================================

    1. TEMPLATES E ESCALABILIDADE:
       - A plataforma usa 'Carteira<double>', mas o mesmo código 
         suportaria 'Carteira<mpf_class>' (precisão infinita) para 
         lidar com moedas nacionais hiper-inflacionadas ou tokens 
         com 18 casas decimais.

    2. GARANTIA DE PRECISÃO (ELITE RULE):
       - O saldo Fiat (BRL) é gerenciado via 'long long' centavos. 
         Em corretoras, o "Floating Point Drift" pode causar perdas 
         de milhares de reais por dia se não houver auditoria 
         estática precisa.

    3. DESIGN PATTERN 'DATA REPOSITORY' (MarketEngine):
       - Centralizamos o Order Book em uma classe gestora. Isso 
         desacopla a lógica de quem "compra" (Carteira) de quem 
         "fornece o preço" (Market).

    4. PERFORMANCE LOGARÍTMICA:
       - O uso intensivo de 'std::map' garante que a busca de 
         preços e o cálculo de equity ocorram em O(log n), permitindo 
         que o sistema suporte milhares de pares de moedas sem 
         degradação perceptível.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Atomic Operations: Negociações em ambientes Multiprocessados.
    - WebSocket Architecture: Conectando preços a APIs reais (Binance).
    - Blockchain Persistence: Salvando saldos em bancos distribuídos.
    ===============================================================
*/

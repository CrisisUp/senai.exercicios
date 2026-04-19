
/**
 * @file atividade-extra29-trading.cpp
 * @brief DESAFIO DE ELITE: Plataforma de Trading G-CRYPTO v1.0.
 * 
 * Este projeto integra:
 * 1. Class Templates (Carteira Genérica)
 * 2. STL map (Order Book e Balanços)
 * 3. Programação Defensiva (Tratamento de Exceções)
 * 4. UI/UX (Interface Colorida de Negociação)
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <exception>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string VERMELHO = "\033[31m";
    const string CIANO    = "\033[36m";
    const string NEGRITO  = "\033[1m";

    void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. GESTÃO DE ERROS FINANCEIROS ---

class ErroTrade : public exception {
    string msg;
public:
    ErroTrade(string m) : msg(UI::VERMELHO + "[EXCHANGE ERROR]: " + m + UI::RESET) {}
    const char* what() const throw() { return msg.c_str(); }
};

// --- 3. CLASSE TEMPLATE: CARTEIRA GENÉRICA ---

/**
 * @brief Gerencia saldos de ativos de qualquer tipo numérico.
 */
template <typename T>
class Carteira {
private:
    // Map: Símbolo do Ativo -> Quantidade
    map<string, T> ativos;
    double saldoBRL;

public:
    Carteira(double saldoInicial) : saldoBRL(saldoInicial) {}

    void adicionarAtivo(string simbolo, T qtd) {
        ativos[simbolo] += qtd;
    }

    bool removerAtivo(string simbolo, T qtd) {
        if (ativos[simbolo] >= qtd) {
            ativos[simbolo] -= qtd;
            return true;
        }
        return false;
    }

    void debitarBRL(double valor) {
        if (valor > saldoBRL) throw ErroTrade("Saldo BRL insuficiente para esta ordem.");
        saldoBRL -= valor;
    }

    void creditarBRL(double valor) {
        saldoBRL += valor;
    }

    double getSaldoBRL() const { return saldoBRL; }
    const map<string, T>& getAtivos() const { return ativos; }
};

// --- 4. MOTOR DE MERCADO (SIMULADO) ---

class MarketEngine {
private:
    map<string, double> orderBook;

public:
    MarketEngine() {
        orderBook["BTC"] = 320500.00; // Bitcoin em R$
        orderBook["ETH"] = 12500.00;  // Ethereum em R$
        orderBook["SOL"] = 750.45;    // Solana em R$
        orderBook["DOT"] = 45.20;     // Polkadot em R$
    }

    double getPreco(string simbolo) {
        if (orderBook.find(simbolo) == orderBook.end()) {
            throw ErroTrade("Ativo '" + simbolo + "' não listado nesta corretora.");
        }
        return orderBook[simbolo];
    }

    void exibirMercado() {
        cout << UI::AMARELO << "\n--- LIVRO DE OFERTAS (LIVE) ---" << UI::RESET << endl;
        for (auto const& [ativo, preco] : orderBook) {
            cout << "Ativo: " << left << setw(5) << ativo 
                 << " | Preço: " << UI::VERDE << "R$ " << fixed << setprecision(2) << preco << UI::RESET << endl;
        }
    }
};

// --- 5. FUNÇÃO PRINCIPAL INTERATIVA ---

int main()
{
    MarketEngine mercado;
    Carteira<double> minhaCarteira(10000.00); // Iniciando com 10k Reais

    int opcao = 0;

    do {
        UI::limparTela();
        cout << UI::CIANO << "===============================================" << endl;
        cout << "      G-CRYPTO: DIGITAL ASSETS EXCHANGE        " << endl;
        cout << "===============================================" << UI::RESET << endl;

        cout << "SALDO DISPONÍVEL: " << UI::VERDE << "R$ " << fixed << setprecision(2) 
             << minhaCarteira.getSaldoBRL() << UI::RESET << endl;

        mercado.exibirMercado();

        cout << "\n--- SUA CARTEIRA ---" << endl;
        bool vazia = true;
        for (auto const& [simbolo, qtd] : minhaCarteira.getAtivos()) {
            if (qtd > 0) {
                cout << simbolo << ": " << UI::NEGRITO << qtd << UI::RESET << endl;
                vazia = false;
            }
        }
        if (vazia) cout << "(Carteira vazia)" << endl;

        cout << "\n[1] Comprar Ativo | [2] Vender Ativo | [3] Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;

        try {
            if (opcao == 1) {
                string sim;
                double qtd;
                cout << "Símbolo do Ativo (ex: BTC): "; cin >> sim;
                cout << "Quantidade desejada: "; cin >> qtd;

                double precoUnit = mercado.getPreco(sim);
                double totalOrdem = precoUnit * qtd;

                cout << "Custo da Ordem: R$ " << totalOrdem << endl;
                cout << "Confirmar compra? (1-Sim / 0-Não): ";
                int conf; cin >> conf;

                if (conf == 1) {
                    minhaCarteira.debitarBRL(totalOrdem);
                    minhaCarteira.adicionarAtivo(sim, qtd);
                    cout << UI::VERDE << "[SUCESSO]: Ordem executada!" << UI::RESET << endl;
                    system("sleep 1");
                }
            }
            else if (opcao == 2) {
                string sim;
                double qtd;
                cout << "Ativo para Venda: "; cin >> sim;
                cout << "Quantidade: "; cin >> qtd;

                if (minhaCarteira.removerAtivo(sim, qtd)) {
                    double precoUnit = mercado.getPreco(sim);
                    double ganho = precoUnit * qtd;
                    minhaCarteira.creditarBRL(ganho);
                    cout << UI::VERDE << "[VENDA]: Saldo BRL atualizado." << UI::RESET << endl;
                    system("sleep 1");
                } else {
                    throw ErroTrade("Você não possui saldo deste ativo suficiente.");
                }
            }
        } catch (const exception& e) {
            cout << e.what() << endl;
            cout << "Pressione ENTER para continuar...";
            cin.ignore(1000, '\n'); cin.get();
        }

    } while (opcao != 3);

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO DE ELITE (G-CRYPTO)
    ===============================================================

    1. TEMPLATES DE CLASSE NA PRÁTICA:
       - A classe 'Carteira<double>' gerencia os ativos. Poderíamos 
         mudar para 'Carteira<long long>' se precisássemos de 
         precisão em Satoshis sem decimais. O código é o mesmo.

    2. PODER DO std::map:
       - Usamos o map para duas funções vitais:
         * Order Book: Busca instantânea do preço do ativo.
         * Balanço: Relação dinâmica de quais ativos o usuário possui.

    3. DESESTRUTURAÇÃO (Structured Bindings - C++17):
       - A sintaxe [ativo, preco] dentro do for permite desempacotar 
         o par do map de forma elegante, tornando o código muito 
         mais legível.

    4. SEGURANÇA TRANSACIONAL:
       - O sistema primeiro debita o saldo (try-catch) e apenas em 
         caso de sucesso ele atualiza a carteira de ativos. Isso 
         evita a criação de "dinheiro imaginário" por erro de código.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Multithreading: Processar ordens em paralelo.
    - Sockets: Receber preços reais via API (Websockets).
    - Precisão Arbitrária: Lidar com 18 casas decimais de tokens.
    ===============================================================
*/

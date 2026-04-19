/**
 * @file atividade-extra16-erp.cpp
 * @brief PROJETO FINAL: Sistema de Gestão Comercial (ERP) v4.0.
 * 
 * Integra todos os conceitos aprendidos:
 * - Vetores (Estoque dinâmico)
 * - Pilhas (Logs de Auditoria)
 * - Filas (Fila de Clientes)
 * - Exceções (Resiliência Financeira)
 * - Cores ANSI (Interface Profissional)
 * - Manipulação de Centavos (Segurança Bancária)
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <exception>
#include <algorithm>
#include <sstream>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERMELHO = "\033[31m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string BRANCO   = "\033[37m";

    void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. GESTÃO DE EXCEÇÕES ---

class ErroERP : public exception {
    string msg;
public:
    ErroERP(string m) : msg(UI::VERMELHO + "[ERRO]: " + m + UI::RESET) {}
    const char* what() const throw() { return msg.c_str(); }
};

// --- 3. ESTRUTURAS DE DADOS ---

struct Produto {
    int id;
    string nome;
    int estoque;
    int custoCentavos;
    int margemLucro; // Porcentagem
    
    int getPrecoVenda() const {
        return custoCentavos + (custoCentavos * margemLucro / 100);
    }
};

struct LogOperacao {
    string timestamp;
    string acao;
    int valorImpacto; // Em centavos (+ para entrada, - para saída)
};

// --- 4. FUNÇÕES UTILITÁRIAS ---

string formatarMoeda(long long centavos) {
    bool negativo = centavos < 0;
    long long valorAbs = abs(centavos);
    double reais = static_cast<double>(valorAbs) / 100.0;
    stringstream ss;
    ss << (negativo ? "-" : "") << "R$ " << fixed << setprecision(2) << reais;
    return ss.str();
}

string getAgora() {
    time_t t = time(0);
    struct tm * now = localtime(&t);
    char buf[20];
    strftime(buf, sizeof(buf), "%H:%M:%S", now);
    return string(buf);
}

// --- 5. O SISTEMA ERP (LÓGICA) ---

class SistemaERP {
private:
    vector<Produto> estoque;
    stack<LogOperacao> logs;
    queue<string> filaClientes;
    long long saldoCaixa;
    long long despesasFixas;

public:
    SistemaERP() : saldoCaixa(500000), despesasFixas(120000) {} // Inicia com R$ 5k e R$ 1.2k de contas fixas

    void carregarDados() {
        ifstream arq("repositorio-extra/atividade-extra16/produtos.txt");
        if (!arq.is_open()) throw ErroERP("Dados do estoque não encontrados.");
        
        string linha;
        while (getline(arq, linha)) {
            stringstream ss(linha);
            string s_id, s_nome, s_est, s_custo, s_margem;
            
            getline(ss, s_id, ';');
            getline(ss, s_nome, ';');
            getline(ss, s_est, ';');
            getline(ss, s_custo, ';');
            getline(ss, s_margem, ';');
            
            if (!s_id.empty()) {
                estoque.push_back({stoi(s_id), s_nome, stoi(s_est), stoi(s_custo), stoi(s_margem)});
            }
        }
        arq.close();
    }

    void registrarLog(string desc, int valor) {
        logs.push({getAgora(), desc, valor});
    }

    void menuPrincipal() {
        int opt = 0;
        do {
            UI::limparTela();
            cout << UI::CIANO << "===============================================" << endl;
            cout << "      SISTEMA DE GESTÃO COMERCIAL (ERP)        " << endl;
            cout << "            Fluxo de Caixa e Estoque           " << endl;
            cout << "===============================================" << UI::RESET << endl;
            
            cout << UI::NEGRITO << "CAIXA ATUAL: " << (saldoCaixa >= 0 ? UI::VERDE : UI::VERMELHO) 
                 << formatarMoeda(saldoCaixa) << UI::RESET << endl;
            cout << "Clientes na Fila: " << UI::AMARELO << filaLeitoresSize() << UI::RESET;
            cout << " | Logs na Sessão: " << logs.size() << endl;
            cout << "-----------------------------------------------" << endl;
            cout << "[1] Entrar Cliente na Fila" << endl;
            cout << "[2] Realizar Venda (Atendimento)" << endl;
            cout << "[3] Comprar Estoque (Fornecedor)" << endl;
            cout << "[4] Pagar Gastos Fixos (Aluguel/Luz)" << endl;
            cout << "[5] Dashboard de Estoque e Auditoria" << endl;
            cout << "[6] Encerrar e Gerar DRE Financeiro" << endl;
            cout << UI::CIANO << "-----------------------------------------------" << UI::RESET << endl;
            
            try {
                cout << "Escolha: ";
                if (!(cin >> opt)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    throw ErroERP("Opção deve ser numérica.");
                }

                switch (opt) {
                    case 1: adicionarCliente(); break;
                    case 2: realizarVenda(); break;
                    case 3: comprarEstoque(); break;
                    case 4: pagarGastosFixos(); break;
                    case 5: mostrarAuditoria(); break;
                }
            } catch (const exception& e) {
                cout << e.what() << endl;
                cout << "Pressione ENTER para continuar...";
                cin.ignore(1000, '\n'); cin.get();
            }

        } while (opt != 6);
        gerarRelatorioFinal();
    }

    int filaLeitoresSize() { return filaClientes.size(); }

    void adicionarCliente() {
        string n;
        cout << "Nome do Cliente: ";
        getline(cin >> ws, n);
        filaClientes.push(n);
        cout << UI::VERDE << "[OK]: " << n << " aguardando atendimento." << UI::RESET << endl;
        system("sleep 1");
    }

    void realizarVenda() {
        if (filaClientes.empty()) throw ErroERP("Nenhum cliente para atender.");
        
        string c = filaClientes.front();
        cout << "\n--- ESTOQUE DISPONÍVEL ---" << endl;
        for (int i = 0; i < (int)estoque.size(); i++) {
            cout << "[" << i << "] " << left << setw(20) << estoque[i].nome 
                 << " | Venda: " << UI::VERDE << formatarMoeda(estoque[i].getPrecoVenda()) << UI::RESET
                 << " | Est: " << estoque[i].estoque << endl;
        }

        int idx;
        cout << "\nSelecione o produto para " << UI::NEGRITO << c << UI::RESET << ": ";
        cin >> idx;

        if (idx < 0 || idx >= (int)estoque.size()) throw ErroERP("Produto inválido.");
        if (estoque[idx].estoque <= 0) throw ErroERP("Produto esgotado no estoque!");

        int preco = estoque[idx].getPrecoVenda();
        saldoCaixa += preco;
        estoque[idx].estoque--;
        filaClientes.pop();

        registrarLog("Venda: " + estoque[idx].nome, preco);
        cout << UI::VERDE << "[SUCESSO]: Venda realizada para " << c << "!" << UI::RESET << endl;
        system("sleep 1");
    }

    void comprarEstoque() {
        cout << "\n--- REPOSIÇÃO DE ESTOQUE ---" << endl;
        for (int i = 0; i < (int)estoque.size(); i++) {
            cout << "[" << i << "] " << left << setw(20) << estoque[i].nome 
                 << " | Custo: " << UI::AMARELO << formatarMoeda(estoque[i].custoCentavos) << UI::RESET << endl;
        }

        int idx, qtd;
        cout << "Produto ID: "; cin >> idx;
        cout << "Quantidade: "; cin >> qtd;

        if (idx < 0 || idx >= (int)estoque.size()) throw ErroERP("Produto inválido.");
        
        long long totalCusto = (long long)estoque[idx].custoCentavos * qtd;
        if (totalCusto > saldoCaixa) throw ErroERP("Caixa insuficiente para compra de fornecedor.");

        saldoCaixa -= totalCusto;
        estoque[idx].estoque += qtd;

        registrarLog("Compra: " + estoque[idx].nome + " (x" + to_string(qtd) + ")", -totalCusto);
        cout << UI::VERDE << "[SUCESSO]: Estoque atualizado. Pagamento efetuado." << UI::RESET << endl;
        system("sleep 1");
    }

    void pagarGastosFixos() {
        if (saldoCaixa < despesasFixas) throw ErroERP("Inadimplência! Saldo insuficiente para pagar despesas fixas.");
        
        saldoCaixa -= despesasFixas;
        registrarLog("Pagamento: Gastos Fixos (Aluguel/Luz/Salários)", -despesasFixas);
        cout << UI::VERDE << "[OK]: Contas do mês pagas com sucesso." << UI::RESET << endl;
        system("sleep 1");
    }

    void mostrarAuditoria() {
        UI::limparTela();
        cout << UI::CIANO << "--- AUDITORIA E DASHBOARD DE ESTOQUE ---" << UI::RESET << endl;
        cout << "\nESTADO DO ESTOQUE:" << endl;
        for (auto& p : estoque) {
            cout << "- " << left << setw(20) << p.nome << ": " << p.estoque << " unidades" << endl;
        }

        cout << "\nÚLTIMOS LOGS (Pilha):" << endl;
        stack<LogOperacao> temp = logs;
        int count = 0;
        while (!temp.empty() && count < 5) {
            LogOperacao l = temp.top();
            cout << "[" << l.timestamp << "] " << left << setw(25) << l.acao 
                 << " | " << (l.valorImpacto >= 0 ? UI::VERDE : UI::VERMELHO) 
                 << formatarMoeda(l.valorImpacto) << UI::RESET << endl;
            temp.pop();
            count++;
        }
        cout << "\n[ENTER] para voltar ao menu...";
        cin.ignore(1000, '\n'); cin.get();
    }

    void gerarRelatorioFinal() {
        ofstream arq("repositorio-extra/atividade-extra16/DRE_SESSAO.txt");
        arq << "===============================================" << endl;
        arq << "      DEMONSTRATIVO DE RESULTADOS (DRE)        " << endl;
        arq << "===============================================" << endl;
        arq << "Saldo em Caixa Final: " << formatarMoeda(saldoCaixa) << endl;
        arq << "Operações na Sessão: " << logs.size() << endl;
        arq << "\nHISTÓRICO DETALHADO:" << endl;
        while (!logs.empty()) {
            LogOperacao l = logs.top();
            arq << "[" << l.timestamp << "] " << l.acao << " : " << formatarMoeda(l.valorImpacto) << endl;
            logs.pop();
        }
        arq.close();
        cout << UI::VERDE << "\n[SISTEMA]: Sessão encerrada. Arquivo 'DRE_SESSAO.txt' gerado." << UI::RESET << endl;
    }
};

// --- 6. MAIN ---

int main() {
    SistemaERP erp;
    try {
        erp.carregarDados();
        erp.menuPrincipal();
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}

/**
 * @file MotorERP.cpp
 * @brief Implementação da lógica de gestão comercial (ERP).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "MotorERP.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <unistd.h> // Para sleep

using namespace std;

// --- IMPLEMENTAÇÃO DA UI ---

void UI::limparTela() { cout << "\033[2J\033[1;1H"; }

// --- IMPLEMENTAÇÃO DO SISTEMA ERP ---

SistemaERP::SistemaERP() : saldoCaixa(500000), despesasFixas(120000) {}

void SistemaERP::carregarDados() {
    ifstream arq("repositorio-extra/atividade-extra16/produtos.txt");
    if (!arq.is_open()) arq.open("produtos.txt");
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
            estoque.push_back({stoi(s_id), s_nome, stoi(s_est), stoll(s_custo), stoi(s_margem)});
        }
    }
    arq.close();
    cout << UI::VERDE << "[SISTEMA]: Banco de dados do ERP carregado." << UI::RESET << endl;
}

void SistemaERP::menuPrincipal() {
    int opt = 0;
    do {
        UI::limparTela();
        cout << UI::CIANO << "===============================================" << endl;
        cout << "      SISTEMA DE GESTÃO COMERCIAL (ERP)        " << endl;
        cout << "            Arquitetura Modular v4.0           " << endl;
        cout << "===============================================" << UI::RESET << endl;
        
        cout << UI::NEGRITO << "CAIXA ATUAL: " << (saldoCaixa >= 0 ? UI::VERDE : UI::VERMELHO) 
             << formatarMoeda(saldoCaixa) << UI::RESET << endl;
        cout << "Clientes na Fila: " << UI::AMARELO << filaClientes.size() << UI::RESET;
        cout << " | Auditoria: " << logs.size() << " entradas" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "[1] Adicionar Cliente | [2] Atender/Venda" << endl;
        cout << "[3] Repor Estoque     | [4] Pagar Contas Fixas" << endl;
        cout << "[5] Ver Auditoria     | [6] Sair e Gerar DRE" << endl;
        cout << UI::CIANO << "-----------------------------------------------" << UI::RESET << endl;
        
        try {
            cout << "Escolha: ";
            if (!(cin >> opt)) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw ErroERP("Entrada inválida.");
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
            cout << "Pressione ENTER...";
            cin.ignore(1000, '\n'); cin.get();
        }

    } while (opt != 6);
    gerarRelatorioFinal();
}

void SistemaERP::adicionarCliente() {
    string n;
    cout << "Nome do Cliente: ";
    getline(cin >> ws, n);
    filaClientes.push(n);
    cout << UI::VERDE << "[OK]: Cliente na fila." << UI::RESET << endl;
    usleep(500000);
}

void SistemaERP::realizarVenda() {
    if (filaClientes.empty()) throw ErroERP("Fila de clientes vazia.");
    
    cout << "\n--- ESTOQUE DE PRODUTOS ---" << endl;
    for (int i = 0; i < (int)estoque.size(); i++) {
        cout << "[" << i << "] " << left << setw(20) << estoque[i].nome 
             << " | Preço: " << UI::VERDE << formatarMoeda(estoque[i].getPrecoVenda()) << UI::RESET
             << " | Est: " << (estoque[i].estoque > 0 ? to_string(estoque[i].estoque) : UI::VERMELHO + "ESG" + UI::RESET) << endl;
    }

    int idx;
    cout << "\nProduto ID para venda: "; cin >> idx;

    if (idx < 0 || idx >= (int)estoque.size()) throw ErroERP("ID inválido.");
    if (estoque[idx].estoque <= 0) throw ErroERP("Produto indisponível.");

    long long preco = estoque[idx].getPrecoVenda();
    saldoCaixa += preco;
    estoque[idx].estoque--;
    filaClientes.pop();

    registrarLog("VENDA: " + estoque[idx].nome, preco);
    cout << UI::VERDE << "[SUCESSO]: Transação concluída." << UI::RESET << endl;
    usleep(500000);
}

void SistemaERP::comprarEstoque() {
    cout << "\n--- FORNECEDORES (REPOSIÇÃO) ---" << endl;
    for (int i = 0; i < (int)estoque.size(); i++) {
        cout << "[" << i << "] " << left << setw(20) << estoque[i].nome 
             << " | Custo: " << UI::AMARELO << formatarMoeda(estoque[i].custoCentavos) << UI::RESET << endl;
    }

    int idx, qtd;
    cout << "ID: "; cin >> idx;
    cout << "Qtd: "; cin >> qtd;

    if (idx < 0 || idx >= (int)estoque.size()) throw ErroERP("ID inválido.");
    
    long long total = estoque[idx].custoCentavos * qtd;
    if (total > saldoCaixa) throw ErroERP("Saldo insuficiente para compra.");

    saldoCaixa -= total;
    estoque[idx].estoque += qtd;

    registrarLog("COMPRA: " + estoque[idx].nome + " (x" + to_string(qtd) + ")", -total);
    cout << UI::VERDE << "[SUCESSO]: Compra registrada no caixa." << UI::RESET << endl;
    usleep(500000);
}

void SistemaERP::pagarGastosFixos() {
    if (saldoCaixa < despesasFixas) throw ErroERP("Alerta de Inadimplência! Saldo insuficiente.");
    
    saldoCaixa -= despesasFixas;
    registrarLog("DESPESA: Contas Mensais", -despesasFixas);
    cout << UI::VERDE << "[OK]: Pagamento efetuado." << UI::RESET << endl;
    usleep(500000);
}

void SistemaERP::mostrarAuditoria() const {
    UI::limparTela();
    cout << UI::CIANO << "--- DASHBOARD DE AUDITORIA ---" << UI::RESET << endl;
    cout << "\nULTIMAS OPERAÇÕES (LIFO):" << endl;
    stack<LogOperacao> temp = logs;
    int count = 0;
    while (!temp.empty() && count < 8) {
        LogOperacao l = temp.top();
        cout << "[" << l.timestamp << "] " << left << setw(25) << l.acao 
             << " | " << (l.valorImpacto >= 0 ? UI::VERDE : UI::VERMELHO) 
             << formatarMoeda(l.valorImpacto) << UI::RESET << endl;
        temp.pop();
        count++;
    }
    cout << "\n[ENTER] para retornar...";
    cin.ignore(1000, '\n'); cin.get();
}

void SistemaERP::registrarLog(const string& desc, long long valor) {
    logs.push({getAgora(), desc, valor});
}

void SistemaERP::gerarRelatorioFinal() const {
    ofstream arq("repositorio-extra/atividade-extra16/DRE_SESSAO.txt");
    if (!arq.is_open()) arq.open("DRE_SESSAO.txt");
    arq << "RELATÓRIO ERP - FECHAMENTO DE CAIXA\n";
    arq << "Saldo Final: " << formatarMoeda(saldoCaixa) << "\n\n";
    
    stack<LogOperacao> temp = logs;
    while (!temp.empty()) {
        LogOperacao l = temp.top();
        arq << "[" << l.timestamp << "] " << l.acao << " : " << formatarMoeda(l.valorImpacto) << "\n";
        temp.pop();
    }
    arq.close();
    cout << UI::VERDE << "\n[ERP]: Fechamento concluído. Verifique DRE_SESSAO.txt." << UI::RESET << endl;
}

string SistemaERP::formatarMoeda(long long centavos) {
    bool neg = centavos < 0;
    double r = static_cast<double>(abs(centavos)) / 100.0;
    stringstream ss;
    ss << (neg ? "-" : "") << "R$ " << fixed << setprecision(2) << r;
    return ss.str();
}

string SistemaERP::getAgora() const {
    time_t t = time(0);
    struct tm * now = localtime(&t);
    char b[10];
    strftime(b, sizeof(b), "%H:%M:%S", now);
    return string(b);
}
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

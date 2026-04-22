/**
 * @file atividade-extra20-banco.cpp
 * @brief DESAFIO INTEGRADOR: Núcleo Bancário G-BANK v1.0 (INTERATIVO).
 * 
 * Este projeto integra:
 * 1. POO (Classes, private/public, static)
 * 2. Robustez (Try-catch para saques/depósitos)
 * 3. Persistência (Escrita de extrato em TXT)
 * 4. UX (Interface ANSI Interativa)
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <exception>
#include <sstream>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERMELHO = "\033[31m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string NEGRITO  = "\033[1m";

    void cabecalho() {
        cout << CIANO << "===============================================" << endl;
        cout << "            G-BANK: CORE SYSTEM v1.0           " << endl;
        cout << "           (Terminal de Autoatendimento)       " << endl;
        cout << "===============================================" << RESET << endl;
    }

    void menu() {
        cout << "\n--- OPERAÇÕES DISPONÍVEIS ---" << endl;
        cout << "[1] Ver Saldo" << endl;
        cout << "[2] Depositar" << endl;
        cout << "[3] Sacar" << endl;
        cout << "[4] Transferir (PIX)" << endl;
        cout << "[5] Auditoria Global do Banco" << endl;
        cout << "[6] Sair e Gerar Extratos" << endl;
        cout << "Escolha: ";
    }
}

// --- 2. CLASSES DE EXCEÇÃO ---

class ErroBancario : public exception {
    string msg;
public:
    ErroBancario(string m) : msg(UI::VERMELHO + "[ERRO BANCÁRIO]: " + m + UI::RESET) {}
    const char* what() const throw() { return msg.c_str(); }
};

// --- 3. CLASSE CONTA BANCÁRIA ---

class ContaBancaria {
private:
    int id;
    string titular;
    long long saldoCentavos;

    static int totalContas;
    static long long reservaTotalBanco;

public:
    ContaBancaria(int _id, string _titular) 
        : id(_id), titular(_titular), saldoCentavos(0) 
    {
        totalContas++;
    }

    ContaBancaria(int _id, string _titular, double depositoInicial)
        : id(_id), titular(_titular)
    {
        if (depositoInicial < 0) throw ErroBancario("Depósito inicial negativo.");
        
        saldoCentavos = static_cast<long long>(depositoInicial * 100);
        reservaTotalBanco += saldoCentavos;
        totalContas++;
    }

    void depositar(double valor) {
        if (valor <= 0) throw ErroBancario("Valor de depósito inválido.");
        long long centavos = static_cast<long long>(valor * 100);
        saldoCentavos += centavos;
        reservaTotalBanco += centavos;
        cout << UI::VERDE << "[SUCESSO]: R$ " << fixed << setprecision(2) << valor << " creditado." << UI::RESET << endl;
    }

    void sacar(double valor) {
        long long centavos = static_cast<long long>(valor * 100);
        if (centavos > saldoCentavos) throw ErroBancario("Saldo insuficiente.");
        if (valor <= 0) throw ErroBancario("Valor inválido.");

        saldoCentavos -= centavos;
        reservaTotalBanco -= centavos;
        cout << UI::VERMELHO << "[SUCESSO]: R$ " << fixed << setprecision(2) << valor << " debitado." << UI::RESET << endl;
    }

    void transferirPara(ContaBancaria &destino, double valor) {
        this->sacar(valor);
        destino.depositar(valor);
        cout << UI::AMARELO << "[PIX]: Transferência realizada!" << UI::RESET << endl;
    }

    void exibirSaldo() const {
        double real = static_cast<double>(saldoCentavos) / 100.0;
        cout << UI::CIANO << "CONTA: " << id << " | TITULAR: " << titular << UI::RESET << endl;
        cout << "SALDO ATUAL: " << UI::NEGRITO << "R$ " << real << UI::RESET << endl;
    }

    string getTitular() const { return titular; }
    static int getTotalContas() { return totalContas; }
    static double getReservaTotal() { return static_cast<double>(reservaTotalBanco) / 100.0; }

    void gerarExtratoTxt() const {
        string nomeArq = "repositorio-extra/atividade-extra20/extrato_" + to_string(id) + ".txt";
        ofstream arq(nomeArq);
        if (arq.is_open()) {
            arq << "--- G-BANK EXTRATO OFICIAL ---\n";
            arq << "TITULAR: " << titular << "\n";
            arq << "SALDO FINAL: R$ " << (static_cast<double>(saldoCentavos) / 100.0) << "\n";
            arq.close();
        }
    }

    // Reset para os testes (Apenas para fins pedagógicos)
    static void resetBanco() {
        totalContas = 0;
        reservaTotalBanco = 0;
    }

    double getSaldoReal() const {
        return static_cast<double>(saldoCentavos) / 100.0;
    }
};

int ContaBancaria::totalContas = 0;
long long ContaBancaria::reservaTotalBanco = 0;

// --- 4. LABORATORIO DE TESTES (O Diferencial do Engenheiro) ---

class SuiteDeTestes {
private:
    static int testesPassados;
    static int totalTestes;

    static void afirmar(bool condicao, string descricao) {
        totalTestes++;
        if (condicao) {
            testesPassados++;
            cout << UI::VERDE << "[PASSOU] " << UI::RESET << descricao << endl;
        } else {
            cout << UI::VERMELHO << "[FALHOU] " << UI::RESET << descricao << endl;
        }
    }

public:
    static void executar() {
        cout << UI::AMARELO << "\n--- INICIANDO DIAGNÓSTICO DO MOTOR BANCÁRIO ---" << UI::RESET << endl;
        ContaBancaria::resetBanco();

        // Teste 1: Depósito Básico
        ContaBancaria t1(1, "Teste1", 100.00);
        t1.depositar(50.00);
        afirmar(t1.getSaldoReal() == 150.00, "Depósito de R$ 50 deve somar ao saldo inicial de R$ 100.");

        // Teste 2: Saque Válido
        t1.sacar(30.00);
        afirmar(t1.getSaldoReal() == 120.00, "Saque de R$ 30 deve subtrair do saldo.");

        // Teste 3: Proteção contra Saldo Insuficiente
        bool erroCapturado = false;
        try { t1.sacar(500.00); } catch(...) { erroCapturado = true; }
        afirmar(erroCapturado, "O sistema deve impedir saques maiores que o saldo disponível.");

        // Teste 4: Integridade do PIX (Transferência)
        ContaBancaria t2(2, "Teste2", 0.00);
        t1.transferirPara(t2, 20.00);
        afirmar(t1.getSaldoReal() == 100.00 && t2.getSaldoReal() == 20.00, 
               "PIX deve debitar da origem e creditar no destino simultaneamente.");

        // Teste 5: Reserva Global do Banco
        afirmar(ContaBancaria::getReservaTotal() == 120.00, "A reserva do banco deve ser a soma de todos os saldos.");

        cout << UI::AMARELO << "-----------------------------------------------" << endl;
        cout << "RESULTADO: " << testesPassados << "/" << totalTestes << " TESTES OK." << endl;
        if (testesPassados == totalTestes) 
            cout << UI::VERDE << "MOTOR BANCÁRIO VALIDADO COM SUCESSO!" << UI::RESET << endl;
        else
            cout << UI::VERMELHO << "ALERTA: FALHA CRÍTICA NO MOTOR BANCÁRIO!" << UI::RESET << endl;
        cout << "-----------------------------------------------\n" << endl;
        
        // Limpa para a execução real
        ContaBancaria::resetBanco();
    }
};
int SuiteDeTestes::testesPassados = 0;
int SuiteDeTestes::totalTestes = 0;

// --- 5. FUNÇÃO PRINCIPAL INTERATIVA ---

int main()
{
    UI::cabecalho();

    // EXECUTANDO VALIDAÇÃO ATIVA ANTES DO MENU
    SuiteDeTestes::executar();

    // Setup de Contas para o Aluno
    ContaBancaria c1(1001, "Cristiano Pessoa", 1000.00);
    ContaBancaria c2(2002, "Aluno SENAI", 10.00);

    int opcao = 0;
    int contaAtiva = 1; // 1 para c1, 2 para c2

    do {
        cout << "\n-----------------------------------------------" << endl;
        cout << "LOGADO COMO: " << UI::AMARELO << (contaAtiva == 1 ? c1.getTitular() : c2.getTitular()) << UI::RESET << endl;
        cout << "[7] Trocar Usuário" << endl;
        
        UI::menu();
        cin >> opcao;

        try {
            ContaBancaria &atual = (contaAtiva == 1) ? c1 : c2;
            ContaBancaria &outra = (contaAtiva == 1) ? c2 : c1;

            switch (opcao) {
                case 1: 
                    atual.exibirSaldo(); 
                    break;
                
                case 2: {
                    double v;
                    cout << "Valor do Depósito: "; cin >> v;
                    atual.depositar(v);
                    break;
                }
                
                case 3: {
                    double v;
                    cout << "Valor do Saque: "; cin >> v;
                    atual.sacar(v);
                    break;
                }
                
                case 4: {
                    double v;
                    cout << "Valor do PIX para " << outra.getTitular() << ": "; cin >> v;
                    atual.transferirPara(outra, v);
                    break;
                }
                
                case 5:
                    cout << "\n--- AUDITORIA CENTRAL DO BANCO ---" << endl;
                    cout << "Total de Contas: " << ContaBancaria::getTotalContas() << endl;
                    cout << "Reserva em Custódia: " << UI::VERDE << "R$ " << ContaBancaria::getReservaTotal() << UI::RESET << endl;
                    break;

                case 7:
                    contaAtiva = (contaAtiva == 1) ? 2 : 1;
                    cout << "[SISTEMA]: Usuário alterado com sucesso." << endl;
                    break;
            }
        } catch (const exception& e) {
            cout << e.what() << endl;
        }

    } while (opcao != 6);

    c1.gerarExtratoTxt();
    c2.gerarExtratoTxt();
    cout << UI::VERDE << "\nObrigado por usar o G-BANK! Extratos gerados." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO INTEGRADOR POO I (INTERATIVO)
    ===============================================================

    1. INTERAÇÃO E ESTADO DO OBJETO:
       - Vimos como o estado interno do objeto (saldo) muda de acordo 
         com as entradas do usuário, mantendo a consistência.

    2. REFERÊNCIAS EM OPERAÇÕES (ContaBancaria &atual):
       - Usamos referências no menu para evitar criar cópias das 
         contas, garantindo que as operações ocorram nos objetos reais.

    3. RESILIÊNCIA DE ENTRADA:
       - O uso de try-catch dentro do loop garante que um erro do 
         usuário (como tentar sacar mais do que tem) não feche o 
         programa, permitindo que ele tente novamente.

    4. AUDITORIA ESTÁTICA:
       - Mesmo com o usuário "brincando" de transferir dinheiro de 
         um lado para o outro, a auditoria estática prova que a 
         reserva total do banco se mantém íntegra.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Construtores Delegados (C++11).
    - Métodos Inline para performance.
    - Manipulação de fluxo (cin.fail()) para evitar letras em números.
    ===============================================================
*/

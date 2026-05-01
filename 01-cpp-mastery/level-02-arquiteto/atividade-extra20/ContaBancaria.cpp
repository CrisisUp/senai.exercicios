#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file ContaBancaria.cpp
 * @brief Implementação da classe ContaBancaria e UI.
 */

#include "ContaBancaria.h"
#include <iomanip>
#include <fstream>

using namespace std;

// --- Implementação UI ---
void UI::cabecalho() {
    cout << CIANO << NEGRITO << "===============================================" << endl;
    cout << "            G-BANK: CORE SYSTEM v2.0           " << endl;
    cout << "           (Terminal de Autoatendimento)       " << endl;
    cout << "===============================================" << RESET << endl;
}

// --- Inicialização de Membros Estáticos ---
int ContaBancaria::totalContas = 0;
long long ContaBancaria::reservaTotalBanco = 0;

// --- Implementação ContaBancaria ---

ContaBancaria::ContaBancaria(int _id, const string& _titular) 
    : id(_id), titular(_titular), saldoCentavos(0) 
{
    totalContas++;
}

ContaBancaria::ContaBancaria(int _id, const string& _titular, double depositoInicial)
    : id(_id), titular(_titular)
{
    if (depositoInicial < 0) throw ErroBancario("Depósito inicial negativo proibido.");
    
    saldoCentavos = static_cast<long long>(depositoInicial * 100);
    reservaTotalBanco += saldoCentavos;
    totalContas++;
}

void ContaBancaria::depositar(double valor) {
    if (valor <= 0) throw ErroBancario("Valor de depósito deve ser positivo.");
    long long centavos = static_cast<long long>(valor * 100);
    saldoCentavos += centavos;
    reservaTotalBanco += centavos;
    cout << UI::VERDE << "[CRÉDITO]: +R$ " << fixed << setprecision(2) << valor << UI::RESET << endl;
}

void ContaBancaria::sacar(double valor) {
    long long centavos = static_cast<long long>(valor * 100);
    if (centavos > saldoCentavos) throw ErroBancario("Saldo insuficiente para saque.");
    if (valor <= 0) throw ErroBancario("Valor de saque inválido.");

    saldoCentavos -= centavos;
    reservaTotalBanco -= centavos;
    cout << UI::VERMELHO << "[DÉBITO]: -R$ " << fixed << setprecision(2) << valor << UI::RESET << endl;
}

void ContaBancaria::transferirPara(ContaBancaria &destino, double valor) {
    this->sacar(valor);
    destino.depositar(valor);
    cout << UI::AMARELO << UI::NEGRITO << "[PIX]: Transferência realizada com sucesso!" << UI::RESET << endl;
}

void ContaBancaria::exibirSaldo() const {
    double real = static_cast<double>(saldoCentavos) / 100.0;
    cout << UI::CIANO << "CONTA: " << id << " | TITULAR: " << UI::NEGRITO << titular << UI::RESET << endl;
    cout << "SALDO ATUAL: " << UI::NEGRITO << UI::VERDE << "R$ " << real << UI::RESET << endl;
}

double ContaBancaria::getSaldoReal() const {
    return static_cast<double>(saldoCentavos) / 100.0;
}

double ContaBancaria::getReservaTotal() {
    return static_cast<double>(reservaTotalBanco) / 100.0;
}

void ContaBancaria::gerarExtratoTxt() const {
    string nomeArq = "01-cpp-mastery/level-02-arquiteto/atividade-extra20/extrato_" + to_string(id) + ".txt";
    ofstream arq(nomeArq);
    if (arq.is_open()) {
        arq << "===============================================\n";
        arq << "          G-BANK EXTRATO OFICIAL               \n";
        arq << "===============================================\n";
        arq << "ID CONTA: " << id << "\n";
        arq << "TITULAR : " << titular << "\n";
        arq << "SALDO FINAL: R$ " << (static_cast<double>(saldoCentavos) / 100.0) << "\n";
        arq << "-----------------------------------------------\n";
        arq.close();
    }
}

void ContaBancaria::resetBanco() {
    totalContas = 0;
    reservaTotalBanco = 0;
}

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

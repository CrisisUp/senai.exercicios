/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file ContaBancaria.h
 * @brief Definições da classe ContaBancaria e utilitários de UI.
 */

#ifndef CONTA_BANCARIA_H
#define CONTA_BANCARIA_H

#include <iostream>
#include <string>
#include <exception>

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";

    inline void limparTela() { std::cout << "\033[2J\033[1;1H"; }
    void cabecalho();
}

// --- 2. GESTÃO DE EXCEÇÕES CUSTOMIZADAS ---
class ErroBancario : public std::exception {
    std::string msg;
public:
    ErroBancario(std::string m) : msg(UI::VERMELHO + "[ERRO BANCÁRIO]: " + m + UI::RESET) {}
    const char* what() const throw() override { return msg.c_str(); }
};

// --- 3. CLASSE CONTA BANCÁRIA ---
class ContaBancaria {
private:
    int id;
    std::string titular;
    long long saldoCentavos;

    static int totalContas;
    static long long reservaTotalBanco;

public:
    ContaBancaria(int _id, const std::string& _titular);
    ContaBancaria(int _id, const std::string& _titular, double depositoInicial);

    void depositar(double valor);
    void sacar(double valor);
    void transferirPara(ContaBancaria &destino, double valor);

    void exibirSaldo() const;
    const std::string& getTitular() const { return titular; }
    double getSaldoReal() const;

    static int getTotalContas() { return totalContas; }
    static double getReservaTotal();

    void gerarExtratoTxt() const;
    static void resetBanco();
};

#endif // CONTA_BANCARIA_H

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

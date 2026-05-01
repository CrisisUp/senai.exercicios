#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file MotorFinanceiro.cpp
 * @brief Implementação da integridade financeira com centavos inteiros.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "MotorFinanceiro.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

GestorFinanceiro::GestorFinanceiro() : caixaTotal(0) {}

void GestorFinanceiro::carregarCatalogo() {
    ifstream arquivo("repositorio-extra/atividade-extra15/catalogo.txt");
    if (!arquivo.is_open()) arquivo.open("catalogo.txt");
    if (!arquivo.is_open()) throw ErroBiblioteca("Arquivo de catálogo ausente.");

    string linha;
    while (getline(arquivo, linha)) {
        size_t p1 = linha.find(';');
        size_t p2 = linha.find(';', p1 + 1);
        size_t p3 = linha.find(';', p2 + 1);

        if (p3 != std::string::npos) {
            Livro l;
            l.titulo = linha.substr(0, p1);
            l.autor = linha.substr(p1 + 1, p2 - p1 - 1);
            l.estoque = stoi(linha.substr(p2 + 1, p3 - p2 - 1));
            l.precoCentavos = stoll(linha.substr(p3 + 1));
            l.id = (int)catalogo.size();
            catalogo.push_back(l);
        }
    }
    cout << UI::VERDE << "[SISTEMA]: Catálogo Financeiro carregado com sucesso." << UI::RESET << endl;
}

void GestorFinanceiro::adicionarLeitor(const string& nome) {
    if (nome.empty()) throw ErroBiblioteca("Nome do leitor não pode ser vazio.");
    filaLeitores.push(nome);
    cout << UI::VERDE << "[OK]: " << nome << " aguardando atendimento." << UI::RESET << endl;
}

void GestorFinanceiro::processarAluguel(int idx, const string& valorStr) {
    if (idx < 0 || idx >= (int)catalogo.size()) throw ErroBiblioteca("ID de livro inválido.");
    if (catalogo[idx].estoque <= 0) throw ErroBiblioteca("Livro esgotado.");

    long long recebido = converterParaCentavos(valorStr);
    long long preco = catalogo[idx].precoCentavos;

    if (recebido < preco) {
        throw ErroFinanceiro("Valor insuficiente! Faltam " + formatarMoeda(preco - recebido));
    }

    // Sucesso na transação
    string leitor = filaLeitores.front();
    filaLeitores.pop();
    
    catalogo[idx].estoque--;
    caixaTotal += preco;

    long long troco = recebido - preco;
    cout << UI::VERDE << "[SUCESSO]: Aluguel de '" << catalogo[idx].titulo << "' confirmado!" << UI::RESET << endl;
    if (troco > 0) cout << "Troco devolvido: " << UI::AMARELO << formatarMoeda(troco) << UI::RESET << endl;

    Aluguel alg = {leitor, catalogo[idx], preco};
    historico.push(alg);
}

string GestorFinanceiro::formatarMoeda(long long centavos) {
    double reais = static_cast<double>(centavos) / 100.0;
    stringstream ss;
    ss << "R$ " << fixed << setprecision(2) << reais;
    return ss.str();
}

long long GestorFinanceiro::converterParaCentavos(string input) {
    replace(input.begin(), input.end(), ',', '.');
    try {
        double valor = stod(input);
        if (valor < 0) throw 1;
        return static_cast<long long>((valor * 100.0) + 0.5);
    } catch (...) {
        throw ErroFinanceiro("Valor monetário inválido: '" + input + "'");
    }
}

int GestorFinanceiro::lerInteiro(const string& prompt) {
    int v;
    cout << prompt;
    if (!(cin >> v)) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw ErroBiblioteca(UI::AMARELO + "[ERRO]: Digite um número válido." + UI::RESET);
    }
    return v;
}

void GestorFinanceiro::exibirBanner() {
    cout << UI::CIANO << "===============================================" << endl;
    cout << "      BIBLIOTECA FINANCEIRA v3.0 (SEGURA)      " << endl;
    cout << "      (Arquitetura Modular Refatorada)         " << endl;
    cout << "===============================================" << UI::RESET << endl;
}
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

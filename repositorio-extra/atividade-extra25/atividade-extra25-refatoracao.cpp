/**
 * @file atividade-extra25-refatoracao.cpp
 * @brief DESAFIO DE MAESTRIA: Refatoração do Sistema de Estoque (v1.0 -> v4.0).
 * 
 * Este programa moderniza a Atividade 01, substituindo variáveis procedurais
 * por uma arquitetura POO com encapsulamento, membros estáticos e exceções.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <exception>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string VERMELHO = "\033[31m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string NEGRITO  = "\033[1m";

    void cabecalho() {
        cout << CIANO << "===============================================" << endl;
        cout << "       ALMOXARIFADO INDUSTRIAL v4.0 (REFAC)    " << endl;
        cout << "===============================================" << RESET << endl;
    }
}

// --- 2. GESTÃO DE EXCEÇÕES ---

class ErroEstoque : public exception {
    string msg;
public:
    ErroEstoque(string m) : msg(UI::VERMELHO + "[ERRO]: " + m + UI::RESET) {}
    const char* what() const throw() { return msg.c_str(); }
};

// --- 3. CLASSE MODERNIZADA (O CORAÇÃO DA REFATORAÇÃO) ---

class ProdutoIndustrial {
private:
    string nome;
    double preco;
    int quantidade;

    // Membros Estáticos: Visão Global do Patrimônio
    static double valorInvestidoGlobal;
    static int contadorProdutos;

public:
    // Construtor com Lista de Inicialização (Moderno)
    ProdutoIndustrial(string _nome, double _preco, int _qtd) 
        : nome(_nome), preco(_preco), quantidade(_qtd) 
    {
        if (_preco < 0 || _qtd < 0) throw ErroEstoque("Dados iniciais inválidos.");
        
        valorInvestidoGlobal += (preco * quantidade);
        contadorProdutos++;
    }

    // --- MÉTODOS DE NEGÓCIO ---

    void registrarSaida(int qtd) {
        if (qtd > quantidade) throw ErroEstoque("Estoque insuficiente para '" + nome + "'.");
        if (qtd <= 0) throw ErroEstoque("Quantidade de saída deve ser positiva.");

        valorInvestidoGlobal -= (preco * qtd);
        quantidade -= qtd;
        cout << UI::VERDE << "[OK]: Saída registrada com sucesso." << UI::RESET << endl;
    }

    void exibirItem() const {
        cout << left << setw(20) << nome 
             << " | Preço: R$ " << setw(10) << preco 
             << " | Qtd: " << setw(5) << quantidade 
             << " | Subtotal: R$ " << (preco * quantidade) << endl;
    }

    // --- MÉTODOS ESTÁTICOS ---
    static double getValorGlobal() { return valorInvestidoGlobal; }
    static int getContador() { return contadorProdutos; }

    string getNome() const { return nome; }
};

// Inicialização de membros estáticos
double ProdutoIndustrial::valorInvestidoGlobal = 0.0;
int ProdutoIndustrial::contadorProdutos = 0;

// --- 4. FUNÇÃO PRINCIPAL ---

int main()
{
    UI::cabecalho();
    cout << fixed << setprecision(2);

    vector<ProdutoIndustrial*> almoxarifado;

    try {
        // Criando itens (Simulando o legado modernizado)
        almoxarifado.push_back(new ProdutoIndustrial("Motor Trifásico", 1250.00, 5));
        almoxarifado.push_back(new ProdutoIndustrial("Sensor Óptico", 85.50, 20));
        almoxarifado.push_back(new ProdutoIndustrial("CLP Siemens", 4500.00, 2));

        cout << "Produtos Cadastrados: " << ProdutoIndustrial::getContador() << endl;
        cout << "Valor Total em Estoque: " << UI::VERDE << "R$ " << ProdutoIndustrial::getValorGlobal() << UI::RESET << endl;
        cout << "-----------------------------------------------" << endl;

        // Simulando Operação de Retirada
        cout << "\n[OPERAÇÃO]: Retirando 2 unidades de 'Motor Trifásico'..." << endl;
        almoxarifado[0]->registrarSaida(2);

        // Listagem Final
        cout << "\n--- RELATÓRIO DE INVENTÁRIO CONSOLIDADO ---" << endl;
        for (auto p : almoxarifado) p->exibirItem();

        cout << "\n-----------------------------------------------" << endl;
        cout << "Patrimônio Total Final: " << UI::AMARELO << "R$ " << ProdutoIndustrial::getValorGlobal() << UI::RESET << endl;

        // Testando Robustez (Tentativa de erro)
        cout << "\n[TESTE DE SEGURANÇA]: Tentando retirar 100 sensores (inválido)..." << endl;
        almoxarifado[1]->registrarSaida(100);

    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Limpeza de memória
    for (auto p : almoxarifado) delete p;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: REFATORAÇÃO EVOLUTIVA (LEGACY TO POO)
    ===============================================================

    1. DE VARIÁVEIS PARA OBJETOS:
       - Na Atividade 01, usávamos variáveis soltas. Aqui, o 
         ProdutoIndustrial é uma entidade autocontida que sabe 
         cuidar dos seus próprios dados.

    2. INTEGRIDADE DE ESTADO:
       - O uso de métodos como registrarSaida() garante que o 
         estoque nunca fique negativo, algo impossível de controlar 
         com variáveis públicas simples.

    3. COMPUTAÇÃO CENTRALIZADA (Static):
       - O valor global do estoque é calculado automaticamente a 
         cada transação. Isso retira a complexidade da função main 
         e a transfere para a inteligência da classe.

    4. RESILIÊNCIA (Exceções):
       - O sistema trata erros de lógica de negócio (estoque 
         insuficiente) como exceções, permitindo que a aplicação 
         continue rodando em vez de gerar resultados errados ou quebrar.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Code Smell: Identificando códigos mal escritos.
    - Testes de Regressão: Garantir que o novo sistema faz o mesmo 
      que o antigo (mas melhor).
    - Princípio DRY (Don't Repeat Yourself).
    ===============================================================
*/

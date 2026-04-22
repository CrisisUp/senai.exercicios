/**
 * @file MotorFinanceiro.h
 * @brief Definições de Integridade Financeira, Centavos e Gestão de Caixa.
 * 
 * Parte da Atividade Extra 15 - Refatoração Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef MOTOR_FINANCEIRO_H
#define MOTOR_FINANCEIRO_H

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <exception>

// --- 1. NAMESPACE DE CORES (ANSI) ---

namespace Cor {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERMELHO = "\033[31m";
    const std::string VERDE    = "\033[32m";
    const std::string AMARELO  = "\033[33m";
    const std::string CIANO    = "\033[36m";
}

// --- 2. CLASSES DE EXCEÇÃO ---

class ErroBiblioteca : public std::exception {
protected:
    std::string mensagem;
public:
    ErroBiblioteca(std::string msg) : mensagem(msg) {}
    virtual const char* what() const throw() { return mensagem.c_str(); }
};

class ErroFinanceiro : public ErroBiblioteca {
public:
    ErroFinanceiro(std::string msg) : ErroBiblioteca(Cor::VERMELHO + "[FINANCEIRO]: " + msg + Cor::RESET) {}
};

// --- 3. ESTRUTURAS DE DADOS ---

struct Livro {
    std::string titulo;
    std::string autor;
    int estoque;
    int precoCentavos; 
    int id;
};

struct Aluguel {
    std::string leitor;
    Livro livro;
    int valorPago;
};

// --- 4. CLASSE GESTOR FINANCEIRO ---

class GestorFinanceiro {
private:
    std::vector<Livro> catalogo;
    std::queue<std::string> filaLeitores;
    std::stack<Aluguel> historico;
    int caixaTotal;

public:
    GestorFinanceiro();

    void carregarCatalogo();
    
    // Ações de Caixa
    void adicionarLeitor(std::string nome);
    void processarAluguel(int idx, std::string valorStr);
    
    // Utilitários de Conversão
    static std::string formatarMoeda(int centavos);
    static int converterParaCentavos(std::string input);
    static int lerInteiro(std::string prompt);
    
    // Getters
    std::vector<Livro>& getCatalogo() { return catalogo; }
    std::queue<std::string>& getFila() { return filaLeitores; }
    int getCaixa() const { return caixaTotal; }
    int getOperacoesCount() const { return (int)historico.size(); }

    static void exibirBanner();
};

#endif // MOTOR_FINANCEIRO_H

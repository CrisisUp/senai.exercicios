/**
 * @file MotorFinanceiro.h
 * @brief Definições de Integridade Financeira, Centavos e Gestão de Caixa.
 * 
 * Parte da Atividade Extra 15 - Refatoração Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap MAPA DE MEMÓRIA (Elite Refactor)
 * - STACK: Variáveis locais, parâmetros de função (long long, int), structs Aluguel temporárias.
 * - HEAP: std::vector<Livro> (Catálogo), std::queue e std::stack (Crescimento dinâmico).
 */

#ifndef MOTOR_FINANCEIRO_H
#define MOTOR_FINANCEIRO_H

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <exception>

// --- 1. NAMESPACE DE UI (ANSI) ---

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERMELHO = "\033[31m";
    const std::string VERDE    = "\033[32m";
    const std::string AMARELO  = "\033[33m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
}

// --- 2. CÓDIGO BLINDADO (EXCEÇÕES CUSTOMIZADAS) ---

class ErroBiblioteca : public std::exception {
protected:
    std::string mensagem;
public:
    ErroBiblioteca(const std::string& msg) : mensagem(msg) {}
    virtual const char* what() const throw() { return mensagem.c_str(); }
};

class ErroFinanceiro : public ErroBiblioteca {
public:
    ErroFinanceiro(const std::string& msg) : ErroBiblioteca(UI::VERMELHO + "[FINANCEIRO]: " + msg + UI::RESET) {}
};

// --- 3. GUARDIÃO FINANCEIRO (CENTAVOS EM LONG LONG) ---

struct Livro {
    std::string titulo;
    std::string autor;
    int estoque;
    long long precoCentavos; 
    int id;
};

struct Aluguel {
    std::string leitor;
    Livro livro;
    long long valorPago;
};

// --- 4. CLASSE GESTOR FINANCEIRO (FANTASMA DO CPU) ---

class GestorFinanceiro {
private:
    std::vector<Livro> catalogo;
    std::queue<std::string> filaLeitores;
    std::stack<Aluguel> historico;
    long long caixaTotal;

public:
    GestorFinanceiro();

    void carregarCatalogo();
    
    // Ações de Caixa
    void adicionarLeitor(const std::string& nome);
    void processarAluguel(int idx, const std::string& valorStr);
    
    // Utilitários de Conversão
    static std::string formatarMoeda(long long centavos);
    static long long converterParaCentavos(std::string input);
    static int lerInteiro(const std::string& prompt);
    
    // Getters Const-Safe (Fantasma do CPU)
    const std::vector<Livro>& getCatalogo() const { return catalogo; }
    const std::queue<std::string>& getFila() const { return filaLeitores; }
    long long getCaixa() const { return caixaTotal; }
    int getOperacoesCount() const { return (int)historico.size(); }

    static void exibirBanner();
};

#endif // MOTOR_FINANCEIRO_H

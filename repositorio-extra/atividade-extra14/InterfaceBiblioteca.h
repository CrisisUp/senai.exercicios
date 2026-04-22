/**
 * @file InterfaceBiblioteca.h
 * @brief Definições de Estilos ANSI, Exceções Coloridas e Classe de Gestão.
 * 
 * Parte da Atividade Extra 14 - Refatoração Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef INTERFACE_BIBLIOTECA_H
#define INTERFACE_BIBLIOTECA_H

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
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string BRANCO   = "\033[37m";
}

// --- 2. CLASSES DE EXCEÇÃO COLORIDAS ---

class ErroBiblioteca : public std::exception {
protected:
    std::string mensagem;
public:
    ErroBiblioteca(std::string msg) : mensagem(msg) {}
    virtual const char* what() const throw() {
        return mensagem.c_str();
    }
};

class ErroArquivo : public ErroBiblioteca {
public:
    ErroArquivo(std::string arquivo) : ErroBiblioteca(Cor::VERMELHO + "[ERRO CRÍTICO]: Arquivo '" + arquivo + "' não encontrado." + Cor::RESET) {}
};

class ErroEntrada : public ErroBiblioteca {
public:
    ErroEntrada() : ErroBiblioteca(Cor::AMARELO + "[AVISO]: Entrada inválida. Digite apenas números." + Cor::RESET) {}
};

class ErroEstoque : public ErroBiblioteca {
public:
    ErroEstoque(std::string titulo) : ErroBiblioteca(Cor::VERMELHO + "[ESTOQUE]: O livro '" + titulo + "' esgotou." + Cor::RESET) {}
};

// --- 3. ESTRUTURAS DE DADOS ---

struct Livro {
    std::string titulo;
    std::string autor;
    int estoque;
    int id;
};

struct Emprestimo {
    std::string leitor;
    Livro livro;
    std::string dataEmp;
    std::string dataDev;
    int indexCatalogo;
};

// --- 4. CLASSE GESTOR ESTILIZADO ---

class GestorEstilizado {
private:
    std::vector<Livro> catalogo;
    std::queue<std::string> filaLeitores;
    std::stack<Emprestimo> historico;

    std::string formatarData(time_t t);

public:
    void carregarCatalogo();
    void salvarRelatorio();
    
    // Ações de Negócio
    void adicionarLeitor(std::string nome);
    void atenderLeitor(int index);
    void desfazerUltimo();

    // Getters para UI
    std::vector<Livro>& getCatalogo() { return catalogo; }
    std::queue<std::string>& getFila() { return filaLeitores; }
    std::stack<Emprestimo>& getHistorico() { return historico; }

    static int lerInteiro(std::string prompt);
    static void exibirBanner();
};

#endif // INTERFACE_BIBLIOTECA_H

/**
 * @file GestorBiblioteca.h
 * @brief Definições de Exceções, Estruturas e Classe Controladora da Biblioteca.
 * 
 * Parte da Atividade Extra 13 - Refatoração Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef GESTOR_BIBLIOTECA_H
#define GESTOR_BIBLIOTECA_H

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <exception>

// --- 1. CLASSES DE EXCEÇÃO CUSTOMIZADAS ---

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
    ErroArquivo(std::string arquivo) : ErroBiblioteca("[ERRO CRÍTICO]: Arquivo '" + arquivo + "' não encontrado.") {}
};

class ErroEntrada : public ErroBiblioteca {
public:
    ErroEntrada() : ErroBiblioteca("[AVISO]: Entrada inválida. Por favor, digite apenas números.") {}
};

class ErroEstoque : public ErroBiblioteca {
public:
    ErroEstoque(std::string titulo) : ErroBiblioteca("[ESTOQUE]: O livro '" + titulo + "' esgotou. Escolha outro.") {}
};

// --- 2. ESTRUTURAS DE DADOS ---

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

// --- 3. CLASSE CONTROLADORA ---

class GestorBiblioteca {
private:
    std::vector<Livro> catalogo;
    std::queue<std::string> filaLeitores;
    std::stack<Emprestimo> historico;

    std::string formatarData(time_t t);

public:
    void carregarCatalogo();
    void salvarRelatorio();
    
    // Getters e Ações
    std::vector<Livro>& getCatalogo() { return catalogo; }
    std::queue<std::string>& getFila() { return filaLeitores; }
    std::stack<Emprestimo>& getHistorico() { return historico; }

    void adicionarLeitor(std::string nome);
    void registrarEmprestimo(int index);
    void cancelarUltimoEmprestimo();
    
    static int lerInteiro(std::string prompt);
    static void exibirBanner();
};

#endif // GESTOR_BIBLIOTECA_H

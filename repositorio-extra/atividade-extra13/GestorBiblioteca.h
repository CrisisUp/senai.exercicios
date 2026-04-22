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
#include <ctime>

/**
 * @section MemoryMap Mapeamento de Memória (Fase 3)
 * - STACK: Instância de GestorBiblioteca.
 * - HEAP: vector<Livro>, queue<string>, stack<Emprestimo>.
 */

// --- CONSOLIDAÇÃO UI ---
namespace UI {
    const std::string RESET = "\033[0m";
    const std::string RED   = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string CYAN  = "\033[36m";
    const std::string YELLOW = "\033[33m";
}

// --- 1. CLASSES DE EXCEÇÃO CUSTOMIZADAS (CÓDIGO BLINDADO) ---

class ErroBiblioteca : public std::exception {
protected:
    std::string mensagem;
public:
    ErroBiblioteca(std::string msg) : mensagem(msg) {}
    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};

class ErroArquivo : public ErroBiblioteca {
public:
    ErroArquivo(const std::string& arquivo) 
        : ErroBiblioteca("ERRO CRÍTICO: Arquivo '" + arquivo + "' não encontrado ou corrompido.") {}
};

class ErroEntrada : public ErroBiblioteca {
public:
    ErroEntrada() : ErroBiblioteca("AVISO: Entrada inválida. Por favor, digite apenas números.") {}
};

class ErroEstoque : public ErroBiblioteca {
public:
    ErroEstoque(const std::string& titulo) 
        : ErroBiblioteca("ESTOQUE: O livro '" + titulo + "' esgotou. Escolha outro.") {}
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
    
    // Getters - FANTASMA DO CPU (const refs e const methods)
    const std::vector<Livro>& getCatalogo() const { return catalogo; }
    size_t totalFila() const { return filaLeitores.size(); }
    size_t totalHistorico() const { return historico.size(); }
    const std::string& getProximoLeitor() const;

    void adicionarLeitor(const std::string& nome);
    void registrarEmprestimo(int index);
    void cancelarUltimoEmprestimo();
    
    static int lerInteiro(const std::string& prompt);
    static void exibirBanner();
};

#endif // GESTOR_BIBLIOTECA_H

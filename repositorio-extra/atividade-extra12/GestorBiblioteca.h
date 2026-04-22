/**
 * @file GestorBiblioteca.h
 * @brief Declaração da classe GestorBiblioteca, structs e exceções.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 24/04/2026
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
    ErroArquivo(std::string arquivo) : ErroBiblioteca("[ERRO CRÍTICO]: Arquivo '" + arquivo + "' não encontrado ou ilegível.") {}
};

class ErroEntrada : public ErroBiblioteca {
public:
    ErroEntrada() : ErroBiblioteca("[AVISO]: Entrada inválida. Digite apenas números.") {}
};

class ErroEstoque : public ErroBiblioteca {
public:
    ErroEstoque(std::string titulo) : ErroBiblioteca("[ESTOQUE]: O livro '" + titulo + "' não está disponível.") {}
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

// --- 3. CLASSE GESTOR ---

class GestorBiblioteca {
private:
    std::vector<Livro> catalogo;
    std::queue<std::string> filaLeitores;
    std::stack<Emprestimo> historico;

public:
    /**
     * @brief Carrega o catálogo de um arquivo.
     */
    void carregarCatalogo(const std::string& caminho);

    /**
     * @brief Adiciona um leitor à fila de espera.
     */
    void adicionarLeitor(const std::string& nome);

    /**
     * @brief Realiza um empréstimo para o próximo leitor na fila.
     * @param indexLivro Índice do livro no catálogo.
     */
    void realizarEmprestimo(int indexLivro);

    /**
     * @brief Desfaz o último empréstimo realizado.
     */
    void desfazerEmprestimo();

    /**
     * @brief Salva o relatório de empréstimos da sessão.
     */
    void salvarRelatorio(const std::string& caminho);

    // Getters
    size_t totalFila() const { return filaLeitores.size(); }
    size_t totalHistorico() const { return historico.size(); }
    const std::vector<Livro>& getCatalogo() const { return catalogo; }
    std::string getProximoLeitor() const { return filaLeitores.empty() ? "" : filaLeitores.front(); }
    bool filaVazia() const { return filaLeitores.empty(); }
    bool historicoVazio() const { return historico.empty(); }

    // Auxiliares
    static void exibirBanner();
    static std::string formatarData(time_t t);
};

#endif // GESTOR_BIBLIOTECA_H

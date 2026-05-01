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
#include <ctime>

/**
 * @section MemoryMap Mapeamento de Memória (Fase 3)
 * - STACK: Instância de GestorBiblioteca e variáveis locais de tempo.
 * - HEAP: Atributos dinâmicos como vector<Livro>, queue e stack.
 */

// --- CONSOLIDAÇÃO UI ---
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
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
        : ErroBiblioteca("ERRO DE ARQUITETURA: Arquivo '" + arquivo + "' corrompido ou inexistente.") {}
};

class ErroEntrada : public ErroBiblioteca {
public:
    ErroEntrada() : ErroBiblioteca("ERRO DE VALIDAÇÃO: Entrada inválida. Esperado dado numérico.") {}
};

class ErroEstoque : public ErroBiblioteca {
public:
    ErroEstoque(const std::string& titulo) 
        : ErroBiblioteca("ERRO DE NEGÓCIO: O livro '" + titulo + "' está esgotado.") {}
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

    // Getters - FANTASMA DO CPU (const refs e const methods)
    size_t totalFila() const { return filaLeitores.size(); }
    size_t totalHistorico() const { return historico.size(); }
    const std::vector<Livro>& getCatalogo() const { return catalogo; }
    const std::string& getProximoLeitor() const;
    bool filaVazia() const { return filaLeitores.empty(); }
    bool historicoVazio() const { return historico.empty(); }

    // Auxiliares
    static void exibirBanner();
    static std::string formatarData(time_t t);
};

#endif // GESTOR_BIBLIOTECA_H

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

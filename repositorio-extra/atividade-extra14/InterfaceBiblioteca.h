/**
 * @file InterfaceBiblioteca.h
 * @brief Definições de Estilos ANSI, Exceções Coloridas e Classe de Gestão.
 * 
 * Parte da Atividade Extra 14 - Refatoração Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap MAPA DE MEMÓRIA (Elite Refactor)
 * - STACK: Objetos Livro/Emprestimo passados por valor, variáveis locais de controle.
 * - HEAP: std::vector<Livro> gerencia alocação dinâmica interna conforme o catálogo cresce.
 */

#ifndef INTERFACE_BIBLIOTECA_H
#define INTERFACE_BIBLIOTECA_H

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
    const std::string BRANCO   = "\033[37m";
}

// --- 2. CÓDIGO BLINDADO (EXCEÇÕES CUSTOMIZADAS) ---

class ErroBiblioteca : public std::exception {
protected:
    std::string mensagem;
public:
    ErroBiblioteca(const std::string& msg) : mensagem(msg) {}
    virtual const char* what() const throw() {
        return mensagem.c_str();
    }
};

class ErroArquivo : public ErroBiblioteca {
public:
    ErroArquivo(const std::string& arquivo) : ErroBiblioteca(UI::VERMELHO + "[ERRO CRÍTICO]: Arquivo '" + arquivo + "' não encontrado." + UI::RESET) {}
};

class ErroEntrada : public ErroBiblioteca {
public:
    ErroEntrada() : ErroBiblioteca(UI::AMARELO + "[AVISO]: Entrada inválida. Digite apenas números." + UI::RESET) {}
};

class ErroEstoque : public ErroBiblioteca {
public:
    ErroEstoque(const std::string& titulo) : ErroBiblioteca(UI::VERMELHO + "[ESTOQUE]: O livro '" + titulo + "' esgotou." + UI::RESET) {}
};

// --- 3. FANTASMA DO CPU (ESTRUTURAS COM REFERÊNCIA) ---

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

// --- 4. CLASSE GESTOR ESTILIZADO (MODULAR) ---

class GestorEstilizado {
private:
    std::vector<Livro> catalogo;
    std::queue<std::string> filaLeitores;
    std::stack<Emprestimo> historico;

    std::string formatarData(time_t t) const;

public:
    void carregarCatalogo();
    void salvarRelatorio() const;
    
    // Ações de Negócio
    void adicionarLeitor(const std::string& nome);
    void atenderLeitor(int index);
    void desfazerUltimo();

    // Getters Const-Safe (Fantasma do CPU)
    const std::vector<Livro>& getCatalogo() const { return catalogo; }
    const std::queue<std::string>& getFila() const { return filaLeitores; }
    const std::stack<Emprestimo>& getHistorico() const { return historico; }

    static int lerInteiro(const std::string& prompt);
    static void exibirBanner();
};

#endif // INTERFACE_BIBLIOTECA_H

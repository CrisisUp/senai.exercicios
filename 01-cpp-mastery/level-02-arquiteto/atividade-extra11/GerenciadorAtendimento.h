/**
 * @file GerenciadorAtendimento.h
 * @brief Declaração da classe GerenciadorAtendimento.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 24/04/2026
 */

#ifndef GERENCIADOR_ATENDIMENTO_H
#define GERENCIADOR_ATENDIMENTO_H

#include <string>
#include <queue>
#include <exception>

/**
 * @section MemoryMap Mapeamento de Memória (Fase 3)
 * - STACK: Instância da classe GerenciadorAtendimento.
 * - HEAP: Elementos da std::queue<std::string> (pacientes).
 */

// --- CÓDIGO BLINDADO (EXCEÇÕES CUSTOMIZADAS) ---
class FilaVaziaException : public std::exception {
public:
    const char* what() const noexcept override {
        return "ERRO CRÍTICO: Tentativa de operação em fila vazia!";
    }
};

class ArquivoCorrompidoException : public std::exception {
public:
    const char* what() const noexcept override {
        return "ERRO DE ARQUITETURA: Falha na integridade do arquivo de pacientes!";
    }
};

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

class GerenciadorAtendimento {
private:
    std::queue<std::string> filaAtendimento;

public:
    /**
     * @brief Carrega pacientes de um arquivo para a fila.
     * @param caminhoArquivo Caminho para o arquivo .txt
     */
    void carregarPacientes(const std::string& caminhoArquivo);

    /**
     * @brief Adiciona um novo paciente à fila.
     * @param nome Nome do paciente
     */
    void adicionarPaciente(const std::string& nome);

    /**
     * @brief Atende o próximo paciente da fila.
     * @return Nome do paciente atendido.
     * @throws FilaVaziaException se não houver pacientes.
     */
    std::string atenderProximo();

    /**
     * @brief Retorna o nome do próximo paciente sem removê-lo.
     * @return Referência constante para o nome (Fantasma do CPU).
     * @throws FilaVaziaException se não houver pacientes.
     */
    const std::string& verProximo() const;

    /**
     * @brief Retorna o tamanho atual da fila.
     */
    size_t totalFila() const;

    /**
     * @brief Exibe o banner do sistema.
     */
    static void exibirBanner();
};

#endif // GERENCIADOR_ATENDIMENTO_H

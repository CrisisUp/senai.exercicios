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
     * @return Nome do paciente atendido ou string vazia se fila estiver vazia.
     */
    std::string atenderProximo();

    /**
     * @brief Retorna o nome do próximo paciente sem removê-lo.
     */
    std::string verProximo() const;

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

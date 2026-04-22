/**
 * @file Buffer.h
 * @brief Definição modular de um Gerenciador de Buffer de Log manual.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <string>

namespace Logistica {

    /**
     * @brief Classe que gerencia a memória dinâmica (Heap) manualmente.
     */
    class BufferLog {
    private:
        char* dados;        ///< Ponteiro para o array na Heap.
        int tamanhoMax;     ///< Capacidade reservada em bytes.
        int posicaoAtual;   ///< Onde a próxima mensagem será escrita.

    public:
        /**
         * @brief Construtor: Onde a Alocação ocorre (new).
         * @param tam Tamanho em bytes do buffer.
         */
        BufferLog(int tam);

        /**
         * @brief Destrutor: Onde a Liberação ocorre (delete).
         * CRITICAL: Se este método não for implementado, a memória
         * nunca voltará ao sistema (Memory Leak).
         */
        ~BufferLog();

        /**
         * @brief Escreve uma mensagem crua no buffer de memória.
         */
        void escrever(const std::string& msg);

        /**
         * @brief Reseta o ponteiro de escrita sem deletar a memória.
         */
        void limpar();

        /**
         * @brief Imprime o conteúdo bruto da memória reservada.
         */
        void despejar() const;

        int getTamanhoDisponivel() const { return tamanhoMax - posicaoAtual; }
    };
}

#endif // BUFFER_H

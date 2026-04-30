/**
 * @file Buffer.h
 * @brief Interface para o Gerenciador de Memória Manual (Buffer).
 * 
 * Atividade Extra 57 - Anatomia da Memória (Nível 31+).
 * Demonstra a alocação dinâmica pura e o padrão RAII.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Manual Heap Layout)
 * - Objeto BufferLog: Alocado na STACK da main/função.
 * - char* dados: Ponteiro de 8 bytes na STACK.
 * - Bloco de Caracteres: Alocado via 'new[]' na HEAP (área de vida longa).
 * - Ciclo de Vida: O controle (Stack) garante que o lixo (Heap) seja limpo.
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <string>

namespace Logistica {

    /**
     * @class BufferLog
     * @brief Gerenciador de memória 'Bare-Metal' para telemetria embarcada.
     */
    class BufferLog {
    private:
        char* dados;        // O endereço bruto na HEAP
        int tamanhoTotal;   // Capacidade total reservada
        int posicaoAtual;   // Cursor de escrita

    public:
        /**
         * @brief Construtor: Realiza a alocação física de RAM.
         * @param tam Tamanho em bytes a ser reservado na HEAP.
         */
        BufferLog(int tam);

        /**
         * @brief DESTRUTOR: Devolve a memória ao S.O. (O Coração do RAII).
         */
        ~BufferLog();

        /** @brief Insere texto no buffer com proteção de limites. */
        void escrever(const std::string& msg);

        /** @brief Exibe o conteúdo e limpa o cursor. */
        void despejar();

        // Getters
        int getTamanhoDisponivel() const { return tamanhoTotal - posicaoAtual; }
    };

} // namespace Logistica

#endif // BUFFER_H

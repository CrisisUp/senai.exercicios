/**
 * @file Buffer.cpp
 * @brief Implementação manual da Alocação e Desalocação de Memória.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include "Buffer.h"
#include <iostream>
#include <cstring> // Para memcpy e memset

namespace Logistica {

    BufferLog::BufferLog(int tam) : tamanhoMax(tam), posicaoAtual(0) {
        /**
         * ALOCAÇÃO DINÂMICA (HEAP):
         * Estamos pedindo ao SO um pedaço de memória de 'tam' bytes.
         * Se o sistema não tiver memória, isso lança uma exceção.
         */
        dados = new char[tamanhoMax];
        
        // Zera a memória para evitar "lixo de memória" (Zero Initialization)
        std::memset(dados, 0, tamanhoMax);
        
        std::cout << "\033[34m[SISTEMA]:\033[0m Memória reservada na HEAP: " << tam << " bytes." << std::endl;
    }

    BufferLog::~BufferLog() {
        /**
         * LIBERAÇÃO MANUAL (DELETE):
         * Esta é a linha mais importante do código. Sem ela,
         * o programa consumirá toda a RAM se for executado 
         * repetidamente.
         */
        delete[] dados;
        
        std::cout << "\033[31m[SISTEMA]:\033[0m Memória devolvida ao sistema. Buffer destruído." << std::endl;
    }

    void BufferLog::escrever(const std::string& msg) {
        int tamMsg = msg.length();
        
        if (posicaoAtual + tamMsg < tamanhoMax) {
            // Copia os bytes da string diretamente para o nosso buffer
            std::memcpy(&dados[posicaoAtual], msg.c_str(), tamMsg);
            posicaoAtual += tamMsg;
            
            // Adiciona um separador de log manual
            if (posicaoAtual < tamanhoMax) {
                dados[posicaoAtual] = '|';
                posicaoAtual++;
            }
        } else {
            std::cout << "[ALERTA]: Buffer de memória lotado!" << std::endl;
        }
    }

    void BufferLog::limpar() {
        std::memset(dados, 0, tamanhoMax);
        posicaoAtual = 0;
        std::cout << "\033[33m[SISTEMA]:\033[0m Conteúdo do buffer zerado." << std::endl;
    }

    void BufferLog::despejar() const {
        std::cout << "\nCONTEÚDO BRUTO DO BUFFER: [" << dados << "]" << std::endl;
    }
}

/**
 * @file Buffer.cpp
 * @brief Implementação da Gestão de RAM Bare-Metal.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include "Buffer.h"
#include <iostream>
#include <cstring> // Para memcpy e memset

namespace Logistica {

    BufferLog::BufferLog(int tam) 
        : tamanhoTotal(tam), posicaoAtual(0) {
        // ALOCAÇÃO DINÂMICA: Reservando array na HEAP
        dados = new char[tamanhoTotal];
        
        // Inicializa com zeros (Boa prática de segurança)
        std::memset(dados, 0, tamanhoTotal);
        
        std::cout << "\033[33m[KERNEL]: Alocação de " << tamanhoTotal 
                  << " bytes na HEAP concluída no endereço: " << (void*)dados << "\033[0m" << std::endl;
    }

    BufferLog::~BufferLog() {
        // LIBERAÇÃO MANUAL: Evitando Memory Leak
        delete[] dados; 
        dados = nullptr; // Neutraliza ponteiro fantasma
        
        std::cout << "\033[31m[KERNEL]: Memória na HEAP liberada (RAII Destructor).\033[0m" << std::endl;
    }

    void BufferLog::escrever(const std::string& msg) {
        int tamMsg = msg.length();
        
        // Bound Checking: Proteção contra Buffer Overflow
        if (posicaoAtual + tamMsg + 1 < tamanhoTotal) {
            std::memcpy(dados + posicaoAtual, msg.c_str(), tamMsg);
            posicaoAtual += tamMsg;
            dados[posicaoAtual++] = '|'; // Separador de log
        } else {
            std::cout << "\033[31m[ERRO]: Buffer cheio! Falha ao gravar: " << msg << "\033[0m" << std::endl;
        }
    }

    void BufferLog::despejar() {
        std::cout << "\033[32m[TELEMETRIA]:\033[0m " << dados << std::endl;
        // Reseta o cursor sem deletar a memória (Reuso do buffer)
        posicaoAtual = 0;
        std::memset(dados, 0, tamanhoTotal);
    }

} // namespace Logistica
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

/**
 * @file atividade-extra57-memoria.cpp
 * @brief Auditoria de RAM: Gerenciamento Manual e RAII de Elite.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a anatomia do uso da Heap e a prevenção de Memory Leaks.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <string>
#include "Buffer.h" 

using namespace std;
using namespace Logistica;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string VERMELHO = "\033[31m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

/**
 * @brief Simula o ciclo de vida de um buffer na STACK que gerencia a HEAP.
 */
void cicloTelemetria(int idCiclo) {
    cout << "\n" << UI::BRANCO << "[CICLO #" << idCiclo << "]: " << UI::RESET 
         << "Iniciando captura de dados do sensor..." << endl;
    
    // OBJETO NA STACK: 'meuBuffer' tem vida limitada a esta função.
    // DADOS NA HEAP: O array interno de meuBuffer tem vida persistente até o delete.
    BufferLog meuBuffer(64); // Reserva 64 bytes 'Bare-Metal'

    meuBuffer.escrever("ID=" + to_string(idCiclo));
    meuBuffer.escrever("TEMP=85.2C");
    meuBuffer.escrever("STATUS=CRITICAL");
    
    meuBuffer.despejar();
    
    cout << UI::AMARELO << "Espaço livre residual: " << meuBuffer.getTamanhoDisponivel() << " bytes." << UI::RESET << endl;
    
    // O Destrutor ~BufferLog() será chamado AQUI ao sair do escopo.
    // Isso é o padrão RAII: O recurso morre quando o dono (Stack) morre.
}

int main() {
    UI::limparTela();
    
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-MEMORY: ANALISADOR DE HEAP v2.0        " << endl;
    cout << "       (Elite Memory Management & RAII)        " << endl;
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << UI::RESET << endl;

    // Executando múltiplos ciclos para provar que a memória não acumula (Vazamento Zero)
    for(int i = 1; i <= 3; i++) {
        cicloTelemetria(i);
    }

    cout << "\n" << UI::VERDE << UI::NEGRITO << "[DIAGNÓSTICO]: Auditoria de RAM finalizada." << UI::RESET << endl;
    cout << "Todos os blocos alocados foram devolvidos ao S.O. via Destrutores RAII." << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ANATOMIA DA RAM (STACK vs HEAP)
    ===============================================================

    1. STACK (PILHA):
       - Memória ultra-rápida e automática. Variáveis locais vivem 
         aqui. O tamanho deve ser conhecido no compile-time. Se 
         você cria uma função recursiva infinita, ocorre o 'Stack 
         Overflow'.

    2. HEAP (MONTE):
       - Memória global e enorme. Usada para dados cujo tamanho só 
         sabemos quando o programa roda (ex: strings longas, 
         vetores dinâmicos). No C++, quem usa o 'new' é o DONO do 
         espaço e deve limpá-lo.

    3. RAII (PADRÃO DE ELITE):
       - 'Resource Acquisition Is Initialization'. É a técnica de 
         amarrar a vida de um recurso complexo (Heap) a um objeto 
         simples (Stack). Se o objeto da Stack morre, ele leva o 
         lixo da Heap junto no seu destrutor.

    4. SEGURANÇA DE MEMÓRIA (ELITE RULE):
       - O uso de 'memset' para zerar a memória após a alocação e o 
         uso de 'nullptr' após a liberação são as marcas de um 
         Engenheiro de Elite, prevenindo vazamento de dados 
         sensíveis e bugs de ponteiros fantasmas.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Smart Pointers (std::unique_ptr): O RAII automatizado.
    - Fragmentação de Memória: Por que muitas alocações pequenas 
      são ruins.
    - Valgrind: O raio-X de vazamentos de memória.
    ===============================================================
*/

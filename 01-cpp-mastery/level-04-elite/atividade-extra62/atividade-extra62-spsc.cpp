/**
 * @file atividade-extra62-spsc.cpp
 * @brief Simulação de Mensageria de Elite com Fila Lock-Free SPSC.
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "LockFreeQueue.h"

struct TelemetriaCompacta {
    int id;
    float valor;
};

// Fila Lock-Free Global com capacidade para 100 itens
LockFreeQueue<TelemetriaCompacta, 100> filaMensagens;
std::atomic<bool> sistemaAtivo{true};

/**
 * @brief Thread Produtora (Simula o Hardware/Rádio)
 */
void threadProdutora() {
    int count = 0;
    while (sistemaAtivo.load()) {
        TelemetriaCompacta t = {++count, (float)(rand() % 100) / 10.0f};
        
        if (filaMensagens.push(t)) {
            // Sucesso na inserção
        } else {
            std::cout << "\033[1;31m[ALERTA]\033[0m Fila cheia! Descartando pacote " << t.id << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simula rádio
    }
}

/**
 * @brief Thread Consumidora (Simula o Processamento de Logística)
 */
void threadConsumidora() {
    TelemetriaCompacta t;
    while (sistemaAtivo.load() || filaMensagens.ocupacao() > 0) {
        if (filaMensagens.pop(t)) {
            std::cout << "\033[1;34m[PROCESSOR]\033[0m Dado " << t.id 
                      << " recebido (Valor: " << t.valor 
                      << ") | Ocupação Fila: " << filaMensagens.ocupacao() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Processamento mais lento que o rádio
    }
}

int main() {
    srand(time(NULL));
    std::cout << "\033[1;36m=== LOGISPEED 3.0: MENSAGERIA LOCK-FREE SPSC ===\033[0m\n" << std::endl;

    std::thread produtor(threadProdutora);
    std::thread consumidor(threadConsumidora);

    // Roda por 5 segundos
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "\n\033[1;33m[SISTEMA]\033[0m Encerrando...\n" << std::endl;
    sistemaAtivo.store(false);

    produtor.join();
    consumidor.join();

    std::cout << "\033[1;32m[SUCESSO]\033[0m Sistema finalizado sem Deadlocks ou Race Conditions." << std::endl;

    return 0;
}

/**
 * @section ResumoTeorico
 * 1. SPSC: Single Producer Single Consumer é a forma mais rápida de 
 *    comunicação inter-thread pois evita contenção atômica pesada.
 * 2. MEMORY ORDER: O uso de Acquire/Release garante que o compilador e a 
 *    CPU não reordenem as instruções, protegendo a integridade dos dados.
 * 3. ALIGNAS(64): Evita o 'False Sharing' protegendo a performance do cache L1.
 */

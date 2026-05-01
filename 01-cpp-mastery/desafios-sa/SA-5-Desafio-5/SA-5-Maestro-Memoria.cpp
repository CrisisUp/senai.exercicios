/**
 * @file SA-5-Maestro-Memoria.cpp
 * @brief Orquestrador de Telemetria Multi-departamental (SA-05).
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <chrono>
#include "Telemetria.h"
#include "SmartBuffer.h"

// Mutex global para sincronizar a saída no console (UX Profissional)
std::mutex consoleMutex;

/**
 * @class ThreadJoiner
 * @brief RAII para garantir que threads sejam finalizadas corretamente.
 */
class ThreadJoiner {
    std::vector<std::thread>& threads;
public:
    explicit ThreadJoiner(std::vector<std::thread>& t) : threads(t) {}
    ~ThreadJoiner() {
        for (auto& t : threads) {
            if (t.joinable()) t.join();
        }
    }
};

/**
 * @brief Simula um departamento processando dados compartilhados.
 */
void processarDepartamento(std::string nome, std::shared_ptr<Telemetria> dados) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100 + rand() % 400));
    
    std::lock_guard<std::mutex> lock(consoleMutex);
    std::cout << "\033[1;34m[" << nome << "]\033[0m Processando Caminhão " << dados->idCaminhao 
              << " | Refs Ativas: " << dados.use_count() << std::endl;
}

int main() {
    srand(time(NULL));
    std::cout << "\033[1;36m=== LOGISPEED 2.0: SISTEMA DE DESPACHO ELITE ===\033[0m\n" << std::endl;

    try {
        // 1. Refatoração Ativ 57: Buffer de Elite para Histórico
        SmartBuffer<Telemetria> historico(10);

        std::vector<std::thread> workers;
        ThreadJoiner joiner(workers);

        // 2. Simulação de Despacho
        for (int i = 1; i <= 3; ++i) {
            // Criamos o dado na Heap via shared_ptr
            auto novaLeitura = std::make_shared<Telemetria>();
            novaLeitura->idCaminhao = 100 + i;
            novaLeitura->velocidade = 80.0 + i;
            novaLeitura->combustivel = 500.0 - (i * 10);

            {
                std::lock_guard<std::mutex> lock(consoleMutex);
                std::cout << "\033[1;32m[DESPACHANTE]\033[0m Gerando dados para Caminhão " << novaLeitura->idCaminhao << std::endl;
            }

            // Enviamos o MESMO ponteiro para diferentes "departamentos" (threads)
            workers.emplace_back(processarDepartamento, "LOGÍSTICA", novaLeitura);
            workers.emplace_back(processarDepartamento, "FATURAMENTO", novaLeitura);
            workers.emplace_back(processarDepartamento, "MANUTENÇÃO", novaLeitura);

            // Guardamos no buffer de histórico (cópia do shared_ptr aumenta contagem)
            historico.adicionar(*novaLeitura);
        }

        std::cout << "\n\033[1;33m[SISTEMA]\033[0m Aguardando finalização dos departamentos...\n" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31m[ERRO CRÍTICO]:\033[0m " << e.what() << std::endl;
    }

    return 0;
}

/**
 * @section TeoriaElite
 * 1. SHARED_PTR: Resolve o problema de 'quem deleta o quê'. O objeto Telemetria
 *    só morre quando Logística, Faturamento, Manutenção E o Histórico terminarem.
 * 2. LOCK_GUARD: Implementa RAII para o Mutex. Se uma thread sofrer exceção, 
 *    o mutex é liberado automaticamente, evitando Deadlock.
 * 3. TEMPLATES: O SmartBuffer agora pode armazenar Telemetria, Logs crus ou
 *    qualquer outro tipo, aumentando a reusabilidade do código.
 */

/* @section MemoryMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */

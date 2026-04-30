/**
 * @file atividade-extra61-lockfree.cpp
 * @brief Benchmark de Mutex vs Atômicos (Sistemas Lock-Free).
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>
#include <iomanip>

using namespace std::chrono;

const int NUM_THREADS = 4;
const int OPERACOES_POR_THREAD = 1000000; // 1 milhão

// Cenário 1: Sincronização via Mutex (Lenta)
long long contadorMutex = 0;
std::mutex mtx;

// Cenário 2: Sincronização via Atômicos (Lock-Free - Rápida)
// alignas(64) evita o "False Sharing" (cada atômico em sua própria linha de cache)
alignas(64) std::atomic<long long> contadorAtomico{0};

/**
 * @brief Função que incrementa usando Mutex.
 */
void incrementarComMutex() {
    for (int i = 0; i < OPERACOES_POR_THREAD; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        contadorMutex++;
    }
}

/**
 * @brief Função que incrementa usando Atômicos.
 */
void incrementarComAtomico() {
    for (int i = 0; i < OPERACOES_POR_THREAD; ++i) {
        contadorAtomico++; // Implementação atômica nativa da CPU
    }
}

int main() {
    std::cout << "\033[1;36m=== BENCHMARK DE PERFORMANCE: MUTEX VS LOCK-FREE ===\033[0m\n" << std::endl;
    std::cout << "Threads: " << NUM_THREADS << " | Operações Totais: " << (NUM_THREADS * OPERACOES_POR_THREAD) << "\n" << std::endl;

    // --- TESTE COM MUTEX ---
    auto start = high_resolution_clock::now();
    std::vector<std::thread> threadsMutex;
    for (int i = 0; i < NUM_THREADS; ++i) threadsMutex.emplace_back(incrementarComMutex);
    for (auto& t : threadsMutex) t.join();
    auto end = high_resolution_clock::now();
    auto durationMutex = duration_cast<milliseconds>(end - start).count();

    std::cout << "\033[1;31m[MUTEX]\033[0m Tempo: " << durationMutex << "ms | Resultado: " << contadorMutex << std::endl;

    // --- TESTE COM ATÔMICOS ---
    start = high_resolution_clock::now();
    std::vector<std::thread> threadsAtomicas;
    for (int i = 0; i < NUM_THREADS; ++i) threadsAtomicas.emplace_back(incrementarComAtomico);
    for (auto& t : threadsAtomicas) t.join();
    end = high_resolution_clock::now();
    auto durationAtomico = duration_cast<milliseconds>(end - start).count();

    std::cout << "\033[1;32m[LOCK-FREE]\033[0m Tempo: " << durationAtomico << "ms | Resultado: " << contadorAtomico.load() << std::endl;

    // --- ANÁLISE ---
    double ganho = (double)durationMutex / durationAtomico;
    std::cout << "\n\033[1;33m[ANÁLISE DE ELITE]\033[0m\n";
    std::cout << "O sistema Lock-Free foi " << std::fixed << std::setprecision(2) << ganho << "x mais rápido." << std::endl;

    return 0;
}

/**
 * @section MemoryMap
 * - STACK: Objetos duration, handles de threads, ponteiro para threadsMutex/Atomicas.
 * - HEAP: Memória alocada internamente pelo std::vector para armazenar os objetos std::thread.
 * - GLOBAL (Static): contadorMutex, mtx, contadorAtomico.
 * 
 * @section ResumoTeorico
 * O Mutex causa um "Sleep" na thread se o recurso estiver ocupado, o que envolve o SO.
 * O Atômico usa a instrução CPU 'LOCK INC' (ou similar), que resolve o conflito 
 * no nível do barramento de memória, sem suspender a execução.
 */

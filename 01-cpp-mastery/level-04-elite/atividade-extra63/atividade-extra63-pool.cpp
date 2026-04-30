/**
 * @file atividade-extra63-pool.cpp
 * @brief Benchmark de Performance: New/Delete vs Object Pool.
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

#include <iostream>
#include <chrono>
#include <vector>
#include "ObjectPool.h"

struct PacoteTelemetria {
    int id;
    double lat, lon, vel;
    char buffer[1024]; // Simula um pacote pesado para enfatizar o custo de alocação
};

const int CICLOS = 100000; // 100 mil alocações/desalocações

int main() {
    std::cout << "\033[1;36m=== BENCHMARK DE MEMÓRIA: NEW/DELETE VS OBJECT POOL ===\033[0m\n" << std::endl;

    // --- TESTE 1: NEW/DELETE TRADICIONAL ---
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < CICLOS; ++i) {
            PacoteTelemetria* p = new PacoteTelemetria();
            p->id = i;
            delete p; // Aloca e desaloca imediatamente (pior cenário de fragmentação)
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "\033[1;31m[TRADICIONAL]\033[0m Tempo com new/delete: " << dur << "ms" << std::endl;
    }

    // --- TESTE 2: OBJECT POOL ---
    {
        ObjectPool<PacoteTelemetria> pool(100); // Pool pequeno para forçar reuso constante
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < CICLOS; ++i) {
            {
                auto p = pool.acquire(); // Pega do pool
                p->id = i;
            } // Ao sair deste escopo, o Deleter Customizado devolve ao pool automaticamente!
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "\033[1;32m[OBJECT POOL]\033[0m Tempo com Pool: " << dur << "ms" << std::endl;
    }

    std::cout << "\n\033[1;33m[ANÁLISE DE ELITE]\033[0m\n";
    std::cout << "O Object Pool elimina as chamadas ao System Call do SO para alocação de memória,\n";
    std::cout << "mantendo a latência baixa e determinística para sistemas de tempo real." << std::endl;

    return 0;
}

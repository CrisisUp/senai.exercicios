/**
 * @file atividade-extra65-coroutines.cpp
 * @brief Implementação de Gerador de Telemetria via Coroutines (C++20).
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

#include <iostream>
#include <coroutine>
#include <string>
#include <optional>

/**
 * @struct Generator
 * @brief Tipo de retorno customizado para coroutines que usam co_yield.
 * Gerencia o ciclo de vida da coroutine (Promise, Handle).
 */
template <typename T>
struct Generator {
    struct promise_type {
        T current_value;
        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        void unhandled_exception() { std::terminate(); }
        void return_void() {}
    };

    std::coroutine_handle<promise_type> handle;

    explicit Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }

    // Impede cópia para evitar destruição dupla do handle
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;

    /**
     * @brief Retoma a execução da coroutine e retorna o próximo valor.
     */
    bool next() {
        if (!handle || handle.done()) return false;
        handle.resume();
        return !handle.done();
    }

    T value() const { return handle.promise().current_value; }
};

/**
 * @brief Coroutine que simula um sensor gerando dados assíncronos.
 */
Generator<std::string> monitorarDrone(int id) {
    std::cout << "\033[1;32m[SENSOR]\033[0m Iniciando monitoramento do Drone " << id << "...\n";
    
    // Simula a geração de 3 pacotes de dados
    co_yield "Drone " + std::to_string(id) + ": Altitude 100m - OK";
    co_yield "Drone " + std::to_string(id) + ": Altitude 150m - OK";
    co_yield "Drone " + std::to_string(id) + ": BATERIA BAIXA - RETORNANDO";
}

int main() {
    std::cout << "\033[1;36m=== LOGISPEED 5.0: ESCALABILIDADE VIA COROUTINES ===\033[0m\n" << std::endl;

    // Criamos a coroutine (ela já inicia suspensa)
    auto sensor1 = monitorarDrone(707);

    std::cout << "[MAIN] Fazendo outras tarefas...\n";

    // Retomamos a coroutine sob demanda
    while (sensor1.next()) {
        std::cout << "\033[1;34m[SISTEMA CENTRAL]\033[0m Recebido: " << sensor1.value() << std::endl;
        std::cout << "[MAIN] Thread liberada para processar outros drones...\n";
    }

    std::cout << "\n\033[1;33m[ANÁLISE DE ELITE]\033[0m\n";
    std::cout << "A coroutine foi suspensa 3 vezes. Em cada suspensão, a thread principal\n";
    std::cout << "pode fazer qualquer outra coisa, economizando recursos massivamente." << std::endl;

    return 0;
}

/**
 * @section ResumoTeorico
 * 1. PROMISE TYPE: Define como a coroutine se comporta (onde salva valores, quando pausa).
 * 2. CO_YIELD: Suspende a função e 'entrega' um valor para quem chamou.
 * 3. STACKLESS: Coroutines C++20 não salvam toda a pilha (stack), apenas o estado 
 *    mínimo necessário na Heap, o que as torna extremamente leves.
 */

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

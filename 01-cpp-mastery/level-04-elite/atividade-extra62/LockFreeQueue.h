#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file LockFreeQueue.h
 * @brief Implementação de Fila Circular SPSC (Single Producer Single Consumer).
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H

#include <atomic>
#include <vector>
#include <memory>

template <typename T, size_t Size>
class LockFreeQueue {
private:
    std::vector<T> buffer;
    alignas(64) std::atomic<size_t> head{0}; // Lido pelo Consumidor, Escrito pelo Produtor
    alignas(64) std::atomic<size_t> tail{0}; // Escrito pelo Produtor, Lido pelo Consumidor

public:
    LockFreeQueue() : buffer(Size) {}

    /**
     * @brief Insere um item na fila (Lock-Free).
     * @return true se inserido, false se a fila estiver cheia.
     */
    bool push(const T& item) {
        size_t current_tail = tail.load(std::memory_order_relaxed);
        size_t next_tail = (current_tail + 1) % Size;

        if (next_tail == head.load(std::memory_order_acquire)) {
            return false; // Fila cheia
        }

        buffer[current_tail] = item;
        // memory_order_release garante que o dado acima foi escrito ANTES da atualização do tail
        tail.store(next_tail, std::memory_order_release);
        return true;
    }

    /**
     * @brief Retira um item da fila (Lock-Free).
     * @return true se retirado, false se a fila estiver vazia.
     */
    bool pop(T& item) {
        size_t current_head = head.load(std::memory_order_relaxed);

        if (current_head == tail.load(std::memory_order_acquire)) {
            return false; // Fila vazia
        }

        item = buffer[current_head];
        // memory_order_release garante que a leitura acima ocorreu ANTES da atualização do head
        head.store((current_head + 1) % Size, std::memory_order_release);
        return true;
    }

    size_t ocupacao() const {
        size_t h = head.load();
        size_t t = tail.load();
        if (t >= h) return t - h;
        return Size - (h - t);
    }
};

#endif // LOCK_FREE_QUEUE_H

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

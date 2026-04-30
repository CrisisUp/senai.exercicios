/**
 * @file SmartBuffer.h
 * @brief Gerenciador de Buffer Genérico com Smart Pointers (Refatoração Ativ 57).
 * @author Engenheiro de Elite
 * @date 2026-04-27
 * 
 * @section MemoryMap
 * - Stack: Objeto SmartBuffer e metadados (tamanho, capacidade).
 * - Heap: Array dinâmico gerenciado por std::unique_ptr<T[]>.
 */

#ifndef SMART_BUFFER_H
#define SMART_BUFFER_H

#include <memory>
#include <stdexcept>
#include <iostream>

template <typename T>
class SmartBuffer {
private:
    std::unique_ptr<T[]> dados;
    size_t capacidade;
    size_t tamanho;

public:
    explicit SmartBuffer(size_t cap) 
        : dados(std::make_unique<T[]>(cap)), capacidade(cap), tamanho(0) {
        std::cout << "\033[1;32m[RAII]\033[0m SmartBuffer alocado para " << cap << " elementos.\n";
    }

    ~SmartBuffer() {
        std::cout << "\033[1;31m[RAII]\033[0m SmartBuffer liberado automaticamente.\n";
    }

    // Impede cópia para evitar double-free (Semântica de Movimento apenas)
    SmartBuffer(const SmartBuffer&) = delete;
    SmartBuffer& operator=(const SmartBuffer&) = delete;

    void adicionar(const T& item) {
        if (tamanho >= capacidade) {
            throw std::overflow_error("Buffer cheio: Risco de corrompimento evitado.");
        }
        dados[tamanho++] = item;
    }

    T& operator[](size_t index) {
        if (index >= tamanho) throw std::out_of_range("Acesso inválido ao buffer.");
        return dados[index];
    }

    size_t getTamanho() const { return tamanho; }
    size_t getCapacidade() const { return capacidade; }
};

#endif // SMART_BUFFER_H

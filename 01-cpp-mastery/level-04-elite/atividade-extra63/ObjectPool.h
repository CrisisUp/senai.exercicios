/**
 * @file ObjectPool.h
 * @brief Implementação de Pool de Objetos com RAII e Custom Deleter.
 * @author Engenheiro de Elite
 * @date 2026-04-27
 */

#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <vector>
#include <memory>
#include <stack>
#include <iostream>
#include <mutex>

template <typename T>
class ObjectPool {
public:
    // Define o tipo de ponteiro que o Pool entrega: um unique_ptr com deleter customizado
    using PoolPtr = std::unique_ptr<T, std::function<void(T*)>>;

private:
    std::stack<T*> objetosLivres;
    std::vector<std::unique_ptr<T>> storage; // Mantém a posse real da memória na Heap
    std::mutex mtx;
    size_t capacidade;

public:
    explicit ObjectPool(size_t tamanho) : capacidade(tamanho) {
        for (size_t i = 0; i < tamanho; ++i) {
            auto obj = std::make_unique<T>();
            objetosLivres.push(obj.get());
            storage.push_back(std::move(obj));
        }
        std::cout << "\033[1;32m[POOL]\033[0m Pré-alocados " << tamanho << " objetos.\n";
    }

    /**
     * @brief Adquire um objeto do pool.
     * @return PoolPtr (unique_ptr que devolve o objeto ao pool ao ser destruído)
     */
    PoolPtr acquire() {
        std::lock_guard<std::mutex> lock(mtx);
        
        if (objetosLivres.empty()) {
            throw std::runtime_error("Pool exaurido! Falha determinística de memória.");
        }

        T* obj = objetosLivres.top();
        objetosLivres.pop();

        // Criamos um unique_ptr com um DELETER CUSTOMIZADO (Lambda)
        // Em vez de 'delete', ele chama 'release' para devolver ao pool
        return PoolPtr(obj, [this](T* t) {
            this->release(t);
        });
    }

    size_t disponiveis() {
        std::lock_guard<std::mutex> lock(mtx);
        return objetosLivres.size();
    }

private:
    /**
     * @brief Devolve o objeto para a pilha de livres.
     */
    void release(T* obj) {
        std::lock_guard<std::mutex> lock(mtx);
        objetosLivres.push(obj);
    }
};

#endif // OBJECT_POOL_H

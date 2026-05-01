/**
 * @file Armazem.h
 * @brief Interface Genérica para Gestão de Estoque Multinível.
 * 
 * Atividade Extra 56 - Programação Genérica (Nível 31+).
 * Implementa o molde para containers de qualquer tipo de dado.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Generic Container Layout)
 * - Objeto Armazem<T>: Alocado na STACK ou HEAP.
 * - std::vector<T> itens: O descritor está no corpo do Armazem.
 * - Elementos T: Alocados em um bloco contíguo na HEAP.
 * - Especialização: O espaço de cada item (sizeof(T)) é decidido pelo compilador.
 */

#ifndef ARMAZEM_H
#define ARMAZEM_H

#include <iostream>
#include <vector>
#include <string>

namespace Logistica {

    /**
     * @class Armazem
     * @brief Container universal para estocagem técnica.
     * @tparam T Tipo da carga (Deve suportar o operador <<).
     */
    template <typename T>
    class Armazem {
    private:
        std::string setor;
        std::vector<T> itens;

    public:
        /** @brief Construtor: Nomeia o setor físico de armazenamento. */
        Armazem(const std::string& _setor) : setor(_setor) {}

        /**
         * @brief Adiciona item ao estoque via Referência Constante (FANTASMA DO CPU).
         */
        void adicionar(const T& item) {
            itens.push_back(item);
        }

        /** @brief Remove a última unidade entrada (LIFO behavior). */
        void removerUltimo() {
            if (!itens.empty()) itens.pop_back();
        }

        /**
         * @brief Itera e exibe a carga usando o polimorfismo de template.
         */
        void exibir() const {
            std::cout << "\n\033[36m--- MANIFESTO DE SETOR: " << setor << " ---\033[0m" << std::endl;
            if (itens.empty()) {
                std::cout << " [VAZIO]" << std::endl;
                return;
            }

            int count = 1;
            for (const auto& item : itens) {
                std::cout << "  " << count++ << ". " << item << std::endl;
            }
            std::cout << "\033[36m" << std::string(35, '-') << "\033[0m" << std::endl;
        }

        // Getters
        size_t getQuantidade() const { return itens.size(); }
    };

} // namespace Logistica

#endif // ARMAZEM_H

/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

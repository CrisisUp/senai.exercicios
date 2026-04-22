/**
 * @file Armazem.h
 * @brief Implementação modular de um Armazém Genérico usando Templates.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#ifndef ARMAZEM_H
#define ARMAZEM_H

#include <iostream>
#include <vector>
#include <string>

namespace Logistica {

    /**
     * @brief Classe Template Armazem (Nível 31 - Engenheiro de Elite).
     * O tipo 'T' será definido no momento da criação do objeto.
     */
    template <typename T>
    class Armazem {
    private:
        std::vector<T> itens;
        std::string nomeSetor;

    public:
        Armazem(std::string nome) : nomeSetor(nome) {}

        /**
         * @brief Adiciona um item genérico ao estoque.
         */
        void adicionar(T item) {
            itens.push_back(item);
        }

        /**
         * @brief Remove o último item (Pilha LIFO).
         */
        void removerUltimo() {
            if (!itens.empty()) itens.pop_back();
        }

        /**
         * @brief Exibe o estoque completo. 
         * Requer que o tipo 'T' suporte o operador '<<'.
         */
        void exibir() const {
            std::cout << "\n\033[34m[SETOR: " << nomeSetor << "]\033[0m" << std::endl;
            if (itens.empty()) {
                std::cout << "  (Vazio)" << std::endl;
                return;
            }
            for (const auto& item : itens) {
                std::cout << "  - " << item << std::endl;
            }
        }

        size_t totalItens() const { return itens.size(); }
    };
}

#endif // ARMAZEM_H

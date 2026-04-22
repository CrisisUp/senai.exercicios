/**
 * @file GestorEstoque.h
 * @brief Serviço de orquestração de estoque e persistência.
 */
#ifndef GESTOR_ESTOQUE_H
#define GESTOR_ESTOQUE_H

#include "Produto.h"
#include <string>

namespace Industrial {
    /**
     * @brief Classe responsável pela lógica de alto nível e integração.
     */
    class GestorEstoque {
    public:
        // Orquestração
        void analisarProduto(const Produto& p);
        
        // Persistência (Simulação para desafio SQL)
        void salvarNoBanco(const Produto& p);
        
        // Integração Industrial (Log)
        void gerarLogJSON(const Produto& p);
    };
}

#endif // GESTOR_ESTOQUE_H

/**
 * @file GestorEstoque.cpp
 * @brief Implementação dos serviços de gestão de estoque.
 */

#include "GestorEstoque.h"
#include <iostream>
#include <iomanip>

namespace Industrial {

    void GestorEstoque::analisarProduto(const Produto& p) {
        std::cout << "\n\033[36m--- ANÁLISE INDUSTRIAL: " << p.getNome() << " ---\033[0m" << std::endl;
        
        if (p.precisaRepor()) {
            std::cout << "\033[31m[STATUS]: CRÍTICO\033[0m" << std::endl;
            std::cout << "Faltam: " << p.calcularQuantidadeFaltante() << " unidades." << std::endl;
            std::cout << "Custo Estimado: R$ " << std::fixed << std::setprecision(2) 
                      << (p.calcularQuantidadeFaltante() * p.getPrecoUnitario()) << std::endl;
        } else {
            std::cout << "\033[32m[STATUS]: OK\033[0m" << std::endl;
            std::cout << "Nível de estoque suficiente para a operação." << std::endl;
        }
    }

    void GestorEstoque::salvarNoBanco(const Produto& p) {
        // ESPAÇO PARA O ALUNO: Implementar conexão SQLite
        std::cout << "\033[34m[DB]:\033[0m Sincronizando '" << p.getNome() << "' com SQL..." << std::endl;
    }

    void GestorEstoque::gerarLogJSON(const Produto& p) {
        // Simulação de saída JSON para integração com outros sistemas
        std::cout << "\033[90m[JSON]: {\"item\": \"" << p.getNome() 
                  << "\", \"stock\": " << p.getEstoqueAtual() 
                  << ", \"reorder\": " << (p.precisaRepor() ? "true" : "false") << "}\033[0m" << std::endl;
    }
}

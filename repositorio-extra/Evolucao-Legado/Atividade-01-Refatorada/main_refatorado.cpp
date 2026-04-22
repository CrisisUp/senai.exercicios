/**
 * @file main_refatorado.cpp
 * @brief Ponto de entrada para o sistema de estoque modernizado.
 * 
 * Este programa demonstra a refatoração da Atividade 01 (Legado)
 * para um padrão de Engenharia de Sistemas (Nível 31+).
 */

#include <iostream>
#include <memory>
#include <vector>
#include "Produto.h"
#include "GestorEstoque.h"

using namespace std;
using namespace Industrial;

int main() {
    try {
        cout << "\033[35m===============================================\033[0m" << endl;
        cout << "       SKYCARGO OS: GESTÃO DE ESTOQUE V3       " << endl;
        cout << "\033[35m===============================================\033[0m" << endl;

        // 1. Instanciação via Smart Pointers (Gestão Segura de Memória)
        auto gestor = make_unique<GestorEstoque>();

        // 2. Criação de Dados de Teste
        // Simulando dados que viriam de um formulário ou sensor
        vector<unique_ptr<Produto>> listaProdutos;
        
        listaProdutos.push_back(make_unique<Produto>("Motor Brushless X1", 2, 5, 450.00));
        listaProdutos.push_back(make_unique<Produto>("Bateria LiPo 4S", 12, 10, 280.00));

        // 3. Processamento em Lote
        for (const auto& p : listaProdutos) {
            gestor->analisarProduto(*p);
            gestor->salvarNoBanco(*p);
            gestor->gerarLogJSON(*p);
        }

        // 4. Teste de Blindagem (Descomente para testar a captura de exceção)
        // cout << "\n[TESTE]: Tentando criar produto com preço negativo..." << endl;
        // auto erro = make_unique<Produto>("Item Inválido", 10, 5, -10.0);

        cout << "\n\033[32m[SISTEMA]: Operação finalizada com sucesso.\033[0m" << endl;

    } catch (const invalid_argument& e) {
        cerr << "\n\033[41m[ERRO DE VALIDAÇÃO]:\033[0m " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cerr << "\n\033[41m[ERRO INESPERADO]:\033[0m " << e.what() << endl;
        return 1;
    }

    return 0;
}

/* 
    ===============================================================
    RESUMO DA REFATORAÇÃO (DO LEGADO AO INDUSTRIAL)
    ===============================================================

    1. MODULARIDADE (SOLID):
       - O código deixou de ser um "blocão" (main) e foi dividido em 
         responsabilidades: Entidade (Produto) e Serviço (Gestor).

    2. ENCAPSULAMENTO:
       - O estado do produto agora é privado. Ninguém pode alterar o 
         preço ou estoque sem passar pelas regras de validação.

    3. FAIL-FAST (EXCEÇÕES):
       - Em vez de aceitar dados errados e falhar depois, o sistema 
         lança uma exceção no exato momento em que detecta o erro.

    4. GERENCIAMENTO DE MEMÓRIA (RAII):
       - O uso de std::unique_ptr garante que não haverá vazamento de 
         memória (Memory Leaks), mesmo que uma exceção ocorra.

    5. PRONTIDÃO PARA ESCALA:
       - O sistema agora gera logs JSON e está preparado para salvar 
         em SQL, permitindo integração com dashboards e nuvem.
    ===============================================================
*/

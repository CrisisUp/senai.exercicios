#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file atividade-extra16-erp.cpp
 * @brief PROJETO FINAL: Sistema de Gestão Comercial (ERP) v4.0.
 * 
 * Versão Refatorada: Arquitetura Modular (Nível 11+).
 * Integra todos os conceitos aprendidos no Nível Arquiteto.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include "MotorERP.h"

using namespace std;

int main() {
    SistemaERP erp;
    
    try {
        erp.carregarDados();
        erp.menuPrincipal();
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    
    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: INTEGRAÇÃO E LÓGICA DE ERP (v4.0)
    ===============================================================

    1. ARQUITETURA MODULAR (PROJETO FINAL):
       - Este projeto demonstra a separação completa entre Interface 
         (UI), Lógica de Negócio (SistemaERP) e Modelagem de Dados 
         (Produto/Log). É a base para sistemas industriais reais.

    2. INTEGRAÇÃO DE ESTRUTURAS STL:
       - vector: Estoque persistente e dinâmico.
       - queue: Fila de atendimento por ordem de chegada (FIFO).
       - stack: Auditoria reversa (LIFO), onde o último evento é o 
         primeiro a ser auditado.

    3. SEGURANÇA FINANCEIRA (Centavos Inteiros):
       - O uso de centavos em long long garante precisão bancária 
         e evita erros de ponto flutuante que quebrariam o fluxo 
         de caixa em grandes volumes.

    4. RESILIÊNCIA COM EXCEÇÕES:
       - O sistema utiliza uma hierarquia de ErroERP para capturar 
         desde falhas de arquivo até inadimplência de caixa, 
         mantendo a aplicação estável.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Bancos de Dados Relacionais: Integrando o ERP com SQL.
    - Padrões de Projeto (Design Patterns): Singleton e Factory.
    - Testes Unitários: Como garantir que o cálculo de lucro está correto.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */


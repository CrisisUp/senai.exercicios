/**
 * @file SA-3-Refinaria.cpp
 * @brief Simulação do Desafio Integrador SA-3: Controle de Refinaria.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <vector>
#include "Tanque.h" // Nossa interface da refinaria

using namespace std;
using namespace Refinaria;

int main() {
    // 1. Instanciação de Tanques (Nível 11: Modular)
    Tanque t1("T-101", "Diesel-S10", 50000.0);
    Tanque t2("T-102", "Diesel-S10", 30000.0);
    Tanque t3("T-201", "Gasolina-Comum", 40000.0);

    cout << "\033[36m===============================================\033[0m" << endl;
    cout << "     SISTEMA DE CONTROLE DE REFINARIA (SA-3)   " << endl;
    cout << "\033[36m===============================================\033[0m" << endl;

    // 2. Simulação de Carga (Encapsulamento)
    cout << "Abastecendo tanques..." << endl;
    t1.carregar(48000.0); // Próximo ao limite
    t2.carregar(15000.0);
    t3.carregar(38000.0); // Quase cheio

    // 3. Relatórios (Sobrecarga <<)
    cout << "\nRELATÓRIO DE ESTOQUE ATUAL:" << endl;
    cout << t1 << endl;
    cout << t2 << endl;
    cout << t3 << endl;

    // 4. Comparação de Níveis (Sobrecarga >)
    if (t1 > t3) {
        cout << "\n\033[33m[ANÁLISE]:\033[0m O tanque t1 possui maior volume estocado." << endl;
    }

    // 5. Transferência de Conteúdo (Sobrecarga + e Tratamento de Exceções)
    cout << "\nIniciando consolidação de estoque Diesel (T1 + T2)..." << endl;
    try {
        Tanque t_consolidado = t1 + t2;
        cout << "\033[32m[SUCESSO]:\033[0m Tanques Diesel consolidados!" << endl;
        cout << t_consolidado << endl;
    } catch (const exception& e) {
        cout << "\033[31m[ERRO CRÍTICO]:\033[0m " << e.what() << endl;
    }

    // 6. Teste de Segurança (Tentar somar Diesel com Gasolina)
    cout << "\nIniciando consolidação perigosa (T1 Diesel + T3 Gasolina)..." << endl;
    try {
        Tanque t_erro = t1 + t3;
        cout << t_erro << endl;
    } catch (const exception& e) {
        cout << "\033[31m[BLOQUEIO DE SEGURANÇA]:\033[0m " << e.what() << endl;
    }

    cout << "\033[36m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO INTEGRADOR SA-3
    ===============================================================

    1. ARQUITETURA MODULAR (PROJETO COMPLETO):
       - Dividimos o sistema em Tanque.h, Tanque.cpp e SA-3-Refinaria.cpp.
       - Isso garante que a lógica de negócio esteja separada da 
         interface com o usuário.

    2. NAMESPACES E ISOLAMENTO:
       - O namespace 'Refinaria' protege nossas classes contra colisões.

    3. SOBRECARGA DE OPERADORES EM NEGÓCIOS:
       - O operador '+' não é apenas uma soma matemática, é uma 
         lógica de FUSÃO DE TANQUES com regras de segurança química.

    4. REUTILIZAÇÃO MODULAR:
       - Notem como usamos includes para referenciar a Atividade 52,
         demonstrando que o conhecimento é cumulativo.
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Gerenciamento de Memória em Classes.
    - Padrão Singleton para Gestores de Refinaria.
    - Persistência de Dados em Arquivos de Log.
    ===============================================================
*/

/**
 * @file atividade-extra58-templates.cpp
 * @brief Interface do Analisador de Precisão (Especialização de Elite).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a resolução estática de lógica customizada vs genérica.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include "Comparador.h" 

using namespace std;
using namespace IoT;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

#include <string>

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. EXECUÇÃO DO MOTOR COMPARADOR ---

int main() {
    UI::limparTela();
    
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-SYSTEM: ANALISADOR DE PRECISÃO v2.0    " << endl;
    cout << "       (Elite Specialization Architecture)     " << endl;
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << UI::RESET << endl;

    // --- TESTE 1: LÓGICA GENÉRICA (int) ---
    int t1 = 45, t2 = 62;
    cout << UI::RESET << "[INT]: " << UI::RESET << "Comparando " << t1 << " e " << t2 << " -> ";
    cout << UI::VERDE << UI::NEGRITO << obterMaior(t1, t2) << UI::RESET << endl;

    // --- TESTE 2: LÓGICA ESPECIALIZADA (string) ---
    // A especialização em Comparador.h escolhe por LENGTH, não por ALFABETO.
    string idA = "S-01";
    string idB = "SNR-PRECISION-998";
    
    cout << UI::RESET << "\n[STRING (Spec)]: " << UI::RESET << "Análise de densidade de ID..." << endl;
    cout << " >> Maior Identificador: " << UI::CIANO << UI::NEGRITO 
         << obterMaior(idA, idB) << UI::RESET << endl;

    // --- TESTE 3: LÓGICA HÍBRIDA (struct + operator< + template) ---
    LeituraSensor s1 = {1001, 85.50};
    LeituraSensor s2 = {2002, 112.45};
    
    cout << UI::RESET << "\n[STRUCT]: " << UI::RESET << "Invocando polimorfismo estático em leitura complexa..." << endl;
    LeituraSensor m = obterMaior(s1, s2);
    
    cout << UI::VERDE << " >> Sensor de Maior Carga: ID " << m.id << " (" << m.valor << " units)" << UI::RESET << endl;

    cout << UI::CIANO << UI::NEGRITO << "\n===============================================" << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: TEMPLATES E ESPECIALIZAÇÃO (ELITE)
    ===============================================================

    1. LÓGICA GENÉRICA VS ESPECIALIZADA:
       - O template genérico é o "Comportamento Padrão". A 
         especialização (`template <>`) é a "Exceção à Regra". O 
         C++ é a única linguagem que permite trocar a lógica de 
         um algoritmo baseada no tipo sem nenhum IF no runtime.

    2. FANTASMA DO CPU (ZERO OVERHEAD):
       - Diferente do polimorfismo dinâmico (virtual), a escolha do 
         template especializado ocorre no momento em que você dá 
         o 'g++'. No executável final, a chamada é direta e o 
         código é tão rápido quanto uma função normal.

    3. SEGURANÇA E SOBRECARGA:
       - Para que o template genérico aceite a struct 'LeituraSensor', 
         fomos obrigados a ensinar à struct como se comparar 
         (operator<). Isso garante que o motor genérico nunca 
         tente comparar "laranjas com bananas" sem saber como.

    4. PASS-BY-REFERENCE (PERFORMANCE):
       - Note o uso de 'const T&' e 'const string&'. Como o template 
         pode lidar com qualquer coisa, de um 'char' a uma 'Base de 
         Dados', a referência constante protege o sistema contra 
         o custo proibitivo de clonar dados pesados.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Partial Specialization: Especializar apenas um parâmetro.
    - Template Meta-Programming (TMP): Programas que rodam no compilador.
    - Concepts (C++20): Validar o tipo T de forma mais elegante.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

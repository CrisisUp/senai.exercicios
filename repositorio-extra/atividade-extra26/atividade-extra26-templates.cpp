/**
 * @file atividade-extra26-templates.cpp
 * @brief Finanças Internacionais: Introdução a Function Templates.
 * 
 * Este programa demonstra como criar funções genéricas que operam com
 * múltiplos tipos de dados (int, float, double) sem duplicação de código.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
}

// --- 2. DEFINIÇÃO DO TEMPLATE DE FUNÇÃO (O NOVO CONCEITO) ---

/**
 * @brief Template que aplica uma taxa multiplicativa a um valor de qualquer tipo numérico.
 * @tparam T Tipo do valor (ex: int, float, double).
 * @tparam U Tipo da taxa (geralmente double).
 */
template <typename T, typename U>
auto aplicarTaxa(T valor, U taxa) -> decltype(valor * taxa) {
    return valor * taxa;
}

/**
 * @brief Template para somar dois valores de tipos potencialmente diferentes.
 */
template <typename T1, typename T2>
auto somarSaldos(T1 s1, T2 s2) -> decltype(s1 + s2) {
    return s1 + s2;
}

// --- 3. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << fixed << setprecision(4);

    cout << UI::CIANO << "===============================================" << endl;
    cout << "      FOREX TEMPLATE ENGINE v1.0 (GENÉRICO)    " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Cenário 1: Moeda inteira (Iene Japonês)
    int ienes = 15000;
    double taxaIeneReal = 0.034;
    auto ieneEmReal = aplicarTaxa(ienes, taxaIeneReal);

    cout << UI::AMARELO << "[INTEIRO]: " << UI::RESET << ienes << " Ienes -> " 
         << UI::VERDE << "R$ " << ieneEmReal << UI::RESET << endl;

    // Cenário 2: Moeda de alta precisão (Dólar)
    double dolares = 1250.75;
    double taxaDolarReal = 5.12;
    auto dolarEmReal = aplicarTaxa(dolares, taxaDolarReal);

    cout << UI::AZUL << "[DOUBLE] : " << UI::RESET << dolares << " Dólares -> " 
         << UI::VERDE << "R$ " << dolarEmReal << UI::RESET << endl;

    // Cenário 3: Somando saldos de tipos diferentes
    auto saldoTotal = somarSaldos(ienes, dolares); // Soma int + double
    cout << "\n[SOMA GENÉRICA]: " << saldoTotal << " unidades monetárias mistas." << endl;

    cout << "-----------------------------------------------" << endl;
    cout << UI::CIANO << "SISTEMA OPERANDO COM SEGURANÇA DE TIPOS" << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: FUNCTION TEMPLATES
    ===============================================================

    1. O QUE SÃO TEMPLATES?
       - São "meta-programação". Você não escreve uma função, mas 
         sim uma "receita" para que o compilador crie a função 
         quando você precisar dela.

    2. TYPENAME T:
       - 'T' é um placeholder (espaço reservado) para o tipo. O 
         compilador olha para o argumento que você passou e 
         substitui o T pelo tipo real (int, double, etc).

    3. MULTI-PARÂMETROS E AUTO (C++11/14):
       - Usamos 'auto' e 'decltype' para que o C++ decida o tipo de 
         retorno com base na operação. Se somarmos int + double, 
         o resultado deve ser double para não perder precisão.

    4. EFICIÊNCIA:
       - Templates não causam lentidão no programa rodando. A 
         "mágica" acontece na compilação. O executável final é tão 
         rápido quanto se você tivesse escrito as funções manuais.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Especialização de Template: Quando um tipo específico precisa 
      de uma lógica diferente.
    - Class Templates: Classes genéricas (como o vector<T>).
    - Concepts (C++20): Restringindo os tipos que o template aceita.
    ===============================================================
*/

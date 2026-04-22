/**
 * @file atividade-extra26-templates.cpp
 * @brief Finanças Internacionais: Programação Genérica com Templates.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a geração automática de código otimizado para múltiplos tipos monetários.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Template Instantiation)
 * - O Template em si não ocupa memória.
 * - Instanciação: Para cada par de tipos (int+double, double+double), o compilador 
 *   gera uma função real no CODE SEGMENT do binário.
 * - Execução: As chamadas são tão rápidas quanto funções comuns, operando na STACK.
 * - Tipo Automático (auto): Resolvido em tempo de compilação (Zero Runtime Overhead).
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. MOTOR GENÉRICO DE CÂMBIO (TEMPLATES) ---

/**
 * @brief Template Universal para aplicação de taxas.
 * Usa Trailing Return Type para dedução precisa da operação.
 */
template <typename T, typename U>
auto aplicarTaxa(T valor, U taxa) -> decltype(valor * taxa) {
    return valor * taxa;
}

/**
 * @brief Template de Soma Genérica (Inter-moedas).
 */
template <typename T1, typename T2>
auto somarSaldos(T1 s1, T2 s2) -> decltype(s1 + s2) {
    return s1 + s2;
}

// --- 3. EXECUÇÃO PRINCIPAL ---

int main()
{
    UI::limparTela();
    cout << fixed << setprecision(4);

    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      FOREX TEMPLATE ENGINE v2.0 (ELITE)       " << endl;
    cout << "       (Generic Financial Architecture)        " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // --- CENÁRIO 1: CONVERSÃO DE MOEDA INTEIRA (IENE) ---
    // O compilador gera: double aplicarTaxa<int, double>(int, double)
    int ienes = 25000;
    double taxaIeneReal = 0.0345;
    auto ieneEmReal = aplicarTaxa(ienes, taxaIeneReal);

    cout << UI::AMARELO << UI::NEGRITO << "[INSTÂNCIA INT]: " << UI::RESET 
         << ienes << " JPY -> " << UI::VERDE << UI::NEGRITO << "R$ " << ieneEmReal << UI::RESET << endl;

    // --- CENÁRIO 2: CONVERSÃO DE MOEDA DOUBLE (DÓLAR) ---
    // O compilador gera: double aplicarTaxa<double, double>(double, double)
    double dolares = 1450.50;
    double taxaDolarReal = 5.2410;
    auto dolarEmReal = aplicarTaxa(dolares, taxaDolarReal);

    cout << UI::AZUL << UI::NEGRITO << "[INSTÂNCIA DOUBLE]: " << UI::RESET 
         << dolares << " USD -> " << UI::VERDE << UI::NEGRITO << "R$ " << dolarEmReal << UI::RESET << endl;

    // --- CENÁRIO 3: SOMA DE TIPOS HETEROGÊNEOS ---
    // O compilador promove o resultado para o tipo mais abrangente automaticamente
    auto patrimonioTotal = somarSaldos(ieneEmReal, dolarEmReal);
    
    cout << "\n" << UI::BRANCO << "DASHBOARD PATRIMONIAL:" << UI::RESET << endl;
    cout << "Soma Consolidada: " << UI::VERDE << UI::NEGRITO << "R$ " << patrimonioTotal << UI::RESET << endl;
    cout << UI::CIANO << "-----------------------------------------------" << endl;
    cout << "Status: " << UI::VERDE << "Tipagem Estática Garantida via Template." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: PROGRAMAÇÃO GENÉRICA (ELITE STANDARD)
    ===============================================================

    1. META-PROGRAMAÇÃO:
       - Templates não são funções, são moldes. O C++ realiza a 
         "Monomorfização", criando funções reais para cada tipo 
         que você usar. Isso une o melhor de dois mundos: a 
         reutilização de código do Python com a velocidade do C.

    2. DEDUÇÃO AUTOMÁTICA (C++11/14):
       - O uso de 'auto' e 'decltype' permite que o compilador 
         analise a expressão (valor * taxa) e decida o tipo de 
         retorno mais seguro (ex: int * double = double), 
         previnindo perdas de precisão financeira.

    3. ZERO RUNTIME COST:
       - Diferente do polimorfismo dinâmico (virtual), que exige 
         consultas à V-Table em tempo de execução, os templates 
         são resolvidos 100% na compilação. É a escolha de elite 
         para performance bruta.

    4. SEGURANÇA DE TIPOS (TYPE SAFETY):
       - Se você tentar passar uma string para o template de taxa, 
         o erro ocorrerá na compilação, e não quando o cliente 
         estiver operando o sistema Forex.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - SFINAE (Substitution Failure Is Not An Error).
    - Variadic Templates (...): Funções com infinitos argumentos.
    - Template Specialization: Lógica customizada para tipos específicos.
    ===============================================================
*/

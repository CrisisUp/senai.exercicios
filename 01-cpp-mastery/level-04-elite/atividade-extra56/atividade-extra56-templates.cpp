/**
 * @file atividade-extra56-templates.cpp
 * @brief Interface do Armazém Genérico (Elite Generic Programming).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a versatilidade de classes genéricas para qualquer tipo de dado.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <string>
#include <iomanip>
#include "Armazem.h" 

using namespace std;
using namespace Logistica;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

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

// --- 2. TIPOS DE DADOS CUSTOMIZADOS ---

/** @struct PecaMecanica: Representa um componente físico. */
struct PecaMecanica {
    string sku;
    double peso;

    // SOBRECARGA OBRIGATÓRIA para compatibilidade com o template
    friend ostream& operator<<(ostream& os, const PecaMecanica& p) {
        os << UI::RESET << "PEÇA [" << UI::RESET << p.sku << UI::RESET 
           << "] | Massa: " << UI::RESET << p.peso << " kg";
        return os;
    }
};

// --- 3. EXECUÇÃO DO ARMAZÉM GLOBAL ---

int main() {
    UI::limparTela();
    
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-WAREHOUSE: ARMAZÉM INTELIGENTE v2.0    " << endl;
    cout << "       (Elite Class Template Architecture)     " << endl;
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << UI::RESET << endl;

    // --- CENÁRIO 1: ARMAZÉM DE IDENTIDADES (string) ---
    Armazem<string> setorDocs("Documentação Fiscal");
    setorDocs.adicionar("Manifesto_NFe_101.pdf");
    setorDocs.adicionar("Guia_Importacao_B4.xml");
    setorDocs.exibir();

    // --- CENÁRIO 2: ARMAZÉM DE LOTES (int) ---
    Armazem<int> setorLotes("Lotes de Produção");
    setorLotes.adicionar(20260401);
    setorLotes.adicionar(20260402);
    setorLotes.exibir();

    // --- CENÁRIO 3: ARMAZÉM DE COMPONENTES (struct) ---
    Armazem<PecaMecanica> setorHardware("Hardware de Precisão");
    
    // Fantasma do CPU: Inserindo objetos pesados via referência constante
    setorHardware.adicionar({"MTR-V8-HYPER", 450.50});
    setorHardware.adicionar({"SNS-LASER-3D", 2.15});
    
    setorHardware.exibir();

    cout << UI::VERDE << UI::NEGRITO << "\n[SISTEMA]: " << UI::RESET 
         << "Logística genérica validada com 100% de integridade estática." << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: PROGRAMAÇÃO GENÉRICA (ELITE)
    ===============================================================

    1. TEMPLATES (CONTÊINERES UNIVERSAIS):
       - O 'Armazem<T>' é um molde. Quando você escreve <string>, o 
         compilador C++ "cospe" uma classe real otimizada para 
         strings. Quando escreve <int>, ele gera outra. Isso une o 
         reuso do Python com a performance do Assembly.

    2. DUCK TYPING EM COMPILE-TIME:
       - O template não exige herança. Ele exige apenas que o tipo 
         'T' ofereça o que ele pede (no caso, o operador <<). Se 
         o tipo satisfaz a interface, ele "entra" no armazém.

    3. FANTASMA DO CPU (PERFORMANCE):
       - Note que no 'Armazem.h', o método 'adicionar(const T& item)' 
         usa referência constante. Isso é vital; se 'T' for uma 
         peça de 1GB de dados, o sistema apenas passará o endereço 
         de memória, economizando tempo e RAM.

    4. SEGURANÇA DE TIPOS:
       - Uma vez que o 'setorLotes' foi definido como <int>, o 
         compilador impedirá qualquer tentativa de colocar uma 
         peça mecânica lá dentro, protegendo o sistema contra 
         erros de lógica.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - SFINAE: 'Substitution Failure Is Not An Error'.
    - Variadic Templates: Aceitar infinitos parâmetros genéricos.
    - Metaprogramação: Executar cálculos em tempo de compilação.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

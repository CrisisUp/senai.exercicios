/**
 * @file atividade-extra52-operadores.cpp
 * @brief Teste de Operadores Customizados para Telemetria.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a integração de álgebra física com tratamento de exceções.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include "Medicao.h" 

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

// --- 2. EXECUÇÃO DA ANÁLISE DE PRECISÃO ---

int main() {
    UI::limparTela();
    
    // Instâncias de Telemetria
    Medicao s1(45.50, "psi");
    Medicao s2(32.15, "psi");
    Medicao s3(45.50, "psi");

    cout << UI::AMARELO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-SYSTEM: ANÁLISE DE SENSORES v2.0       " << endl;
    cout << "       (Elite Operator Overloading Engine)     " << endl;
    cout << UI::AMARELO << UI::NEGRITO << "===============================================" << UI::RESET << endl;

    // TESTE 1: Renderização via Operator<< (Friend)
    cout << UI::RESET << "TELEMETRIA S1: " << UI::RESET << UI::CIANO << s1 << UI::RESET << endl;
    cout << UI::RESET << "TELEMETRIA S2: " << UI::RESET << UI::CIANO << s2 << UI::RESET << endl;
    cout << UI::RESET << "TELEMETRIA S3: " << UI::RESET << UI::CIANO << s3 << UI::RESET << endl;

    // TESTE 2: Álgebra de Sensores (Operator+)
    try {
        Medicao cargaTotal = s1 + s2;
        cout << "\n" << UI::VERDE << UI::NEGRITO << "[ALGEBRA]: " << UI::RESET 
             << "Carga Combinada (S1+S2): " << UI::NEGRITO << cargaTotal << UI::RESET << endl;
    } catch (const exception& e) {
        cout << UI::VERMELHO << "[ERRO FISICO]: " << e.what() << UI::RESET << endl;
    }

    // TESTE 3: Lógica de Comparação (Operator< e Operator==)
    cout << "\n" << UI::NEGRITO << "ANÁLISE DE FLUXO E CALIBRAÇÃO:" << UI::RESET << endl;
    
    if (s2 < s1) {
        cout << " >> S2 opera em regime " << UI::AMARELO << "REDUZIDO" << UI::RESET << " comparado a S1." << endl;
    }

    if (s1 == s3) {
        cout << " >> S1 e S3 apresentam " << UI::VERDE << "CALIBRAÇÃO IDÊNTICA" << UI::RESET << "." << endl;
    }

    // TESTE 4: Proteção de Unidade (Cientista do Caos)
    cout << "\n" << UI::VERMELHO << "[STRESS TEST]: Somando grandezas incompatíveis (PSI + C)..." << UI::RESET << endl;
    try {
        Medicao t1(25.0, "C");
        Medicao falha = s1 + t1; // Deve disparar exceção
    } catch (const exception& e) {
        cout << UI::VERDE << "[CONTENÇÃO]: Sistema bloqueou operação ilegal: " << UI::RESET << e.what() << endl;
    }

    cout << UI::AMARELO << UI::NEGRITO << "\n===============================================" << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: SOBRECARGA DE OPERADORES (ELITE)
    ===============================================================

    1. SINTAXE NATURAL E READABILITY:
       - O C++ permite que 's1 + s2' seja código válido para objetos. 
         Isso remove a verbosidade de 's1.somar(s2)', tornando o 
         sistema mais limpo e próximo da modelagem matemática.

    2. FUNÇÕES FRIEND (operator<<):
       - O operador de saída não é membro da classe Medicao (pois o 
         objeto à esquerda é o std::cout). Usamos 'friend' para que 
         essa função externa possa ler os atributos privados de 
         Medicao sem quebrá-los.

    3. PROTEÇÃO FISICA VIA EXCEÇÕES:
       - Operadores não devem apenas processar dados, devem garantir 
         a lógica do domínio. Impedir a soma de PSI com Celsius via 
         'operator+' é um exemplo de design defensivo sênior.

    4. FANTASMA DO CPU (RETURN VALUE OPTIMIZATION):
       - Embora o 'operator+' retorne um objeto por valor, os 
         compiladores modernos realizam RVO (Return Value 
         Optimization), construindo o resultado diretamente na 
         memória de destino, eliminando cópias pesadas na Stack.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Operator Overloading vs Method Calling.
    - Postfix vs Prefix operators (++obj vs obj++).
    - Conversões Implícitas e a palavra-chave 'explicit'.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

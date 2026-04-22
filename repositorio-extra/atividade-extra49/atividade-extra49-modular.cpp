/**
 * @file atividade-extra49-modular.cpp
 * @brief Programa principal da calculadora de engenharia (UI).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <iomanip>
#include "Calculadora.h" // Importando nossa interface modular

using namespace std;

int main() {
    double r, h;

    cout << "\033[34m===============================================\033[0m" << endl;
    cout << "     SISTEMA DE ENGENHARIA MODULAR (C++17)     " << endl;
    cout << "\033[34m===============================================\033[0m" << endl;

    cout << "Digite o raio da fundação (metros): ";
    cin >> r;
    cout << "Digite a altura do pilar (metros): ";
    cin >> h;

    // Usando o motor de cálculo definido em Calculadora.h/cpp
    double volume = CalculadoraEngenharia::calcularVolumeCilindro(r, h);

    cout << fixed << setprecision(2);
    cout << "\n\033[32m[RESULTADO]:\033[0m O volume necessário de concreto é: " 
         << volume << " m³" << endl;

    cout << "\033[34m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ARQUITETURA MODULAR (.h vs .cpp)
    ===============================================================

    1. ARQUIVO .h (HEADER):
       - Contém o "Contrato" ou a "Interface".
       - Define O QUE o sistema faz (classes, assinaturas de funções).
       - Usa-se include guards (#ifndef / #define) para evitar erros
         de redefinição durante a compilação.

    2. ARQUIVO .cpp (IMPLEMENTAÇÃO):
       - Contém o "Como o sistema faz" (a lógica real).
       - Mantém a função main() limpa e focada apenas na UI.

    3. VANTAGEM DIDÁTICA:
       - Facilita a Manutenção: Se a fórmula do volume mudar, só 
         mexemos em um lugar (Calculadora.cpp), e o resto do 
         sistema (main.cpp) continua funcionando.
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Compilação Separada e Linkagem.
    - CMake: Automação de Projetos Multi-arquivos.
    - Encapsulamento em C++.
    ===============================================================
*/

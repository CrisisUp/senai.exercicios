/**
 * @file atividade-extra52-operadores.cpp
 * @brief Programa para testar a Sobrecarga de Operadores em medições de sensores.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <iomanip>
#include "Medicao.h" // Nossa interface modular de medições

using namespace std;
using namespace IoT;

int main() {
    // Definindo medições de diferentes sensores.
    Medicao sensor_A(45.5, "psi");
    Medicao sensor_B(30.2, "psi");
    Medicao sensor_C(45.5, "psi");

    cout << "\033[33m===============================================\033[0m" << endl;
    cout << "     SISTEMA DE ANÁLISE DE SENSORES (OPERADORES) " << endl;
    cout << "\033[33m===============================================\033[0m" << endl;

    // Teste 1: Exibição usando o operador << sobrecarregado.
    cout << "SENSOR A: " << sensor_A << endl;
    cout << "SENSOR B: " << sensor_B << endl;
    cout << "SENSOR C: " << sensor_C << endl;

    // Teste 2: Adição usando o operador + sobrecarregado.
    Medicao carga_total = sensor_A + sensor_B;
    cout << "\n\033[32m[SOMA]:\033[0m A carga total da tubulação (A+B) é: " 
         << carga_total << endl;

    // Teste 3: Comparação usando o operador < sobrecarregado.
    if (sensor_B < sensor_A) {
        cout << "\n\033[32m[ANÁLISE]:\033[0m O sensor B está com MENOR carga que o sensor A." << endl;
    }

    // Teste 4: Igualdade usando o operador == sobrecarregado.
    if (sensor_A == sensor_C) {
        cout << "\033[32m[PRECISÃO]:\033[0m Os sensores A e C estão calibrados igualmente." << endl;
    }

    // Teste 5: Tratamento de erro (Tentar somar psi com Celsius).
    try {
        Medicao temp(25.0, "C");
        cout << "\nTentando somar psi com Celsius..." << endl;
        Medicao erro = sensor_A + temp;
    } catch (const exception& e) {
        cout << "\033[31m[ERRO TRATADO]:\033[0m " << e.what() << endl;
    }

    cout << "\033[33m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: SOBRECARGA DE OPERADORES
    ===============================================================

    1. O QUE É:
       - É dar uma nova função a um operador existente para que ele
         saiba como tratar seus próprios objetos.
       - Melhora drasticamente a legibilidade do código.

    2. OPERADORES COMUNS:
       - Unários: ++, --, !.
       - Binários: +, -, *, /, ==, <, >.
       - Entrada/Saída: <<, >>.

    3. PALAVRA-CHAVE 'operator':
       - Usada para definir a função especial: `operator+(const Medicao& outras)`.

    4. VANTAGEM DIDÁTICA:
       - Aproxima a programação da lógica matemática real do aluno.
       - Ensina sobre o sistema de tipos e assinaturas de funções em C++.
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Funções Friend (Amigas).
    - Manipulação de Exceções (try-catch).
    - Polimorfismo Ad-hoc.
    ===============================================================
*/

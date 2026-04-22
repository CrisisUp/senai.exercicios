/**
 * @file atividade-extra58-templates.cpp
 * @brief Programa principal para testar Templates de Funções e Especialização.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <iomanip>
#include "Comparador.h" // Nossa interface modular genérica

using namespace std;
using namespace IoT;

int main() {
    cout << "\033[35m===============================================\033[0m" << endl;
    cout << "     ANALISADOR DE PRECISÃO (TEMPLATES)        " << endl;
    cout << "\033[35m===============================================\033[0m" << endl;

    // 1. Usando com Inteiros (Genérico)
    int tempA = 45, tempB = 52;
    cout << "MAIOR TEMPERATURA: " << obterMaior(tempA, tempB) << endl;

    // 2. Usando com Doubles (Genérico)
    double pressaoA = 88.5, pressaoB = 82.3;
    cout << "MAIOR PRESSÃO: " << obterMaior(pressaoA, pressaoB) << endl;

    // 3. Usando com Strings (Especializado: Comprimento)
    // No C++, "LoteA" é menor que "Lote_Especial" em comprimento, 
    // mas alfabeticamente "LoteA" seria maior que "Lote_". 
    // Nossa especialização decide por comprimento.
    string id1 = "S-01";
    string id2 = "SENSOR-PRINCIPAL-ALTO-FLUXO";
    cout << "\nMAIOR IDENTIFICADOR (Especialização): " 
         << obterMaior(id1, id2) << endl;

    // 4. Usando com Structs (Combinação de Template + Sobrecarga)
    LeituraSensor s1 = {101, 45.8};
    LeituraSensor s2 = {202, 55.4};
    
    LeituraSensor resultado = obterMaior(s1, s2);
    
    cout << "\n\033[32m[RESULTADO]:\033[0m A maior leitura complexa detectada foi ID: " 
         << resultado.id << " com VALOR: " << resultado.valor << endl;

    cout << "\033[35m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: TEMPLATES E ESPECIALIZAÇÃO
    ===============================================================

    1. TEMPLATE DE FUNÇÃO (Function Template):
       - Permite que o compilador crie uma versão da função 'na hora'
         para cada tipo que você passar (int, double, float, etc).

    2. ESPECIALIZAÇÃO EXPLÍCITA:
       - Quando a lógica genérica não serve para um tipo específico. 
       - No nosso caso, o 'obterMaior' genérico compararia as strings 
         em ordem alfabética. Nossa especialização mudou a regra 
         para comparar o 'tamanho' do texto.

    3. RESOLUÇÃO DE NOMES:
       - O compilador do C++ sempre escolhe a versão MAIS ESPECÍFICA.
       - Se houver uma função normal, ela ganha do template. 
       - Se houver um template especializado, ele ganha do genérico.

    4. VANTAGEM DIDÁTICA:
       - Introduz o conceito de "Design Flexível": o código é robusto o 
         suficiente para lidar com o comum (genérico), mas esperto o 
         suficiente para tratar exceções (especialização).
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Sobrecarga de Templates (Function Template Overloading).
    - Metaprogramação (SFINAE - Substitution Failure Is Not An Error).
    - Traits e Políticas em Templates.
    ===============================================================
*/

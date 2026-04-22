/**
 * @file atividade-extra56-templates.cpp
 * @brief Programa principal para testar Programação Genérica com Templates.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <string>
#include "Armazem.h" // Nossa interface genérica modular

using namespace std;
using namespace Logistica;

/**
 * @brief Exemplo de um tipo de dado personalizado para estocagem.
 */
struct PecaMecanica {
    string nome;
    int serial;

    // SOBRECARGA NECESSÁRIA: O Armazem::exibir() precisa do '<<'.
    friend ostream& operator<<(ostream& os, const PecaMecanica& p) {
        os << "PEÇA: " << p.nome << " (S/N: " << p.serial << ")";
        return os;
    }
};

int main() {
    cout << "\033[36m===============================================\033[0m" << endl;
    cout << "     SISTEMA DE ARMAZÉM GENÉRICO (TEMPLATES)   " << endl;
    cout << "\033[36m===============================================\033[0m" << endl;

    // 1. Armazém de Strings (Nomes de Clientes ou Fornecedores)
    Armazem<string> setorEscritorio("Material de Escritório");
    setorEscritorio.adicionar("Papel A4");
    setorEscritorio.adicionar("Canetas Azuis");
    setorEscritorio.exibir();

    // 2. Armazém de Inteiros (Códigos de Barras isolados)
    Armazem<int> setorIDs("Controle de Lotes");
    setorIDs.adicionar(101);
    setorIDs.adicionar(202);
    setorIDs.adicionar(303);
    setorIDs.removerUltimo(); // Retira o 303
    setorIDs.exibir();

    // 3. Armazém de Objetos Complexos (PecaMecanica)
    // O mesmo código do armazém agora lida com structs!
    Armazem<PecaMecanica> setorManutencao("Oficina Central");
    
    PecaMecanica p1 = {"Biela de Aço", 9988};
    PecaMecanica p2 = {"Pistão Hidráulico", 7766};
    
    setorManutencao.adicionar(p1);
    setorManutencao.adicionar(p2);
    setorManutencao.exibir();

    cout << "\n\033[32m[LOGÍSTICA]:\033[0m Total de setores gerenciados: 3." << endl;
    cout << "\033[36m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: PROGRAMAÇÃO GENÉRICA (TEMPLATES)
    ===============================================================

    1. O QUE SÃO TEMPLATES?
       - É uma "receita" para o compilador. Em vez de você escrever 
         várias classes para tipos diferentes, você escreve uma 
         que usa 'T' e o C++ faz o resto do trabalho.

    2. VANTAGEM DIDÁTICA:
       - Demonstra que o código pode ser universal, abstraindo até 
         mesmo os tipos de dados básicos.
       - Ensina sobre o custo de compilação: O código do template 
         só é gerado para os tipos que você efetivamente utiliza.

    3. REQUISITOS DE TIPO (CONSTRAINTS):
       - Note que nosso Armazem<T>::exibir() exige que o tipo 'T' 
         saiba usar o operador '<<'. Se tentarmos usar um tipo 
         que não tenha esse operador, o compilador dará um erro 
         claro apontando a falta dessa funcionalidade.

    4. POSICIONAMENTO EM CADEIA:
       - Templates são a base de bibliotecas famosas como a STL 
         (Standard Template Library), que usamos desde a Atividade 1.
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Especialização de Templates (Template Specialization).
    - Metaprogramação em C++.
    - Conceitos (C++20 Concepts).
    ===============================================================
*/

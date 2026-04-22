/**
 * @file atividade-extra18-logistica.cpp
 * @brief Rastreio de Logística: Sobrecarga de Construtores e Inicialização.
 * 
 * Versão Refatorada: Agora utilizando Arquitetura Modular (.h e .cpp)
 * seguindo as normas do Nível 11+ do SENAI C++.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include "PacoteLogistico.h"

using namespace std;

int main()
{
    cout << fixed << setprecision(2);

    cout << UI::CIANO << "===============================================" << endl;
    cout << "      LOGÍSTICA SMART WAREHOUSE v2.0           " << endl;
    cout << "      (MÓDULO DE RASTREIO ATIVADO)             " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Cenário 1: Scanner Automático (Construtor Completo)
    PacoteLogistico pacoteEsteira("BR-12345-SCAN", 2.5, "São Paulo - SP");
    pacoteEsteira.exibirEtiqueta();

    // Cenário 2: Cadastro Manual (Construtor Parcial)
    cout << "\nCadastrando novo pacote manual..." << endl;
    PacoteLogistico pacoteManual("BR-99887-MAN");
    pacoteManual.exibirEtiqueta();

    // Atualizando o pacote manual posteriormente
    cout << "\nPesando o pacote manual na balança..." << endl;
    pacoteManual.setPeso(5.8);
    pacoteManual.setDestino("Curitiba - PR");
    
    pacoteManual.exibirEtiqueta();

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ARQUITETURA MODULAR E POO PROFISSIONAL
    ===============================================================

    1. SEPARAÇÃO DE RESPONSABILIDADES (Header vs Source):
       - .h (Header): Contém as DECLARAÇÕES (o que a classe faz). 
         Funciona como o manual de instruções para outros módulos.
       - .cpp (Source): Contém as IMPLEMENTAÇÕES (como a classe faz). 
         O código fonte fica protegido e organizado.

    2. SOBRECARGA DE CONSTRUTORES (Constructor Overloading):
       - Permite criar objetos em estados diferentes (Scanner vs Manual) 
         mantendo a consistência dos dados.

    3. LISTA DE INICIALIZAÇÃO (Member Initializer List):
       - Usada nos construtores em PacoteLogistico.cpp para 
         máxima performance na criação do objeto.

    4. NAMESPACES DE INTERFACE:
       - O uso de UI:: permite organizar constantes de estilo sem 
         poluir o namespace global do sistema.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Incluse Guards (#ifndef): Proteção contra inclusões múltiplas.
    - Operador de Escopo (::): Como o C++ identifica funções de classes.
    - Compilação Separada: Por que o build fica mais rápido em sistemas grandes.
    - Gerenciamento de Memória: Stack vs Heap para objetos.
    ===============================================================
*/

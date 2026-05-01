#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file atividade-extra18-logistica.cpp
 * @brief Rastreio de Logística: Sobrecarga de Construtores e Inicialização Elite.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a eficiência da alocação via Member Initializer List.
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
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      LOGÍSTICA SMART WAREHOUSE v3.0           " << endl;
    cout << "       (Elite Engineering Refactored)          " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // --- CENÁRIO 1: SCANNER AUTOMÁTICO (Instanciação na STACK) ---
    // Uso do Construtor Completo
    PacoteLogistico pacoteEsteira("BR-12345-SCAN", 2.5, "São Paulo - SP");
    pacoteEsteira.exibirEtiqueta();

    // --- CENÁRIO 2: CADASTRO MANUAL (Instanciação na STACK) ---
    // Uso do Construtor Parcial (Sobrecarga)
    cout << "\n" << UI::RESET << "Iniciando cadastro de pacote manual..." << UI::RESET << endl;
    PacoteLogistico pacoteManual("BR-99887-MAN");
    pacoteManual.exibirEtiqueta();

    // Atualização simulada via sensor/usuário
    cout << "\n" << UI::RESET << "Processando pesagem e rota final..." << UI::RESET << endl;
    
    if (!pacoteManual.setPeso(5.85)) {
        cout << UI::VERMELHO << "Falha crítica na pesagem." << UI::RESET << endl;
    }
    
    if (!pacoteManual.setDestino("Curitiba - PR")) {
        cout << UI::VERMELHO << "Falha crítica na definição de rota." << UI::RESET << endl;
    }
    
    // Relatório Final consolidado
    pacoteManual.exibirEtiqueta();

    cout << UI::VERDE << UI::NEGRITO << "\nLogística de saída processada com sucesso." << UI::RESET << endl;
    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: PERFORMANCE E FLEXIBILIDADE EM POO
    ===============================================================

    1. MEMBER INITIALIZER LIST (LISTA DE INICIALIZAÇÃO):
       - Diferente de atribuir valores dentro das chaves do construtor 
         (nome = n), a lista de inicialização (: nome(n)) ocorre no 
         momento exato em que o objeto nasce. Isso evita que o C++ 
         inicialize o atributo com lixo e depois mude o valor, 
         poupando ciclos de processamento.

    2. SOBRECARGA DE CONSTRUTORES (CONSTRUCTOR OVERLOADING):
       - É o polimorfismo em tempo de compilação aplicado à criação 
         de objetos. Permite que o sistema trate diferentes fluxos 
         de entrada (Automático vs Manual) com a mesma classe.

    3. PROTEÇÃO DE MEMÓRIA (FANTASMA DO CPU):
       - Passamos e retornamos strings por REFERÊNCIA CONSTANTE. 
         Em logística, onde podemos ter milhões de pacotes, evitar 
         a cópia de strings economiza gigabytes de tráfego na HEAP.

    4. RESILIÊNCIA DE DADOS:
       - Setters com retorno booleano permitem que a interface 
         reaja a erros de validação sem que o objeto entre em um 
         estado fisicamente impossível (ex: peso negativo).

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Default Arguments: Uma alternativa à sobrecarga de construtores.
    - Explicit Keyword: Evitando conversões implícitas indesejadas.
    - Delegação de Construtores (C++11): Como um construtor chama outro.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */


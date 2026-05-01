#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file atividade-extra17-saude.cpp
 * @brief Monitoramento de UTI: Introdução a Classes e Encapsulamento Profissional.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a transição de 'struct' para 'class' com proteção de memória.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include "MonitorSaude.h"

using namespace std;

int main()
{
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "     SISTEMA DE MONITORAMENTO DE UTI v2.0      " << endl;
    cout << "       (Elite Engineering Refactored)          " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Instanciação na STACK (Otimizado)
    PacienteMonitorado p1("João da Silva");

    int entradaBPM, entradaOxy;
    double entradaTemp;

    // Interface de entrada com validação de fluxo
    cout << UI::RESET << "Digite o BPM atual do paciente: " << UI::RESET;
    if (!(cin >> entradaBPM)) {
        cout << UI::VERMELHO << "ERRO: Entrada inválida detectada (Input Failure)." << UI::RESET << endl;
        return 1;
    }
    if (!p1.setBPM(entradaBPM)) {
        cout << UI::AMARELO << "AVISO: Valor de BPM fora da faixa médica segura." << UI::RESET << endl;
    }

    cout << UI::RESET << "Digite a Temperatura atual (°C): " << UI::RESET;
    cin >> entradaTemp;
    if (!p1.setTemperatura(entradaTemp)) {
        cout << UI::AMARELO << "AVISO: Valor de Temperatura ignorado (Inconsistência)." << UI::RESET << endl;
    }

    cout << UI::RESET << "Digite a Oxigenação (%): " << UI::RESET;
    cin >> entradaOxy;
    if (!p1.setOxigenacao(entradaOxy)) {
        cout << UI::AMARELO << "AVISO: Valor de Oxigenação crítico ou inválido." << UI::RESET << endl;
    }

    // Processamento do Relatório Clínica (UI encapsulada)
    p1.analisarEstado();

    cout << UI::VERDE << "\nMonitoramento concluído com sucesso." << UI::RESET << endl;
    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ENGENHARIA DE ELITE E ENCAPSULAMENTO
    ===============================================================

    1. ANATOMIA DA MEMÓRIA (STACK vs HEAP):
       - O objeto 'p1' reside inteiramente na STACK. No entanto, o seu 
         atributo 'std::string nome' gerencia um ponteiro para a HEAP, 
         onde o texto real está guardado. Ao usar referências constantes 
         (const string&), evitamos que o C++ duplique esse texto na HEAP 
         toda vez que chamamos o construtor ou um Getter.

    2. ENCAPSULAMENTO COMO BARREIRA DE SEGURANÇA:
       - Diferente da struct (onde tudo é público), a 'class' protege 
         seus membros com o modificador 'private'. Isso cria uma 
         \"Invariante de Classe\": o BPM do paciente NUNCA será 
         negativo, pois o único caminho para alterá-lo (setBPM) 
         bloqueia valores ilegais.

    3. OTIMIZAÇÃO FANTASMA DO CPU:
       - O método getNome() retorna 'const string&'. Isso é 
         fundamental em sistemas de alta performance; se retornássemos 
         apenas 'string', o C++ criaria uma cópia temporária do nome 
         a cada leitura, desperdiçando ciclos de CPU.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - RAII (Resource Acquisition Is Initialization): O coração do C++.
    - Rule of Three/Five: Como gerenciar cópias de classes complexas.
    - Inline Functions: Otimizando pequenos métodos como Getters.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */


/**
 * @file atividade-extra53-frota.cpp
 * @brief Interface do sistema de gestão de frota (Herança de Elite).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a especialização de classes e o uso de membros protegidos.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include "Frota.h" 

using namespace std;
using namespace Logistica;

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

// --- 2. EXECUÇÃO DA GESTÃO DE LOGÍSTICA ---

int main() {
    UI::limparTela();
    
    // Instanciação de um objeto especializado na STACK
    Caminhao volvo("SCANIA-R450", "LogiSpeed-Express", 40.0);

    cout << UI::AZUL << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-LOGISTICS: MONITORAMENTO DE FROTA v2.0 " << endl;
    cout << "       (Elite Class Inheritance Standard)       " << endl;
    cout << UI::AZUL << UI::NEGRITO << "===============================================" << UI::RESET << endl;

    // --- TESTE DE COMPORTAMENTO HERDADO (BASE) ---
    cout << UI::RESET << "\n[SISTEMA]: " << UI::RESET << "Iniciando ordem de serviço para Rastreio GPS..." << endl;
    volvo.viajar(850.50); 

    // --- TESTE DE COMPORTAMENTO ESPECIALIZADO (FILHA) ---
    cout << UI::RESET << "[CARGA]: " << UI::RESET << "Tentando embarque de 35 toneladas..." << endl;
    if (volvo.carregar(35.0)) {
        cout << UI::VERDE << UI::NEGRITO << " >> SUCESSO: " << UI::RESET << "Manobra de carregamento autorizada." << endl;
    }

    cout << UI::RESET << "\n[CARGA]: " << UI::RESET << "Tentando embarque extra de 10 toneladas..." << endl;
    if (!volvo.carregar(10.0)) {
        cout << UI::VERMELHO << UI::NEGRITO << " >> BLOQUEIO: " << UI::RESET 
             << UI::VERMELHO << "Excesso de carga detectado. Riscos estruturais!" << UI::RESET << endl;
    }

    // --- RELATÓRIO CONSOLIDADO ---
    cout << "\n" << UI::RESET << volvo.getRelatorioCaminhao() << UI::RESET << endl;

    cout << UI::AZUL << UI::NEGRITO << "\n===============================================" << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: HERANÇA E REUSABILIDADE (ELITE)
    ===============================================================

    1. RELACIONAMENTO "IS-A" (É-UM):
       - A herança é a ferramenta mais poderosa para evitar a 
         duplicação de código. Ao definir 'Veiculo', garantimos que 
         Vans, Carros e Caminhões tenham Placa e KM sem precisar 
         escrever isso três vezes.

    2. O MODIFICADOR PROTECTED:
       - Diferente do 'private', o 'protected' é um "voto de 
         confiança" para a família. Ele impede que a main() mexa no 
         odômetro, mas permite que o Caminhão o faça livremente, 
         equilibrando segurança e flexibilidade.

    3. FANTASMA DO CPU (MEMORY ALIGNMENT):
       - Na memória, o objeto Caminhão é contíguo. Primeiro vem os 
         dados do pai, depois os do filho. Isso torna o acesso aos 
         membros herdados tão rápido quanto o acesso aos membros 
         nativos.

    4. CHAINING DE CONSTRUTORES:
       - O C++ garante a ordem de nascimento: primeiro o objeto 
         genérico (Veiculo) é validado e construído, e apenas 
         depois a especialização (Caminhao) recebe seus dados. Isso 
         evita que um caminhão exista com uma placa inválida.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Sobrescrita de Métodos (Overriding).
    - Upcasting e Downcasting (Conversão de ponteiros).
    - Classes Abstratas (Próxima Atividade).
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

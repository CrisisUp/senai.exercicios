/**
 * @file atividade-extra54-imoveis.cpp
 * @brief Interface de Gestão Imobiliária (Polimorfismo de Elite).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a força das tabelas de métodos virtuais para escalabilidade.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include "Imovel.h" 

using namespace std;
using namespace Imobiliaria;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string AMARELO  = "\033[33m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. EXECUÇÃO DA GESTÃO DE PORTFÓLIO ---

int main() {
    UI::limparTela();
    
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-ESTATE: GESTÃO DE ATIVOS IMOBILIÁRIOS  " << endl;
    cout << "       (Elite Polymorphism & V-Table Engine)   " << endl;
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << UI::RESET << endl;

    // Coleção Polimórfica: Gerenciando diferentes tipos sob o mesmo contrato
    vector<Imovel*> portfolio;

    // Alocação na HEAP (Simulando banco de dados de ativos)
    portfolio.push_back(new Apartamento("Rua das Oliveiras, 45 - Apto 302", 1850.00, 450.00));
    portfolio.push_back(new Casa("Avenida dos Estados, 1200", 3500.00, 250.00));
    portfolio.push_back(new Apartamento("Pça da República, 10 - Cobertura", 12400.00, 2200.00));

    cout << UI::BRANCO << "\nDEMONSTRATIVO DE FATURAMENTO MENSAL (LATE BINDING):" << UI::RESET << endl;
    cout << string(60, '-') << endl;

    double faturamentoTotal = 0;

    // FANTASMA DO CPU: Iteração polimórfica via ponteiros da Base
    for (const auto* ativo : portfolio) {
        if (ativo) {
            double totalAtivo = ativo->calcularTotal(); // Decisão em RUNTIME via vptr
            faturamentoTotal += totalAtivo;

            cout << " >> LOCAL: " << left << setw(40) << ativo->getEndereco() 
                 << " | VALOR: " << UI::VERDE << UI::NEGRITO << "R$ " << fixed << setprecision(2) << totalAtivo << UI::RESET << endl;
        }
    }

    cout << string(60, '-') << endl;
    cout << UI::CIANO << UI::NEGRITO << "PATRIMÔNIO LÍQUIDO MENSAL: R$ " << faturamentoTotal << UI::RESET << endl;

    // --- CICLO DE DESALOCAÇÃO SEGURA ---
    cout << "\n" << UI::AMARELO << "[SISTEMA]: Encerrando sessão e liberando V-Table pointers..." << UI::RESET << endl;
    for (auto& item : portfolio) {
        // Devido ao DESTRUTOR VIRTUAL, o C++ sabe limpar a Casa ou o Apto corretamente
        delete item; 
        item = nullptr;
    }
    portfolio.clear();

    cout << UI::VERDE << UI::NEGRITO << "Vazamento Zero garantido. Engenharia de Elite concluída." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: POLIMORFISMO E DINÂMICA (ELITE)
    ===============================================================

    1. LATE BINDING (LIGAÇÃO TARDIA):
       - Diferente da herança simples, o polimorfismo permite que o 
         programa decida qual código rodar apenas no momento da 
         execução. O 'ativo->calcularTotal()' não aponta para um 
         endereço fixo, mas consulta um "mapa" (V-Table).

    2. DESTRUTOR VIRTUAL (A REGRA DE OURO):
       - Sem o 'virtual ~Imovel()', o comando 'delete ativo' 
         limparia apenas a parte 'Imovel' do objeto, deixando a 
         taxa de condomínio ou de jardim "vazando" na RAM para 
         sempre. O virtual garante a limpeza total.

    3. ESCALABILIDADE ARQUITETURAL:
       - Se a imobiliária começar a alugar 'Vagas de Garagem', 
         basta criar uma classe 'Vaga' herdando de 'Imovel'. O 
         loop de faturamento na main() continuará funcionando sem 
         precisar de uma única alteração.

    4. GUARDIÃO FINANCEIRO (CENTAVOS):
       - Note que embora a interface exiba 'double', o motor 
         interno (Imovel.cpp) processa tudo em centavos inteiros, 
         evitando erros acumulados em portfólios de milhares de 
         imóveis.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - RTTI (Run-Time Type Information) e 'dynamic_cast'.
    - Slicing Problem: O perigo de passar objetos por valor.
    - Abstract Base Classes (ABC): Próximo Nível.
    ===============================================================
*/

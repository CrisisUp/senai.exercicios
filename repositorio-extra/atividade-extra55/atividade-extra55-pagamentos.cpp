/**
 * @file atividade-extra55-pagamentos.cpp
 * @brief Interface do Gateway de Pagamentos (Interfaces de Elite).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a força do desacoplamento via Classes Abstratas e Smart Pointers.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <vector>
#include <memory> 
#include "Pagamento.h" 

using namespace std;
using namespace Financeiro;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string AZUL     = "\033[34m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string VERMELHO = "\033[31m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. EXECUÇÃO DO MOTOR DE CHECKOUT ---

int main() {
    UI::limparTela();
    
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-PAY: GATEWAY DE PAGAMENTOS v3.0        " << endl;
    cout << "       (Elite Abstract Interface Standard)     " << endl;
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << UI::RESET << endl;

    // --- ARQUITETURA MODERNA: GESTÃO RAII ---
    // Usamos unique_ptr para garantir que a memória seja limpa sem intervenção manual
    vector<unique_ptr<MetodoPagamento>> queue;

    // População dinâmica do gateway (Simulando injeção de dependência)
    queue.push_back(make_unique<CartaoCredito>("4532-1111-2222-9988"));
    queue.push_back(make_unique<Pix>("financeiro@empresa.com"));
    queue.push_back(make_unique<CartaoCredito>("5588-4400-3333-2211"));

    double valorTransacao = 1250.75;

    cout << UI::BRANCO << "\nINICIANDO PROCESSAMENTO DE FILA POLIMÓRFICA:" << UI::RESET << endl;
    cout << string(50, '-') << endl;

    // FANTASMA DO CPU: Iteração polimórfica via ponteiros inteligentes
    for (const auto& metodo : queue) {
        if (metodo) {
            cout << UI::AMARELO << "\n[TRANSACAO EM CURSO]:" << UI::RESET << endl;
            
            try {
                // A main não sabe se é Pix ou Cartão, apenas sabe que 'processar' existe.
                metodo->processar(valorTransacao);
                cout << UI::VERDE << "[STATUS]: Liquidação autorizada pelo core." << UI::RESET << endl;
            } catch (const exception& e) {
                cout << UI::VERMELHO << "[ERRO]: " << e.what() << UI::RESET << endl;
            }
        }
    }

    cout << string(50, '-') << endl;
    cout << UI::VERDE << UI::NEGRITO << "Fim da sessão de faturamento. Auditoria RAM: OK (Vazamento Zero)." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: CLASSES ABSTRATAS E CONTRATOS (ELITE)
    ===============================================================

    1. PROGRAMANDO PARA INTERFACES:
       - O segredo da G-Pay é que o motor principal não conhece as 
         classes concretas (Pix/Cartão). Ele depende apenas da 
         classe abstrata 'MetodoPagamento'. Isso permite adicionar 
         'Criptomoeda' ou 'Boleto' sem mudar uma linha da main().

    2. VIRTUAL PURO (= 0):
       - Ao definir o método como puro, impedimos erros lógicos de 
         negócio, como tentar instanciar um "Pagamento" que não 
         sabe como ser processado. A classe torna-se um molde puro.

    3. SMART POINTERS (std::unique_ptr):
       - Em sistemas financeiros, a perda de memória (leak) pode 
         levar à instabilidade do servidor de transações. O RAII 
         elimina este risco, transformando o C++ em uma linguagem 
         tão segura quanto o Rust em termos de posse única.

    4. POLIMORFISMO DE INTERFACE:
       - Diferente da herança de implementação (onde você herda 
         código pronto), aqui você herda a OBRIGAÇÃO de implementar. 
         Isso garante que todos os módulos do sistema sigam o 
         mesmo padrão arquitetural.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Dependency Injection: Passar os métodos de pagamento prontos.
    - Strategy Pattern: Trocar a estratégia de cobrança em runtime.
    - Liskov Substitution Principle (SOLID): Pilares da POO Senior.
    ===============================================================
*/

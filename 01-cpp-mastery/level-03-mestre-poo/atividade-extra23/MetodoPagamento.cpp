#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file MetodoPagamento.cpp
 * @brief Implementação dos métodos de pagamento e lógica de polimorfismo.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Abstract Interface)
 * - Classe Abstrata: Não possui instâncias próprias. Ocupa 0 bytes de memória 
 *   até que uma filha seja criada.
 * - Objeto Derivado (Pix/Cartão): Geralmente alocado na HEAP para vida dinâmica. 
 *   Contém o valor (8 bytes) e o ponteiro para a V-TABLE da filha.
 * - V-Table: Garante que o método virtual puro seja resolvido para a 
 *   implementação correta no runtime.
 * - Stack: Armazena ponteiros para a classe base que apontam para objetos na Heap.
 */

#include "MetodoPagamento.h"

using namespace std;

// --- MetodoPagamento ---

MetodoPagamento::MetodoPagamento(double v) : valorCentavos(static_cast<long long>(v * 100)) {}

void MetodoPagamento::exibirRecibo() const {
    double real = static_cast<double>(valorCentavos) / 100.0;
    cout << UI::CIANO << UI::NEGRITO << "-----------------------------------------------" << UI::RESET << endl;
    cout << UI::NEGRITO << "COMPROVANTE G-PAY" << UI::RESET << endl;
    cout << "Valor Processado : " << UI::VERDE << UI::NEGRITO << "R$ " << fixed << setprecision(2) << real << UI::RESET << endl;
    cout << "Status           : " << UI::VERDE << "CONFIRMADO" << UI::RESET << endl;
    cout << UI::CIANO << UI::NEGRITO << "-----------------------------------------------" << UI::RESET << endl;
}

MetodoPagamento::~MetodoPagamento() {}

// --- PagamentoPix ---

PagamentoPix::PagamentoPix(double v) : MetodoPagamento(v) {}

void PagamentoPix::processar() {
    cout << UI::VERDE << UI::NEGRITO << "[MODAL PIX]: " << UI::RESET 
         << "Gerando Payload BR Code dinâmico..." << endl;
    cout << UI::AMARELO << "CODE: 00020126360014BR.GOV.BCB.PIX0114998877665544" << UI::RESET << endl;
    cout << "[SISTEMA]: Aguardando liquidação em tempo real... OK!" << endl;
}

// --- PagamentoCartao ---

PagamentoCartao::PagamentoCartao(double v, const string& n) 
    : MetodoPagamento(v), numeroMascarado(n) {}

void PagamentoCartao::processar() {
    cout << UI::AZUL << UI::NEGRITO << "[MODAL CARTÃO]: " << UI::RESET 
         << "Comunicando com Gateway de Adquirência..." << endl;
    string final = (numeroMascarado.length() >= 4) ? numeroMascarado.substr(numeroMascarado.length() - 4) : "****";
    cout << "[SISTEMA]: Autorizando final " << UI::NEGRITO << final << UI::RESET << "..." << endl;
    cout << UI::VERDE << "[OK]: Transação capturada com sucesso." << UI::RESET << endl;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ABSTRAÇÃO E CONTRATOS DE SOFTWARE
    ===============================================================

    1. INTERFACES (CLASSES ABSTRATAS):
       - Servem para definir "O QUE" um objeto deve fazer, sem 
         especificar "COMO". No G-PAY, garantimos que todo método 
         de pagamento tenha um valor e possa ser processado.

    2. VIRTUAL PURO (= 0):
       - É o mecanismo que proíbe a criação de objetos da classe 
         mãe. Isso evita erros lógicos, como criar um "Pagamento" 
         que não tem tipo definido.

    3. INTEGRIDADE FINANCEIRA (ELITE RULE):
       - Note que o valor é guardado em centavos (long long). 
         Ao trabalhar com dinheiro, o tipo 'double' é perigoso 
         devido a imprecisões binárias (ex: 0.1 + 0.2 != 0.3). 
         Cálculos inteiros são a lei em Fintechs.

    4. RESILIÊNCIA DE DESIGN:
       - O polimorfismo dinâmico permite que o G-PAY aceite novos 
         métodos (ex: Cripto, Boleto) sem que o código da main() 
         ou da fila precise ser alterado.
    ===============================================================
*/


#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @file ProdutoIndustrial.cpp
 * @brief Implementação da classe ProdutoIndustrial e UI.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Refactored Layout)
 * - Variáveis Estáticas: Alocados no DATA SEGMENT (Persistem por toda a vida).
 * - Objetos ProdutoIndustrial: Alocados na HEAP para permitir inventário dinâmico.
 * - Strings (nome): Objeto na HEAP (Product) -> Dados reais em outro bloco na HEAP.
 * - Stack: Armazena ponteiros e variáveis de controle da aplicação.
 */

#include "ProdutoIndustrial.h"

using namespace std;

// --- UI ---
void UI::cabecalho() {
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "       ALMOXARIFADO INDUSTRIAL v4.0 (REFAC)    " << endl;
    cout << "       (Elite Engineering & Safety Core)       " << endl;
    cout << "===============================================" << UI::RESET << endl;
}

// --- ErroEstoque ---
ErroEstoque::ErroEstoque(string m) : msg(UI::VERMELHO + "[ALERTA DE ESTOQUE]: " + m + UI::RESET) {}
const char* ErroEstoque::what() const throw() { return msg.c_str(); }

// --- ProdutoIndustrial ---
long long ProdutoIndustrial::valorGlobalCentavos = 0;
int ProdutoIndustrial::totalItens = 0;

ProdutoIndustrial::ProdutoIndustrial(const string& _nome, double _preco, int _qtd) 
    : nome(_nome), precoCentavos(static_cast<long long>(_preco * 100)), quantidade(_qtd) 
{
    if (_preco < 0 || _qtd < 0) throw ErroEstoque("Parâmetros de inicialização inválidos para '" + nome + "'.");
    
    valorGlobalCentavos += (precoCentavos * quantidade);
    totalItens++;
}

void ProdutoIndustrial::registrarSaida(int qtd) {
    if (qtd <= 0) throw ErroEstoque("Quantidade de movimentação deve ser positiva.");
    if (qtd > quantidade) throw ErroEstoque("Ruptura de estoque detectada para '" + nome + "'.");

    valorGlobalCentavos -= (precoCentavos * qtd);
    quantidade -= qtd;
    cout << UI::VERDE << "[OK]: Remessa de " << qtd << " un. de '" << nome << "' liberada." << UI::RESET << endl;
}

void ProdutoIndustrial::exibirItem() const {
    double precoReal = static_cast<double>(precoCentavos) / 100.0;
    double subtotal = (static_cast<double>(precoCentavos * quantidade)) / 100.0;

    cout << UI::RESET << left << setw(20) << nome << UI::RESET 
         << " | Preço: R$ " << right << setw(9) << fixed << setprecision(2) << precoReal 
         << " | Qtd: " << UI::CIANO << setw(5) << quantidade << UI::RESET
         << " | Subtotal: R$ " << UI::NEGRITO << setw(10) << subtotal << UI::RESET << endl;
}

const string& ProdutoIndustrial::getNome() const { return nome; }
double ProdutoIndustrial::getValorGlobal() { return static_cast<double>(valorGlobalCentavos) / 100.0; }
int ProdutoIndustrial::getTotalItens() { return totalItens; }

/* 
    ===============================================================
    RESUMO TEÓRICO: MODERNIZAÇÃO E DÍVIDA TÉCNICA
    ===============================================================

    1. O FIM DAS VARIÁVEIS SOLTAS: Encapsulamento protege o estado interno.
    2. AUDITORIA ESTÁTICA: Uso de membros static para visão global O(1).
    3. PROTEÇÃO CONTRA IMPRECISÃO: Uso de long long centavos para Fintech/Industrial.
    4. GESTÃO DE MEMÓRIA: Alocação dinâmica com limpeza rigorosa.
    ===============================================================
*/


/**
 * @file atividade-extra28-stl-map.cpp
 * @brief Checkout de Supermercado: Performance de Busca com STL std::map.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a eficiência das Árvores Rubro-Negras para indexação de produtos.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Red-Black Tree Layout)
 * - std::map: Alocado na HEAP como uma série de nós espalhados.
 * - Nó do Mapa: Contém a Chave (string), o Valor (long long), 3 ponteiros de 
 *   navegação e metadados de balanceamento (cor do nó).
 * - Busca O(log n): O ponteiro de iteração percorre os nós da árvore, nunca 
 *   tocando em itens irrelevantes para a busca.
 */

#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <exception>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string VERMELHO = "\033[31m";
    const string CIANO    = "\033[36m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. GESTÃO DE EXCEÇÕES DE BUSCA ---

class ErroCatalogo : public exception {
    string msg;
public:
    ErroCatalogo(const string& m) : msg(UI::VERMELHO + "[SISTEMA]: " + m + UI::RESET) {}
    const char* what() const throw() { return msg.c_str(); }
};

// --- 3. MOTOR DE PREÇOS (ELITE MAP ARCHITECTURE) ---

class SistemaPrecos {
private:
    // map<Chave, ValorCentavos>
    // Garantia de Integridade Financeira: cálculos inteiros em centavos.
    map<string, long long> catalogo;

public:
    SistemaPrecos() {
        // Inicialização do Inventário Crítico
        catalogo["789123"] = 550;   // Arroz 1kg
        catalogo["789456"] = 1290;  // Feijão 1kg
        catalogo["789789"] = 325;   // Sal 1kg
        catalogo["112233"] = 199;   // Água Mineral
        catalogo["445566"] = 2500;  // Carne Alcatra (Kg)
        catalogo["556677"] = 8990;  // Vinho Importado
    }

    /**
     * @brief Consulta rápida usando busca binária balanceada.
     * @param sku Referência constante para evitar cópia da chave.
     */
    void consultarPreco(const string& sku) const {
        // FANTASMA DO CPU: .find() evita criar itens fantasmas como o operador []
        auto it = catalogo.find(sku);

        if (it != catalogo.end()) {
            double real = static_cast<double>(it->second) / 100.0;
            cout << UI::VERDE << UI::NEGRITO << "[SUCESSO]: Item Identificado." << UI::RESET << endl;
            cout << UI::BRANCO << "SKU   : " << UI::RESET << it->first << endl;
            cout << UI::BRANCO << "PREÇO : " << UI::RESET << UI::NEGRITO << "R$ " << fixed << setprecision(2) << real << UI::RESET << endl;
        } else {
            throw ErroCatalogo("Código SKU '" + sku + "' não localizado na base de dados.");
        }
    }

    /**
     * @brief Exibe o catálogo completo (já ordenado nativamente pelo map).
     */
    void mostrarTodos() const {
        cout << "\n" << UI::NEGRITO << "CATÁLOGO DE PREÇOS (ORDEM ALFABÉTICA SKU):" << UI::RESET << endl;
        cout << string(45, '-') << endl;
        for (const auto& par : catalogo) {
            double preco = static_cast<double>(par.second) / 100.0;
            cout << "SKU: " << UI::CIANO << left << setw(10) << par.first << UI::RESET 
                 << " | Unitário: R$ " << right << setw(8) << preco << endl;
        }
        cout << string(45, '-') << endl;
    }
};

// --- 4. EXECUÇÃO DO CHECKOUT INTERATIVO ---

int main()
{
    SistemaPrecos checkout;
    string entrada;

    do {
        UI::limparTela();
        cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
        cout << "      G-MARKET: SISTEMA DE CHECKOUT v2.0       " << endl;
        cout << "       (Elite STL & Balanced Trees)            " << endl;
        cout << "===============================================" << UI::RESET << endl;

        checkout.mostrarTodos();

        cout << UI::BRANCO << "\n[SCANNER]: Passe o código (ou 'S' p/ sair): " << UI::RESET;
        cin >> entrada;

        if (entrada != "S" && entrada != "s") {
            try {
                checkout.consultarPreco(entrada);
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
            cout << UI::AMARELO << "\nContinuar operação [ENTER]..." << UI::RESET;
            cin.ignore(1000, '\n'); cin.get();
        }

    } while (entrada != "S" && entrada != "s");

    cout << UI::VERDE << UI::NEGRITO << "\nTerminal de Vendas encerrado. Caixa Fechado." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: STL std::map E INDEXAÇÃO
    ===============================================================

    1. DICIONÁRIOS (CHAVE-VALOR):
       - O 'std::map' armazena pares (std::pair). Ele é a estrutura 
         perfeita para indexação, onde uma informação (SKU) serve 
         como ponteiro para outra (Preço).

    2. ÁRVORES RUBRO-NEGRAS:
       - O map não é um array. Ele é uma árvore binária que se 
         "auto-conserta" (rebalanceia) a cada inserção. Isso mantém 
         a profundidade da árvore mínima, garantindo que a busca 
         seja sempre rápida (Complexidade Logarítmica).

    3. PROTEÇÃO FANTASMA DO CPU:
       - Nunca use 'map[chave]' para consultas de leitura. Se a 
         chave não existir, o C++ irá INSERIR um valor padrão para 
         aquela chave, consumindo memória e alterando o catálogo. 
         Sempre use '.find()' para buscas seguras.

    4. GUARDIÃO FINANCEIRO:
       - O valor é processado como 'long long' centavos. Em um 
         supermercado com milhões de vendas diárias, imprecisões de 
         ponto flutuante acumuladas resultariam em quebras de caixa 
         inexplicáveis no final do mês.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Hash Tables (std::unordered_map): Busca O(1).
    - Cache Locality: Por que vectors podem ser mais rápidos que 
      maps para dados pequenos.
    - Iteradores Bidirecionais.
    ===============================================================
*/

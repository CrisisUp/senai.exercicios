/**
 * @file atividade-extra28-stl-map.cpp
 * @brief Checkout de Supermercado: Uso de std::map para buscas eficientes.
 * 
 * Este programa demonstra como o container std::map permite associar chaves
 * únicas (códigos de barras) a valores (preços), otimizando o tempo de resposta.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <exception>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string VERMELHO = "\033[31m";
    const string CIANO    = "\033[36m";
    const string NEGRITO  = "\033[1m";

    void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. GESTÃO DE EXCEÇÕES ---

class ErroCatalogo : public exception {
    string msg;
public:
    ErroCatalogo(string m) : msg(UI::VERMELHO + "[ERRO]: " + m + UI::RESET) {}
    const char* what() const throw() { return msg.c_str(); }
};

// --- 3. SISTEMA DE PREÇOS (O NOVO CONCEITO) ---

class SistemaPrecos {
private:
    // std::map<Chave, Valor>
    // Armazena os dados em uma árvore binária balanceada.
    map<string, double> catalogo;

public:
    SistemaPrecos() {
        // Inicialização do "Banco de Dados" em memória
        catalogo["789123"] = 5.50;  // Arroz 1kg
        catalogo["789456"] = 12.90; // Feijão 1kg
        catalogo["789789"] = 3.25;  // Sal 1kg
        catalogo["112233"] = 1.99;  // Água Mineral
        catalogo["445566"] = 25.00; // Carne Alcatra (Kg)
    }

    void consultarPreco(string sku) {
        // O método .find() do map é O(log n) - Ultra rápido!
        auto it = catalogo.find(sku);

        if (it != catalogo.end()) {
            cout << UI::VERDE << "PRODUTO LOCALIZADO!" << UI::RESET << endl;
            cout << "Código SKU: " << it->first << endl; // first é a chave
            cout << "Preço Unit: " << UI::NEGRITO << "R$ " << fixed << setprecision(2) << it->second << UI::RESET << endl; // second é o valor
        } else {
            throw ErroCatalogo("Código de barras '" + sku + "' não encontrado no sistema.");
        }
    }

    void mostrarTodos() {
        cout << "\n--- CATÁLOGO COMPLETO DE PREÇOS ---" << endl;
        // Percorrer um map retorna os itens já ORDENADOS pela chave automaticamente!
        for (const auto& par : catalogo) {
            cout << "SKU: " << par.first << " | Preço: R$ " << par.second << endl;
        }
    }
};

// --- 4. FUNÇÃO PRINCIPAL INTERATIVA ---

int main()
{
    SistemaPrecos sistema;
    string entrada;

    do {
        UI::limparTela();
        cout << UI::CIANO << "===============================================" << endl;
        cout << "      SISTEMA DE PREÇOS ULTRA-RÁPIDO v1.0      " << endl;
        cout << "===============================================" << UI::RESET << endl;

        sistema.mostrarTodos();

        cout << "\n[SIMULADOR DE SCANNER]" << endl;
        cout << "Passe o código de barras (ou 'sair' para encerrar): ";
        cin >> entrada;

        if (entrada != "sair") {
            try {
                sistema.consultarPreco(entrada);
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
            cout << "\nPressione ENTER para continuar...";
            cin.ignore(1000, '\n'); cin.get();
        }

    } while (entrada != "sair");

    cout << UI::VERDE << "\nSistema encerrado com sucesso." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: STL std::map (DICIONÁRIOS)
    ===============================================================

    1. ESTRUTURA CHAVE-VALOR:
       - O 'std::map' é um container associativo. Diferente do vetor 
         (que usa índices 0, 1, 2...), o map usa chaves de qualquer 
         tipo (como string para SKU).

    2. PERFORMANCE LOGARÍTMICA O(log n):
       - Internamente, o map usa uma Árvore Rubro-Negra. Isso garante 
         que a busca seja extremamente rápida, mesmo com milhões de 
         registros, pois o computador "poda" metade da árvore a 
         cada passo da busca.

    3. ORDENAÇÃO AUTOMÁTICA:
       - Uma característica marcante do map é que ele mantém as 
         chaves sempre ordenadas. Ao percorrer o catálogo, os SKUs 
         aparecem em ordem alfabética/numérica sem esforço extra.

    4. CHAVES ÚNICAS:
       - Em um map padrão, não podem existir duas chaves iguais. Se 
         você inserir um valor para um SKU que já existe, o C++ 
         atualiza o valor antigo (perfeito para mudança de preços).

    ===============================================================
    ASSUNTOS CORRELATOS:
    - std::unordered_map: Busca ainda mais rápida (O(1)) usando Hash.
    - std::multimap: Quando você precisa de chaves duplicadas.
    - Iteradores (it->first, it->second): Como navegar na STL.
    ===============================================================
*/

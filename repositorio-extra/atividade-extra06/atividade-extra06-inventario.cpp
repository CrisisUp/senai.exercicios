/**
 * @file atividade-extra06-inventario.cpp
 * @brief Sistema de Inventário (v3.0 - Robusto contra erros de Buffer).
 * 
 * Esta versão introduz a limpeza de buffer para evitar que digitações 
 * incorretas (como pontos em números inteiros) afetem o fluxo.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória
 * - Structs (Produto): Alocadas na STACK por possuírem tamanho fixo.
 * - std::string: Os metadados estão na STACK, mas o conteúdo longo é 
 *   alocado dinamicamente na HEAP pelo gerenciador de memória da STL.
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <limits> // Necessário para limpeza profissional do buffer
#include <vector> // Uso de vetores para organização

using namespace std;

// Namespace para Interface de Usuário com cores ANSI
namespace UI {
    const string RESET = "\033[0m";
    const string VERDE = "\033[32m";
    const string VERMELHO = "\033[31m";
    const string AMARELO = "\033[33m";
    const string CIANO = "\033[36m";
}

// --- 1. Estrutura ---
struct Produto {
    string nome;
    int id;
    double preco;
};

// --- 2. Protótipos ---
void limparBuffer();
void exibirCabecalho();
void exibirProduto(const Produto& p); // Fantasma do CPU: Passagem por referência constante
void exibirBanner();

// --- 3. Função Principal ---
int main()
{
    cout << fixed << setprecision(2);
    
    // Definindo o inventário com 2 produtos
    const int TAMANHO = 2;
    Produto inventario[TAMANHO];

    exibirBanner();

    for (int i = 0; i < TAMANHO; ++i) {
        cout << UI::AMARELO << "\n--- Cadastro do Produto 0" << (i + 1) << " ---" << UI::RESET << endl;
        cout << "Nome : "; getline(cin >> ws, inventario[i].nome);
        cout << "ID   : "; cin >> inventario[i].id;
        limparBuffer(); // Garante que sobras de ponto/texto sumam aqui
        cout << "Preço: "; cin >> inventario[i].preco;
        limparBuffer();
    }

    cout << UI::CIANO << "\n===============================================" << endl;
    cout << "          RELATÓRIO FINAL DE INVENTÁRIO        " << endl;
    cout << "===============================================" << endl << UI::RESET;
    
    exibirCabecalho();
    
    // Fantasma do CPU: Loop com 'const auto&' para evitar cópias pesadas de structs/strings
    for (const auto& p : inventario) {
        exibirProduto(p);
    }

    cout << UI::CIANO << "===============================================" << UI::RESET << endl;

    cout << "\nPressione Enter para finalizar...";
    cin.get(); 

    return 0;
}

// --- 4. Implementação ---

/**
 * Limpa o buffer de entrada do teclado.
 * Ignora todos os caracteres até encontrar o próximo 'Enter'.
 */
void limparBuffer() {
    cin.clear(); // Limpa estados de erro do cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void exibirCabecalho() {
    cout << left << "ID    | " 
         << setw(20) << "ITEM" << " | " 
         << right << setw(12) << "PRECO (R$)" << endl;
    cout << "-----------------------------------------------" << endl;
}

/**
 * Exibe um produto formatado.
 * @param p Referência constante para o produto (evita cópia de string).
 */
void exibirProduto(const Produto& p) {
    cout << left << setw(5) << p.id << " | "
         << left << setw(20) << p.nome << " | "
         << right << setw(12) << p.preco << endl;
}

void exibirBanner() {
    cout << UI::VERDE << "===============================================" << endl;
    cout << "       CONTROLE DE INVENTÁRIO AGRÍCOLA         " << endl;
    cout << "===============================================" << UI::RESET << endl;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: O BUFFER DE ENTRADA (cin) E EFICIÊNCIA
    ===============================================================
    1. O PROBLEMA DO BUFFER:
       - O 'cin' lê apenas o que ele espera. Se você digita '9.5' em 
         um 'int', ele lê o 9 e deixa o '.5' no "cano" (buffer).
       - O próximo 'cin' vai pegar esse lixo sem perguntar ao usuário.

    2. FANTASMA DO CPU (Referência Constante):
       - Ao passar 'const Produto& p', evitamos que o C++ crie uma 
         cópia temporária da struct e da string 'nome' na memória.
       - Isso economiza ciclos de CPU e memória RAM.

    3. QUANDO USAR:
       - Sempre após ler números (int, double) se a próxima leitura 
         for um texto ou outro número que possa ser contaminado.
    ===============================================================
*/

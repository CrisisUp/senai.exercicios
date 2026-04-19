/**
 * @file atividade-extra06-inventario.cpp
 * @brief Sistema de Inventário (v3.0 - Robusto contra erros de Buffer).
 * 
 * Esta versão introduz a limpeza de buffer para evitar que digitações 
 * incorretas (como pontos em números inteiros) afetem o fluxo.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <limits> // Necessário para limpeza profissional do buffer

using namespace std;

// --- 1. Estrutura ---
struct Produto {
    string nome;
    int id;
    double preco;
};

// --- 2. Protótipos ---
void limparBuffer();
void exibirCabecalho();
void exibirProduto(Produto p);
void exibirBanner();

// --- 3. Função Principal ---
int main()
{
    cout << fixed << setprecision(2);
    Produto p1, p2;

    exibirBanner();

    // CADASTRO PRODUTO 01
    cout << "\n--- Cadastro do Produto 01 ---" << endl;
    cout << "Nome: "; getline(cin >> ws, p1.nome);
    cout << "ID  : "; cin >> p1.id;
    limparBuffer(); // Garante que sobras de ponto/texto sumam aqui
    cout << "Preço: "; cin >> p1.preco;
    limparBuffer();

    // CADASTRO PRODUTO 02
    cout << "\n--- Cadastro do Produto 02 ---" << endl;
    cout << "Nome: "; getline(cin >> ws, p2.nome);
    cout << "ID  : "; cin >> p2.id;
    limparBuffer(); // Protege o próximo campo
    cout << "Preço: "; cin >> p2.preco;
    limparBuffer();

    cout << "\n===============================================" << endl;
    cout << "          RELATÓRIO FINAL DE INVENTÁRIO        " << endl;
    cout << "===============================================" << endl;
    
    exibirCabecalho();
    exibirProduto(p1);
    exibirProduto(p2);

    cout << "===============================================" << endl;

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

void exibirProduto(Produto p) {
    cout << left << setw(5) << p.id << " | "
         << left << setw(20) << p.nome << " | "
         << right << setw(12) << p.preco << endl;
}

void exibirBanner() {
    cout << "===============================================" << endl;
    cout << "       CONTROLE DE INVENTÁRIO AGRÍCOLA         " << endl;
    cout << "===============================================" << endl;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: O BUFFER DE ENTRADA (cin)
    ===============================================================
    1. O PROBLEMA:
       - O 'cin' lê apenas o que ele espera. Se você digita '9.5' em 
         um 'int', ele lê o 9 e deixa o '.5' no "cano" (buffer).
       - O próximo 'cin' vai pegar esse lixo sem perguntar ao usuário.

    2. A SOLUÇÃO (limparBuffer):
       - 'cin.clear()': Reinicia o canal de entrada se ele travou.
       - 'cin.ignore()': Joga fora os caracteres indesejados. 
       - 'numeric_limits<streamsize>::max()': Diz para ignorar o 
         máximo de caracteres possível até o '\n' (Enter).

    3. QUANDO USAR:
       - Sempre após ler números (int, double) se a próxima leitura 
         for um texto ou outro número que possa ser contaminado.
    ===============================================================
*/

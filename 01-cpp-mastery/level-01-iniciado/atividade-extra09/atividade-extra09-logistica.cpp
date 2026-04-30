/**
 * @file atividade-extra09-logistica.cpp
 * @brief Sistema de Logística (v3.0 - Alinhamento Visual Humano).
 * 
 * Versão definitiva para o terminal do Mac. Utiliza lógica bitwise para 
 * contar caracteres visuais (UTF-8) e garantir que a tabela nunca desalinhe.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória
 * - Matriz (ItemLogistica): Alocada na STACK (estática) por possuir tamanho fixo.
 * - std::string: O objeto de controle está na STACK, mas o texto longo 
 *   é alocado dinamicamente na HEAP.
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Namespace para Interface de Usuário com cores ANSI
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
}

struct ItemLogistica {
    string nome;
    long long valorCents; // Guardião Financeiro: Integridade Bancária
};

// --- 1. Protótipos das Funções ---
void exibirBanner();
void exibirMapa(const ItemLogistica armazem[3][3]);
int contarLetrasVisuais(const string& s); // Fantasma do CPU: Referência constante
void imprimirCelula(const string& s, int largura);

// --- 2. Função Principal ---
int main()
{
    ItemLogistica armazem[3][3];
    exibirBanner();

    cout << UI::AMARELO << "\n--- MAPEAMENTO DO ARMAZÉM ---" << UI::RESET << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "C" << (i + 1) << " P" << (j + 1) << " Nome : ";
            getline(cin >> ws, armazem[i][j].nome);
            if (armazem[i][j].nome.empty() || armazem[i][j].nome == "---") {
                armazem[i][j].nome = "VAZIO";
                armazem[i][j].valorCents = 0;
            } else {
                double preco;
                cout << "C" << (i + 1) << " P" << (j + 1) << " Valor (R$): ";
                cin >> preco;
                armazem[i][j].valorCents = (long long)(preco * 100 + 0.5);
            }
        }
    }

    exibirMapa(armazem);

    cout << "\nPressione Enter para finalizar...";
    cin.ignore();
    cin.get();
    return 0;
}

// --- 3. Implementação das Funções ---

/**
 * CONTA APENAS O QUE O OLHO VÊ (Ignora bytes extras de acentos).
 */
int contarLetrasVisuais(const string& s) {
    int visual = 0;
    // Fantasma do CPU: Loop com char simples (cópia de byte é desprezível)
    for (unsigned char c : s) {
        // Em UTF-8, bytes extras começam com os bits '10'.
        if ((c & 0xC0) != 0x80) visual++;
    }
    return visual;
}

/**
 * Imprime o texto e completa com espaços até a largura desejada.
 */
void imprimirCelula(const string& s, int largura) {
    int letras = contarLetrasVisuais(s);
    cout << s;
    for (int i = 0; i < (largura - letras); i++) {
        cout << " ";
    }
}

void exibirMapa(const ItemLogistica armazem[3][3]) 
{
    cout << UI::CIANO << "\n--- MAPA ATUAL DO ESTOQUE (Alinhamento Real) ---" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "CORR | PRATELEIRA 1      | PRATELEIRA 2      | PRATELEIRA 3      |" << endl;
    cout << "------------------------------------------------------------------------" << UI::RESET << endl;

    for (int i = 0; i < 3; i++) 
    {
        cout << UI::CIANO << "C" << (i + 1) << "   | " << UI::RESET;
        for (int j = 0; j < 3; j++) 
        {
            imprimirCelula(armazem[i][j].nome, 17); 
            cout << UI::CIANO << " | " << UI::RESET;
        }
        cout << endl;
        
        // Exibe os valores (Guardião Financeiro)
        cout << "     | ";
        for (int j = 0; j < 3; j++) {
            string v = "R$ " + to_string(armazem[i][j].valorCents / 100.0);
            // Corta se for muito longo para o terminal
            if(v.length() > 17) v = v.substr(0, 14) + "...";
            imprimirCelula(v, 17);
            cout << UI::CIANO << " | " << UI::RESET;
        }
        cout << endl << UI::CIANO << "------------------------------------------------------------------------" << UI::RESET << endl;
    }
}

void exibirBanner() {
    cout << UI::VERDE << "===============================================" << endl;
    cout << "       SISTEMA DE LOGÍSTICA DE ARMAZÉM         " << endl;
    cout << "===============================================" << UI::RESET << endl;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: LÓGICA DE BYTES E GUARDIÃO FINANCEIRO
    ===============================================================
    1. GUARDIÃO FINANCEIRO:
       - O uso de 'long long valorCents' protege o sistema contra 
         erros de arredondamento em matrizes de grandes estoques.

    2. FANTASMA DO CPU:
       - Passagem de matrizes e strings por referência constante 
         evita a cópia de centenas de bytes a cada chamada de função.

    3. UTF-8 BITWISE:
       - A operação '(c & 0xC0) != 0x80' é uma técnica de baixo nível 
         para identificar o início de um caractere multi-byte.
    ===============================================================
*/

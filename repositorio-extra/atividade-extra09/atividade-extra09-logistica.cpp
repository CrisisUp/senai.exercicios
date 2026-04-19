/**
 * @file atividade-extra09-logistica.cpp
 * @brief Sistema de Logística (v3.0 - Alinhamento Visual Humano).
 * 
 * Versão definitiva para o terminal do Mac. Utiliza lógica bitwise para 
 * contar caracteres visuais (UTF-8) e garantir que a tabela nunca desalinhe.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// --- 1. Protótipos das Funções ---
void exibirBanner();
void exibirMapa(string armazem[3][3]);
int contarLetrasVisuais(string s); // O segredo do alinhamento
void imprimirCelula(string s, int largura);

// --- 2. Função Principal ---
int main()
{
    string armazem[3][3];
    exibirBanner();

    cout << "\n--- MAPEAMENTO DO ARMAZÉM ---" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "C" << (i + 1) << " P" << (j + 1) << ": ";
            getline(cin >> ws, armazem[i][j]);
            if (armazem[i][j].empty()) armazem[i][j] = "---";
        }
    }

    exibirMapa(armazem);

    cout << "\nPressione Enter para finalizar...";
    cin.get();
    return 0;
}

// --- 3. Implementação das Funções ---

/**
 * CONTA APENAS O QUE O OLHO VÊ (Ignora bytes extras de acentos).
 */
int contarLetrasVisuais(string s) {
    int visual = 0;
    for (unsigned char c : s) {
        // Em UTF-8, bytes extras começam com os bits '10'.
        // Nós só contamos bytes que NÃO são extras (0x80 = 10000000).
        if ((c & 0xC0) != 0x80) visual++;
    }
    return visual;
}

/**
 * Imprime o texto e completa com espaços até a largura desejada.
 */
void imprimirCelula(string s, int largura) {
    int letras = contarLetrasVisuais(s);
    cout << s;
    // Adiciona os espaços que faltam para chegar na largura
    for (int i = 0; i < (largura - letras); i++) {
        cout << " ";
    }
}

void exibirMapa(string armazem[3][3]) 
{
    cout << "\n--- MAPA ATUAL DO ESTOQUE (Alinhamento Real) ---" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "CORR | PRATELEIRA 1    | PRATELEIRA 2    | PRATELEIRA 3    |" << endl;
    cout << "--------------------------------------------------------" << endl;

    for (int i = 0; i < 3; i++) 
    {
        cout << "C" << (i + 1) << "   | ";
        for (int j = 0; j < 3; j++) 
        {
            imprimirCelula(armazem[i][j], 15); // Cada célula tem 15 de largura
            cout << " | ";
        }
        cout << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}

void exibirBanner() {
    cout << "===============================================" << endl;
    cout << "       SISTEMA DE LOGÍSTICA DE ARMAZÉM         " << endl;
    cout << "===============================================" << endl;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: LÓGICA DE BYTES vs VISUAL
    ===============================================================
    1. O QUE APRENDEMOS:
       - 'setw' e 'length()' contam BYTES (memória). 
       - Caracteres especiais (á, õ, ç) ocupam 2 bytes. 
       - Isso quebra tabelas no terminal.

    2. A FUNÇÃO 'contarLetrasVisuais':
       - Ela analisa os bits de cada byte. Se o byte for apenas a 
         "continuação" de um acento, ela não conta como letra nova.
       - Isso garante que "café" conte como 4 e "leite" como 5.

    3. MANIPULAÇÃO MANUAL:
       - Quando as ferramentas prontas (setw) falham, o programador 
         C++ usa laços 'for' para preencher espaços manualmente.
    ===============================================================
*/

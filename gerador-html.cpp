/**
 * @file gerador-html.cpp
 * @brief Utilitário para gerar material de estudo COLORIDO (v9.0).
 * 
 * Corrige problemas de acentuação (UTF-8) para garantir que os 
 * comentários em português apareçam corretamente no navegador.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 */

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main() 
{
    string nomeArquivo;

    cout << "===============================================" << endl;
    cout << "    GERADOR DE MATERIAL DE ESTUDO (HTML UTF-8) " << endl;
    cout << "===============================================" << endl;

    cout << "Digite o nome do arquivo (sem o .cpp): ";
    cin >> nomeArquivo;

    /* 
       O COMANDO HIGHLIGHT (MODO CORREÇÃO DE ACENTOS):
       -I: Inclui o CSS (as cores) dentro do próprio arquivo
       --encoding=utf-8: GARANTE LEITURA CORRETA DE ACENTOS
    */
   
    // Comando dividido para respeitar o limite de 80 caracteres
    string comando = "/opt/homebrew/bin/highlight -O html -I "
                     "--encoding=utf-8 --font-size=14 --line-numbers "
                     "--style=base16/monokai -i " + nomeArquivo + ".cpp "
                     "-o " + nomeArquivo + ".html 2>/dev/null";

    cout << "\nColorindo o código e corrigindo acentuação..." << endl;

    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "-----------------------------------------------" << endl;
        cout << "SUCESSO: Arquivo '" << nomeArquivo << ".html' "
             << "criado com UTF-8!" << endl;
        cout << "Os acentos e a pontuação devem aparecer "
             << "corretamente." << endl;
        cout << "-----------------------------------------------" << endl;
    } else {
        cout << "ERRO: O arquivo .cpp não foi encontrado." << endl;
    }

    cout << "===============================================" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: CODIFICAÇÃO DE CARACTERES (UTF-8)
    ===============================================================

    1. O QUE É UTF-8?
       - É o padrão mundial de codificação de texto. Permite que 
         caracteres especiais (á, é, í, õ, ç) sejam representados 
         corretamente em qualquer computador.

    2. POR QUE O PROBLEMA OCORRE?
       - Se o programa não avisar que usa UTF-8, o navegador pode 
         tentar ler em outro padrão, resultando em símbolos 
         estranhos.

    3. FLAGS DE CODIFICAÇÃO:
       - O parâmetro '--encoding=utf-8' no highlight força o 
         sistema a respeitar a acentuação do código fonte.
    ===============================================================
*/

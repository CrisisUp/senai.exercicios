/**
 * @file gerador-pdf.cpp
 * @brief Utilitário DEFINITIVO de conversão CPP -> PDF (v7.0).
 * 
 * Esta versão utiliza o 'paps' de forma otimizada para o macOS,
 * garantindo a criação de arquivos PDF válidos e de alta qualidade.
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
    cout << "    GERADOR DE PDF PROFISSIONAL (VERSÃO 7.0)   " << endl;
    cout << "===============================================" << endl;

    cout << "Digite o nome do arquivo (sem o .cpp): ";
    cin >> nomeArquivo;

    /* 
       O COMANDO PAPS (MODO OTIMIZADO):
       - paps: O motor de texto para PDF
       --font="Courier New 10": Fonte padrão de alta qualidade
       --header: Nome do arquivo no topo
       --markup: Permite cores se o texto estiver formatado (opcional)
    */
    // Gerando PDF profissional direto no Mac
    string comando = "/opt/homebrew/bin/paps " + nomeArquivo + ".cpp --font=\"Courier New 11\" --header | /opt/homebrew/bin/ps2pdf - " + nomeArquivo + ".pdf 2>/dev/null";

    cout << "\nGerando PDF profissional de alta fidelidade..." << endl;

    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "SUCESSO: PDF profissional gerado com sucesso!" << endl;
    } else {
        cout << "ERRO: O arquivo não foi encontrado ou o sistema falhou." << endl;
    }

    cout << "===============================================" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: O PODER DO PAPS (v7.0)
    ===============================================================

    1. RENDERIZAÇÃO PANGO (paps):
       - O 'paps' usa a biblioteca Pango para desenhar o texto. Ela é 
         a mesma usada no Linux e no Android para renderizar letras 
         com perfeição absoluta.

    2. O SÍMBOLO PIPE ( | ) REVISITADO:
       - O pipe conecta o 'desenhista' (paps) com o 'encadernador' 
         (ps2pdf), criando um PDF sem erros de estrutura.

    3. COMPATIBILIDADE macOS:
       - Esta versão ignora o sistema de impressão do Mac (que às vezes 
         falha com HTML complexo) e usa ferramentas diretas de baixo 
         nível, tornando o gerador inquebrável.
    ===============================================================
*/

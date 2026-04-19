/**
 * @file gerador-pdf.cpp
 * @brief Utilitário DEFINITIVO de conversão CPP -> PDF (v7.1 - Bugfix).
 * 
 * Versão corrigida para validar a existência do arquivo e suportar
 * caminhos de subpastas no macOS.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream> // Necessário para verificar se o arquivo existe

using namespace std;

int main() 
{
    string caminhoArquivo;

    cout << "===============================================" << endl;
    cout << "    GERADOR DE PDF PROFISSIONAL (VERSÃO 7.1)   " << endl;
    cout << "===============================================" << endl;

    cout << "Digite o caminho/nome do arquivo (sem o .cpp): " << endl;
    cout << "Ex: repositorio-extra/atividade-extra03/atividade-extra03" << endl;
    cout << ">> ";
    cin >> caminhoArquivo;

    // Validação de segurança: Verifica se o arquivo .cpp existe
    string testeArquivo = caminhoArquivo + ".cpp";
    ifstream arquivo(testeArquivo.c_str());
    
    if (!arquivo.good()) {
        cout << "\n[ERRO]: O arquivo '" << testeArquivo << "' não foi encontrado!" << endl;
        cout << "Verifique se o caminho e o nome estão corretos." << endl;
        cout << "===============================================" << endl;
        return 1;
    }
    arquivo.close();

    // Comando PAPS (v7.0)
    string comando = "/opt/homebrew/bin/paps " + caminhoArquivo + ".cpp "
                     "--font=\"Courier New 11\" --header | "
                     "/opt/homebrew/bin/ps2pdf - " + caminhoArquivo + ".pdf 2>/dev/null";

    cout << "\nGerando PDF de alta fidelidade..." << endl;

    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "SUCESSO: PDF gerado em: " << caminhoArquivo << ".pdf" << endl;
    } else {
        cout << "ERRO: Falha crítica no motor de conversão." << endl;
    }

    cout << "===============================================" << endl;

    return 0;
}

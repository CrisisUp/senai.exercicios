/**
 * @file gerador-pdf.cpp
 * @brief Utilitário DEFINITIVO de conversão CPP -> PDF (v8.0 - Portable).
 * 
 * Versão corrigida para ser portátil entre sistemas Unix (macOS/Linux),
 * validando as dependências de sistema antes da execução.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

/**
 * @brief Verifica se um comando está disponível no PATH do sistema.
 */
bool comandoDisponivel(string comando) {
    string check = "command -v " + comando + " > /dev/null 2>&1";
    return (system(check.c_str()) == 0);
}

int main() 
{
    string caminhoArquivo;

    cout << "===============================================" << endl;
    cout << "    GERADOR DE PDF PROFISSIONAL (PORTÁTIL v8)  " << endl;
    cout << "===============================================" << endl;

    // 1. Validação de Dependências de Sistema
    bool temPaps = comandoDisponivel("paps");
    bool temPs2pdf = comandoDisponivel("ps2pdf");

    if (!temPaps || !temPs2pdf) {
        cout << "\033[31m[ERRO]: Dependências ausentes!\033[0m" << endl;
        if (!temPaps)   cout << " - Faltando: 'paps'" << endl;
        if (!temPs2pdf) cout << " - Faltando: 'ps2pdf' (Ghostscript)" << endl;
        
        cout << "\nInstalação sugerida (macOS): brew install paps ghostscript" << endl;
        cout << "Instalação sugerida (Linux): sudo apt install paps ghostscript" << endl;
        cout << "===============================================" << endl;
        return 1;
    }

    cout << "Digite o caminho/nome do arquivo (sem o .cpp): " << endl;
    cout << "Ex: repositorio-extra/atividade-extra03/atividade-extra03" << endl;
    cout << ">> ";
    cin >> caminhoArquivo;

    // 2. Validação do arquivo fonte
    string testeArquivo = caminhoArquivo + ".cpp";
    ifstream arquivo(testeArquivo.c_str());
    if (!arquivo.good()) {
        cout << "\n\033[31m[ERRO]:\033[0m O arquivo '" << testeArquivo << "' não existe!" << endl;
        return 1;
    }
    arquivo.close();

    /* 
       Comando portátil usando Pipes.
       O sistema resolve a localização dos binários via PATH.
    */
    string comando = "paps " + caminhoArquivo + ".cpp "
                     "--font=\"Courier New 11\" --header | "
                     "ps2pdf - " + caminhoArquivo + ".pdf 2>/dev/null";

    cout << "\nGerando PDF de alta fidelidade..." << endl;

    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "\033[32mSUCESSO:\033[0m PDF gerado em: " << caminhoArquivo << ".pdf" << endl;
    } else {
        cout << "\033[31mERRO:\033[0m Falha no motor de conversão PostScript." << endl;
    }

    cout << "===============================================" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: PIPELINES E DEPENDÊNCIAS
    ===============================================================

    1. O CONCEITO DE PIPE (|):
       - O símbolo '|' (pipe) envia a SAÍDA de um programa diretamente 
         para a ENTRADA de outro. Aqui, o 'paps' gera um código 
         PostScript que o 'ps2pdf' converte para PDF sem criar 
         arquivos temporários no disco.

    2. DESTRAVANDO O PATH:
       - Ao remover caminhos como '/opt/homebrew/bin/', permitimos 
         que o código rode em servidores de Integração Contínua (CI) 
         ou computadores de outros alunos que instalaram as 
         ferramentas em pastas diferentes.

    3. GHOSTSCRIPT:
       - O 'ps2pdf' faz parte do pacote Ghostscript, um motor 
         poderoso e mundialmente usado para processamento de 
         documentos digitais.
    ===============================================================
*/

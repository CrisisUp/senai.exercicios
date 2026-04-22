/**
 * @file gerador-html.cpp
 * @brief Utilitário para gerar material de estudo COLORIDO (v10.0 - Portable).
 * 
 * Versão Portátil: Remove caminhos absolutos e valida a instalação
 * das ferramentas de terceiros antes de executar.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;

/**
 * @brief Verifica se um comando está disponível no sistema.
 * @param comando Nome do executável (ex: "highlight")
 * @return true se estiver no PATH, false caso contrário.
 */
bool comandoDisponivel(string comando) {
    string check = "command -v " + comando + " > /dev/null 2>&1";
    return (system(check.c_str()) == 0);
}

int main() 
{
    string nomeArquivo;

    cout << "===============================================" << endl;
    cout << "    GERADOR DE MATERIAL (HTML PORTÁTIL v10)    " << endl;
    cout << "===============================================" << endl;

    // 1. Validação de Dependências
    if (!comandoDisponivel("highlight")) {
        cout << "\033[31m[ERRO CRÍTICO]: A ferramenta 'highlight' não foi encontrada!\033[0m" << endl;
        cout << "Instalação sugerida:" << endl;
        cout << " - macOS: brew install highlight" << endl;
        cout << " - Linux: sudo apt install highlight" << endl;
        cout << "===============================================" << endl;
        return 1;
    }

    cout << "Digite o nome do arquivo (sem o .cpp): ";
    cin >> nomeArquivo;

    /* 
       Uso de comando relativo: O sistema buscará no PATH automaticamente.
       Isso torna o código compatível com qualquer instalação padrão.
    */
    string comando = "highlight -O html -I "
                     "--encoding=utf-8 --font-size=14 --line-numbers "
                     "--style=base16/monokai -i " + nomeArquivo + ".cpp "
                     "-o " + nomeArquivo + ".html 2>/dev/null";

    cout << "\nColorindo o código com UTF-8..." << endl;

    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "-----------------------------------------------" << endl;
        cout << "\033[32mSUCESSO:\033[0m Arquivo '" << nomeArquivo << ".html' criado!" << endl;
        cout << "-----------------------------------------------" << endl;
    } else {
        cout << "\033[31mERRO:\033[0m O arquivo '" << nomeArquivo << ".cpp' não existe." << endl;
    }

    cout << "===============================================" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: PORTABILIDADE E DEPENDÊNCIAS
    ===============================================================

    1. CAMINHOS ABSOLUTOS VS. RELATIVOS:
       - Caminhos fixos (/opt/...) quebram o código em outros PCs. 
         Ao usar apenas 'highlight', deixamos o Sistema Operacional 
         resolver onde o programa está instalado através do PATH.

    2. VALIDAÇÃO DE AMBIENTE (Pre-flight Check):
       - Programas profissionais verificam se suas dependências estão 
         prontas antes de começar o trabalho pesado. Isso evita que 
         o programa "quebre no meio" de forma silenciosa.

    3. VARIÁVEIS DE AMBIENTE (PATH):
       - O PATH é uma lista de pastas que o sistema consulta quando 
         você digita um comando. Entender como o sistema localiza 
         binários é fundamental para DevOps e Engenharia de Software.

    ===============================================================
*/

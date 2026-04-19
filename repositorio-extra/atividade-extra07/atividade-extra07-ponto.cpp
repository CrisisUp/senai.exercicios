/**
 * @file atividade-extra07-ponto.cpp
 * @brief Sistema de Ponto Eletrônico (v2.0 - Com Validação de Nome).
 * 
 * Versão aprimorada que captura a data/hora e valida se o nome do 
 * funcionário não contém números, garantindo integridade dos dados.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 */

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cctype> // Necessária para validar tipos de caracteres

using namespace std;

// --- 1. Estrutura ---
struct RegistroPonto {
    string nomeFuncionario;
    int dia, mes, ano;
    int hora, min, seg;
};

// --- 2. Protótipos ---
void exibirBanner();
RegistroPonto baterPonto(string nome);
void exibirComprovante(RegistroPonto r);
bool validarNome(string nome); // Nova função de validação

// --- 3. Função Principal ---
int main()
{
    string nome;
    bool nomeValido = false;

    exibirBanner();

    // Loop de Validação: Só sai daqui quando o nome for correto
    do {
        cout << "Digite o nome completo do funcionário: ";
        getline(cin >> ws, nome);

        if (validarNome(nome)) {
            nomeValido = true;
        } else {
            cout << "[ERRO]: O nome não pode conter números. Tente novamente.\n" << endl;
        }
    } while (!nomeValido);

    RegistroPonto registro = baterPonto(nome);
    exibirComprovante(registro);

    cout << "\nPressione Enter para finalizar...";
    cin.get();

    return 0;
}

// --- 4. Implementação das Funções ---

/**
 * Verifica se o nome contém apenas letras e espaços.
 * @param nome A string digitada pelo usuário.
 * @return true se for válido, false se contiver números.
 */
bool validarNome(string nome) {
    if (nome.empty()) return false;

    for (char c : nome) {
        // Se encontrar qualquer dígito numérico, retorna falso imediatamente
        if (isdigit(c)) {
            return false;
        }
    }
    return true;
}

RegistroPonto baterPonto(string nome) 
{
    RegistroPonto r;
    r.nomeFuncionario = nome;
    time_t tempoBruto = time(0);
    tm *tempoLocal = localtime(&tempoBruto);

    r.dia  = tempoLocal->tm_mday;
    r.mes  = tempoLocal->tm_mon + 1;
    r.ano  = tempoLocal->tm_year + 1900;
    r.hora = tempoLocal->tm_hour;
    r.min  = tempoLocal->tm_min;
    r.seg  = tempoLocal->tm_sec;

    return r;
}

void exibirComprovante(RegistroPonto r) 
{
    cout << "\n===============================================" << endl;
    cout << "          COMPROVANTE DE PONTO ELETRÔNICO      " << endl;
    cout << "===============================================" << endl;
    cout << "Funcionário : " << r.nomeFuncionario << endl;
    cout << "Data        : " << setfill('0') << setw(2) << r.dia << "/" 
                            << setw(2) << r.mes << "/" << r.ano << endl;
    cout << "Horário     : " << setw(2) << r.hora << ":" 
                            << setw(2) << r.min  << ":" 
                            << setw(2) << r.seg  << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "      REGISTRO REALIZADO COM SUCESSO!          " << endl;
    cout << "===============================================" << endl;
}

void exibirBanner() 
{
    cout << "===============================================" << endl;
    cout << "        SISTEMA DE RH - CONTROLE DE PONTO      " << endl;
    cout << "===============================================" << endl;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: VALIDAÇÃO DE STRINGS (<cctype>)
    ===============================================================

    1. BIBLIOTECA <cctype>:
       - Oferece funções para testar caracteres individuais.
       - isdigit(c): Retorna verdadeiro se o caractere for um número.
       - isalpha(c): Retorna verdadeiro se for uma letra.
       - isspace(c): Retorna verdadeiro se for um espaço/tab/enter.

    2. LOOP DO-WHILE:
       - É ideal para validação de dados, pois garante que o código 
         dentro do 'do' execute pelo menos uma vez antes de testar 
         se deve repetir.

    3. RANGE-BASED FOR (for char c : nome):
       - Uma forma moderna (C++11) de percorrer cada "letra" de uma 
         string do início ao fim sem precisar de índices [i].

    ===============================================================
    TÓPICOS COMPLEMENTARES PARA O EXAME
    ===============================================================

    A. FUNÇÃO toupper() e tolower():
       - Também da <cctype>, servem para converter letras para 
         MAIÚSCULAS ou minúsculas.

    B. O TIPO 'bool':
       - É um tipo lógico que armazena apenas dois estados: true 
         (1/verdadeiro) ou false (0/falso).
    ===============================================================
*/

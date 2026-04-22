/**
 * @file atividade-extra07-ponto.cpp
 * @brief Sistema de Ponto Eletrônico (v2.0 - Com Validação de Nome).
 * 
 * Versão aprimorada que captura a data/hora e valida se o nome do 
 * funcionário não contém números, garantindo integridade dos dados.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória
 * - Struct (tm): Alocada na STACK pelo 'localtime' (estática interna 
 *   ou fornecida pelo SO).
 * - RegistroPonto: Alocada na STACK por possuir tamanho fixo.
 * - std::string: Cabeçalho na STACK, conteúdo dinâmico na HEAP.
 */

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cctype> // Necessária para validar tipos de caracteres

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
struct RegistroPonto {
    string nomeFuncionario;
    int dia, mes, ano;
    int hora, min, seg;
};

// --- 2. Protótipos ---
void exibirBanner();
RegistroPonto baterPonto(string nome);
void exibirComprovante(const RegistroPonto& r); // Fantasma do CPU: Referência constante
bool validarNome(const string& nome); // Fantasma do CPU: Referência constante

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
            cout << UI::VERMELHO << "[ERRO]: O nome não pode conter números. Tente novamente.\n" << UI::RESET << endl;
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
 * @param nome Referência constante (evita cópia desnecessária).
 * @return true se for válido, false se contiver números.
 */
bool validarNome(const string& nome) {
    if (nome.empty()) return false;

    // Fantasma do CPU: Percorrendo por referência constante
    for (const char& c : nome) {
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

void exibirComprovante(const RegistroPonto& r) 
{
    cout << UI::CIANO << "\n===============================================" << endl;
    cout << "          COMPROVANTE DE PONTO ELETRÔNICO      " << endl;
    cout << "===============================================" << UI::RESET << endl;
    cout << "Funcionário : " << UI::AMARELO << r.nomeFuncionario << UI::RESET << endl;
    cout << "Data        : " << setfill('0') << setw(2) << r.dia << "/" 
                            << setw(2) << r.mes << "/" << r.ano << endl;
    cout << "Horário     : " << setw(2) << r.hora << ":" 
                            << setw(2) << r.min  << ":" 
                            << setw(2) << r.seg  << endl;
    cout << UI::CIANO << "-----------------------------------------------" << endl;
    cout << UI::VERDE << "      REGISTRO REALIZADO COM SUCESSO!          " << endl;
    cout << UI::CIANO << "===============================================" << UI::RESET << endl;
}

void exibirBanner() 
{
    cout << UI::VERDE << "===============================================" << endl;
    cout << "        SISTEMA DE RH - CONTROLE DE PONTO      " << endl;
    cout << "===============================================" << UI::RESET << endl;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: VALIDAÇÃO E EFICIÊNCIA
    ===============================================================

    1. BIBLIOTECA <cctype>:
       - isdigit(c): Retorna verdadeiro se o caractere for um número.

    2. FANTASMA DO CPU (Referência Constante):
       - 'const string& nome': Passamos o endereço da string original 
         em vez de criar uma cópia na pilha (STACK). Essencial para 
         strings longas.

    3. RANGE-BASED FOR (for const char& c : nome):
       - Acesso direto e somente leitura aos caracteres da string, 
         evitando overhead de indexação redundante.

    ===============================================================
*/

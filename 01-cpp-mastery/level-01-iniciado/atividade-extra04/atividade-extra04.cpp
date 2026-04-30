/**
 * @file atividade-extra04.cpp
 * @brief DESAFIO 4: Sistema de Gestão de Performance de Frota.
 * 
 * Este programa consolida os conhecimentos de vetores, estatísticas,
 * busca de valores extremos e lógica condicional dinâmica para 
 * analisar o consumo de combustível de uma frota de caminhões.
 * 
 * @section MemoryMap Mapeamento de Memória (STACK):
 * - numCaminhoes (int): 4 bytes na Stack.
 * - somaConsumoCent (long): 8 bytes na Stack (Guardião Financeiro).
 * - maiorKmCent (int): 4 bytes na Stack.
 * - menorKmCent (int): 4 bytes na Stack.
 * - frotaCent (vector<int>): Objeto na Stack, dados no HEAP.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

/**
 * @namespace UI
 * @brief Gerencia a interface visual do sistema através de cores ANSI.
 */
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
}

int main()
{
    // Configuração de saída profissional
    cout << fixed << setprecision(2);

    int numCaminhoes;
    long somaConsumoCent = 0; // Guardião Financeiro: Inteiros p/ precisão
    int maiorKmCent = -1, menorKmCent = 99900; // Valores em centésimos
    int idMelhor = 0, idPior = 0;

    // --- 1. Entrada de Dados ---
    cout << UI::CIANO << "===============================================" << UI::RESET << endl;
    cout << UI::NEGRITO << "       GESTÃO DE PERFORMANCE DE FROTA          " << UI::RESET << endl;
    cout << UI::CIANO << "===============================================" << UI::RESET << endl;

    cout << "Digite a quantidade de caminhões na frota: ";
    cin >> numCaminhoes;

    if (numCaminhoes <= 0) {
        cout << UI::VERMELHO << "[ERRO]: Quantidade inválida." << UI::RESET << endl;
        return 1;
    }

    // Vetor armazenando em "centavos" (Km/L * 100)
    vector<int> frotaCent(numCaminhoes);

    // --- 2. Coleta e Processamento (O Cérebro) ---
    cout << "\n--- " << UI::AMARELO << "REGISTRO DE CONSUMO (Km/L)" << UI::RESET << " ---" << endl;
    for (int i = 0; i < numCaminhoes; i++)
    {
        double entrada;
        cout << "Caminhão #" << (i + 1) << ": ";
        cin >> entrada;

        // Conversão para o Guardião Financeiro
        frotaCent[i] = static_cast<int>(entrada * 100);

        somaConsumoCent += frotaCent[i];

        // Lógica de Maior (Mais Econômico)
        if (frotaCent[i] > maiorKmCent) {
            maiorKmCent = frotaCent[i];
            idMelhor = i + 1;
        }

        // Lógica de Menor (Mais Gastão)
        if (frotaCent[i] < menorKmCent) {
            menorKmCent = frotaCent[i];
            idPior = i + 1;
        }
    }

    double mediaFrota = (somaConsumoCent / 100.0) / numCaminhoes;

    // --- 3. Relatório Estatístico ---
    cout << "\n" << UI::CIANO << "===============================================" << UI::RESET << endl;
    cout << UI::NEGRITO << "          ESTATÍSTICAS DA FROTA                " << UI::RESET << endl;
    cout << UI::CIANO << "===============================================" << UI::RESET << endl;
    cout << "Média da Frota    : " << mediaFrota << " Km/L" << endl;
    cout << "Mais Econômico    : " << (maiorKmCent / 100.0) << " Km/L (#" 
         << idMelhor << ")" << endl;
    cout << "Mais Gastão       : " << (menorKmCent / 100.0) << " Km/L (#" 
         << idPior << ")" << endl;
    cout << "Amplitude Consumo : " << (maiorKmCent - menorKmCent) / 100.0 << " Km/L" << endl;
    cout << "-----------------------------------------------" << endl;

    // --- 4. Relatório de Inspeção Individual ---
    cout << "\n--- " << UI::AMARELO << "ANÁLISE INDIVIDUAL" << UI::RESET << " ---" << endl;
    for (int i = 0; i < numCaminhoes; i++)
    {
        double kmL = frotaCent[i] / 100.0;
        cout << "Caminhão #" << setw(2) << (i + 1) << ": " 
             << setw(6) << kmL << " Km/L ";

        // Regras de Negócio Dinâmicas
        if (kmL < (mediaFrota * 0.80)) {
            cout << UI::VERMELHO << "[CRÍTICO: REVISÃO]" << UI::RESET;
        } else if (kmL > mediaFrota) {
            cout << UI::VERDE << "[ÓTIMO DESEMPENHO]" << UI::RESET;
        } else {
            cout << UI::AZUL << "[DESEMPENHO REGULAR]" << UI::RESET;
        }
        cout << endl;
    }

    // --- 5. Simulação de Viagem (Extra) ---
    double litrosViagem = 500.0 / (maiorKmCent / 100.0);
    cout << "\n" << UI::CIANO << "-----------------------------------------------" << UI::RESET << endl;
    cout << UI::NEGRITO << "SIMULAÇÃO: Viagem de 500 Km (Melhor Caminhão)" << UI::RESET << endl;
    cout << "Combustível Estimado: " << UI::VERDE << litrosViagem << " Litros" << UI::RESET << endl;
    cout << UI::CIANO << "===============================================" << UI::RESET << endl;

    cout << "\nPressione Enter para finalizar...";
    cin.ignore();
    cin.get();

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO PARA EXAME FINAL (CONSOLIDAÇÃO)
    ===============================================================

    1. GUARDIÃO FINANCEIRO (INTEGRIDADE):
       - Transformar valores decimais em inteiros (multiplicando por 100) 
         garante que operações de soma acumulada não sofram com a 
         imprecisão binária do ponto flutuante.

    2. NAMESPACE UI (ARQUITETURA):
       - Isolar elementos de interface em um namespace próprio facilita 
         a transição futura para outras bibliotecas gráficas.

    3. LÓGICA DE EXTREMOS DUPLOS:
       - Para encontrar Maior e Menor simultaneamente, usamos dois 
         'ifs' independentes dentro do mesmo loop.

    4. CÁLCULO DE AMPLITUDE:
       - Diferença entre o maior e o menor valor, indicando a dispersão 
         dos dados de consumo.

    ===============================================================
    TÓPICOS COMPLEMENTARES PARA O EXAME
    ===============================================================

    A. CONSTANTES (const):
       - O uso de 'const string' no namespace UI protege os códigos de 
         cores de modificações acidentais.

    B. TIPO 'long':
       - Essencial quando trabalhamos com acumuladores que podem 
         ultrapassar o limite de 2 bilhões do 'int' padrão.

    C. VALIDAÇÃO DE ENTRADA (cin.fail):
       - O uso de 'if (numCaminhoes <= 0)' e a detecção de falha na 
         leitura são pilares de um código de nível "Elite".
    ===============================================================
*/

/**
 * @file atividade-extra04.cpp
 * @brief DESAFIO 4: Sistema de Gestão de Performance de Frota.
 * 
 * Este programa consolida os conhecimentos de vetores, estatísticas,
 * busca de valores extremos e lógica condicional dinâmica para 
 * analisar o consumo de combustível de uma frota de caminhões.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 */

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
    // Configuração de saída profissional
    cout << fixed << setprecision(2);

    int numCaminhoes;
    double somaConsumo = 0.0, mediaFrota = 0.0;
    double maiorKm = -1.0, menorKm = 999.0;
    int idMelhor = 0, idPior = 0;

    // --- 1. Entrada de Dados ---
    cout << "===============================================" << endl;
    cout << "       GESTÃO DE PERFORMANCE DE FROTA          " << endl;
    cout << "===============================================" << endl;

    cout << "Digite a quantidade de caminhões na frota: ";
    cin >> numCaminhoes;

    if (numCaminhoes <= 0) {
        cout << "[ERRO]: Quantidade inválida." << endl;
        return 1;
    }

    vector<double> frota(numCaminhoes);

    // --- 2. Coleta e Processamento (O Cérebro) ---
    cout << "\n--- REGISTRO DE CONSUMO (Km/L) ---" << endl;
    for (int i = 0; i < numCaminhoes; i++)
    {
        cout << "Caminhão #" << (i + 1) << ": ";
        cin >> frota[i];

        somaConsumo += frota[i];

        // Lógica de Maior (Mais Econômico)
        if (frota[i] > maiorKm) {
            maiorKm = frota[i];
            idMelhor = i + 1;
        }

        // Lógica de Menor (Mais Gastão)
        if (frota[i] < menorKm) {
            menorKm = frota[i];
            idPior = i + 1;
        }
    }

    mediaFrota = somaConsumo / numCaminhoes;

    // --- 3. Relatório Estatístico ---
    cout << "\n===============================================" << endl;
    cout << "          ESTATÍSTICAS DA FROTA                " << endl;
    cout << "===============================================" << endl;
    cout << "Média da Frota    : " << mediaFrota << " Km/L" << endl;
    cout << "Mais Econômico    : " << maiorKm << " Km/L (#" 
         << idMelhor << ")" << endl;
    cout << "Mais Gastão       : " << menorKm << " Km/L (#" 
         << idPior << ")" << endl;
    cout << "Amplitude Consumo : " << (maiorKm - menorKm) << " Km/L" << endl;
    cout << "-----------------------------------------------" << endl;

    // --- 4. Relatório de Inspeção Individual ---
    cout << "\n--- ANÁLISE INDIVIDUAL ---" << endl;
    for (int i = 0; i < numCaminhoes; i++)
    {
        cout << "Caminhão #" << setw(2) << (i + 1) << ": " 
             << setw(6) << frota[i] << " Km/L ";

        // Regras de Negócio Dinâmicas
        if (frota[i] < (mediaFrota * 0.80)) {
            cout << "[CRÍTICO: REVISÃO]";
        } else if (frota[i] > mediaFrota) {
            cout << "[ÓTIMO DESEMPENHO]";
        } else {
            cout << "[DESEMPENHO REGULAR]";
        }
        cout << endl;
    }

    // --- 5. Simulação de Viagem (Extra) ---
    double litrosViagem = 500.0 / maiorKm;
    cout << "\n-----------------------------------------------" << endl;
    cout << "SIMULAÇÃO: Viagem de 500 Km (Melhor Caminhão)" << endl;
    cout << "Combustível Estimado: " << litrosViagem << " Litros" << endl;
    cout << "===============================================" << endl;

    cout << "\nPressione Enter para finalizar...";
    cin.ignore();
    cin.get();

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO PARA EXAME FINAL (CONSOLIDAÇÃO)
    ===============================================================

    1. LÓGICA DE EXTREMOS DUPLOS:
       - Para encontrar Maior e Menor simultaneamente, usamos dois 
         'ifs' independentes dentro do mesmo loop.
       - Menor: Inicialize com um valor muito alto.
       - Maior: Inicialize com zero ou valor muito baixo.

    2. CÁLCULO DE AMPLITUDE:
       - Em estatística, é a diferença entre o maior e o menor valor. 
         Útil para ver a variação de qualidade em uma frota.

    3. CONDICIONAIS COM PORCENTAGEM:
       - Podemos usar matemática dentro do 'if'. 
         Ex: if (valor < (media * 0.8)).

    4. SIMULAÇÃO DE VARIÁVEIS:
       - O programa usa dados processados (maiorKm) para prever 
         resultados futuros (litros para 500km).

    ===============================================================
    TÓPICOS COMPLEMENTARES PARA O EXAME
    ===============================================================

    A. CONSTANTES (const):
       - Se o valor '500.0' da viagem for fixo, poderíamos usar:
         const double DISTANCIA_PADRAO = 500.0;
       - Isso protege o valor de ser alterado acidentalmente.

    B. TIPO 'long double':
       - Para precisão ainda maior que 'double', usado em cálculos 
         astronômicos ou científicos complexos.

    C. VALIDAÇÃO DE ENTRADA:
       - O uso de 'if (numCaminhoes <= 0)' evita que o programa tente 
         criar um vetor vazio ou divida por zero.
    ===============================================================
*/

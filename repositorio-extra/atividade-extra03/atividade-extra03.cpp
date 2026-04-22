/**
 * @file atividade3-producao.cpp
 * @brief Sistema de Monitoramento e Estatística de Produção Leiteira.
 * 
 * Este programa gerencia a produção diária de um rebanho, calculando
 * a produção total, a média do dia e identificando o animal com a
 * maior produtividade (campeã do dia).
 * 
 * @section MemoryMap Mapeamento de Memória (STACK):
 * - numVacas (int): 4 bytes na Stack.
 * - totalMililitros (long): 8 bytes na Stack (Guardião Financeiro).
 * - mediaProducao (float): 4 bytes na Stack.
 * - maiorMililitros (int): 4 bytes na Stack.
 * - vacaCampeã (int): 4 bytes na Stack.
 * - producao (vector<int>): Objeto na Stack, dados no HEAP.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 */

#include <iostream> // Entrada e saída de dados
#include <vector>   // Uso de vetores dinâmicos
#include <iomanip>  // Formatação de precisão decimal e alinhamento
#include <string>

using namespace std;

/**
 * @namespace UI
 * @brief Gerencia a interface visual do sistema através de cores ANSI.
 */
namespace UI {
    const string RESET   = "\033[0m";
    const string BOLD    = "\033[1m";
    const string RED     = "\033[31m";
    const string GREEN   = "\033[32m";
    const string YELLOW  = "\033[33m";
    const string BLUE    = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN    = "\033[36m";
}

int main()
{
    // Configuração de saída: 2 casas decimais fixas
    cout << fixed << setprecision(2);

    int numVacas;
    long totalMililitros = 0; // Guardião Financeiro: Inteiros p/ precisão
    int maiorMililitros = -1;
    int vacaCampeã = 0;

    // --- 1. Entrada de Configurações ---
    cout << UI::CYAN << "===============================================" << UI::RESET << endl;
    cout << UI::BOLD << "      MONITORAMENTO DE PRODUÇÃO LEITEIRA       " << UI::RESET << endl;
    cout << UI::CYAN << "===============================================" << UI::RESET << endl;

    cout << "Digite a quantidade de vacas no rebanho: ";
    cin >> numVacas;

    // Inicialização do vetor com o tamanho definido pelo usuário
    // Armazenamos em mililitros (int) para garantir integridade dos dados
    vector<int> producaoMililitros(numVacas);

    // --- 2. Coleta de Dados e Processamento Inicial ---
    cout << "\n--- " << UI::YELLOW << "REGISTRO DE PRODUÇÃO DIÁRIA" << UI::RESET << " ---" << endl;
    for (int i = 0; i < numVacas; i++)
    {
        float entradaLitros;
        cout << "Produção da vaca " << (i + 1) << " (litros): ";
        cin >> entradaLitros;

        // Conversão para o Guardião Financeiro (L -> ml)
        producaoMililitros[i] = static_cast<int>(entradaLitros * 1000);

        // Acumulando o total para cálculo da média posterior
        totalMililitros += producaoMililitros[i];

        // Lógica para encontrar a maior produção (Campeã)
        if (producaoMililitros[i] > maiorMililitros)
        {
            maiorMililitros = producaoMililitros[i];
            vacaCampeã = i + 1;
        }
    }

    // Cálculo da média (convertendo de volta para float apenas na exibição)
    float mediaProducaoLitros = 0.0;
    if (numVacas > 0) mediaProducaoLitros = (totalMililitros / 1000.0) / numVacas;

    // --- 3. Relatório Estatístico ---
    cout << "\n" << UI::CYAN << "===============================================" << UI::RESET << endl;
    cout << UI::BOLD << "          RELATÓRIO DE DESEMPENHO              " << UI::RESET << endl;
    cout << UI::CYAN << "===============================================" << UI::RESET << endl;
    cout << "Produção Total : " << (totalMililitros / 1000.0) << " litros" << endl;
    cout << "Média Diária   : " << mediaProducaoLitros << " litros" << endl;
    cout << "Vaca Campeã    : Vaca " << vacaCampeã << " (" 
         << (maiorMililitros / 1000.0) << " L)" << endl;
    cout << "-----------------------------------------------" << endl;

    // --- 4. Relatório de Inspeção Individual ---
    for (int i = 0; i < numVacas; i++)
    {
        float litrosVaca = producaoMililitros[i] / 1000.0;
        cout << "Vaca " << setw(2) << (i + 1) << ": " 
             << setw(6) << litrosVaca << " L";

        // Comparação dinâmica com a média calculada
        if (litrosVaca < mediaProducaoLitros)
        {
            cout << UI::RED << " [ALERTA: DESEMPENHO BAIXO]" << UI::RESET;
        }
        else 
        {
            cout << UI::GREEN << " [OK]" << UI::RESET;
        }
        cout << endl;
    }
    cout << UI::CYAN << "===============================================" << UI::RESET << endl;

    // --- 5. Finalização ---
    cout << "\nPressione Enter para finalizar...";
    cin.ignore();
    cin.get();

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO PARA EXAME FINAL (ESTATÍSTICA E ALGORITMOS)
    ===============================================================

    1. GUARDIÃO FINANCEIRO (INTEGRIDADE):
       - Uso de inteiros para representar valores decimais (ex: mililitros 
         em vez de litros) para evitar erros de arredondamento inerentes 
         ao tipo 'float' e 'double'.
       - Regra: Multiplicar por 1000 na entrada e dividir por 1000.0 na exibição.

    2. NAMESPACE UI (ORGANIZAÇÃO):
       - Agrupar constantes de cores ANSI em um 'namespace' evita poluir 
         o escopo global e facilita a manutenção da interface.

    3. ACUMULADORES (Soma Total):
       - Uma variável (geralmente inicializada com 0) que recebe ela 
         mesma mais um novo valor a cada volta do loop.

    4. BUSCA DE MAIOR/MENOR VALOR:
       - Técnica do "Rei da Montanha": Criamos uma variável para guardar 
         o maior valor visto até agora. A cada iteração, comparamos o 
         item atual com esse "rei".

    ===============================================================
    TÓPICOS COMPLEMENTARES PARA O EXAME
    ===============================================================

    A. INICIALIZAÇÃO DE SENTINELAS:
       - Ao procurar o maior valor, podemos inicializar a variável com 
         o primeiro elemento do vetor ou com um número impossível (-1).

    B. PRECISÃO DE DADOS (long vs float):
       - O tipo 'long' (inteiro) oferece 100% de precisão para operações 
         de soma acumulada, evitando os erros de ponto flutuante.

    C. ESTADO DE FALHA (cin.fail):
       - Se o usuário digitar texto onde se espera número, o 'cin' entra 
         em erro. Validar a entrada é essencial para sistemas robustos.
    ===============================================================
*/

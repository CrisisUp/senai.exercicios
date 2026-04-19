/**
 * @file atividade3-producao.cpp
 * @brief Sistema de Monitoramento e Estatística de Produção Leiteira.
 * 
 * Este programa gerencia a produção diária de um rebanho, calculando
 * a produção total, a média do dia e identificando o animal com a
 * maior produtividade (campeã do dia).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 */

#include <iostream> // Entrada e saída de dados
#include <vector>   // Uso de vetores dinâmicos
#include <iomanip>  // Formatação de precisão decimal e alinhamento

using namespace std;

int main()
{
    // Configuração de saída: 2 casas decimais fixas
    cout << fixed << setprecision(2);

    int numVacas;
    float totalProducao = 0.0, mediaProducao = 0.0;
    float maiorProducao = -1.0; // Inicializamos com valor impossível
    int vacaCampeã = 0;

    // --- 1. Entrada de Configurações ---
    cout << "===============================================" << endl;
    cout << "      MONITORAMENTO DE PRODUÇÃO LEITEIRA       " << endl;
    cout << "===============================================" << endl;

    cout << "Digite a quantidade de vacas no rebanho: ";
    cin >> numVacas;

    // Inicialização do vetor com o tamanho definido pelo usuário
    vector<float> producao(numVacas);

    // --- 2. Coleta de Dados e Processamento Inicial ---
    cout << "\n--- REGISTRO DE PRODUÇÃO DIÁRIA ---" << endl;
    for (int i = 0; i < numVacas; i++)
    {
        cout << "Produção da vaca " << (i + 1) << " (litros): ";
        cin >> producao[i];

        // Acumulando o total para cálculo da média posterior
        totalProducao += producao[i];

        // Lógica para encontrar a maior produção (Campeã)
        if (producao[i] > maiorProducao)
        {
            maiorProducao = producao[i];
            vacaCampeã = i + 1;
        }
    }

    // Cálculo da média
    if (numVacas > 0) mediaProducao = totalProducao / numVacas;

    // --- 3. Relatório Estatístico ---
    cout << "\n===============================================" << endl;
    cout << "          RELATÓRIO DE DESEMPENHO              " << endl;
    cout << "===============================================" << endl;
    cout << "Produção Total : " << totalProducao << " litros" << endl;
    cout << "Média Diária   : " << mediaProducao << " litros" << endl;
    cout << "Vaca Campeã    : Vaca " << vacaCampeã << " (" 
         << maiorProducao << " L)" << endl;
    cout << "-----------------------------------------------" << endl;

    // --- 4. Relatório de Inspeção Individual ---
    for (int i = 0; i < numVacas; i++)
    {
        cout << "Vaca " << setw(2) << (i + 1) << ": " 
             << setw(6) << producao[i] << " L";

        // Comparação dinâmica com a média calculada
        if (producao[i] < mediaProducao)
        {
            cout << " [ALERTA: DESEMPENHO BAIXO]";
        }
        else 
        {
            cout << " [OK]";
        }
        cout << endl;
    }
    cout << "===============================================" << endl;

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

    1. ACUMULADORES (Soma Total):
       - Uma variável (geralmente inicializada com 0) que recebe ela 
         mesma mais um novo valor a cada volta do loop.
       - Sintaxe: total += valor;

    2. CÁLCULO DE MÉDIA:
       - A média aritmética é a soma de todos os elementos dividida 
         pela quantidade total de elementos. 
       - IMPORTANTE: Sempre verifique se o divisor não é zero!

    3. BUSCA DE MAIOR/MENOR VALOR:
       - Técnica do "Rei da Montanha": Criamos uma variável para guardar 
         o maior valor visto até agora. A cada iteração, comparamos o 
         item atual com esse "rei". Se o atual for maior, ele assume 
         o trono.

    4. COMPARAÇÃO COM VARIÁVEIS DINÂMICAS:
       - Diferente dos exercícios anteriores onde a meta era fixa, 
         aqui o limite (média) é calculado pelo próprio programa 
         antes de ser usado na comparação do relatório.

    ===============================================================
    TÓPICOS COMPLEMENTARES PARA O EXAME
    ===============================================================

    A. INICIALIZAÇÃO DE SENTINELAS:
       - Ao procurar o maior valor, podemos inicializar a variável com 
         o primeiro elemento do vetor ou com um número muito pequeno.

    B. PRECISÃO DE DADOS (float vs double):
       - Litros de leite não exigem precisão financeira, por isso o 
         'float' (7 casas decimais) é suficiente e economiza memória.

    C. FORMATAÇÃO COM 'setw':
       - O 'setw' (Set Width) garante que as colunas fiquem alinhadas 
         mesmo quando passamos de 9 para 10 vacas (unidades p/ dezenas).
    ===============================================================
*/

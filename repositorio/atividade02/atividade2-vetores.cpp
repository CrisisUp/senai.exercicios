/**
 * @file atividade2-vetores.cpp
 * @brief Sistema de Controle de Irrigação e Monitoramento de Ração.
 * 
 * Este programa permite ao usuário gerenciar a alimentação de currais,
 * registrando a quantidade de ração fornecida e comparando-a com uma
 * meta mínima estabelecida, alertando sobre possíveis irregularidades.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 */

#include <iostream> // Permite a entrada e saída de dados (cin, cout, endl)
#include <vector>   // Permite o uso de vetores dinâmicos, que se ajustam ao 
                    // tamanho definido pelo usuário
#include <iomanip>  // Oferece ferramentas de formatação para alinhar tabelas 
                    // e fixar casas decimais


using namespace std;

int main()
{
    // Configuração da formatação de saída para 2 casas decimais
    cout << fixed << setprecision(2);

    // Variáveis de configuração do sistema
    int numCurrais;
    float minimoRacao;

    // --- 1. Entrada de Configurações Iniciais ---
    cout << "===============================================" << endl;
    cout << "   SISTEMA DE CONTROLE DE RAÇÃO - FAZENDA      " << endl;
    cout << "===============================================" << endl;
    
    cout << "Digite a quantidade de currais: ";
    cin >> numCurrais;

    cout << "Digite a meta mínima de ração (kg) por curral: ";
    cin >> minimoRacao;

    // --- 2. Inicialização do Vetor ---
    // Uso de vector para permitir tamanho dinâmico conforme escolha do usuário
    vector<float> racaoCurrais(numCurrais);

    // --- 3. Coleta de Dados dos Currais ---
    cout << "\n--- REGISTRO DE DADOS ---" << endl;
    for (int i = 0; i < numCurrais; i++)
    {
        cout << "Ração fornecida no curral " << (i + 1) << " (kg): ";
        cin >> racaoCurrais[i];
    }

    // --- 4. Processamento e Relatório de Inspeção ---
    cout << "\n--- RELATÓRIO DE INSPEÇÃO ---" << endl;
    cout << "Meta estabelecida: " << minimoRacao << " kg" << endl;
    cout << "-----------------------------------------------" << endl;

    for (int i = 0; i < numCurrais; i++)
    {
        cout << "Curral " << setw(2) << (i + 1) << ": " 
             << setw(6) << racaoCurrais[i] << " kg";

   // Lógica de Alerta: Verifica se o valor está abaixo do limite de segurança
        if (racaoCurrais[i] < minimoRacao)
        {
            cout << " [ALERTA: ABAIXO DA META!]";
        }
        else 
        {
            cout << " [OK]";
        }

        cout << endl;
    }
    cout << "-----------------------------------------------" << endl;

    return 0;
}

/* 
    ============================================================================
    RESUMO TEÓRICO PARA EXAME FINAL (C++ VETORES E LOOPS)
    ============================================================================

    1. VETORES DINÂMICOS (std::vector):
       - Diferente de um array comum [ ], o 'vector' permite definir 
         seu tamanho durante a execução do programa (tempo de execução).
       - Sintaxe: vector<tipo> nome(tamanho);
       - Vantagem: Gerenciamento automático de memória e flexibilidade.

    2. ESTRUTURAS DE REPETIÇÃO (Loop for):
       - Usado para percorrer todos os elementos de um vetor.
       - for (inicio; condição; incremento)
       - No C++, a contagem de posições (índices) SEMPRE começa em 0.

    3. ALINHAMENTO DE TABELAS (setw):
       - 'setw(n)': Define a largura de campo para o próximo item a ser 
       impresso.

    4. LÓGICA DE INSPEÇÃO (Decisão em Loop):
       - Podemos colocar estruturas 'if' dentro de 'for' para analisar 
         cada item individualmente enquanto a lista é percorrida.

    5. ACESSO AOS ELEMENTOS:
       - Usamos colchetes [ i ] para acessar ou gravar um valor em uma 
         posição específica do vetor.

    ============================================================================
    TÓPICOS COMPLEMENTARES PARA O EXAME (NÃO USADOS NESTE CÓDIGO)
    ============================================================================

    A. OUTROS TIPOS DE LOOPS:
       - while (condição): Executa enquanto a condição for verdadeira. 
         Útil quando não sabemos quantas vezes o loop vai rodar.
       - do-while: Similar ao while, mas garante que o código rode 
         PELO MENOS UMA VEZ antes de testar a condição.
       - Range-based for (C++11): Uma forma moderna de percorrer vetores:
         for (float r : racaoCurrais) { cout << r; }

    B. MÉTODOS IMPORTANTES DE VECTOR:
       - .size(): Retorna a quantidade de elementos no vetor.
       - .push_back(valor): Adiciona um novo item ao final do vetor.
       - .pop_back(): Remove o último item do vetor.
       - .clear(): Apaga todos os itens do vetor.
       - .at(índice): Acesso mais seguro que [ ], pois avisa se o índice não 
       existe.

    C. ARRAYS ESTÁTICOS (ANTIGOS):
       - tipo nome[TAMANHO_FIXO];
       - Ex: int notas[10]; // O tamanho deve ser um número fixo, não uma 
       variável.

    D. BIBLIOTECA <algorithm>:
       - Permite usar funções prontas como sort() para ordenar o vetor 
         ou reverse() para inverter a ordem dos elementos.
    ============================================================================
*/

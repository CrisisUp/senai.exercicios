/**
 * @file atividade1-vetores.cpp
 * @brief Sistema de Análise e Controle de Estoque.
 * 
 * Este programa realiza a gestão básica de estoque, verificando se a 
 * quantidade atual atende ao mínimo necessário. Caso falte produto, 
 * o sistema calcula a reposição necessária e o custo total.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 15/04/2026
 */

#include <iostream> // Permite entrada e saída de dados (cin, cout, endl)
#include <iomanip>  // Necessário para formatação de moeda e alinhamento

using namespace std; // Define uso do escopo padrão para evitar prefixo 'std::'

int main()
{
    // Configuração para exibir valores monetários com 2 casas decimais
    cout << fixed << setprecision(2);

    // Variáveis do sistema
    int estoqueAtual, quantidadeMinima, quantidadeReposicao;
    double precoUnitario, custoTotal;

    // --- 1. Entrada de Dados ---
    cout << "===============================================" << endl;
    cout << "       SISTEMA DE ANÁLISE DE ESTOQUE           " << endl;
    cout << "===============================================" << endl;

    cout << "Digite a quantidade atual em estoque: ";
    cin >> estoqueAtual;

    cout << "Digite a quantidade mínima ideal: ";
    cin >> quantidadeMinima;

    cout << "Digite o preço unitário do produto (R$): ";
    cin >> precoUnitario;

    // --- 2. Processamento e Verificação ---
    cout << "\n          --- RESULTADO DA ANÁLISE ---" << endl;

    if (estoqueAtual < quantidadeMinima)
    {
        // Cálculo de reposição
        quantidadeReposicao = quantidadeMinima - estoqueAtual;
        custoTotal = quantidadeReposicao * precoUnitario;

        // --- 3. Exibição (Necessário Repor) ---
        cout << "        STATUS: [ REPOSIÇÃO NECESSÁRIA ]" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Quantidade em falta: " << quantidadeReposicao << " unidades." << endl;
        cout << "Custo da reposição : R$ " << custoTotal << endl;
    }
    else
    {
        // --- 3. Exibição (Estoque OK) ---
        cout << "         STATUS: [ ESTOQUE SUFICIENTE ]" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Nenhuma ação de compra é necessária no momento." << endl;
    }

    cout << "===============================================" << endl;

    // --- 4. Finalização do Programa ---
    cout << "\nPressione Enter para finalizar...";
    cin.ignore(); // Limpa o buffer do teclado
    cin.get();    // Aguarda o usuário pressionar Enter

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO PARA EXAME FINAL (C++ FUNDAMENTOS)
    ===============================================================

    1. BIBLIOTECAS (INCLUDES):
       - <iostream>: Biblioteca padrão para Fluxos de Entrada e Saída.
       - <iomanip>: "Input/Output Manipulation". Usada para formatar como 
         os dados aparecem (casas decimais, alinhamento).

    2. NAMESPACE:
       - 'using namespace std;': Evita a necessidade de escrever 'std::' 
         antes de cada comando (cout, cin, endl).

    3. VARIÁVEIS E TIPOS DE DADOS:
       - int: Números inteiros (ex: quantidade de estoque).
       - double: Números de precisão dupla (decimais). Ideal para cálculos 
         financeiros por ser mais preciso que o 'float'.

    4. FORMATAÇÃO DE SAÍDA (iomanip):
       - 'fixed': Trava o ponto decimal em uma posição fixa.
       - 'setprecision(n)': Define quantas casas decimais aparecerão.

    5. ESTRUTURA CONDICIONAL (if-else):
       - if (condição): Executa um bloco de código se a condição for VERDADEIRA.
       - else: Executa um bloco alternativo se a condição for FALSA.

    6. OPERADORES ARITMÉTICOS:
       - Subtração (-): Usada para calcular a falta (mínimo - atual).
       - Multiplicação (*): Usada para calcular custo total (quant * preço).

    7. MANIPULAÇÃO DE BUFFER:
       - cin.ignore(): Limpa caracteres residuais do teclado.
       - cin.get(): Pausa a execução e aguarda interação do usuário.

    ===============================================================
    TÓPICOS COMPLEMENTARES PARA O EXAME (NÃO USADOS NESTE CÓDIGO)
    ===============================================================

    A. OUTROS TIPOS DE DADOS:
       - float: Decimal de precisão simples.
       - char: Armazena um único caractere (ex: 'A'). Usa aspas simples.
       - string: Armazena textos (ex: "Cristiano"). Usa aspas duplas.
       - bool: Valores lógicos (true ou false).

    B. OPERADORES LÓGICOS (PARA CONDIÇÕES COMPLEXAS):
       - && (E): Verdadeiro apenas se AMBAS as condições forem reais.
       - || (OU): Verdadeiro se PELO MENOS UMA condição for real.
       - ! (NÃO): Inverte o valor da condição.

    C. SWITCH-CASE (ALTERNATIVA AO IF-ELSE):
       - Usado para testar uma única variável contra vários valores fixos.

    D. OPERADOR TERNÁRIO:
       - Uma forma curta de fazer um if-else em uma linha:
         (condição) ? valor_se_verdadeiro : valor_se_falso;
    ===============================================================
*/

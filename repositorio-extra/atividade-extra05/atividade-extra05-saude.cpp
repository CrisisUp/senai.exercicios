/**
 * @file atividade-extra05-saude.cpp
 * @brief Sistema de Monitoramento de Saúde (IMC e Hidratação).
 * 
 * Este programa demonstra o uso de FUNÇÕES para modularizar o código,
 * separando a lógica de exibição, cálculo de IMC e recomendação
 * hídrica em blocos reutilizáveis.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 */

#include <iostream>
#include <iomanip>

using namespace std;

// --- 1. Protótipos das Funções (Declaração) ---
void exibirBanner();
double calcularIMC(double peso, double altura);
double recomendarAgua(double peso);

// --- 2. Função Principal (Fluxo do Programa) ---
int main()
{
    // Configuração de saída
    cout << fixed << setprecision(2);

    double pesoUser, alturaUser;

    // Chamada de função sem retorno (void)
    exibirBanner();

    // Coleta de dados
    cout << "Digite o seu peso (kg): ";
    cin >> pesoUser;
    cout << "Digite a sua altura (m): ";
    cin >> alturaUser;

    // Chamada de funções com retorno (armazenando em variáveis)
    double imc = calcularIMC(pesoUser, alturaUser);
    double litrosAgua = recomendarAgua(pesoUser);

    // Relatório Final
    cout << "\n===============================================" << endl;
    cout << "          RELATÓRIO DE SAÚDE INDIVIDUAL        " << endl;
    cout << "===============================================" << endl;
    cout << "Seu IMC atual é    : " << imc << endl;
    cout << "Meta de Água/Dia   : " << litrosAgua << " Litros" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "DICA: Mantenha-se sempre hidratado!" << endl;
    cout << "===============================================" << endl;

    cout << "\nPressione Enter para finalizar...";
    cin.ignore();
    cin.get();

    return 0;
}

// --- 3. Implementação das Funções ---

/**
 * Exibe o cabeçalho estilizado do sistema.
 * Tipo void: Não retorna valor, apenas executa comandos.
 */
void exibirBanner() 
{
    cout << "===============================================" << endl;
    cout << "       SISTEMA DE APOIO À SAÚDE CLÍNICA        " << endl;
    cout << "===============================================" << endl;
}

/**
 * Calcula o Índice de Massa Corporal.
 * @param peso Peso em kg.
 * @param altura Altura em metros.
 * @return O valor do IMC calculado.
 */
double calcularIMC(double peso, double altura) 
{
    // Fórmula: IMC = peso / altura²
    return peso / (altura * altura);
}

/**
 * Calcula a recomendação de água baseada no peso.
 * @param peso Peso em kg.
 * @return Quantidade de litros recomendada.
 */
double recomendarAgua(double peso) 
{
    // Cálculo: 35ml (0.035L) por cada quilo de peso
    return peso * 0.035;
}

/* 
    ===============================================================
    RESUMO TEÓRICO PARA EXAME FINAL (FUNÇÕES / MODULARIZAÇÃO)
    ===============================================================

    1. O QUE SÃO FUNÇÕES?
       - São blocos de código independentes que realizam uma tarefa 
         específica. Elas ajudam a manter o código organizado.

    2. TIPO VOID (Sem Retorno):
       - Usado quando a função apenas executa algo (como imprimir 
         na tela) e não precisa devolver um número ou texto.

    3. FUNÇÕES COM RETORNO (double, int, etc):
       - Usam a palavra-chave 'return' para enviar um resultado de 
         volta para quem a chamou (ex: para a função main).

    4. PARÂMETROS:
       - São as "informações" que a função precisa para trabalhar. 
         Ficam entre os parênteses (ex: peso, altura).

    5. REUTILIZAÇÃO:
       - Uma vez criada, a função 'calcularIMC' pode ser usada em 
         qualquer parte do programa, quantas vezes for necessário.

    ===============================================================
    TÓPICOS COMPLEMENTARES PARA O EXAME
    ===============================================================

    A. ESCOPO DE VARIÁVEIS:
       - Variáveis criadas dentro de uma função são LOCAIS. Elas não 
         existem fora daquela função.

    B. PASSAGEM POR VALOR vs REFERÊNCIA:
       - Por padrão, o C++ faz uma "cópia" do valor para a função. 
         (Aprenderemos 'referência' em atividades futuras).

    C. DOCUMENTAÇÃO (Doxygen):
       - O uso de blocos de comentários específicos em cima das funções 
         é um padrão de documentação profissional usado para gerar manuais.

    ===============================================================
*/

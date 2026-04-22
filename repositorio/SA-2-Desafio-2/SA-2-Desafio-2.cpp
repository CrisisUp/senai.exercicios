/**
 * @file SA-2-Desafio-2.cpp
 * @brief Sistema de Análise de Consumo de Água por Setor.
 * 
 * Este programa coleta dados de consumo de água de diferentes setores
 * de uma fazenda e gera um relatório consolidado.
 * 
 * @author Cristiano Batista Pessoa
 * @date 19/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória
 * As variáveis primitivas (int, double) estão alocadas na STACK (estática) 
 * por possuírem tamanho fixo conhecido em tempo de compilação.
 */

#include <iostream>
#include <vector>
#include <iomanip> // Para formatação de saída

// Namespace para Interface de Usuário com cores ANSI
namespace UI {
    const std::string RESET = "\033[0m";
    const std::string VERDE = "\033[32m";
    const std::string VERMELHO = "\033[31m";
}

// Função: Coleta os dados de consumo de cada setor da fazenda (usando centavos/centilitros)
void lerConsumoDosSetores(std::vector<int> &consumoPorSetorCents, int numSetores)
{
    for (int i = 0; i < numSetores; ++i)
    {
        double input;
        std::cout << "Digite o consumo de água do Setor " << (i + 1) << " (em litros): ";
        std::cin >> input;
        consumoPorSetorCents[i] = (int)(input * 100 + 0.5);
    }
}

// Função: Calcula a soma total da água utilizada
int calcularTotal(const std::vector<int> &consumoPorSetorCents)
{
    int total = 0;
    for (int valor : consumoPorSetorCents)
    {
        total += valor;
    }
    return total;
}

// Função: Exibe o relatório final de forma organizada
void exibirRelatorio(const std::vector<int> &consumoPorSetorCents, int totalCents)
{
    std::cout << "\n" << UI::VERDE << "--- Relatório de Consumo de Água ---" << UI::RESET << "\n";
    for (size_t i = 0; i < consumoPorSetorCents.size(); ++i)
    {
        std::cout << "Setor " << (i + 1) << ": " << (consumoPorSetorCents[i] / 100.0) << " litros\n";
    }
    std::cout << "------------------------------------\n";
    std::cout << "Total de água utilizada: " << UI::VERDE << (totalCents / 100.0) << " litros." << UI::RESET << std::endl;
}

int main()
{
    int numSetores;

    std::cout << "Informe a quantidade de setores da fazenda: ";
    std::cin >> numSetores;

    // Validação simples para evitar vetores de tamanho negativo
    if (numSetores <= 0)
    {
        std::cerr << UI::VERMELHO << "Quantidade de setores inválida." << UI::RESET << std::endl;
        return 1;
    }

    // Configuração de precisão
    std::cout << std::fixed << std::setprecision(2);

    // Declaração do vetor conforme solicitado (Guardião Financeiro: Cents)
    std::vector<int> consumoPorSetorCents(numSetores);

    // Chamada das funções
    lerConsumoDosSetores(consumoPorSetorCents, numSetores);
    int totalAguaCents = calcularTotal(consumoPorSetorCents);
    exibirRelatorio(consumoPorSetorCents, totalAguaCents);

    return 0;
}
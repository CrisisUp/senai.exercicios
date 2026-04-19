/**
 * Programa: AnaliseDeConsumoAgua.cpp
 * Objetivo: Coletar consumo de água por setor e exibir relatório total.
 * Autor: Cristiano Batista Pessoa
 */

#include <iostream>
#include <vector>
#include <iomanip> // Para formatação de saída

// Função: Coleta os dados de consumo de cada setor da fazenda
void lerConsumoDosSetores(std::vector<double> &consumoPorSetor, int numSetores)
{
    for (int i = 0; i < numSetores; ++i)
    {
        std::cout << "Digite o consumo de água do Setor " << (i + 1) << " (em litros): ";
        std::cin >> consumoPorSetor[i];
    }
}

// Função: Calcula a soma total da água utilizada
double calcularTotal(const std::vector<double> &consumoPorSetor)
{
    double total = 0.0;
    for (double valor : consumoPorSetor)
    {
        total += valor;
    }
    return total;
}

// Função: Exibe o relatório final de forma organizada
void exibirRelatorio(const std::vector<double> &consumoPorSetor, double total)
{
    std::cout << "\n--- Relatório de Consumo de Água ---\n";
    for (size_t i = 0; i < consumoPorSetor.size(); ++i)
    {
        std::cout << "Setor " << (i + 1) << ": " << consumoPorSetor[i] << " litros\n";
    }
    std::cout << "------------------------------------\n";
    std::cout << "Total de água utilizada: " << total << " litros." << std::endl;
}

int main()
{
    int numSetores;

    std::cout << "Informe a quantidade de setores da fazenda: ";
    std::cin >> numSetores;

    // Validação simples para evitar vetores de tamanho negativo
    if (numSetores <= 0)
    {
        std::cerr << "Quantidade de setores inválida." << std::endl;
        return 1;
    }

    // Declaração do vetor conforme solicitado
    std::vector<double> consumoPorSetor(numSetores);

    // Chamada das funções
    lerConsumoDosSetores(consumoPorSetor, numSetores);
    double totalAgua = calcularTotal(consumoPorSetor);
    exibirRelatorio(consumoPorSetor, totalAgua);

    return 0;
}
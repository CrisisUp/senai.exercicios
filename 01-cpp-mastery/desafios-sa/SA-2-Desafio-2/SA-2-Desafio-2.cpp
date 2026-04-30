/**
 * @file SA-2-Desafio-2.cpp
 * @brief Sistema de Análise de Consumo de Água por Setor (Refatorado).
 * 
 * @author Cristiano Batista Pessoa
 * @date 19/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória
 * - Variáveis primitivas (int, double): STACK (estática).
 * - Vetor de consumo (std::vector): Controle na STACK, dados na HEAP.
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

// Namespace para Interface de Usuário com cores ANSI
namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
}

using namespace std;

// Função: Coleta os dados de consumo de cada setor da fazenda (usando centavos/centilitros)
void lerConsumoDosSetores(vector<int> &consumoPorSetorCents, int numSetores)
{
    for (int i = 0; i < numSetores; ++i)
    {
        double input;
        cout << "Digite o consumo de água do Setor " << (i + 1) << " (em litros): ";
        cin >> input;
        consumoPorSetorCents[i] = (int)(input * 100 + 0.5);
    }
}

// Função: Calcula a soma total da água utilizada
int calcularTotal(const vector<int> &consumoPorSetorCents)
{
    int total = 0;
    for (int valor : consumoPorSetorCents)
    {
        total += valor;
    }
    return total;
}

// Função: Exibe o relatório final de forma organizada
void exibirRelatorio(const vector<int> &consumoPorSetorCents, int totalCents)
{
    cout << "\n" << UI::VERDE << "--- Relatório de Consumo de Água ---" << UI::RESET << "\n";
    for (size_t i = 0; i < consumoPorSetorCents.size(); ++i)
    {
        cout << "Setor " << (i + 1) << ": " << (consumoPorSetorCents[i] / 100.0) << " litros\n";
    }
    cout << "------------------------------------\n";
    cout << "Total de água utilizada: " << UI::VERDE << (totalCents / 100.0) << " litros." << UI::RESET << endl;
}

int main()
{
    int numSetores;

    cout << "Informe a quantidade de setores da fazenda: ";
    cin >> numSetores;

    if (numSetores <= 0)
    {
        cerr << UI::VERMELHO << "Quantidade de setores inválida." << UI::RESET << endl;
        return 1;
    }

    cout << fixed << setprecision(2);

    vector<int> consumoPorSetorCents(numSetores);

    lerConsumoDosSetores(consumoPorSetorCents, numSetores);
    int totalAguaCents = calcularTotal(consumoPorSetorCents);
    exibirRelatorio(consumoPorSetorCents, totalAguaCents);

    return 0;
}

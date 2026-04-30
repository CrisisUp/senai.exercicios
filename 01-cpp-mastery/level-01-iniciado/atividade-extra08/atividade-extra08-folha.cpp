/**
 * @file atividade-extra08-folha.cpp
 * @brief DESAFIO DE FASE: Sistema de Folha de Pagamento Mensal.
 * 
 * Este programa realiza o processamento completo de um mês de trabalho,
 * identificando finais de semana automaticamente, calculando horas extras,
 * descontando encargos (INSS/IR) e gerando um holerite detalhado.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 18/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória
 * - Struct (Funcionario/RegistroDiario): Alocadas na STACK por possuírem tamanho fixo.
 * - std::vector<RegistroDiario>: Cabeçalho na STACK, elementos dinâmicos na HEAP.
 * - std::string: Conteúdo alocado dinamicamente na HEAP para textos longos.
 */

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

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

// --- 1. ESTRUTURAS DE DADOS ---

struct RegistroDiario {
    int dia;
    double horasNormais;
    double horasExtras;
    bool diaUtil;
};

struct Funcionario {
    string nome;
    long long valorHoraCents;  // Guardião Financeiro: Centavos Inteiros
    long long totalBrutoCents;
    long long descontoINSSCents;
    long long descontoIRCents;
    long long salarioLiquidoCents;
};

// --- 2. PROTÓTIPOS DAS FUNÇÕES ---

void exibirBanner();
bool ehFinalDeSemana(int dia, int mes, int ano);
long long calcularINSS(long long brutoCents);
long long calcularIR(long long brutoCents);
void exibirHolerite(const Funcionario& f, const vector<RegistroDiario>& registros); // Fantasma do CPU

// --- 3. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << fixed << setprecision(2);
    Funcionario f = {"", 0, 0, 0, 0, 0};
    vector<RegistroDiario> folha;

    exibirBanner();

    // Cadastro Inicial
    cout << "Nome do Funcionário: ";
    getline(cin >> ws, f.nome);
    
    double precoInput;
    cout << "Valor da Hora (R$): ";
    cin >> precoInput;
    f.valorHoraCents = (long long)(precoInput * 100 + 0.5);

    cout << UI::AMARELO << "\n--- PROCESSANDO MÊS DE ABRIL/2026 ---" << UI::RESET << endl;

    // Loop pelos 30 dias do mês (Apenas 5 dias para demonstração rápida, mas mantendo lógica de 30)
    const int DIAS_MES = 30;
    for (int d = 1; d <= DIAS_MES; d++) 
    {
        RegistroDiario reg;
        reg.dia = d;
        reg.horasNormais = 0;
        reg.horasExtras = 0;

        // Regra de Negócio: Verificar se é dia de trabalho
        if (ehFinalDeSemana(d, 3, 126)) // 3 = Abril, 126 = 2026
        {
            reg.diaUtil = false;
        } 
        else 
        {
            reg.diaUtil = true;
            double h;
            cout << "Dia " << setfill('0') << setw(2) << d 
                 << " (Útil) - Horas trabalhadas (Máx 10h): ";
            cin >> h;

            // Validação e separação de horas extras
            if (h > 8) {
                reg.horasNormais = 8;
                reg.horasExtras = (h > 10) ? 2 : (h - 8);
            } else {
                reg.horasNormais = h;
            }

            // Cálculo do Bruto Parcial (Guardião Financeiro)
            f.totalBrutoCents += (long long)(reg.horasNormais * f.valorHoraCents);
            f.totalBrutoCents += (long long)(reg.horasExtras * f.valorHoraCents * 1.5); // +50%
        }
        folha.push_back(reg);
    }

    // Cálculos de Encargos
    f.descontoINSSCents = calcularINSS(f.totalBrutoCents);
    f.descontoIRCents = calcularIR(f.totalBrutoCents);
    f.salarioLiquidoCents = f.totalBrutoCents - f.descontoINSSCents - f.descontoIRCents;

    // Resultado Final
    exibirHolerite(f, folha);

    return 0;
}

// --- 4. IMPLEMENTAÇÃO DAS FUNÇÕES ---

bool ehFinalDeSemana(int dia, int mes, int ano) 
{
    tm data = {};
    data.tm_mday = dia;
    data.tm_mon = mes;
    data.tm_year = ano;
    mktime(&data);
    // 0 = Domingo, 6 = Sábado
    return (data.tm_wday == 0 || data.tm_wday == 6);
}

long long calcularINSS(long long brutoCents) {
    return (long long)(brutoCents * 0.11); // 11% fixo para o desafio
}

long long calcularIR(long long brutoCents) {
    if (brutoCents > 250000) return (long long)(brutoCents * 0.075); // 7.5% acima de 2.5k
    return 0;
}

void exibirHolerite(const Funcionario& f, const vector<RegistroDiario>& registros) 
{
    cout << UI::CIANO << "\n\n===============================================" << endl;
    cout << "           HOLERITE MENSAL - 04/2026           " << endl;
    cout << "===============================================" << UI::RESET << endl;
    cout << "FUNCIONÁRIO: " << UI::AMARELO << f.nome << UI::RESET << endl;
    cout << "VALOR HORA : R$ " << (f.valorHoraCents / 100.0) << endl;
    cout << UI::CIANO << "-----------------------------------------------" << endl;
    cout << "DIA | TIPO | H.NORM | H.EXTR" << UI::RESET << endl;
    
    // Fantasma do CPU: Loop com const auto& para evitar cópias de RegistroDiario
    for (const auto& r : registros) {
        if (r.diaUtil) {
            cout << setfill('0') << setw(2) << r.dia << "  | UTIL | " 
                 << fixed << setprecision(1) << r.horasNormais << "    | " 
                 << r.horasExtras << endl;
        }
    }

    cout << UI::CIANO << "-----------------------------------------------" << UI::RESET << endl;
    cout << fixed << setprecision(2);
    cout << "SALÁRIO BRUTO      : R$ " << (f.totalBrutoCents / 100.0) << endl;
    cout << "(-) INSS (11%)     : R$ " << (f.descontoINSSCents / 100.0) << endl;
    cout << "(-) IMP. RENDA     : R$ " << (f.descontoIRCents / 100.0) << endl;
    cout << UI::CIANO << "-----------------------------------------------" << endl;
    cout << UI::VERDE << "SALÁRIO LÍQUIDO    : R$ " << (f.salarioLiquidoCents / 100.0) << endl;
    cout << UI::CIANO << "===============================================" << UI::RESET << endl;
}

void exibirBanner() {
    cout << UI::VERDE << "===============================================" << endl;
    cout << "      SISTEMA DE FOLHA DE PAGAMENTO v2.0       " << endl;
    cout << "===============================================" << UI::RESET << endl;
}

/* 
    ===============================================================
    RESUMO TEÓRICO DO PROJETO DE FASE (ELITE)
    ===============================================================

    1. GUARDIÃO FINANCEIRO (CENTAVOS INTEIROS):
       - Nunca use 'double' ou 'float' para acumular valores monetários.
       - Multiplicamos por 100 e usamos 'long long' para garantir que 
         não haja erros de arredondamento em cálculos fiscais.

    2. FANTASMA DO CPU (REFERÊNCIAS CONSTANTES):
       - 'const Funcionario& f' e 'const vector& registros' evitam 
         que o computador gaste tempo e memória copiando dados 
         grandes para dentro da função.

    3. REGRAS DE NEGÓCIO ROBUSTAS:
       - O programa calcula horas extras com peso 1.5 e descontos 
         progressivos (IR) baseados no bruto acumulado.

    ===============================================================
*/

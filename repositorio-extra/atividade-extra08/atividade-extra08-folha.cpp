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
 */

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

// --- 1. ESTRUTURAS DE DADOS ---

struct RegistroDiario {
    int dia;
    double horasNormais;
    double horasExtras;
    bool diaUtil;
};

struct Funcionario {
    string nome;
    double valorHora;
    double totalBruto;
    double descontoINSS;
    double descontoIR;
    double salarioLiquido;
};

// --- 2. PROTÓTIPOS DAS FUNÇÕES ---

void exibirBanner();
bool ehFinalDeSemana(int dia, int mes, int ano);
double calcularINSS(double bruto);
double calcularIR(double bruto);
void exibirHolerite(Funcionario f, const vector<RegistroDiario>& registros);

// --- 3. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << fixed << setprecision(2);
    Funcionario f = {"", 0.0, 0.0, 0.0, 0.0, 0.0};
    vector<RegistroDiario> folha;

    exibirBanner();

    // Cadastro Inicial
    cout << "Nome do Funcionário: ";
    getline(cin >> ws, f.nome);
    cout << "Valor da Hora (R$): ";
    cin >> f.valorHora;

    cout << "\n--- PROCESSANDO MÊS DE ABRIL/2026 ---" << endl;

    // Loop pelos 30 dias do mês
    for (int d = 1; d <= 30; d++) 
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

            // Cálculo do Bruto Parcial
            f.totalBruto += (reg.horasNormais * f.valorHora);
            f.totalBruto += (reg.horasExtras * f.valorHora * 1.5); // +50%
        }
        folha.push_back(reg);
    }

    // Cálculos de Encargos
    f.descontoINSS = calcularINSS(f.totalBruto);
    f.descontoIR = calcularIR(f.totalBruto);
    f.salarioLiquido = f.totalBruto - f.descontoINSS - f.descontoIR;

    // Resultado Final
    exibirHolerite(f, folha);

    return 0;
}

// --- 4. IMPLEMENTAÇÃO DAS FUNÇÕES ---

bool ehFinalDeSemana(int dia, int mes, int ano) 
{
    tm data = {0};
    data.tm_mday = dia;
    data.tm_mon = mes;
    data.tm_year = ano;
    mktime(&data);
    // 0 = Domingo, 6 = Sábado
    return (data.tm_wday == 0 || data.tm_wday == 6);
}

double calcularINSS(double bruto) {
    return bruto * 0.11; // 11% fixo para o desafio
}

double calcularIR(double bruto) {
    if (bruto > 2500.0) return bruto * 0.075; // 7.5% acima de 2.5k
    return 0.0;
}

void exibirHolerite(Funcionario f, const vector<RegistroDiario>& registros) 
{
    cout << "\n\n===============================================" << endl;
    cout << "           HOLERITE MENSAL - 04/2026           " << endl;
    cout << "===============================================" << endl;
    cout << "FUNCIONÁRIO: " << f.nome << endl;
    cout << "VALOR HORA : R$ " << f.valorHora << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "DIA | TIPO | H.NORM | H.EXTR" << endl;
    
    for (auto const& r : registros) {
        if (r.diaUtil) {
            cout << setfill('0') << setw(2) << r.dia << "  | UTIL | " 
                 << fixed << setprecision(1) << r.horasNormais << "    | " 
                 << r.horasExtras << endl;
        }
    }

    cout << "-----------------------------------------------" << endl;
    cout << fixed << setprecision(2);
    cout << "SALÁRIO BRUTO      : R$ " << f.totalBruto << endl;
    cout << "(-) INSS (11%)     : R$ " << f.descontoINSS << endl;
    cout << "(-) IMP. RENDA     : R$ " << f.descontoIR << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "SALÁRIO LÍQUIDO    : R$ " << f.salarioLiquido << endl;
    cout << "===============================================" << endl;
}

void exibirBanner() {
    cout << "===============================================" << endl;
    cout << "      SISTEMA DE FOLHA DE PAGAMENTO v1.0       " << endl;
    cout << "===============================================" << endl;
}

/* 
    ===============================================================
    RESUMO TEÓRICO DO PROJETO DE FASE
    ===============================================================

    1. LÓGICA DE CALENDÁRIO:
       - Usamos mktime() para que o sistema operacional preencha 
         o dia da semana (tm_wday) automaticamente para nós.

    2. VETORES DE STRUCTS:
       - Guardamos o histórico de todos os 30 dias em um vetor de 
         RegistroDiario, permitindo gerar o relatório ao final.

    3. REGRAS DE NEGÓCIO:
       - O programa aplica diferentes pesos (1.0 para normal e 1.5 
         para extra) dependendo do dado inserido.

    4. PASSAGEM POR REFERÊNCIA (const vector&):
       - Na função exibirHolerite, usamos '&' para não copiar o 
         vetor inteiro (o que economiza memória). O 'const' garante 
         que a função não altere os dados originais.
    ===============================================================
*/

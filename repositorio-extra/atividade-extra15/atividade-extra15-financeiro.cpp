/**
 * @file atividade-extra15-financeiro.cpp
 * @brief ATIVIDADE 15: Financeiro, Conversões e Segurança de Dados.
 * 
 * Este programa demonstra como gerenciar valores monetários e converter tipos:
 * 1. Uso de Inteiros (centavos) para evitar erros de ponto flutuante.
 * 2. Formatação de moeda e Casting (static_cast).
 * 3. Validação robusta de entrada de dinheiro (suporta vírgula e ponto).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <exception>
#include <algorithm>
#include <sstream>

using namespace std;

// --- 1. NAMESPACE DE CORES (ANSI) ---

namespace Cor {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERMELHO = "\033[31m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
}

// --- 2. CLASSES DE EXCEÇÃO ---

class ErroBiblioteca : public exception {
protected:
    string mensagem;
public:
    ErroBiblioteca(string msg) : mensagem(msg) {}
    virtual const char* what() const throw() { return mensagem.c_str(); }
};

class ErroFinanceiro : public ErroBiblioteca {
public:
    ErroFinanceiro(string msg) : ErroBiblioteca(Cor::VERMELHO + "[FINANCEIRO]: " + msg + Cor::RESET) {}
};

// --- 3. ESTRUTURAS DE DADOS ---

struct Livro {
    string titulo;
    string autor;
    int estoque;
    int precoCentavos; // Dinheiro em inteiros!
    int id;
};

struct Emprestimo {
    string leitor;
    Livro livro;
    string dataEmp;
    int valorPago;
};

// --- 4. PROTÓTIPOS DAS FUNÇÕES ---

void exibirBanner();
void carregarCatalogo(vector<Livro> &catalogo);
string formatarMoeda(int centavos);
int converterParaCentavos(string input);
int lerInteiro(string prompt);

// --- 5. FUNÇÃO PRINCIPAL ---

int main()
{
    vector<Livro> catalogo;
    queue<string> filaLeitores;
    stack<Emprestimo> historico;
    int opcao = 0;
    int caixaTotal = 0;

    exibirBanner();

    try {
        carregarCatalogo(catalogo);

        do {
            cout << "\n" << Cor::CIANO << Cor::NEGRITO << "--- SISTEMA FINANCEIRO DA BIBLIOTECA ---" << Cor::RESET << endl;
            cout << "Fila: " << Cor::AMARELO << filaLeitores.size() << Cor::RESET;
            cout << " | Caixa do Dia: " << Cor::VERDE << formatarMoeda(caixaTotal) << Cor::RESET << endl;
            cout << "[1] Novo Leitor | [2] Atender (Aluguel) | [3] Relatório | [4] Sair" << endl;
            
            try {
                opcao = lerInteiro("Escolha: ");

                if (opcao == 1) {
                    string nome;
                    cout << "Nome do Leitor: ";
                    getline(cin >> ws, nome);
                    filaLeitores.push(nome);
                    cout << Cor::VERDE << "[OK]: " << nome << " aguardando." << Cor::RESET << endl;
                }
                else if (opcao == 2) {
                    if (filaLeitores.empty()) throw ErroBiblioteca("Fila vazia.");
                    
                    string leitor = filaLeitores.front();
                    
                    cout << "\n--- CATÁLOGO DE ALUGUEL ---" << endl;
                    cout << left << setw(4) << "ID" << setw(25) << "LIVRO" << "PREÇO/ALUGUEL" << endl;
                    for (int i = 0; i < (int)catalogo.size(); i++) {
                        cout << "[" << i << "] " << setw(25) << catalogo[i].titulo 
                             << Cor::AMARELO << formatarMoeda(catalogo[i].precoCentavos) << Cor::RESET 
                             << (catalogo[i].estoque > 0 ? "" : Cor::VERMELHO + " (ESGOTADO)" + Cor::RESET) << endl;
                    }

                    int idx = lerInteiro("\nEscolha o Livro (ID): ");
                    
                    if (idx < 0 || idx >= (int)catalogo.size()) throw ErroBiblioteca("ID inválido.");
                    if (catalogo[idx].estoque <= 0) throw ErroBiblioteca("Livro esgotado.");

                    // Processo de Pagamento
                    cout << "Total a pagar: " << Cor::VERDE << formatarMoeda(catalogo[idx].precoCentavos) << Cor::RESET << endl;
                    string valorStr;
                    cout << "Digite o valor recebido (ex: 5.00 ou 5,00): ";
                    cin >> valorStr;

                    int recebido = converterParaCentavos(valorStr);
                    int preco = catalogo[idx].precoCentavos;

                    if (recebido < preco) {
                        throw ErroFinanceiro("Valor insuficiente! Faltam " + formatarMoeda(preco - recebido));
                    }

                    // Sucesso no Pagamento
                    filaLeitores.pop();
                    catalogo[idx].estoque--;
                    caixaTotal += preco;

                    int troco = recebido - preco;
                    cout << Cor::VERDE << "[SUCESSO]: Aluguel confirmado!" << Cor::RESET << endl;
                    if (troco > 0) cout << "Troco: " << Cor::AMARELO << formatarMoeda(troco) << Cor::RESET << endl;

                    Emprestimo emp = {leitor, catalogo[idx], "Hoje", preco};
                    historico.push(emp);
                }
                else if (opcao == 3) {
                    cout << "\n--- RESUMO DE CAIXA ---" << endl;
                    cout << "Total Arrecadado: " << Cor::VERDE << formatarMoeda(caixaTotal) << Cor::RESET << endl;
                    cout << "Operações Realizadas: " << historico.size() << endl;
                }

            } catch (const exception& e) {
                cout << e.what() << endl;
            }

        } while (opcao != 4);

    } catch (const exception& e) {
        cerr << Cor::VERMELHO << "FALHA CRÍTICA: " << e.what() << Cor::RESET << endl;
        return 1;
    }

    return 0;
}

// --- 6. IMPLEMENTAÇÃO DAS FUNÇÕES ---

void exibirBanner() {
    cout << Cor::CIANO << "===============================================" << endl;
    cout << "      BIBLIOTECA FINANCEIRA v3.0 (SEGURA)      " << endl;
    cout << "      (Módulo de Dinheiro e Conversões)        " << endl;
    cout << "===============================================" << Cor::RESET << endl;
}

/**
 * @brief Converte centavos inteiros em uma string formatada R$.
 */
string formatarMoeda(int centavos) {
    // static_cast para converter int em double apenas para a divisão
    double reais = static_cast<double>(centavos) / 100.0;
    
    // Usando stringstream para formatar as casas decimais
    stringstream ss;
    ss << "R$ " << fixed << setprecision(2) << reais;
    return ss.str();
}

/**
 * @brief Converte entrada de texto do usuário em centavos inteiros.
 * Suporta pontos e vírgulas (ex: "2.50" ou "2,50").
 */
int converterParaCentavos(string input) {
    // Substitui vírgula por ponto para o stof funcionar
    replace(input.begin(), input.end(), ',', '.');
    
    try {
        // Converte para float temporário e depois para centavos (int)
        float valor = stof(input);
        
        if (valor < 0) throw 1;

        // Arredondamento de segurança para evitar erros de float (0.5 centavos)
        return static_cast<int>((valor * 100.0f) + 0.5f);
    } catch (...) {
        throw ErroFinanceiro("Valor monetário inválido: '" + input + "'");
    }
}

int lerInteiro(string prompt) {
    int v;
    cout << prompt;
    if (!(cin >> v)) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw ErroBiblioteca(Cor::AMARELO + "[ERRO]: Digite um número válido." + Cor::RESET);
    }
    return v;
}

void carregarCatalogo(vector<Livro> &catalogo) {
    ifstream arquivo("repositorio-extra/atividade-extra15/catalogo.txt");
    if (!arquivo.is_open()) arquivo.open("catalogo.txt");
    if (!arquivo.is_open()) throw ErroBiblioteca("Arquivo de catálogo ausente.");

    string linha;
    while (getline(arquivo, linha)) {
        size_t p1 = linha.find(';');
        size_t p2 = linha.find(';', p1 + 1);
        size_t p3 = linha.find(';', p2 + 1);

        if (p3 != string::npos) {
            Livro l;
            l.titulo = linha.substr(0, p1);
            l.autor = linha.substr(p1 + 1, p2 - p1 - 1);
            l.estoque = stoi(linha.substr(p2 + 1, p3 - p2 - 1));
            l.precoCentavos = stoi(linha.substr(p3 + 1));
            l.id = catalogo.size();
            catalogo.push_back(l);
        }
    }
    cout << Cor::VERDE << "[SISTEMA]: Catálogo Financeiro carregado." << Cor::RESET << endl;
}

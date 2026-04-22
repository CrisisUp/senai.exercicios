/**
 * @file atividade-extra48-estoque-evolutivo.cpp
 * @brief DESAFIO DE REFATORAÇÃO: Sistema de Suprimentos Industrial.
 * 
 * Evolução da Atividade 01 utilizando as técnicas de Engenharia:
 * 1. POO com Encapsulamento de Atributos (Private).
 * 2. Gestão de Memória Moderna (std::unique_ptr e make_unique).
 * 3. Validação Ativa via Suite de Testes Unitários.
 * 4. Containers STL (std::vector) para múltiplos itens.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <memory>   // Para unique_ptr (C++ Moderno)
#include <algorithm>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (Cores ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string VERMELHO = "\033[31m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string NEGRITO  = "\033[1m";

    void cabecalho() {
        cout << CIANO << "===============================================" << endl;
        cout << "      G-STOCK: SISTEMA DE GESTÃO INDUSTRIAL    " << endl;
        cout << "          (Evolução da Atividade 01)           " << endl;
        cout << "===============================================" << RESET << endl;
    }
}

// --- 2. MODELO DE NEGÓCIO: CLASSE PRODUTO ---

class Produto {
private:
    string nome;
    int atual;
    int minimo;
    double preco;

public:
    Produto(string n, int a, int m, double p) 
        : nome(n), atual(a), minimo(m), preco(p) {}

    // Getters e Lógica de Negócio (Encapsulamento)
    string getNome() const { return nome; }
    bool precisaRepor() const { return atual < minimo; }
    int getFalta() const { return (precisaRepor()) ? (minimo - atual) : 0; }
    double getCustoReposicao() const { return getFalta() * preco; }
    
    void exibirStatus() const {
        cout << UI::NEGRITO << left << setw(15) << nome << UI::RESET;
        cout << " | " << setw(5) << atual << " / " << setw(5) << minimo;
        if (precisaRepor()) {
            cout << UI::VERMELHO << " | FALTA: " << setw(4) << getFalta() 
                 << " | CUSTO: R$ " << fixed << setprecision(2) << getCustoReposicao() << UI::RESET << endl;
        } else {
            cout << UI::VERDE << " | ESTOQUE SUFICIENTE" << UI::RESET << endl;
        }
    }
};

// --- 3. LABORATORIO DE TESTES (VALIDAÇÃO ATIVA) ---

class SuiteDeTestes {
public:
    static void executar() {
        int falhas = 0;
        cout << UI::AMARELO << "\n--- TESTANDO LOGICA DE REPOSICAO ---" << UI::RESET << endl;

        // Caso 1: Estoque abaixo do mínimo
        Produto p1("Teste1", 5, 10, 2.0);
        if (p1.getFalta() != 5 || p1.getCustoReposicao() != 10.0) {
            cout << UI::VERMELHO << "[FALHA]: Cálculo de reposição incorreto para p1." << UI::RESET << endl;
            falhas++;
        } else {
            cout << UI::VERDE << "[OK]: Cálculo de falta e custo validado." << UI::RESET << endl;
        }

        // Caso 2: Estoque exatamente no mínimo
        Produto p2("Teste2", 10, 10, 2.0);
        if (p2.precisaRepor()) {
            cout << UI::VERMELHO << "[FALHA]: Produto no limite não deve repor." << UI::RESET << endl;
            falhas++;
        } else {
            cout << UI::VERDE << "[OK]: Limite de estoque validado." << UI::RESET << endl;
        }

        cout << UI::AMARELO << "-----------------------------------------------" << endl;
        if (falhas == 0) 
            cout << UI::VERDE << "RESULTADO: MOTOR DE ESTOQUE 100% CONFIAVEL.\n" << UI::RESET << endl;
        else
            exit(1); // Aborta se a lógica estiver errada (Rigor de Engenharia)
    }
};

// --- 4. FUNÇÃO PRINCIPAL ---

int main()
{
    UI::cabecalho();

    // EXIGÊNCIA DE ENGENHARIA: Validar antes de rodar
    SuiteDeTestes::executar();

    // Gestão Moderna com Smart Pointers e Coleções STL
    vector<unique_ptr<Produto>> estoque;

    // Cadastro de produtos (Simulando uma carga de banco de dados/arquivo)
    estoque.push_back(make_unique<Produto>("Monitor LED", 12, 15, 450.00));
    estoque.push_back(make_unique<Produto>("Teclado Mec", 45, 20, 180.00));
    estoque.push_back(make_unique<Produto>("Mouse Laser", 8, 25, 90.00));

    cout << UI::NEGRITO << left << setw(15) << "PRODUTO" << " | ESTOQUE / MIN | STATUS" << UI::RESET << endl;
    cout << "-----------------------------------------------" << endl;

    double custoTotalGeral = 0;

    for (const auto& item : estoque) {
        item->exibirStatus();
        custoTotalGeral += item->getCustoReposicao();
    }

    cout << "-----------------------------------------------" << endl;
    cout << UI::CIANO << "INVESTIMENTO TOTAL NECESSARIO: R$ " 
         << fixed << setprecision(2) << custoTotalGeral << UI::RESET << endl;
    cout << "===============================================" << endl;

    // Nota: Nenhum 'delete' manual é necessário. 
    // O unique_ptr limpa a memória automaticamente ao sair do escopo.

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: O CICLO DE EVOLUÇÃO (REFATORAÇÃO)
    ===============================================================

    1. POR QUE REFATORAR?
       - Refatorar não é apenas "mudar o nome da variável". É elevar o 
         código para novos padrões de segurança. A Atividade 01 era 
         funcional, mas esta Atividade 48 é INDUSTRIAL.

    2. SMART POINTERS NO ESTOQUE:
       - Ao usar std::unique_ptr, eliminamos o risco de o sistema 
         perder um produto da memória e causar um crash. O 
         gerenciamento agora é determinístico e automático.

    3. O PODER DOS TESTES UNITÁRIOS:
       - No primeiro dia (Ativ. 01), você testava digitando valores. 
         Agora, o SuiteDeTestes faz isso em milissegundos, provando 
         que o código está certo matematicamente.

    4. ENCAPSULAMENTO (SEGURANÇA):
       - Ao tornar os atributos privados, impedimos que uma parte 
         acidental do código altere o preço de um produto sem passar 
         pela lógica de negócio.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Serialização JSON: Como salvar este estoque em arquivos modernos.
    - Padrão de Projeto Factory: Para criar produtos de diferentes tipos.
    - Injeção de Dependência: Como testar o sistema com dados falsos.
    ===============================================================
*/

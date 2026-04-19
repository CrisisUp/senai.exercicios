/**
 * @file atividade-extra23-pagamentos.cpp
 * @brief Gateway de Pagamentos: Classes Abstratas e Interfaces.
 * 
 * Demonstra o uso de métodos virtuais puros para criar classes base
 * que servem exclusivamente como contratos para classes especializadas.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
}

// --- 2. CLASSE ABSTRATA (CONTRATO) ---

class MetodoPagamento {
protected:
    double valor;

public:
    MetodoPagamento(double v) : valor(v) {}

    // MÉTODO VIRTUAL PURO: Torna a classe abstrata.
    // O '= 0' obriga qualquer classe filha a implementar este método.
    virtual void processar() = 0; 

    // Método concreto (comum a todas)
    void exibirRecibo() const {
        cout << UI::CIANO << "-----------------------------------------------" << endl;
        cout << "RECIBO G-PAY: Valor Total R$ " << fixed << setprecision(2) << valor << endl;
        cout << "Status: PROCESSADO COM SUCESSO" << endl;
        cout << "-----------------------------------------------" << UI::RESET << endl;
    }

    virtual ~MetodoPagamento() {} // Destrutor virtual essencial
};

// --- 3. CLASSES CONCRETAS (FILHAS) ---

class PagamentoPix : public MetodoPagamento {
public:
    PagamentoPix(double v) : MetodoPagamento(v) {}

    // Implementação obrigatória do contrato
    void processar() override {
        cout << UI::VERDE << "[PIX]: Gerando chave dinâmica..." << endl;
        cout << "Chave: 00020126360014BR.GOV.BCB.PIX0114123456789" << endl;
        cout << "Aguardando confirmação do BACEN... Pronto!" << UI::RESET << endl;
    }
};

class PagamentoCartao : public MetodoPagamento {
private:
    string numeroCartao;

public:
    PagamentoCartao(double v, string n) : MetodoPagamento(v), numeroCartao(n) {}

    void processar() override {
        cout << UI::AZUL << "[CARTÃO]: Conectando com a operadora..." << endl;
        cout << "Validando cartão final: " << numeroCartao.substr(numeroCartao.length() - 4) << endl;
        cout << "Autorização aprovada: CODE-998877" << UI::RESET << endl;
    }
};

// --- 4. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << UI::CIANO << "===============================================" << endl;
    cout << "      GATEWAY DE PAGAMENTOS (G-PAY v1.0)       " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // A mágica: Tratamos formas diferentes através do mesmo contrato abstrato
    vector<MetodoPagamento*> carrinho;

    carrinho.push_back(new PagamentoPix(150.50));
    carrinho.push_back(new PagamentoCartao(450.00, "1234-5678-9012-3456"));
    carrinho.push_back(new PagamentoPix(25.90));

    cout << "\n[SISTEMA]: Processando fila de pagamentos pendentes...\n" << endl;

    for (MetodoPagamento* pgto : carrinho) {
        pgto->processar();    // Cada um faz do seu jeito
        pgto->exibirRecibo(); // Todos usam o recibo padrão
        cout << endl;
    }

    // Limpeza
    for (MetodoPagamento* pgto : carrinho) delete pgto;

    /* 
       DICA DIDÁTICA:
       Se tentarmos a linha abaixo, o compilador gerará um ERRO:
       MetodoPagamento generico(100); 
       Isso porque a classe é ABSTRATA (Incompleta por design).
    */

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: CLASSES ABSTRATAS E INTERFACES
    ===============================================================

    1. O QUE SÃO CLASSES ABSTRATAS?
       - São classes que não podem criar objetos. Elas existem 
         apenas para serem herdadas. São ideais para representar 
         CONCEITOS genéricos (ex: MetodoPagamento, Animal, Forma).

    2. MÉTODOS VIRTUAIS PUROS (virtual ... = 0):
       - É a ferramenta que torna a classe abstrata. Ela define que 
         toda classe filha TEM A OBRIGAÇÃO de implementar aquele 
         comportamento, senão ela também será abstrata.

    3. INTERFACES NO C++:
       - Diferente de Java ou C#, o C++ não tem uma palavra-chave 
         'interface'. Usamos classes puramente abstratas (apenas 
         métodos virtuais puros) para simular esse comportamento.

    4. SEGURANÇA DE DESIGN:
       - Isso impede que programadores cometam o erro de criar 
         instâncias que não deveriam existir, garantindo que o 
         sistema sempre lide com implementações concretas e válidas.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Polimorfismo Ad-Hoc.
    - Princípio da Inversão de Dependência (SOLID).
    - Design Pattern 'Strategy': Usa classes abstratas para trocar 
      algoritmos em tempo de execução.
    ===============================================================
*/

/**
 * @file atividade-extra23-pagamentos.cpp
 * @brief Gateway de Pagamentos: Classes Abstratas e Interfaces de Elite.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra o uso de métodos virtuais puros para garantir contratos arquiteturais.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Abstract Interface)
 * - Classe Abstrata: Não possui instâncias próprias. Ocupa 0 bytes de memória 
 *   até que uma filha seja criada.
 * - Objeto Derivado (Pix/Cartão): Alocado na HEAP. Contém o valor (8 bytes) e 
 *   o ponteiro para a V-TABLE da filha.
 * - V-Table: Garante que o método virtual puro seja resolvido para a 
 *   implementação correta no runtime.
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERMELHO = "\033[31m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string AZUL     = "\033[34m";
    const string CIANO    = "\033[36m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. CLASSE ABSTRATA (CONTRATO) ---

/**
 * @class MetodoPagamento
 * @brief Define o contrato obrigatório para qualquer gateway de pagamento.
 * Aplica o padrão 'Guardião Financeiro' para precisão de centavos.
 */
class MetodoPagamento {
protected:
    long long valorCentavos; // Integridade Bancária (Int64)

public:
    /**
     * @brief Construtor: Recebe valor e converte internamente para centavos.
     */
    MetodoPagamento(double v) : valorCentavos(static_cast<long long>(v * 100)) {}

    /**
     * @brief MÉTODO VIRTUAL PURO: Torna a classe abstrata.
     * Obriga a implementação nas classes filhas.
     */
    virtual void processar() = 0; 

    /**
     * @brief Método Concreto: Implementação comum de comprovante.
     */
    void exibirRecibo() const {
        double real = static_cast<double>(valorCentavos) / 100.0;
        cout << UI::CIANO << UI::NEGRITO << "-----------------------------------------------" << UI::RESET << endl;
        cout << UI::NEGRITO << "COMPROVANTE G-PAY" << UI::RESET << endl;
        cout << "Valor Processado : " << UI::VERDE << UI::NEGRITO << "R$ " << fixed << setprecision(2) << real << UI::RESET << endl;
        cout << "Status           : " << UI::VERDE << "CONFIRMADO" << UI::RESET << endl;
        cout << UI::CIANO << UI::NEGRITO << "-----------------------------------------------" << UI::RESET << endl;
    }

    virtual ~MetodoPagamento() {} // Destrutor virtual essencial
};

// --- 3. CLASSES CONCRETAS (FILHAS) ---

/**
 * @class PagamentoPix
 * @brief Especialização para transações instantâneas via BACEN.
 */
class PagamentoPix : public MetodoPagamento {
public:
    PagamentoPix(double v) : MetodoPagamento(v) {}

    void processar() override {
        cout << UI::VERDE << UI::NEGRITO << "[MODAL PIX]: " << UI::RESET 
             << "Gerando Payload BR Code dinâmico..." << endl;
        cout << UI::AMARELO << "CODE: 00020126360014BR.GOV.BCB.PIX0114998877665544" << UI::RESET << endl;
        cout << "[SISTEMA]: Aguardando liquidação em tempo real... OK!" << endl;
    }
};

/**
 * @class PagamentoCartao
 * @brief Especialização para transações via Adquirentes (Visa/Master).
 */
class PagamentoCartao : public MetodoPagamento {
private:
    string numeroMascarado;

public:
    PagamentoCartao(double v, const string& n) 
        : MetodoPagamento(v), numeroMascarado(n) {}

    void processar() override {
        cout << UI::AZUL << UI::NEGRITO << "[MODAL CARTÃO]: " << UI::RESET 
             << "Comunicando com Gateway de Adquirência..." << endl;
        string final = (numeroMascarado.length() >= 4) ? numeroMascarado.substr(numeroMascarado.length() - 4) : "****";
        cout << "[SISTEMA]: Autorizando final " << UI::NEGRITO << final << UI::RESET << "..." << endl;
        cout << UI::VERDE << "[OK]: Transação capturada com sucesso." << UI::RESET << endl;
    }
};

// --- 4. EXECUÇÃO DO CHECKOUT ---

int main()
{
    UI::limparTela();
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      GATEWAY DE PAGAMENTOS (G-PAY v2.0)       " << endl;
    cout << "       (Elite Abstract Infrastructure)         " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // A mágica: Polimorfismo através de uma Interface Abstrata
    vector<MetodoPagamento*> filaProcessamento;

    // Alocação na HEAP para vida dinâmica
    filaProcessamento.push_back(new PagamentoPix(250.75));
    filaProcessamento.push_back(new PagamentoCartao(1200.00, "4532-XXXX-XXXX-8899"));
    filaProcessamento.push_back(new PagamentoPix(15.90));

    cout << "\n" << UI::BRANCO << "[OPERACIONAL]: Iniciando processamento de fila assíncrona...\n" << UI::RESET << endl;

    // Execução polimórfica (Fantasma do CPU)
    for (auto* pgto : filaProcessamento) {
        if (pgto) {
            pgto->processar();    // Chamada dinâmica via V-Table
            pgto->exibirRecibo(); // Chamada estática da Base
            cout << endl;
        }
    }

    // --- CICLO DE DESALOCAÇÃO SEGURA ---
    cout << UI::BRANCO << "[SISTEMA]: Limpando buffer de transações..." << UI::RESET << endl;
    for (auto& pgto : filaProcessamento) {
        delete pgto;
        pgto = nullptr;
    }
    filaProcessamento.clear();

    cout << UI::VERDE << UI::NEGRITO << "\nCheckpoint: Todos os pagamentos liquidados com 100% de integridade." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: ABSTRAÇÃO E CONTRATOS DE SOFTWARE
    ===============================================================

    1. INTERFACES (CLASSES ABSTRATAS):
       - Servem para definir "O QUE" um objeto deve fazer, sem 
         especificar "COMO". No G-PAY, garantimos que todo método 
         de pagamento tenha um valor e possa ser processado.

    2. VIRTUAL PURO (= 0):
       - É o mecanismo que proíbe a criação de objetos da classe 
         mãe. Isso evita erros lógicos, como criar um "Pagamento" 
         que não tem tipo definido.

    3. INTEGRIDADE FINANCEIRA (ELITE RULE):
       - Note que o valor é guardado em centavos (long long). 
         Ao trabalhar com dinheiro, o tipo 'double' é perigoso 
         devido a imprecisões binárias (ex: 0.1 + 0.2 != 0.3). 
         Cálculos inteiros são a lei em Fintechs.

    4. RESILIÊNCIA DE DESIGN:
       - O polimorfismo dinâmico permite que o G-PAY aceite novos 
         métodos (ex: Cripto, Boleto) sem que o código da main() 
         ou da fila precise ser alterado.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Interface Segregation Principle (SOLID).
    - Factory Pattern: Como criar objetos de pagamento dinamicamente.
    - Double Dispatch: Operações complexas entre múltiplos tipos abstratos.
    ===============================================================
*/

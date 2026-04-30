/**
 * @file atividade-extra20-banco.cpp
 * @brief DESAFIO INTEGRADOR: Núcleo Bancário G-BANK v2.0 (Elite Engineering).
 * 
 * Integra: POO Avançado (Static), Testes Unitários e Persistência Resiliente.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Elite Architecture)
 * - Variáveis Estáticas (totalContas, reservaTotalBanco): Alocadas no DATA SEGMENT (permanente).
 * - Objetos ContaBancaria: Alocados na STACK na main() (40 bytes aprox cada).
 * - Atributo 'titular': Objeto string na STACK, conteúdo textual na HEAP.
 * - Suíte de Testes: Executa na STACK e limpa o estado global via métodos estáticos.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <exception>
#include <sstream>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
    void cabecalho() {
        cout << CIANO << NEGRITO << "===============================================" << endl;
        cout << "            G-BANK: CORE SYSTEM v2.0           " << endl;
        cout << "           (Terminal de Autoatendimento)       " << endl;
        cout << "===============================================" << RESET << endl;
    }
}

// --- 2. GESTÃO DE EXCEÇÕES CUSTOMIZADAS ---

class ErroBancario : public exception {
    string msg;
public:
    ErroBancario(string m) : msg(UI::VERMELHO + "[ERRO BANCÁRIO]: " + m + UI::RESET) {}
    const char* what() const throw() { return msg.c_str(); }
};

// --- 3. CLASSE CONTA BANCÁRIA (O GUARDIÃO FINANCEIRO) ---

class ContaBancaria {
private:
    int id;
    string titular;
    long long saldoCentavos; // Integridade Bancária: Sem ponto flutuante

    // Membros Estáticos (Data Segment)
    static int totalContas;
    static long long reservaTotalBanco;

public:
    /**
     * @brief Construtor 1 (Simples): Sobrecarga para contas novas.
     */
    ContaBancaria(int _id, const string& _titular) 
        : id(_id), titular(_titular), saldoCentavos(0) 
    {
        totalContas++;
    }

    /**
     * @brief Construtor 2 (Premium): Sobrecarga com depósito inicial.
     */
    ContaBancaria(int _id, const string& _titular, double depositoInicial)
        : id(_id), titular(_titular)
    {
        if (depositoInicial < 0) throw ErroBancario("Depósito inicial negativo proibido.");
        
        saldoCentavos = static_cast<long long>(depositoInicial * 100);
        reservaTotalBanco += saldoCentavos;
        totalContas++;
    }

    // --- OPERAÇÕES BANCÁRIAS ---

    void depositar(double valor) {
        if (valor <= 0) throw ErroBancario("Valor de depósito deve ser positivo.");
        long long centavos = static_cast<long long>(valor * 100);
        saldoCentavos += centavos;
        reservaTotalBanco += centavos;
        cout << UI::VERDE << "[CRÉDITO]: +R$ " << fixed << setprecision(2) << valor << UI::RESET << endl;
    }

    void sacar(double valor) {
        long long centavos = static_cast<long long>(valor * 100);
        if (centavos > saldoCentavos) throw ErroBancario("Saldo insuficiente para saque.");
        if (valor <= 0) throw ErroBancario("Valor de saque inválido.");

        saldoCentavos -= centavos;
        reservaTotalBanco -= centavos;
        cout << UI::VERMELHO << "[DÉBITO]: -R$ " << fixed << setprecision(2) << valor << UI::RESET << endl;
    }

    /**
     * @brief Transação PIX entre objetos.
     */
    void transferirPara(ContaBancaria &destino, double valor) {
        this->sacar(valor);
        destino.depositar(valor);
        cout << UI::AMARELO << UI::NEGRITO << "[PIX]: Transferência realizada com sucesso!" << UI::RESET << endl;
    }

    // --- GETTERS (FANTASMA DO CPU - REFERÊNCIAS CONSTANTES) ---
    
    void exibirSaldo() const {
        double real = static_cast<double>(saldoCentavos) / 100.0;
        cout << UI::CIANO << "CONTA: " << id << " | TITULAR: " << UI::NEGRITO << titular << UI::RESET << endl;
        cout << "SALDO ATUAL: " << UI::NEGRITO << UI::VERDE << "R$ " << real << UI::RESET << endl;
    }

    const string& getTitular() const { return titular; }
    double getSaldoReal() const { return static_cast<double>(saldoCentavos) / 100.0; }

    static int getTotalContas() { return totalContas; }
    static double getReservaTotal() { return static_cast<double>(reservaTotalBanco) / 100.0; }

    // --- PERSISTÊNCIA ---

    void gerarExtratoTxt() const {
        string nomeArq = "repositorio-extra/atividade-extra20/extrato_" + to_string(id) + ".txt";
        ofstream arq(nomeArq);
        if (arq.is_open()) {
            arq << "===============================================\n";
            arq << "          G-BANK EXTRATO OFICIAL               \n";
            arq << "===============================================\n";
            arq << "ID CONTA: " << id << "\n";
            arq << "TITULAR : " << titular << "\n";
            arq << "SALDO FINAL: R$ " << (static_cast<double>(saldoCentavos) / 100.0) << "\n";
            arq << "-----------------------------------------------\n";
            arq.close();
        }
    }

    static void resetBanco() {
        totalContas = 0;
        reservaTotalBanco = 0;
    }
};

// Inicialização de Membros Estáticos
int ContaBancaria::totalContas = 0;
long long ContaBancaria::reservaTotalBanco = 0;

// --- 4. SUÍTE DE TESTES UNITÁRIOS (DIAGNÓSTICO ELITE) ---

class SuiteDeTestes {
private:
    static int testesPassados;
    static int totalTestes;

    static void afirmar(bool condicao, string descricao) {
        totalTestes++;
        if (condicao) {
            testesPassados++;
            cout << UI::VERDE << "  [PASSOU] " << UI::RESET << descricao << endl;
        } else {
            cout << UI::VERMELHO << "  [FALHOU] " << UI::RESET << descricao << endl;
        }
    }

public:
    static void executar() {
        cout << UI::AMARELO << UI::NEGRITO << "\n>>> INICIANDO AUTO-DIAGNÓSTICO DO MOTOR BANCÁRIO..." << UI::RESET << endl;
        ContaBancaria::resetBanco();

        ContaBancaria t1(1, "Sandbox", 1000.00);
        
        afirmar(t1.getSaldoReal() == 1000.00, "Inicialização Premium com R$ 1000.");
        
        t1.depositar(500.25);
        afirmar(t1.getSaldoReal() == 1500.25, "Depósito com precisão de centavos.");

        t1.sacar(200.00);
        afirmar(t1.getSaldoReal() == 1300.25, "Saque debita corretamente do saldo.");

        bool excessaoOK = false;
        try { t1.sacar(5000.00); } catch(const exception& e) { excessaoOK = true; }
        afirmar(excessaoOK, "Proteção contra saque a descoberto (Exception).");

        afirmar(ContaBancaria::getReservaTotal() == 1300.25, "Auditoria Global de Reserva Estática.");

        cout << UI::AMARELO << "-----------------------------------------------" << endl;
        if (testesPassados == totalTestes) 
            cout << UI::VERDE << UI::NEGRITO << "RESULTADO: MOTOR HOMOLOGADO (100% OK)" << UI::RESET << endl;
        else
            cout << UI::VERMELHO << UI::NEGRITO << "ALERTA: FALHA NO MOTOR - REVISÃO NECESSÁRIA!" << UI::RESET << endl;
        cout << UI::AMARELO << "-----------------------------------------------\n" << UI::RESET << endl;
        
        ContaBancaria::resetBanco();
    }
};
int SuiteDeTestes::testesPassados = 0;
int SuiteDeTestes::totalTestes = 0;

// --- 5. EXECUÇÃO PRINCIPAL ---

int main()
{
    UI::limparTela();
    UI::cabecalho();

    // Validação de Integridade antes da entrada do usuário
    SuiteDeTestes::executar();

    ContaBancaria c1(1001, "Cristiano Pessoa", 1000.00);
    ContaBancaria c2(2002, "Aluno SENAI", 0.00);

    int opcao = 0;
    int contaAtiva = 1;

    do {
        ContaBancaria &atual = (contaAtiva == 1) ? c1 : c2;
        ContaBancaria &outra = (contaAtiva == 1) ? c2 : c1;

        cout << "\nUSUÁRIO ATIVO: " << UI::NEGRITO << UI::AMARELO << atual.getTitular() << UI::RESET << endl;
        cout << "[1] Ver Saldo   [2] Depósito   [3] Saque   [4] PIX" << endl;
        cout << "[5] Auditoria   [6] Sair       [7] Trocar Usuário" << endl;
        cout << UI::RESET << "Ação: " << UI::RESET;
        
        if (!(cin >> opcao)) break;

        try {
            switch (opcao) {
                case 1: atual.exibirSaldo(); break;
                case 2: {
                    double v; cout << "Valor: "; cin >> v;
                    atual.depositar(v); break;
                }
                case 3: {
                    double v; cout << "Valor: "; cin >> v;
                    atual.sacar(v); break;
                }
                case 4: {
                    double v; cout << "PIX para " << outra.getTitular() << ": "; cin >> v;
                    atual.transferirPara(outra, v); break;
                }
                case 5:
                    cout << "\n" << UI::CIANO << ">>> AUDITORIA G-BANK <<<" << UI::RESET << endl;
                    cout << "Contas Ativas   : " << ContaBancaria::getTotalContas() << endl;
                    cout << "Reserva Total   : " << UI::VERDE << "R$ " << ContaBancaria::getReservaTotal() << UI::RESET << endl;
                    break;
                case 7:
                    contaAtiva = (contaAtiva == 1) ? 2 : 1;
                    UI::limparTela(); UI::cabecalho();
                    cout << UI::VERDE << "[SISTEMA]: Sessão alterada." << UI::RESET << endl;
                    break;
            }
        } catch (const exception& e) {
            cout << e.what() << endl;
        }

    } while (opcao != 6);

    c1.gerarExtratoTxt();
    c2.gerarExtratoTxt();
    cout << UI::VERDE << UI::NEGRITO << "\nSessão encerrada com segurança. Extratos em disco." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO INTEGRADOR POO (ELITE STANDARD)
    ===============================================================

    1. MEMBROS ESTÁTICOS (STATIC):
       - São atributos que pertencem à CLASSE, e não ao objeto. 
         Eles residem no DATA SEGMENT da RAM. No G-Bank, usamos 
         isso para saber o saldo total de todos os clientes sem 
         precisar percorrer uma lista, mantendo a performance O(1).

    2. INTEGRIDADE FINANCEIRA (CENTAVOS INTEIROS):
       - Nunca usamos 'double' ou 'float' para acumular dinheiro 
         em sistemas profissionais. Usamos 'long long' (centavos) 
         para evitar os famosos erros de arredondamento binário.

    3. SUÍTE DE TESTES (TEST-DRIVEN MINDSET):
       - A inclusão de uma classe de teste prova que o motor 
         financeiro é confiável antes mesmo do cliente tocar no 
         teclado. É o padrão de qualidade do Silicon Valley.

    4. TRATAMENTO DE EXCEÇÕES:
       - O uso de blocos try-catch garante que o programa não 
         \"morra\" diante de um erro de negócio (saldo insuficiente). 
         O erro é tratado como um evento gerenciável.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Thread-Safety: Como o static se comporta em sistemas paralelos.
    - Serialização: Salvar objetos complexos em formatos como JSON/Binary.
    - Singleton Pattern: Quando apenas UMA instância da classe pode existir.
    ===============================================================
*/

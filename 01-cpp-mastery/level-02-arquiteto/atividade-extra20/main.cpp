#define ANSI_RESET "\033[0m"
#define ANSI_GREEN "\033[32m"
/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file main.cpp
 * @brief Execução principal e suíte de testes do G-BANK v2.0.
 */

#include "ContaBancaria.h"

using namespace std;

// --- 4. SUÍTE DE TESTES UNITÁRIOS ---
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

int main()
{
    UI::limparTela();
    UI::cabecalho();

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

/* @section MemoryMap
 * Stack: Variáveis locais e de escopo.
 * Heap: Alocações dinâmicas.
 */
/*
 * RESUMO TEÓRICO
 * Implementação seguindo as diretrizes do Padrão de Entrega de Elite.
 */

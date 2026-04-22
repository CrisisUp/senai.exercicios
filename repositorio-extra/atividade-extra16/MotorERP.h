/**
 * @file MotorERP.h
 * @brief Definições de Estruturas, Interface e Classe Controladora do ERP.
 * 
 * Parte da Atividade Extra 16 - Refatoração Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#ifndef MOTOR_ERP_H
#define MOTOR_ERP_H

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <exception>

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERMELHO = "\033[31m";
    const std::string VERDE    = "\033[32m";
    const std::string AMARELO  = "\033[33m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string BRANCO   = "\033[37m";

    void limparTela();
}

// --- 2. GESTÃO DE EXCEÇÕES ---

class ErroERP : public std::exception {
    std::string msg;
public:
    ErroERP(std::string m) : msg(UI::VERMELHO + "[ERRO]: " + m + UI::RESET) {}
    virtual const char* what() const throw() { return msg.c_str(); }
};

// --- 3. ESTRUTURAS DE DADOS ---

struct Produto {
    int id;
    std::string nome;
    int estoque;
    int custoCentavos;
    int margemLucro; // Porcentagem
    
    int getPrecoVenda() const {
        return custoCentavos + (custoCentavos * margemLucro / 100);
    }
};

struct LogOperacao {
    std::string timestamp;
    std::string acao;
    long long valorImpacto; // Centavos (+ entrada, - saída)
};

// --- 4. O SISTEMA ERP ---

class SistemaERP {
private:
    std::vector<Produto> estoque;
    std::stack<LogOperacao> logs;
    std::queue<std::string> filaClientes;
    long long saldoCaixa;
    long long despesasFixas;

    std::string getAgora();
    void registrarLog(std::string desc, long long valor);
    void gerarRelatorioFinal();

public:
    SistemaERP();
    
    void carregarDados();
    void menuPrincipal();
    
    // Ações do ERP
    void adicionarCliente();
    void realizarVenda();
    void comprarEstoque();
    void pagarGastosFixos();
    void mostrarAuditoria();

    // Utilitários
    static std::string formatarMoeda(long long centavos);
};

#endif // MOTOR_ERP_H

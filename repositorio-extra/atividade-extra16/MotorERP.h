/**
 * @file MotorERP.h
 * @brief Definições de Estruturas, Interface e Classe Controladora do ERP.
 * 
 * Parte da Atividade Extra 16 - Refatoração Modular (Nível 11+).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap MAPA DE MEMÓRIA (Elite Refactor)
 * - STACK: Pointers this, variávies locais de controle (opt, idx, qtd), structs temporárias.
 * - HEAP: std::vector<Produto> (Estoque Central), std::stack (Logs de Auditoria), std::queue (Fila Clientes).
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

// --- 2. CÓDIGO BLINDADO (EXCEÇÕES CUSTOMIZADAS) ---

class ErroERP : public std::exception {
    std::string msg;
public:
    ErroERP(const std::string& m) : msg(UI::VERMELHO + "[ERRO]: " + m + UI::RESET) {}
    virtual const char* what() const throw() { return msg.c_str(); }
};

// --- 3. GUARDIÃO FINANCEIRO (ESTRUTURAS COM CENTAVOS) ---

struct Produto {
    int id;
    std::string nome;
    int estoque;
    long long custoCentavos;
    int margemLucro; // Porcentagem
    
    long long getPrecoVenda() const {
        return custoCentavos + (custoCentavos * margemLucro / 100);
    }
};

struct LogOperacao {
    std::string timestamp;
    std::string acao;
    long long valorImpacto; // Centavos (+ entrada, - saída)
};

// --- 4. O SISTEMA ERP (FANTASMA DO CPU) ---

class SistemaERP {
private:
    std::vector<Produto> estoque;
    std::stack<LogOperacao> logs;
    std::queue<std::string> filaClientes;
    long long saldoCaixa;
    long long despesasFixas;

    std::string getAgora() const;
    void registrarLog(const std::string& desc, long long valor);
    void gerarRelatorioFinal() const;

public:
    SistemaERP();
    
    void carregarDados();
    void menuPrincipal();
    
    // Ações do ERP
    void adicionarCliente();
    void realizarVenda();
    void comprarEstoque();
    void pagarGastosFixos();
    void mostrarAuditoria() const;

    // Utilitários Const-Safe (Fantasma do CPU)
    static std::string formatarMoeda(long long centavos);
};

#endif // MOTOR_ERP_H

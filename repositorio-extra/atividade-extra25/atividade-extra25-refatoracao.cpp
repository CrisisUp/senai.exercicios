/**
 * @file atividade-extra25-refatoracao.cpp
 * @brief DESAFIO DE MAESTRIA: Refatoração Industrial v1.0 -> v4.0 (Elite).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a transição de um sistema procedural frágil para uma arquitetura POO blindada.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (Refactored Layout)
 * - Variáveis Estáticas: Alocadas no DATA SEGMENT (Persistem por toda a vida do app).
 * - Almoxarifado (vector): O container vive na STACK, mas a lista de ponteiros na HEAP.
 * - Objetos ProdutoIndustrial: Alocados na HEAP para permitir inventário dinâmico.
 * - Strings (nome): Objeto na HEAP (Product) -> Dados reais em outro bloco na HEAP.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <exception>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

namespace UI {
    const string RESET    = "\033[0m";
    const string NEGRITO  = "\033[1m";
    const string VERDE    = "\033[32m";
    const string VERMELHO = "\033[31m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
    const string BRANCO   = "\033[37m";

    inline void limparTela() { cout << "\033[2J\033[1;1H"; }

    void cabecalho() {
        cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
        cout << "       ALMOXARIFADO INDUSTRIAL v4.0 (REFAC)    " << endl;
        cout << "       (Elite Engineering & Safety Core)       " << endl;
        cout << "===============================================" << UI::RESET << endl;
    }
}

// --- 2. GESTÃO DE EXCEÇÕES INDUSTRIAIS ---

class ErroEstoque : public exception {
    string msg;
public:
    ErroEstoque(string m) : msg(UI::VERMELHO + "[ALERTA DE ESTOQUE]: " + m + UI::RESET) {}
    const char* what() const throw() { return msg.c_str(); }
};

// --- 3. CLASSE MODERNIZADA (O GUARDIÃO FINANCEIRO) ---

class ProdutoIndustrial {
private:
    string nome;
    long long precoCentavos; // Integridade Bancária (Guardião Financeiro)
    int quantidade;

    // Membros Estáticos: Visão Global do Patrimônio (Data Segment)
    static long long valorGlobalCentavos;
    static int totalItens;

public:
    /**
     * @brief Construtor de Elite com validação e Lista de Inicialização.
     */
    ProdutoIndustrial(const string& _nome, double _preco, int _qtd) 
        : nome(_nome), precoCentavos(static_cast<long long>(_preco * 100)), quantidade(_qtd) 
    {
        if (_preco < 0 || _qtd < 0) throw ErroEstoque("Parâmetros de inicialização inválidos para '" + nome + "'.");
        
        valorGlobalCentavos += (precoCentavos * quantidade);
        totalItens++;
    }

    // --- MÉTODOS DE OPERAÇÃO ---

    void registrarSaida(int qtd) {
        if (qtd <= 0) throw ErroEstoque("Quantidade de movimentação deve ser positiva.");
        if (qtd > quantidade) throw ErroEstoque("Ruptura de estoque detectada para '" + nome + "'.");

        valorGlobalCentavos -= (precoCentavos * qtd);
        quantidade -= qtd;
        cout << UI::VERDE << "[OK]: Remessa de " << qtd << " un. de '" << nome << "' liberada." << UI::RESET << endl;
    }

    void exibirItem() const {
        double precoReal = static_cast<double>(precoCentavos) / 100.0;
        double subtotal = (static_cast<double>(precoCentavos * quantidade)) / 100.0;

        cout << UI::BRANCO << left << setw(20) << nome << UI::RESET 
             << " | Preço: R$ " << right << setw(9) << fixed << setprecision(2) << precoReal 
             << " | Qtd: " << UI::CIANO << setw(5) << quantidade << UI::RESET
             << " | Subtotal: R$ " << UI::NEGRITO << setw(10) << subtotal << UI::RESET << endl;
    }

    // --- ACESSO DE ELITE (FANTASMA DO CPU) ---
    const string& getNome() const { return nome; }
    static double getValorGlobal() { return static_cast<double>(valorGlobalCentavos) / 100.0; }
    static int getTotalItens() { return totalItens; }
};

// Inicialização de membros estáticos
long long ProdutoIndustrial::valorGlobalCentavos = 0;
int ProdutoIndustrial::totalItens = 0;

// --- 4. EXECUÇÃO DO SISTEMA REFATORADO ---

int main()
{
    UI::limparTela();
    UI::cabecalho();

    vector<ProdutoIndustrial*> almoxarifado;

    try {
        cout << UI::AMARELO << "[SISTEMA]: Migrando dados do legado (Atividade 01)..." << UI::RESET << endl;
        
        // Simulação de entrada de itens industriais
        almoxarifado.push_back(new ProdutoIndustrial("Inversor de Frequência", 2850.75, 4));
        almoxarifado.push_back(new ProdutoIndustrial("Sensor Ultrassônico", 115.20, 50));
        almoxarifado.push_back(new ProdutoIndustrial("Relé Industrial 24V", 45.00, 120));

        cout << "\nStatus Atual do Armazém:" << endl;
        cout << "-> Unidades Cadastradas : " << ProdutoIndustrial::getTotalItens() << endl;
        cout << "-> Patrimônio Líquido   : " << UI::VERDE << "R$ " << ProdutoIndustrial::getValorGlobal() << UI::RESET << endl;
        cout << string(60, '-') << endl;

        // Simulando Operação Crítica
        cout << "\n" << UI::BRANCO << "[REQUISIÇÃO]: Solicitando saída de material..." << UI::RESET << endl;
        almoxarifado[0]->registrarSaida(2); // Retira 2 inversores

        // Listagem Consolidada
        cout << "\n" << UI::NEGRITO << "RELATÓRIO DE INVENTÁRIO CONSOLIDADO:" << UI::RESET << endl;
        for (const auto* item : almoxarifado) {
            if (item) item->exibirItem();
        }

        cout << string(60, '-') << endl;
        cout << "Patrimônio Consolidado : " << UI::VERDE << UI::NEGRITO << "R$ " << ProdutoIndustrial::getValorGlobal() << UI::RESET << endl;

        // Testando Resiliência (🧪 Cientista do Caos)
        cout << "\n" << UI::VERMELHO << "[STRESS TEST]: Tentando retirar estoque fantasma..." << UI::RESET << endl;
        almoxarifado[1]->registrarSaida(1000); // Força erro

    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // --- LIMPEZA DE MEMÓRIA (BOA PRÁTICA DE ENGENHARIA) ---
    cout << "\n" << UI::BRANCO << "[SISTEMA]: Encerrando e desalocando recursos..." << UI::RESET << endl;
    for (auto& item : almoxarifado) {
        delete item;
        item = nullptr;
    }
    almoxarifado.clear();

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: MODERNIZAÇÃO E DÍVIDA TÉCNICA
    ===============================================================

    1. O FIM DAS VARIÁVEIS SOLTAS:
       - Refatorar o legado significa transformar dados desprotegidos 
         em objetos inteligentes. O 'ProdutoIndustrial' agora possui 
         regras de validade inerentes a ele (Encapsulamento).

    2. AUDITORIA ESTÁTICA EM TEMPO REAL:
       - Ao centralizar o cálculo do patrimônio global em atributos 
         'static', eliminamos loops de soma desnecessários e 
         garantimos que o banco de dados e a memória estejam 
         sempre em sincronia O(1).

    3. PROTEÇÃO CONTRA IMPRECISÃO (ELITE RULE):
       - A migração para 'long long centavos' é o que separa um 
         estagiário de um Engenheiro de Elite. Em sistemas 
         industriais, erros de 0,01 centavos acumulados podem gerar 
         milhões em prejuízo após anos de operação.

    4. GESTÃO DE MEMÓRIA RESILIENTE:
       - O uso de ponteiros com limpeza manual rigorosa (delete + 
         nullptr) prepara o desenvolvedor para entender sistemas de 
         baixo nível antes de migrar para a segurança automática 
         do Rust ou Smart Pointers.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Code Refactoring: Patterns and Practices.
    - Unit Testing: Como automatizar o teste desta classe.
    - Aritmética de Ponto Fixo vs Ponto Flutuante.
    ===============================================================
*/

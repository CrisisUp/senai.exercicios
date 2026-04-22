/**
 * @file atividade-extra48-estoque-evolutivo.cpp
 * @brief G-STOCK: Evolução Industrial da Atividade 01 para Elite C++.
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Integra Smart Pointers (unique_ptr), Testes Unitários e Integridade Financeira.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 * 
 * @section MemoryMap Mapeamento de Memória (RAII Suppli Chain Layout)
 * - Objeto Estoque: Alocado na STACK da main.
 * - std::vector<unique_ptr<Produto>>: Descritor na STACK, lista de Smart Pointers na HEAP.
 * - Instâncias Produto: Alocadas na HEAP via make_unique.
 * - Gestão RAII: O ciclo de vida da memória é atado ao escopo do vector. 
 *   Remover um item do vector limpa a RAM instantaneamente sem 'delete'.
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <memory>
#include <algorithm>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE (ANSI ELITE) ---

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
        cout << "      G-STOCK: GESTÃO DE SUPRIMENTOS v3.0      " << endl;
        cout << "       (Elite Engineering Refactored)          " << endl;
        cout << "===============================================" << UI::RESET << endl;
    }
}

// --- 2. MODELO DE DOMÍNIO: CLASSE PRODUTO (GUARDIÃO FINANCEIRO) ---

class Produto {
private:
    string nome;
    int qtdAtual;
    int qtdMinima;
    long long precoCentavos; // Integridade Bancária: Centavos Inteiros

public:
    /**
     * @brief Construtor de Elite com Inicialização por Lista.
     */
    Produto(const string& n, int a, int m, double p) 
        : nome(n), qtdAtual(a), qtdMinima(m), 
          precoCentavos(static_cast<long long>(p * 100)) {}

    // Lógica de Negócio Encapsulada
    const string& getNome() const { return nome; }
    bool precisaRepor() const { return qtdAtual < qtdMinima; }
    int getFalta() const { return (precisaRepor()) ? (qtdMinima - qtdAtual) : 0; }
    
    long long getCustoReposicaoCentavos() const { 
        return getFalta() * precoCentavos; 
    }

    double getPrecoReal() const { return static_cast<double>(precoCentavos) / 100.0; }

    /**
     * @brief Renderiza linha de status com feedback de criticidade.
     */
    void exibirStatus() const {
        cout << UI::NEGRITO << left << setw(18) << nome << UI::RESET;
        cout << " | Stock: " << setw(4) << qtdAtual << " / " << setw(4) << qtdMinima;
        
        if (precisaRepor()) {
            double custoReal = static_cast<double>(getCustoReposicaoCentavos()) / 100.0;
            cout << UI::VERMELHO << " | [BAIXO] " << UI::RESET 
                 << UI::AMARELO << "Falta: " << setw(3) << getFalta() 
                 << " | Invest: R$ " << fixed << setprecision(2) << custoReal << UI::RESET << endl;
        } else {
            cout << UI::VERDE << " | [OK] " << UI::RESET << "Estoque Nominal" << endl;
        }
    }
};

// --- 3. SUÍTE DE DIAGNÓSTICO (ZERO TOLERANCE QA) ---

class DiagnosticSuite {
public:
    static void executar() {
        cout << UI::AMARELO << UI::NEGRITO << ">>> INICIANDO AUTO-DIAGNÓSTICO DE LÓGICA..." << UI::RESET << endl;
        int erros = 0;

        // Teste 1: Cálculo de Reposição Crítica
        Produto t1("Chipset", 5, 20, 10.00); // Falta 15, Custo 150.00
        if (t1.getFalta() != 15 || t1.getCustoReposicaoCentavos() != 15000) {
            cout << UI::VERMELHO << " [FALHA]: Cálculo de reposição incoerente em T1." << UI::RESET << endl;
            erros++;
        }

        // Teste 2: Limite de Segurança
        Produto t2("Sensor", 10, 10, 5.00); 
        if (t2.precisaRepor()) {
            cout << UI::VERMELHO << " [FALHA]: Produto no limite (10/10) disparou alerta falso." << UI::RESET << endl;
            erros++;
        }

        if (erros == 0) {
            cout << UI::VERDE << " [PASSOU]: Todas as invariantes de negócio validadas." << UI::RESET << endl;
        } else {
            cout << UI::VERMELHO << UI::NEGRITO << " [CRÍTICO]: MOTOR DE LÓGICA CORROMPIDO. ABORTANDO." << UI::RESET << endl;
            exit(1); // Engenharia de Elite: Não rodar com erros de lógica
        }
    }
};

// --- 4. EXECUÇÃO DO SISTEMA DE SUPRIMENTOS ---

int main()
{
    UI::limparTela();
    UI::cabecalho();

    // Validação Mandatória (Cientista do Caos prevention)
    DiagnosticSuite::executar();

    // Coleção Segura: std::unique_ptr garante que nenhum produto vaze da RAM
    vector<unique_ptr<Produto>> armazem;

    // População do Estoque (Simulando persistência)
    armazem.push_back(make_unique<Produto>("Monitor 4K", 12, 15, 2450.75));
    armazem.push_back(make_unique<Produto>("Servidor Rack", 2, 5, 18200.00));
    armazem.push_back(make_unique<Produto>("Nobreak Ind", 45, 20, 850.30));
    armazem.push_back(make_unique<Produto>("Cabos Cat6", 150, 50, 4.50));

    cout << "\n" << UI::BRANCO << left << setw(18) << "PRODUTO" << " | MÉTRICAS DE ESTOQUE | STATUS DE REPOSIÇÃO" << UI::RESET << endl;
    cout << string(70, '-') << endl;

    long long investimentoTotalCentavos = 0;

    // Iteração Eficiente (Fantasma do CPU)
    for (const auto& item : armazem) {
        if (item) {
            item->exibirStatus();
            investimentoTotalCentavos += item->getCustoReposicaoCentavos();
        }
    }

    cout << string(70, '-') << endl;
    double totalReal = static_cast<double>(investimentoTotalCentavos) / 100.0;
    cout << UI::CIANO << UI::NEGRITO << "CAPEX NECESSÁRIO PARA REPOSIÇÃO: R$ " << fixed << setprecision(2) << totalReal << UI::RESET << endl;
    cout << UI::CIANO << "======================================================================" << UI::RESET << endl;

    cout << UI::VERDE << "\nSessão de suprimentos encerrada. RAII limpando HEAP..." << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: REFATORAÇÃO EVOLUTIVA (ELITE)
    ===============================================================

    1. O FIM DO GERENCIAMENTO MANUAL:
       - Substituir 'new/delete' por 'std::unique_ptr' é o maior 
         salto de produtividade no C++. O código torna-se "Safe 
         by Design", aproximando-se da segurança do Rust.

    2. INTEGRALIDADE BANCÁRIA (ELITE RULE):
       - Refatoramos os preços para 'long long' centavos. Isso 
         elimina o "Drifting de Ponto Flutuante" (0.1 + 0.2 != 0.3), 
         essencial para auditorias em armazéns de alto valor.

    3. UNIT TESTING COMO GATEKEEPER:
       - Um sistema industrial nunca deve abrir para o usuário se a 
         lógica interna falhar. O SuiteDeTestes garante que o 
         "Coração" do software esteja batendo corretamente no boot.

    4. ENCAPSULAMENTO DE MÉTRICAS:
       - A classe Produto não apenas guarda dados; ela "conhece" a 
         regra de reposição. Isso remove a lógica da main() e a 
         distribui entre os objetos, facilitando a manutenção futura.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Smart Pointer 'std::shared_ptr': Quando vários donos dividem um recurso.
    - Custom Deleters: Fechar arquivos ou sockets automaticamente.
    - Test-Driven Development (TDD): Escrever o teste ANTES do código.
    ===============================================================
*/

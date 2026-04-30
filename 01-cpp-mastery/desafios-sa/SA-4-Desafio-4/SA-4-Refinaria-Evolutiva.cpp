/**
 * @file SA-4-Refinaria-Evolutiva.cpp
 * @brief Simulação do Desafio Integrador SA-4: Refatoração Genérica e Segura.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <vector>
#include <memory>
#include "TanqueEvolutivo.h" // Nossa interface genérica e inteligente

using namespace std;
using namespace EngenhariaElite;

/**
 * @brief Função que simula o monitoramento central de uma fazenda de tanques.
 * @tparam T Tipo de dado do tanque sendo monitorado.
 */
template <typename T>
void monitorarTanques(const vector<shared_ptr<TanqueEvolutivo<T>>>& lista) {
    cout << "\n\033[33m--- MONITORAMENTO DE OPERAÇÃO EM TEMPO REAL ---\033[0m" << endl;
    for (const auto& t : lista) {
        cout << *t << endl;
    }
}

int main() {
    cout << "\033[35m===============================================\033[0m" << endl;
    cout << "     CENTRAL DE REFINARIA EVOLUTIVA (SA-4)     " << endl;
    cout << "\033[35m===============================================\033[0m" << endl;

    // 1. FAZENDA DE LÍQUIDOS (Tanques que usam double)
    // Usamos shared_ptr para permitir que Logística e Faturamento compartilhem o mesmo tanque.
    vector<shared_ptr<TanqueEvolutivo<double>>> fazendaLiquidos;
    
    auto t1 = make_shared<TanqueEvolutivo<double>>("D-900", 100000.0, "litros");
    auto t2 = make_shared<TanqueEvolutivo<double>>("D-901", 50000.0, "litros");

    t1->carregar(95000.0); // Nível crítico (vermelho)
    t2->carregar(25000.0);

    fazendaLiquidos.push_back(t1);
    fazendaLiquidos.push_back(t2);

    monitorarTanques(fazendaLiquidos);

    // 2. FAZENDA DE GASES (Tanques que usam int para contagem de cilindros)
    // Demonstra o reuso do mesmo código (TEMPLATE) para outro tipo de dado.
    vector<shared_ptr<TanqueEvolutivo<int>>> fazendaGases;

    auto g1 = make_shared<TanqueEvolutivo<int>>("GAS-01", 500, "unid");
    g1->carregar(150);

    fazendaGases.push_back(g1);

    monitorarTanques(fazendaGases);

    // 3. SEGURANÇA E RAII:
    // Observe no terminal que ao chegar no final do main(), todos os 
    // tanques serão destruídos e a memória liberada AUTOMATICAMENTE 
    // pelos Smart Pointers. Não usamos 'delete' em nenhum lugar!

    cout << "\n\033[32m[ENCERRAMENTO]:\033[0m Desativando central de controle..." << endl;
    cout << "\033[35m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: DESAFIO INTEGRADOR SA-4 (O MONUMENTO)
    ===============================================================

    1. REFATORAÇÃO EVOLUTIVA:
       - O aluno não apenas fez uma tarefa nova, ele modernizou 
         um sistema existente. Isso é o dia a dia da engenharia.

    2. TEMPLATES (Logística Flexível):
       - A classe TanqueEvolutivo lida com double (volume) ou 
         int (unidades) com o mesmo código fonte. Isso reduz 
         erros e duplicação.

    3. SMART POINTERS (Segurança de Hardware):
       - Eliminamos o risco de Memory Leak e Dangling Pointers. 
       - O uso de shared_ptr demonstra como vários departamentos 
         podem monitorar o mesmo recurso físico simultaneamente.

    4. VANTAGEM PEDAGÓGICA FINAL:
       - Este projeto fecha o Nível 31 provando que o aluno domina
         a complexidade do C++ Moderno e sabe aplicá-la em 
         cenários de missão crítica.
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Factory Pattern com Templates.
    - Design patterns de monitoramento (Observer).
    - Otimização de compilação em projetos de grande escala.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

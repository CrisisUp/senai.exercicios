/**
 * @file atividade-extra54-imoveis.cpp
 * @brief Programa principal para testar o Polimorfismo e a Sobrescrita.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include "Imovel.h" // Nossa interface imobiliária modular

using namespace std;
using namespace Imobiliaria;

int main() {
    // 1. Criando instâncias de diferentes tipos de imóveis.
    Apartamento ap1("Av. Paulista, 1000", 2500.0, 800.0);
    Casa casa1("Rua das Flores, 50", 3500.0, 300.0);

    cout << "\033[36m===============================================\033[0m" << endl;
    cout << "     SISTEMA DE GESTÃO IMOBILIÁRIA (POLIMORFISMO) " << endl;
    cout << "\033[36m===============================================\033[0m" << endl;

    cout << fixed << setprecision(2);

    // 2. Chamada direta de métodos sobrescritos.
    cout << "APARTAMENTO:\n  End: " << ap1.getEndereco() 
         << "\n  Total Mensal: R$ " << ap1.calcularTotal() << endl;

    cout << "\nCASA:\n  End: " << casa1.getEndereco() 
         << "\n  Total Mensal: R$ " << casa1.calcularTotal() << endl;

    // 3. Demonstrando o "Poder do Polimorfismo" (Uso de Ponteiros da Classe Base).
    // Note como tratamos tipos diferentes através de uma interface comum.
    cout << "\n\033[33m[PROCESSAMENTO POLIMÓRFICO EM LOTE]:\033[0m" << endl;
    
    vector<Imovel*> listaImoveis;
    listaImoveis.push_back(&ap1);
    listaImoveis.push_back(&casa1);

    for (Imovel* imovel : listaImoveis) {
        // Aqui o sistema decide EM TEMPO DE EXECUÇÃO qual calcularTotal() chamar.
        // Se for um Apartamento, chama a lógica do Apartamento.
        // Se for uma Casa, chama a lógica da Casa.
        cout << "- Imóvel em: " << imovel->getEndereco() 
             << " | VALOR TOTAL: R$ " << imovel->calcularTotal() << endl;
    }

    cout << "\033[36m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: SOBRESCRITA E POLIMORFISMO
    ===============================================================

    1. MÉTODOS VIRTUAIS (virtual):
       - Quando declaramos um método como 'virtual', o C++ cria 
         uma tabela interna (vtable) para decidir qual versão do 
         método executar dependendo do tipo REAL do objeto, e 
         não do tipo do ponteiro.

    2. SOBRESCRITA (override):
       - O método na classe filha DEVE ter a mesma assinatura do 
         método no pai. A palavra 'override' ajuda o compilador 
         a validar isso, evitando que criemos uma nova função 
         por acidente (ex: errando uma letra ou tipo).

    3. DESTRUTOR VIRTUAL:
       - SEMPRE use destrutores virtuais em classes bases. Se não 
         usar, ao deletar um objeto 'Filho' através de um ponteiro 
         'Pai', o destrutor do Filho NUNCA será chamado, causando 
         vazamentos de memória (Memory Leaks).

    4. VANTAGEM DIDÁTICA:
       - Ensinamos que o sistema pode ser extensível. Se criarmos um
         novo tipo 'GalpaoIndustrial', basta herdar de 'Imovel' e 
         sobrescrever 'calcularTotal'. O restante do sistema não 
         precisa de nenhuma alteração para suportá-lo.
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Classes Abstratas e Métodos Virtuais Puros.
    - Ponteiros Inteligentes (unique_ptr/shared_ptr).
    - Ligação Tardia (Late Binding).
    ===============================================================
*/

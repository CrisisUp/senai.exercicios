/**
 * @file atividade-extra55-pagamentos.cpp
 * @brief Programa principal (Gateway) para testar Classes Abstratas.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <vector>
#include <memory> // Requisito moderno: Ponteiros inteligentes (unique_ptr)
#include "Pagamento.h" // Nossa interface de pagamentos modular

using namespace std;
using namespace Financeiro;

int main() {
    cout << "\033[35m===============================================\033[0m" << endl;
    cout << "     GATEWAY DE PAGAMENTOS (CLASSES ABSTRATAS)  " << endl;
    cout << "\033[35m===============================================\033[0m" << endl;

    // 1. Criando uma lista de pagamentos usando a classe abstrata como ponteiro.
    // Usamos unique_ptr para demonstrar boas práticas de gerenciamento de memória.
    vector<unique_ptr<MetodoPagamento>> gateway;

    // Adicionando diferentes formas de pagamento ao nosso sistema
    gateway.push_back(make_unique<CartaoCredito>("1234-5678-9012-3456"));
    gateway.push_back(make_unique<Pix>("financeiro@senai.com.br"));

    // 2. Processando os pagamentos polimorficamente.
    // O sistema não sabe EXATAMENTE qual pagamento é, ele apenas sabe
    // que todo MetodoPagamento TEM O MÉTODO 'processar()'.
    double valorCompra = 1500.00;

    for (const auto& metodo : gateway) {
        cout << "\n\033[33m[PROCESSANDO TRANSACAO]:\033[0m" << endl;
        metodo->processar(valorCompra);
    }

    // 3. Demonstrando a restrição da Classe Abstrata:
    // Se você tentar descomentar a linha abaixo, o código NÃO COMPILARÁ!
    // MetodoPagamento pagamentoGenerico; // Erro: Cannot instantiate abstract class

    cout << "\033[35m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: CLASSES ABSTRATAS E INTERFACES
    ===============================================================

    1. CLASSE ABSTRATA:
       - É uma classe que serve como modelo para outras, mas não 
         pode ter objetos criados diretamente dela.
       - No C++, ela é definida por conter pelo menos um "Método 
         Virtual Puro" (virtual ... = 0;).

    2. INTERFACE (CONTRATO):
       - Uma classe abstrata atua como um contrato. Ela garante 
         que QUALQUER classe filha que queira ser um 'MetodoPagamento'
         DEVE implementar a lógica de 'processar()'.

    3. POLIMORFISMO DE INTERFACE:
       - Permite que o código principal (o Gateway) aceite novas 
         formas de pagamento (como Boleto ou Cripto) sem precisar 
         ser alterado, bastando que o novo objeto siga o contrato.

    4. VANTAGEM DIDÁTICA:
       - Introduz o conceito de "Design Patterns" e Arquitetura de 
         Software Limpa, onde se programa para "Interfaces" e não 
         para "Implementações específicas".
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Ponteiros Inteligentes (std::unique_ptr).
    - Princípio da Inversão de Dependência (SOLID).
    - Métodos Virtuais Puros em Cadeia.
    ===============================================================
*/

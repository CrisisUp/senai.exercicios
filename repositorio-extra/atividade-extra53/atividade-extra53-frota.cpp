/**
 * @file atividade-extra53-frota.cpp
 * @brief Programa para testar a Herança em um sistema de frota logística.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <iomanip>
#include "Frota.h" // Nossa nova interface de logística

using namespace std;
using namespace Logistica;

int main() {
    // 1. Criando um Caminhão (Classe Derivada)
    // Passamos placa, marca (Base) e capacidade (Derivada)
    Caminhao caminhao1("ABC-1234", "VOLVO FH", 30.5);

    cout << "\033[34m===============================================\033[0m" << endl;
    cout << "     SISTEMA DE GESTÃO DE FROTA (HERANÇA)      " << endl;
    cout << "\033[34m===============================================\033[0m" << endl;

    // 2. Testando comportamento herdado (Métodos da Base)
    cout << "\nIniciando viagem de entrega..." << endl;
    caminhao1.viajar(450.0); // O Caminhão usa o método 'viajar' que veio do Veiculo!

    // 3. Testando comportamento especializado (Métodos da Derivada)
    cout << "Tentando carregar 20 toneladas..." << endl;
    if (caminhao1.carregar(20.0)) {
        cout << "\033[32m[SUCESSO]:\033[0m Carga autorizada." << endl;
    }

    cout << "\nTentando carregar mais 15 toneladas..." << endl;
    if (!caminhao1.carregar(15.0)) {
        cout << "\033[31m[BLOQUEIO]:\033[0m Excesso de peso! Capacidade máxima excedida." << endl;
    }

    // 4. Exibindo Relatório Final (Combinação de dados Base + Derivada)
    cout << "\n" << caminhao1.getRelatorioCaminhao() << endl;

    cout << "\033[34m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: HERANÇA SIMPLES ("É-UM")
    ===============================================================

    1. O QUE É HERANÇA:
       - É a capacidade de uma classe (Derivada) adquirir atributos e 
         métodos de outra classe (Base).
       - Exemplo: Um Caminhão É UM Veículo.

    2. MODIFICADOR 'protected':
       - Diferente do 'private', o 'protected' permite que a Classe 
         Filha (Caminhao) acesse os membros do Pai (Veiculo) 
         diretamente, mantendo o encapsulamento contra o mundo externo.

    3. LISTA DE INICIALIZAÇÃO DO CONSTRUTOR:
       - A classe filha DEVE chamar o construtor da classe base 
         na sua lista de inicialização: `Caminhao(...) : Veiculo(...)`.

    4. VANTAGEM DIDÁTICA:
       - O aluno aprende a criar hierarquias de conhecimento. 
       - O código fica muito mais limpo: toda a lógica de 
         movimentação (viajar) só existe em um lugar (Veiculo).
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Polimorfismo (Próxima Etapa).
    - Sobrescrita de Métodos (Override).
    - Herança Múltipla (Caminhos complexos).
    ===============================================================
*/

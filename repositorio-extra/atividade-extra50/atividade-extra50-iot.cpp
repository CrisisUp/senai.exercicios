/**
 * @file atividade-extra50-iot.cpp
 * @brief Programa principal (Interface) para monitoramento IoT industrial.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <vector>
#include "Monitoramento.h" // Importando nossa interface IoT modular

using namespace std;

/**
 * Ao usar 'using namespace IoT;', podemos chamar SensorPressao diretamente.
 */
using namespace IoT;

int main() {
    // Criando um sensor IoT identificado como Pressão da Caldeira Principal
    SensorPressao sensor1("CALDEIRA_01");
    double novaLeitura;

    cout << "\033[36m===============================================\033[0m" << endl;
    cout << "     SISTEMA DE MONITORAMENTO IoT (NÍVEL 11+)  " << endl;
    cout << "\033[36m===============================================\033[0m" << endl;
    cout << "ID SENSOR: " << sensor1.getId() << endl;

    cout << "\nDigite a leitura atual de pressão (psi): ";
    cin >> novaLeitura;

    // Chamada modular: A validação interna protege o sistema.
    if (sensor1.registrarLeitura(novaLeitura)) {
        cout << "\n\033[32m[SUCESSO]:\033[0m Leitura registrada: " 
             << sensor1.getValor() << " psi." << endl;
    } else {
        cout << "\n\033[31m[ALERTA]:\033[0m Valor de " << novaLeitura 
             << " psi FORA DA MARGEM DE SEGURANÇA!" << endl;
        cout << "Sistema de emergência acionado." << endl;
    }

    cout << "\033[36m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: NAMESPACES E ENCAPSULAMENTO AVANÇADO
    ===============================================================

    1. NAMESPACES (namespace IoT):
       - Servem para agrupar funcionalidades lógicas em "pastas".
       - Permite que você tenha uma classe 'SensorPressao' em IoT 
         e outra diferente em 'Financeiro' sem que o compilador 
         se confunda.
       - Acesso: `IoT::SensorPressao` ou `using namespace IoT;`.

    2. MÉTODOS PRIVADOS EM MÓDULOS:
       - No arquivo Monitoramento.h, 'valorEhSeguro' é privado. 
       - O usuário do módulo (main) não consegue chamá-lo diretamente.
       - Isso garante que a regra de segurança da fábrica nunca 
         seja ignorada ou burlada por outros desenvolvedores.

    3. VANTAGEM DIDÁTICA:
       - O sistema cresce de forma segura e organizada, seguindo os 
         padrões de Engenharia de Software de grandes empresas.
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Escopo de Variáveis em C++.
    - Princípio da Responsabilidade Única (SOLID).
    - Interfaces vs Implementações.
    ===============================================================
*/

/**
 * @file atividade-extra51-motor.cpp
 * @brief Interface do sistema de controle de motores (Composição de Elite).
 * 
 * Versão Refatorada: Padrão de Engenharia de Elite (Silicon Valley Standard).
 * Demonstra a sinergia entre módulos de hardware virtual (IoT Sensor + Motor).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 22/04/2026
 */

#include <iostream>
#include <iomanip>
#include "Motor.h" 

using namespace std;
using namespace IoT;

// --- 1. NAMESPACE DE INTERFACE (ANSI) ---

#include <string>

namespace UI {
    const std::string RESET    = "\033[0m";
    const std::string NEGRITO  = "\033[1m";
    const std::string VERDE    = "\033[32m";
    const std::string VERMELHO = "\033[31m";
    const std::string AZUL     = "\033[34m";
    const std::string CIANO    = "\033[36m";
    const std::string AMARELO  = "\033[33m";
    inline void limparTela() { cout << "\033[2J\033[1;1H"; }
}

// --- 2. EXECUÇÃO DO PAINEL DE CONTROLE ---

int main() {
    UI::limparTela();
    
    // Instanciação na STACK com Composição Interna
    MotorIndustrial turbina("HYPER-REACTOR-X1", "SNR-BETA-44");
    double leituraPSI;

    cout << UI::CIANO << UI::NEGRITO << "===============================================" << endl;
    cout << "      G-SYSTEM: CONTROLE DE MOTORES v2.0       " << endl;
    cout << "       (Elite Class Composition Standard)       " << endl;
    cout << UI::CIANO << UI::NEGRITO << "===============================================" << UI::RESET << endl;

    cout << UI::RESET << "Status de Boot: " << UI::RESET << turbina.statusMotor() << endl;

    cout << "\nIniciando ignição do sistema..." << endl;
    turbina.ligar();

    // Loop de Operação Baseado em Telemetria
    while (turbina.estaLigado()) {
        cout << "\n" << UI::RESET << "Monitoramento Ativo. Informe Pressão (psi): " << UI::RESET;
        if (!(cin >> leituraPSI)) break;

        // O Motor delega a inteligência para o sensor interno
        if (turbina.atualizarOperacao(leituraPSI)) {
            cout << UI::VERDE << UI::NEGRITO << " [ESTÁVEL]: " << UI::RESET 
                 << "Parâmetros físicos aceitos." << endl;
            cout << UI::RESET << " >> " << UI::RESET << turbina.statusMotor() << endl;
        } else {
            cout << "\n" << UI::VERMELHO << UI::NEGRITO << " [CRÍTICO]: ANOMALIA TÉRMICA/PRESSÃO DETECTADA!" << UI::RESET << endl;
            cout << UI::VERMELHO << "Protocolo RAII de shut-down acionado pelo core do motor." << UI::RESET << endl;
            cout << UI::RESET << " >> " << UI::RESET << turbina.statusMotor() << endl;
            break; 
        }
    }

    cout << UI::CIANO << UI::NEGRITO << "\n===============================================" << UI::RESET << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: COMPOSIÇÃO E DELEGAÇÃO (ELITE)
    ===============================================================

    1. COMPOSIÇÃO ("HAS-A"):
       - Em vez de herdar comportamentos (o que o torna rígido), o 
         Motor Industrial CONTÉM um sensor. Isso permite que 
         troquemos o tipo de sensor no futuro sem alterar a 
         hierarquia de classes do motor.

    2. DELEGAÇÃO DE RESPONSABILIDADE:
       - O Motor não sabe que 101 psi é perigoso. Quem sabe é o 
         SensorPressao. Ao chamar 'sensor.registrarLeitura()', o 
         motor delega a decisão de segurança, mantendo seu código 
         limpo e focado apenas em 'ligar/desligar'.

    3. LISTA DE INICIALIZAÇÃO (CONSTRUTOR):
       - Como o sensor não tem um construtor vazio, o motor é 
         OBRIGADO a inicializá-lo na Member Initializer List. Isso 
         garante que o motor nunca nasça com um sensor corrompido 
         ou "lixo" na memória.

    4. PERFORMANCE E CACHE LOCALITY:
       - Como o sensor é um atributo direto (não um ponteiro), ele 
         reside fisicamente dentro do bloco de memória do motor. 
         Isso significa que quando a CPU carrega o motor no cache, 
         o sensor vem junto, acelerando as leituras de segurança.

    ===============================================================
    ASSUNTOS CORRELATOS:
    - Dependency Injection: Passar o sensor pronto para o motor.
    - Estratégia Pattern: Trocar o sensor em tempo de execução.
    - Law of Demeter: O motor não deve expor as entranhas do sensor.
    ===============================================================
*/
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

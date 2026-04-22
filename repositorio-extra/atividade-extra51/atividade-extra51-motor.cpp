/**
 * @file atividade-extra51-motor.cpp
 * @brief Interface para o sistema de motores industriais (Composição).
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 20/04/2026
 */

#include <iostream>
#include <iomanip>
#include "Motor.h" // Nossa nova interface modular
#include "../atividade-extra50/Monitoramento.h" // Requerida para a compilação completa

using namespace std;
using namespace IoT;

int main() {
    // Criando um Motor Industrial "Super-V8" que já vem com seu próprio Sensor.
    MotorIndustrial motorV8("Turbine-X100", "S-PRESS-001");
    double leitura;

    cout << "\033[35m===============================================\033[0m" << endl;
    cout << "     SIMULADOR DE MOTOR INDUSTRIAL (COMPOSIÇÃO) " << endl;
    cout << "\033[35m===============================================\033[0m" << endl;

    cout << "Status inicial: " << motorV8.statusMotor() << endl;

    cout << "\nLigando o sistema..." << endl;
    motorV8.ligar();

    while (motorV8.estaLigado()) {
        cout << "\nMonitorando... Digite a pressão do motor (0 a 120 psi): ";
        cin >> leitura;

        // O Motor usa seu sensor interno para decidir se continua rodando.
        if (motorV8.atualizarOperacao(leitura)) {
            cout << "\033[32m[OK]:\033[0m Operação estável." << endl;
            cout << motorV8.statusMotor() << endl;
        } else {
            cout << "\n\033[31m[PERIGO]:\033[0m Sensor detectou anomalia!" << endl;
            cout << "O motor foi desligado automaticamente para evitar explosão." << endl;
            cout << motorV8.statusMotor() << endl;
            break; // Sair do loop de operação
        }
    }

    cout << "\033[35m===============================================\033[0m" << endl;

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: COMPOSIÇÃO DE CLASSES ("Has-A")
    ===============================================================

    1. O QUE É COMPOSIÇÃO:
       - É o ato de colocar um objeto de uma classe dentro de outra 
         classe como um atributo.
       - Exemplo: Motor "TEM UM" Sensor.

    2. VANTAGEM DA MODULARIZAÇÃO:
       - Não precisamos reescrever o código do Sensor (Monitoramento.cpp).
       - O CMake e o Compilador agora "juntam" o Motor.cpp e o 
         Monitoramento.cpp na hora de gerar o executável.

    3. LISTA DE INICIALIZAÇÃO:
       - Note como usamos `: sensorPressao(idSensor)` no construtor.
       - Isso é necessário quando um objeto composto não possui um 
         construtor padrão (sem parâmetros).

    4. DELEGAÇÃO:
       - O Motor não sabe validar pressão. Ele "delega" essa tarefa 
         para o Sensor. Isso mantém as responsabilidades separadas.
    ===============================================================
    ASSUNTOS CORRELATOS:
    - Agregação vs Composição.
    - Ciclo de Vida de Objetos Compostos.
    - Acoplamento Fraco (Loose Coupling).
    ===============================================================
*/

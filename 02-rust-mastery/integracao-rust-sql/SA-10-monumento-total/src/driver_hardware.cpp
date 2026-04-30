#include <iostream>

/**
 * @file driver_hardware.cpp
 * @brief Driver de baixo nível simulado em C++.
 */

extern "C"
{
    /**
     * Simula a ignição dos motores de alta performance do drone.
     * @return 1 se os motores iniciaram sem vibração, 0 se houve falha mecânica.
     */
    int iniciar_motores_cpp(int potencia_inicial)
    {
        std::cout << "[MUNDO C++]: Iniciando rotores com potência " << potencia_inicial << "%..." << std::endl;

        if (potencia_inicial > 90)
        {
            std::cout << "[MUNDO C++]: ERRO! Pico de corrente detectado." << std::endl;
            return 0;
        }

        std::cout << "[MUNDO C++]: Rotores estáveis. Pronto para decolagem." << std::endl;
        return 1;
    }
}
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */
